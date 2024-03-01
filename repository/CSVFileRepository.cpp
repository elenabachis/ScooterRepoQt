#include "CSVFileRepo.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>


CSVFileRepository::CSVFileRepository(const QString &filename) {
    this->file = filename;
    QFile fileToWrite(this->file);
    if(!fileToWrite.open(QIODevice::ReadWrite)){
        qCritical() << "Could not open file!";
        qCritical() << fileToWrite.errorString();
        return;
    }
    QTextStream stream(&fileToWrite);
    QString line;
    line = stream.readLine();
    if (line.size() == 0) {
        stream << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << Qt::endl;
    }
    fileToWrite.close();
}

CSVFileRepository::~CSVFileRepository() = default;

bool CSVFileRepository::create(Scooter new_entity) {
    QFile fileToWrite(this->file);
    if(!fileToWrite.open(QIODevice::Append)){
        qCritical() << "Failed to open file" << Qt::endl;
        qCritical() << fileToWrite.errorString();
        return false;
    }
    QTextStream stream(&fileToWrite);
    stream << QString::fromStdString(new_entity.getId()) << ',' << QString::fromStdString(new_entity.getModel()) << ',';
    stream << new_entity.getRegistration().year << '-' << new_entity.getRegistration().month << '-'
      << new_entity.getRegistration().day << ',';
    stream << new_entity.get_Kilometer_Count() << ',' << QString::fromStdString(new_entity.get_Last_Address()) << ',';
    //    Parked, Reserved, In_Use, In_Service, Out_of_Order
    switch (new_entity.get_actual_state()) {
    case Parked: {
        stream << "parked" << Qt::endl;
        break;
    }
    case Reserved:
        stream << "reserved" << Qt::endl;
        break;
    case In_Use:
        stream << "in use" << Qt::endl;
        break;
    case In_Service:
        stream << "in service" << Qt::endl;
        break;
    case Out_of_Order:
        stream << "out of order" << Qt::endl;
        break;
    }
    fileToWrite.close();
    return true;
}

void CSVFileRepository::read(vector<Scooter>& elements) {
    QFile fileToWrite(this->file);
    if(!fileToWrite.exists()){
        qCritical() << "File not found" << Qt::endl;
        qCritical() << fileToWrite.errorString();
        return;
    }
    if(!fileToWrite.open(QIODevice::ReadWrite)){
        qCritical() << "Failed to open file" << Qt::endl;
        qCritical() << fileToWrite.errorString();
        return;
    }
    QTextStream stream(&fileToWrite);
    stream.readLine();

    QString line;
    while (stream.readLineInto(&line)) {
        // Parse the line and create a new Scooter object
        Scooter scooter = parseLine(line);
        elements.push_back(scooter);
    }
    fileToWrite.close();
}

bool CSVFileRepository::update(Scooter entity) {
    vector<Scooter> elements;
    read(elements);
    auto it = find_if(elements.begin(), elements.end(), [&](const Scooter &scooter) {
        return entity.getId() == scooter.getId();
    });
    if (it != elements.end()) {
        (*it).set_Last_Address(entity.get_Last_Address());
        (*it).set_State(entity.get_actual_state());
        (*it).set_kilometer_count(entity.get_Kilometer_Count());
        QFile fileToWrite(this->file);
        if(!fileToWrite.open(QIODevice::Truncate)){
            qCritical() << "Failed to open file" << Qt::endl;
            qCritical() << fileToWrite.errorString();
            return false;
        }
        QTextStream stream(&fileToWrite);
        stream << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << Qt::endl;
        fileToWrite.close();

        for (auto element : elements){
            CSVFileRepository::create(element);
        }
        return true;
    }
    return false;
}

bool CSVFileRepository::remove(Scooter entity) {
    vector<Scooter> elements;
    read(elements);
    auto it = find_if(elements.begin(), elements.end(), [&](const Scooter &scooter) {
        return scooter.getId() == entity.getId();
    });
    if (it != elements.end()) {
        elements.erase(it);
        QFile fileToWrite(this->file);
        if(!fileToWrite.open(QIODevice::Truncate)){
            qCritical() << "Failed to open file" << Qt::endl;
            qCritical() << fileToWrite.errorString();
            return false;
        }
        QTextStream stream(&fileToWrite);
        stream << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << Qt::endl;
        fileToWrite.close();

        for (auto element : elements){
            CSVFileRepository::create(element);
        }
        return true;
    }
    return false;
}

domain::Scooter parseLine(const QString &line) {
    QStringList list = line.split(u',');
    // Extract the necessary data from the tokens and create a Scooter object
    // Modify the code below according to your CSV file structure and Scooter class implementation

    std::string id = list[0].toStdString();
    std::string model = list[1].toStdString();
    QStringList registrationList=list[2].split(u'-');

    date registration_date;
    registration_date.year = registrationList[0].toInt();
    registration_date.month = registrationList[1].toInt();
    registration_date.day = registrationList[2].toInt();
    int kilometer = list[3].toInt();
    std::string location = list[4].toStdString();
    std::string status = list[5].toStdString();
    if (status == "parked") {
        return Scooter(id, model, registration_date, kilometer, location, State::Parked);
    }
    if (status == "reserved") {
        return Scooter(id, model, registration_date, kilometer, location, State::Reserved);
    }
    if (status == "in use") {
        return Scooter(id, model, registration_date, kilometer, location, State::In_Use);
    }
    if (status == "in service") {
        return Scooter(id, model, registration_date, kilometer, location, State::In_Service);
    }
    if (status == "out of order") {
        return Scooter(id, model, registration_date, kilometer, location, State::Out_of_Order);
    }
}

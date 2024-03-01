#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    Parked, Reserved, In_Use, In_Service, Out_of_Order

    ui->stateComboBox->addItem("Parked");

    ui->stateComboBox->addItem("Reserved");

    ui->stateComboBox->addItem("In_Use");

    ui->stateComboBox->addItem("In_Service");

    ui->stateComboBox->addItem("Out_of_Order");

    this->controller = new Controller();

    this->controller->add_Scooter("123","Honda",{2022,1,1},200,"Strada Ploiesti 20");

    this->controller->add_Scooter("124","Honda",{2023,1,1},100,"Strada Ploiesti 20");


    vector<Scooter> scooters;
    this->controller->get_all(scooters);

    model = new QStandardItemModel(scooters.size(),6,this);

    auto it=scooters.begin();

    for (int row = 0; row < scooters.size(); row++){
        for (int col = 0; col < 6;col++){
            QModelIndex index = model->index(row,col,QModelIndex());
            switch(col){
            case 0:{
                string str = (*it).getId();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 1:{
                string str = (*it).getModel();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 2:{
                int x = (*it).getRegistration().year;
                model->setData(index,x);
                break;
            }
            case 3:{
                int x = (*it).get_Kilometer_Count();
                model->setData(index,x);
                break;
            }
            case 4:{
                string str = (*it).get_Last_Address();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 5:{
                State str = (*it).get_actual_state();
                model->setData(index,str);
                break;
            }
            }
        }
        it++;
    }

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow(){
    delete model;
    delete controller;
    delete ui;
}




QString MainWindow::on_idEdit_editingFinished()
{
    if(ui->idEdit->text().size() != 3){
        QMessageBox::warning(this,"Error","The ID should only be 3 characters max.");
    }
    return ui->idEdit->text();
}


QString MainWindow::on_modelEdit_editingFinished()
{
    if(ui->modelEdit->text().size() == 0){
        QMessageBox::warning(this,"Error","Scooter model field empty. Please type a model for your scooter!");
    }
    return ui->modelEdit->text();
}



int MainWindow::on_yearEdit_editingFinished()
{
    if(ui->yearEdit->text().toInt() <= 0){
        QMessageBox::warning(this,"Error","Invalid value.");
    }
    return ui->yearEdit->text().toInt();
}


int MainWindow::on_monthEdit_editingFinished()
{
    if(ui->monthEdit->text().toInt() <=0 || ui->monthEdit->text().toInt() > 12){
        QMessageBox::warning(this,"Error","Invalid value.");
    }
    return ui->monthEdit->text().toInt();
}


int MainWindow::on_dayEdit_editingFinished()
{
    if(ui->dayEdit->text().toInt() <=0 || ui->monthEdit->text().toInt() > 31){
        QMessageBox::warning(this,"Error","Invalid value.");
    }
    return ui->dayEdit->text().toInt();
}


int MainWindow::on_kilometerEdit_editingFinished()
{
    if(ui->kilometerEdit->text().toInt() <=0){
        QMessageBox::warning(this,"Error","Invalid value.");
    }
    return ui->kilometerEdit->text().toInt();
}


QString MainWindow::on_addressEdit_editingFinished()
{
    if(ui->addressEdit->text().size() == 0){
        QMessageBox::warning(this,"Error","Address field empty. Please type an address for your scooter!");
    }
    return ui->addressEdit->text();
}



State MainWindow::on_stateComboBox_currentTextChanged(const QString &arg1)
{
    switch(ui->stateComboBox->currentIndex()){
    case 0:{
        return State::Parked;
        break;
    }
    case 1:{
        return State::Reserved;
        break;
    }
    case 2:{
        return State::In_Use;
        break;
    }
    case 3:{
        return State::In_Service;
        break;
    }
    case 4:{
        return State::Out_of_Order;
        break;
    }
}
}

State MainWindow::on_stateComboBox_textActivated(const QString &arg1){
   if(arg1 == "Parked"){
        return State::Parked;
    }
   if(arg1 == "Reserved"){
        return State::Reserved;
   }
   if(arg1 == "In_Use"){
        return State::In_Use;
   }
   if(arg1 == "In_Service"){
        return State::In_Service;
   }
   if(arg1 == "Out_of_Order"){
        return State::Out_of_Order;
   }
}


void MainWindow::on_Add_clicked()
{
   string id = on_idEdit_editingFinished().toStdString();
   string model = on_modelEdit_editingFinished().toStdString();
   date reg_date;
   reg_date.year = on_yearEdit_editingFinished();
   reg_date.month = on_monthEdit_editingFinished();
   reg_date.day = on_dayEdit_editingFinished();
   int km = on_kilometerEdit_editingFinished();
   string address = on_addressEdit_editingFinished().toStdString();
   State state = on_stateComboBox_textActivated(ui->stateComboBox->currentText());
   controller->add_Scooter(id,model,reg_date,km,address,state);
}


void MainWindow::on_actionOpen_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this, "Open the file");
   controller->set_CSV_repository(filename);
}


void MainWindow::on_showButton_clicked()
{
   delete model;

   vector<Scooter> scooters;

   controller->get_all(scooters);

   model = new QStandardItemModel(scooters.size(),6,this);

   auto it=scooters.begin();

   for (int row = 0; row < scooters.size(); row++){
        for (int col = 0; col < 6;col++){
            QModelIndex index = model->index(row,col,QModelIndex());
            switch(col){
            case 0:{
                string str = (*it).getId();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 1:{
                string str = (*it).getModel();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 2:{
                int x = (*it).getRegistration().year;
                model->setData(index,x);
                break;
            }
            case 3:{
                int x = (*it).get_Kilometer_Count();
                model->setData(index,x);
                break;
            }
            case 4:{
                string str = (*it).get_Last_Address();
                QString qstr = QString::fromStdString(str);
                model->setData(index,qstr);
                break;
            }
            case 5:{
                State str = (*it).get_actual_state();
                model->setData(index,str);
                break;
            }
            }
        }
        it++;
   }

   ui->tableView->setModel(model);
}


void MainWindow::on_filterButton_clicked()
{

}


void MainWindow::on_pushButton_3_clicked()
{
   string id = on_idEdit_editingFinished().toStdString();
   string model = on_modelEdit_editingFinished().toStdString();
   date reg_date;
   reg_date.year = on_yearEdit_editingFinished();
   reg_date.month = on_monthEdit_editingFinished();
   reg_date.day = on_dayEdit_editingFinished();
   int km = on_kilometerEdit_editingFinished();
   string address = on_addressEdit_editingFinished().toStdString();
   State state = on_stateComboBox_textActivated(ui->stateComboBox->currentText());
   Scooter scooter_to_update = Scooter(id,model,reg_date,km,address,state);
   controller->update(scooter_to_update);
}


void MainWindow::on_pushButton_2_clicked()
{
   string id = on_idEdit_editingFinished().toStdString();
   string model = on_modelEdit_editingFinished().toStdString();
   date reg_date;
   reg_date.year = on_yearEdit_editingFinished();
   reg_date.month = on_monthEdit_editingFinished();
   reg_date.day = on_dayEdit_editingFinished();
   int km = on_kilometerEdit_editingFinished();
   string address = on_addressEdit_editingFinished().toStdString();
   State state = on_stateComboBox_textActivated(ui->stateComboBox->currentText());
   Scooter scooter_to_delete = Scooter(id,model,reg_date,km,address,state);
   controller->delete_Scooter(scooter_to_delete);
}


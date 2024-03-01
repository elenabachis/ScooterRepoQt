#ifndef CSVFILEREPO_H
#define CSVFILEREPO_H
#include "Electroscooter.h"
#include <QtCore>
#include "CRUDRepository.h"

using namespace std;
using namespace domain;

Scooter parseLine(const QString& line);

class CSVFileRepository : public CrudRepository<Scooter> {
    QString file;
public:
    CSVFileRepository(const QString& filename);

    bool create(Scooter new_entity) override;

    void read(vector<Scooter>& elements) override;

    bool update(Scooter entity) override;

    bool remove(Scooter entity) override;

    ~CSVFileRepository();
};

#endif // CSVFILEREPO_H

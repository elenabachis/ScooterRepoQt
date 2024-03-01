#pragma once

#include "CRUDRepository.h"
#include "Electroscooter.h"

using namespace std;
using namespace domain;
namespace repository {
class InMemoryRepository : public CrudRepository<Scooter> {
    private:
        vector<Scooter> elements;
    public:
        InMemoryRepository();

        bool create(Scooter new_entity) override;

        void read(vector<Scooter>& entities) override;

        bool update(Scooter new_entity) override;

        bool remove(Scooter new_entity) override;

        ~InMemoryRepository();
    };

}

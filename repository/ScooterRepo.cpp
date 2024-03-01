
#include <algorithm>

#include "ScooterRepo.h"

using namespace repository;
using namespace domain;

InMemoryRepository::InMemoryRepository() = default;

InMemoryRepository::~InMemoryRepository() = default;

bool InMemoryRepository::create(Scooter new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const Scooter &entity) {
        return new_entity.getId() == entity.getId();
    });
    if (it == elements.end()) {
        elements.push_back(new_entity);
        return true;
    }
    return false;
}

void InMemoryRepository::read(vector<Scooter>& entities) {
    entities = this->elements;
}

bool InMemoryRepository::update(Scooter new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const Scooter &entity) {
        return new_entity.getId() == entity.getId();
    });
    if (it != elements.end()) {
        (*it).set_Last_Address(new_entity.get_Last_Address());
        (*it).set_State(new_entity.get_actual_state());
        (*it).set_kilometer_count(new_entity.get_Kilometer_Count());
        return true;
    }
    return false;
}

bool InMemoryRepository::remove(Scooter new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const Scooter &entity) {
        return new_entity.getId() == entity.getId();
    });
    if (it != elements.end()) {
        elements.erase(it);
        return true;
    }
    return false;
}



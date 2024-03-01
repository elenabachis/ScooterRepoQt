#include "ScooterController.h"
#include <string>

using namespace std;
using namespace controller;
using namespace repository;


Controller::Controller() : scooter_repository_(){
    this->scooter_repository_ = make_unique<InMemoryRepository>();
}

void Controller::set_CSV_repository(QString filename){
    auto repo = make_unique<CSVFileRepository>(filename);
    this->scooter_repository_ = std::move(repo);
}

bool Controller::add_Scooter(string id_, string model_, date reg_date, int kilometer_count_,
                                         string address_, State initial_state) {
    return scooter_repository_->create(Scooter(id_, model_, reg_date, kilometer_count_, address_, initial_state));
}

bool Controller::delete_Scooter(const Scooter& scooter) {
    return scooter_repository_->remove(scooter);
}

bool Controller::update(const Scooter& scooter) {
    return scooter_repository_->update(scooter);
}

vector<Scooter> Controller::filter_by_age(int query) {
    vector<Scooter> filtered_scooters;
    vector<Scooter> all_scooters;

    scooter_repository_->read(all_scooters);
    for (auto scooter : all_scooters) {
        if (scooter.getRegistration().year == query)
            filtered_scooters.push_back(scooter);
    }
    return filtered_scooters;
}

vector<Scooter> Controller::filter_by_location(string query) {
    vector<Scooter> filtered_scooters;
    vector<Scooter> all_scooters;
    scooter_repository_->read(all_scooters);
    for (auto scooter: all_scooters) {
        if (scooter.get_Last_Address() == query)
            filtered_scooters.push_back(scooter);
    }
    return filtered_scooters;
}

vector<Scooter> Controller::filter_by_kilometer_count(int query) {
    vector<shared_ptr<domain::Scooter>> filtered_scooters;
    vector<Scooter> all_scooters;
    scooter_repository_->read(all_scooters);
    for (auto scooter: all_scooters) {
        if (scooter.get_Kilometer_Count() >= query)
            all_scooters.push_back(scooter);
    }
    return all_scooters;

}

vector<Scooter> Controller::show_by_ascending_age_order() {
    vector<Scooter> all_scooters;
    scooter_repository_->read(all_scooters);
    sort(all_scooters.begin(), all_scooters.end(), [](const Scooter &a,
                                                      const Scooter &b) {
        return a.getRegistration().year < b.getRegistration().year;
    });
    return all_scooters;
}

bool Controller::reserve_Scooter(Scooter& scooter) {
    if (scooter.get_actual_state() == State::Parked) {
        scooter.set_State(State::Reserved);
        return true;
    }
    return false;
}

void Controller::get_all(vector<Scooter>& elements) {

    scooter_repository_->read(elements);
}

Controller::~Controller() = default;

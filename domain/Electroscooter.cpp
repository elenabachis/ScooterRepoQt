#include "Electroscooter.h"
#include <iostream>
#include <vector>

using namespace domain;

Scooter::Scooter(string id_, string model_, date reg_date, int kilometer_count_, string address_,
                 State initial_state) :
        id{id_}, model{model_}, registration_date{reg_date},
        kilometer_count{kilometer_count_}, last_address{address_},
        actual_state{initial_state} {}

Scooter::~Scooter() = default;

Scooter::Scooter(const Scooter &other) {
    this->id = other.id;
    this->model = other.model;
    this->registration_date = other.registration_date;
    this->kilometer_count = other.kilometer_count;
    this->last_address = other.last_address;
    this->actual_state = other.actual_state;
}

Scooter &Scooter::operator=(const Scooter &other) {
    if (this == &other) {
        return *this;
    }
    this->id = other.id;
    this->model = other.model;
    this->registration_date = other.registration_date;
    this->kilometer_count = other.kilometer_count;
    this->last_address = other.last_address;
    this->actual_state = other.actual_state;
    return *this;
}

string Scooter::getId() const {
    return this->id;
}

string Scooter::getModel() const {
    return this->model;
}

date Scooter::getRegistration() const {
    return this->registration_date;
}

int Scooter::get_Kilometer_Count() const {
    return this->kilometer_count;
}

string Scooter::get_Last_Address() {
    return this->last_address;
}

State Scooter::get_actual_state() const {
    return this->actual_state;
}

void Scooter::set_State(State new_state) {
    this->actual_state = new_state;
}

void Scooter::set_Last_Address(string new_address) {
    this->last_address = new_address;
}

void Scooter::set_kilometer_count(int new_kilometer_count) {
    this->kilometer_count = new_kilometer_count;
}

void Scooter::print_scooter() {
    std::vector<string> states = {"Parked", "Reserved", "In_Use", "In_Service", "Out_of_Order"};
    std::cout << "ID: " << id << " " << "\nMODEL: " << model << " " << "\nREGISTRATION DATE: " <<
              registration_date.day << "/" << registration_date.month << "/" << registration_date.year <<
              "\nKM COUNT: " << kilometer_count << "\nLAST ADDRESS: " << last_address << "\nSTATE: "
              << states[actual_state]<<"\n\n";

}


void test_print_scooter() {
    Scooter scooter1("12D", "Vega", {2003, 03, 20},
                     1200, "Los Angeles, Street nr 1", State::Reserved);
    scooter1.print_scooter();
}

#pragma once
#include "ScooterRepo.h"
#include "CSVFileRepo.h"
#include "QString"
#include <algorithm>
#include <memory>

using namespace std;
using namespace domain;

namespace controller{
    class Controller{
        unique_ptr<CrudRepository<Scooter>> scooter_repository_;
    public:

        /// \param scooter_repository
        explicit Controller();

        ~Controller();

        void set_CSV_repository(QString filename);

        /// \param id_
        /// \param model_
        /// \param reg_date
        /// \param kilometer_count_
        /// \param address_
        /// \param initial_state
        /// \return true if the scooter was added
        bool add_Scooter(string id_, string model_, date reg_date, int kilometer_count_, string address_, State initial_state = State::Parked);

        /// \param scooter
        /// \return true if the scooter was deleted
        bool delete_Scooter(const Scooter& scooter);

        /// \param scooter
        /// \return true if the scooter was updated
        bool update(const Scooter& scooter);

        /// \param query
        /// \return a vector of shared pointers to a Scooter Class
        vector<Scooter> filter_by_age(int query);

        /// \param query
        /// \return a vector of shared pointers to a Scooter Class
        vector<Scooter> filter_by_location(string query);

        /// \param query
        /// \return a vector of instances to a Scooter Class
        vector<Scooter> filter_by_kilometer_count(int query);

        /// \return a vector of instaces to a Scooter Class
        vector<Scooter> show_by_ascending_age_order();

        /// \param scooter
        /// \return true if the client can reserve the scooter
        bool reserve_Scooter(Scooter& scooter);

        void get_all(vector<Scooter>& elements);
    };
}

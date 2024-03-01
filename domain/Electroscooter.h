#pragma once

#include <string>

using std::string;

/// \brief Defines a date Object. Used later as an attribute in the class definition
struct date {
    int year;
    int month;
    int day;
};

/// \brief Defining a State enum object, used later as an attribute in the class definition of Scooter
enum State {
    Parked, Reserved, In_Use, In_Service, Out_of_Order
};

namespace domain {
    class Scooter {
        string id;
        string model;
        date registration_date;
        int kilometer_count;
        string last_address;
        State actual_state;
    public:
        /// \brief Constructor for a Scooter object
        /// \param id_  String Pass by Reference, stores the ID of a Scooter Object
        /// \param model_  String Pass by Reference, stores the model name of a Scooter Object
        /// \param reg_date  date Pass by Value, stores the registration date of a Scooter Object
        /// \param kilometer_count_  Integer Pass by Value, stores the total kilometer count in a scooter's lifetime
        /// \param address_  String Pass by Reference, stores the last address of a Scooter Object
        /// \param initial_state  State Pass by Value, stores the state of a Scooter Object, whether it is In_Use, Reserved etc.
        Scooter(string id_, string model_, date reg_date, int kilometer_count_, string address_,
                State initial_state);

        /// \brief Destructor
        ~Scooter();

        /// \brief Copy Constructor
        /// \param other Scooter Reference, the object to be copied
        Scooter(const Scooter &other);

        /// \brief Assignment Operator
        /// \param other Scooter Pass by Reference, the object to be copied
        /// \return A Scooter Reference
        Scooter& operator=(const Scooter &other);

        /// \brief Getter for model attribute
        /// \return A String with the value of the attribute
        string getModel() const;

        /// \brief Getter for the last address
        /// \return A string representing the last address
        string get_Last_Address();

        /// \brief Getter for the actual state
        /// \return A State type object representing the actual state
        State get_actual_state() const;

        /// \brief Getter for the ID
        /// \return A String with the ID
        string getId() const;

        /// \brief Getter for the registration date
        /// \return A date type object with the registration date
        date getRegistration() const;

        /// \brief Getter for the kilometer count
        /// \return An Integer with the kilometer count
        int get_Kilometer_Count() const;

        /// \brief Setter for the actual state
        /// \param new_state State Pass by Value, stores
        void set_State(State new_state);

        /// \brief Setter for the last address attribute
        /// \param new_address String Pass by Reference, stores the new address
        void set_Last_Address(string new_address);

        /// \brief Setter for the kilometer count
        /// \param new_kilometer_count Integer Pass by Value, stores the new kilometer count
        void set_kilometer_count(int new_kilometer_count);

        void print_scooter();
    };

}

void test_print_scooter();

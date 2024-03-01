#include <iostream>
#include <iomanip>
#include "ScooterUi.h"

using namespace std;
using namespace domain;


namespace ui {
    UI::UI(const Controller &controller1) {
        // Initialize the controller and repository
        scootercontroller = make_shared<Controller>(controller1);
    }

    UI::~UI() = default;

    void UI::run() {

        add_data();
        // Display the main menu
        while (true) {
            menu();
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    sub_menu_application();
                    int app_choice;
                    cin >> app_choice;
                    console_application(app_choice);
                    break;
                case 2:
                    sub_menu_tests();
                    break;
                case 3:
                    cout << "Exiting the program... Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid choice! Please try again." << endl;
                    break;
            }
        }
    }

    void UI::console_application(int choice) {
        switch (choice) {
            case 1:
                sub_menu_manager();
                int choice;
                cin >> choice;
                console_application_manager(choice);
                break;
            case 2:
                sub_menu_client();
                cin >> choice;
                console_application_client(choice);
                break;
            default:
                break;
        }

    }

    void UI::sub_menu_tests() {
//        test_repository::test_all();
//        test_all();
//        test_print_scooter();
    }

    void UI::menu() {

        cout << "Welcome to the Electric Scooter Rental System!" << endl;
        std::cout << "~MENU~\n"
                     "1. run application\n"
                     "2. test application\n"
                     "3. exit\n"
                     "Type an option: ";
    }


    void UI::sub_menu_client() {

        std::cout << "You are a client\n"
                     "--OPTIONS--\n"
                     "1. Reserve a scooter\n"
                     "2. Search by location\n"
                     "3. Search by age\n"
                     "4. Search by kilometer count\n"
                     "5. Show all scooters\n"
                     "6. Return to home screen\n";
    }

    void UI::sub_menu_manager() {

        std::cout << "You are the manager\n"
                     "--OPTIONS--\n"
                     "1. Add a scooter\n"
                     "2. Delete a scooter\n"
                     "3. Update a scooter\n"
                     "4. Show all scooters by ascending age\n"
                     "5. Filter by age\n"
                     "6. Filter by kilometer count\n"
                     "7. Return to home screen\n";
    }

    void UI::sub_menu_application() {
        std::cout << "Choose your role\n"
                     "1. Manager\n"
                     "2. Client\n";
    }

    void UI::console_application_client(int choice) {
        switch (choice) {
            case 1: {
                std::cout << "AVAILABLE SCOOTERS:\n";
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->get_all();
                int i = 1;
                for (auto s: scooters) {
                    cout << i << ". ";
                    (*s).print_scooter();
                    i++;
                }
                cout << "Type a number to select a scooter:";
                cin >> i;
                try {
                    if (i > scooters.size()) {
                        throw std::invalid_argument("Invalid input: number too high");
                    }
                } catch (std::invalid_argument &invalid_argument) {
                    cout << "Reservation failed" << endl;
                    cout << invalid_argument.what() << endl;
                    cout << "Returning to home screen" << endl;
                    break;
                }
                cout << "\nReserving scooter...\n";
                (*scootercontroller).reserve_Scooter(scooters[i - 1]);
                cout << "Scooter reserved!" << endl;
                break;
            }
            case 2: {
                std::cout << "GIVE A LOCATION: \n";
                string location;
                cin.ignore();
                getline(cin, location);
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->filter_by_location(location);
                std::cout << "RESULTS FOR LOCATION " << location << " ARE: ";
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }

            case 3: {
                std::cout << "INTRODUCE AN AGE: \n";
                int age;
                cin >> age;
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->filter_by_age(age);
                std::cout << "RESULTS FOR AGE " << age << " ARE: ";
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }
            case 4: {
                std::cout << "INTRODUCE THE KM COUNT: \n";
                int km;
                cin >> km;
                try{
                    validate_number(km);
                } catch(exception& e){
                    cout << "Invalid kilometer count\n" << e.what() << endl;
                    break;
                }
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->filter_by_age(km);
                std::cout << "RESULTS FOR KM COUNT " << km << " ARE: ";
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }
            case 5: {
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->get_all();
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }
            default:
                break;
        }
    }

    void UI::console_application_manager(int choice) {
        switch (choice) {
            case 1: {
                cout << "ADD A NEW SCOOTER:\n";
                string id, model, location;
                int km;
                date d;
                cout << "ID:\n";
                cin.ignore();
                getline(cin, id);
                cout << "MODEL:\n";
                cin.ignore();
                getline(cin, model);
                cout << "DAY:\n";
                cin >> d.day;
                cout << "MONTH:\n";
                cin >> d.month;
                cout << "YEAR:\n";
                cin >> d.year;
                try {
                    validate_date(d);
                } catch(exception& e){
                    cout << "Invalid date" << e.what() << endl;
                    cout << "Returning to home screen\n";
                    break;
                }
                cout << "LOCATION:\n";
                cin.ignore();
                getline(cin, location);
                cout << "KM:\n";
                cin.ignore();
                cin >> km;
                try {
                    validate_number(km);
                } catch (exception &e) {
                    cout << "FAILED TO REGISTER NEW KILOMETER COUNT\n" << e.what();
                    cout << "Returning to home screen\n";
                    break;
                }
                scootercontroller->add_Scooter(id, model, d, km, location, State::Parked);
            }
            case 2: {
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->get_all();
                int i = 1;
                for (auto s: scooters) {
                    cout << i << ". ";
                    (*s).print_scooter();
                    i++;
                }
                cout << "Type the number for the object you want to delete:\n";
                cin >> i;
                try {
                    if (i < 0 || i > scooters.size())
                        throw std::invalid_argument("FALSE\n");
                }
                catch (std::exception &e) {
                    cout << "FAILED TO DELETE SCOOTER\n" << e.what();
                    cout << "RETURNING TO HOME SCREEN\n";
                    break;
                }
                scootercontroller->delete_Scooter(scooters[i - 1]);
            }
            case 3: {
                cout << "SCOOTER UPDATE:\n";
                auto scooters = (*scootercontroller).get_all();
                int i = 1;
                string address;
                int km;
                State s;
                cout << "NEW ADDRESS:\n";
                cin.ignore();
                getline(cin, address);
                cin >> km;
                try {
                    validate_number(km);
                } catch (exception &e) {
                    cout << "FAILED TO REGISTER NEW KILOMETER COUNT\n" << e.what();
                    cout << "Returning to home screen\n";
                    break;
                }
            }
            case 4: {
                cout << "SHOWING ALL SCOOTERS BY ASCENDING AGE\n";
                auto scooters = scootercontroller->show_by_ascending_age_order();
                for (auto it: scooters) {
                    it->print_scooter();
                }
                break;
            }
            case 5: {
                std::cout << "INTRODUCE AN AGE: \n";
                int age;
                cin >> age;
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->filter_by_age(age);
                std::cout << "RESULTS FOR AGE " << age << " ARE: ";
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }
            case 6: {
                cout << "FILTERING BY KILOMETER COUNT\n";
                std::cout << "INTRODUCE THE KM COUNT: \n";
                int km;
                cin >> km;
                vector<shared_ptr<domain::Scooter>> scooters = scootercontroller->filter_by_age(km);
                std::cout << "RESULTS FOR KM COUNT " << km << " ARE: ";
                for (auto s: scooters) {
                    (*s).print_scooter();
                }
                break;
            }
            default:
                break;
        }
    }

    void UI::add_data() {

        scootercontroller->add_Scooter("12D", "Vega", {2003, 03, 20},
                                       1200, "Los Angeles Street nr 1", State::Parked);
        scootercontroller->add_Scooter("13D", "V", {2003, 04, 20},
                                       1300, "Los Angeles Street nr 1", State::Reserved);
        scootercontroller->add_Scooter("17D", "Suc", {2012, 03, 20},
                                       12500, "Tokyo Street nr 1", State::In_Use);
        scootercontroller->add_Scooter("10D", "Maro", {2012, 05, 20},
                                       5200, "Los Angeles Street nr 1", State::Reserved);
        scootercontroller->add_Scooter("134D", "Csem", {2012, 03, 01},
                                       12050, "Berlin Street nr 1", State::Parked);

        scootercontroller->add_Scooter("13DA", "Knoll", {2010, 01, 02},
                                       12500, "Vienna Street nr 1", State::Out_of_Order);
        scootercontroller->add_Scooter("16G", "Dede", {2011, 01, 02},
                                       12050, "Bistrita Street nr 1", State::Out_of_Order);
        scootercontroller->add_Scooter("123D", "Maro", {2015, 06, 03},
                                       12050, "Los Angeles Street nr 1", State::Parked);
        scootercontroller->add_Scooter("15D", "Coco", {2011, 03, 01},
                                       800, "Bucharest Street nr 1", State::In_Use);
        scootercontroller->add_Scooter("131D", "Roco", {2022, 02, 01},
                                       150, "Ibiza Street nr 1", State::In_Service);
        scootercontroller->add_Scooter("1323D", "Selo", {2012, 03, 01},
                                       500, "Madrid Street nr 1", State::Parked);
    }

    void UI::validate_date(date &d) {
        if ((d.day < 1 || d.day > 31) && (d.month < 1 || d.month > 12) || d.year <= 0) {
            throw std::invalid_argument("Invalid date");
        }

    }

    void UI::validate_number(int &a) {
        if (a <= 0) {
            throw invalid_argument("Invalid argument");
        }
    }


}


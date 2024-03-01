#pragma once
//#include "test_repository.h"
//#include "test_controller.h"
#include "ScooterController.h"

using namespace controller;

namespace ui {
    class UI {
        shared_ptr<controller::Controller> scootercontroller;
    public:
        UI();

        UI(const Controller& controller1);
        ~UI();

        void run();

        void add_data();

        void console_application(int choice);

        void console_application_client(int choice);

        void console_application_manager(int choice);

        void menu();

        void sub_menu_application();

        void sub_menu_tests();

        void sub_menu_client();

        void sub_menu_manager();

        void validate_date(date& d);

        void validate_number(int& a);

//        ....
    };
}
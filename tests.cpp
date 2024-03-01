#include "tests.h"
#include "ScooterController.h"
#include "CSVFileRepo.h"
#include <memory>
#include <cassert>


void test_controller::test_addScooter() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    bool result = controller.add_Scooter("1", "Model A", {2003, 7, 8}, 100, "Address 1", State::Parked);
    assert(result);
}

void test_controller::test_deleteScooter() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("1", "Model A", {2003, 7, 8}, 100, "Address 1", State::Parked);
    controller.add_Scooter("2", "Model B", {2003, 7, 8}, 1200, "Address 3", State::Parked);
    domain::Scooter scooter("1", "Model A", {2003, 7, 8}, 100, "Address 1", State::Parked);
    auto sc = make_shared<domain::Scooter>(scooter);
    controller.delete_Scooter(sc);
    vector<shared_ptr<domain::Scooter>> scooters = controller.get_all();
    assert(scooters.size() == 1);
}

void test_controller::test_updateScooter() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("1", "Model A", {2003, 7, 8}, 100, "Address 1", State::Parked);
    domain::Scooter scooter("1", "Model A", {2003, 7, 8}, 100, "Address 1", State::Parked);
    auto sc = make_shared<domain::Scooter>(scooter);
    bool result = controller.update(sc);
    assert(result);

}

void test_controller::test_filterByAge() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("12D", "Vega", {2003, 03, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("15D", "Marco", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 10", State::Reserved);
    controller.add_Scooter("12D", "Louis", {2004, 03, 20},
                           1200, "Los Angeles, Street nr 3", State::Reserved);
    controller.add_Scooter("15D", "Gustav", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 4", State::Reserved);
    controller.add_Scooter("12D", "Socrate", {2005, 03, 20},
                           1200, "Los Angeles, Street nr 2", State::Reserved);
    controller.add_Scooter("15D", "Motor", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 8", State::Reserved);

    vector<shared_ptr<domain::Scooter>> scooters = controller.filter_by_age(2003);
    for (auto it: scooters) {
        assert(it->getRegistration().year == 2003);
    }
}

void test_controller::test_filterByLocation() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("12D", "Vega", {2003, 03, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("15D", "Marco", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 10", State::Reserved);
    controller.add_Scooter("12D", "Louis", {2004, 03, 20},
                           1200, "Los Angeles, Street nr 3", State::Reserved);
    controller.add_Scooter("15D", "Gustav", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("12D", "Socrate", {2005, 03, 20},
                           1200, "Los Angeles, Street nr 2", State::Reserved);
    controller.add_Scooter("15D", "Motor", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 1", State::Reserved);
    vector<shared_ptr<domain::Scooter>> scooters = controller.filter_by_location("Los Angeles, Street nr 1");
    for (auto it: scooters) {
        assert(it->get_Last_Address() == "Los Angeles, Street nr 1");
    }
}

void test_controller::test_filterByKMCount() {

    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("12D", "Vega", {2003, 03, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("15D", "Marco", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 10", State::Reserved);
    controller.add_Scooter("12D", "Louis", {2004, 03, 20},
                           3200, "Los Angeles, Street nr 3", State::Reserved);
    controller.add_Scooter("15D", "Gustav", {2003, 05, 20},
                           5200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("12D", "Socrate", {2005, 03, 20},
                           2200, "Los Angeles, Street nr 2", State::Reserved);
    controller.add_Scooter("15D", "Motor", {2003, 05, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    vector<shared_ptr<domain::Scooter>> scooters = controller.filter_by_kilometer_count(2200);
    for (auto it: scooters) {
        assert(it->get_Kilometer_Count() >= 2200);
    }
}


void test_controller::test_showByAscendingAgeOrder() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("12D", "Vega", {2002, 03, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("15D", "Marco", {2003, 05, 20},
                           4200, "Los Angeles, Street nr 10", State::Reserved);
    controller.add_Scooter("12D", "Louis", {2004, 03, 20},
                           3200, "Los Angeles, Street nr 3", State::Reserved);
    controller.add_Scooter("15D", "Gustav", {2003, 05, 20},
                           5200, "Los Angeles, Street nr 1", State::Reserved);
    controller.add_Scooter("12D", "Socrate", {2005, 03, 20},
                           2200, "Los Angeles, Street nr 2", State::Reserved);
    controller.add_Scooter("15D", "Motor", {2001, 05, 20},
                           1200, "Los Angeles, Street nr 1", State::Reserved);
    vector<shared_ptr<domain::Scooter>> scooters = controller.show_by_ascending_age_order();
    bool ok = true;
    for (int i = 0; i < scooters.size() - 1; i++) {
        if (scooters[i]->getRegistration().year > scooters[i + 1]->getRegistration().year) {
            ok = false;
            break;
        }
    }
    assert(ok);
}

void test_controller::test_ReserveScooter() {
    shared_ptr<repository::InMemoryRepository> scooterRepository;
    controller::Controller controller(scooterRepository);
    controller.add_Scooter("12D", "Vega", {2003, 03, 20},
                           1200, "Los Angeles, Street nr 1", State::Parked);

    domain::Scooter scooter("12D", "Vega", {2003, 03, 20},
                            1200, "Los Angeles, Street nr 1", State::Parked);
    auto sc = make_shared<domain::Scooter>(scooter);
    bool result = controller.reserve_Scooter(sc);
    assert(result);
}

void test_in_memory_repository::testCreate() {
    repository::InMemoryRepository repository;
    domain::Scooter scooter1("123", "Bolt", {2023, 1, 3}, 10, "Plopilor, Cluj-Napoca", State::Parked);
    domain::Scooter scooter2("456", "Lime", {2023, 2, 5}, 20, "Victoriei, Bucharest", State::Reserved);

    // Test creating a new entity
    bool created = repository.create(std::make_shared<domain::Scooter>(scooter1));
    assert(created);

    // Test creating a duplicate entity
    created = repository.create(std::make_shared<domain::Scooter>(scooter1));
    assert(created == false);

    // Test creating a different entity
    created = repository.create(std::make_shared<domain::Scooter>(scooter2));
    assert(created);
}

void test_in_memory_repository::testRead() {
    repository::InMemoryRepository repository;
    domain::Scooter scooter1("123", "Bolt", {2023, 1, 3}, 10, "Plopilor, Cluj-Napoca", State::Parked);
    domain::Scooter scooter2("456", "Lime", {2023, 2, 5}, 20, "Victoriei, Bucharest", State::Reserved);

    // Add entities to the repository
    assert(repository.create(std::make_shared<domain::Scooter>(scooter1)));
    assert(repository.create(std::make_shared<domain::Scooter>(scooter2)));

    // Test reading entities
    std::vector<std::shared_ptr<domain::Scooter>> elements = repository.read();

    assert(elements.size() == 2);
    assert(elements[0]->getId() == "123");
    assert(elements[1]->getId() == "456");
}

void test_in_memory_repository::testUpdate() {
    repository::InMemoryRepository repository;
    domain::Scooter scooter1("123", "Bolt", {2023, 1, 3}, 10, "Plopilor, Cluj-Napoca", State::Parked);
    domain::Scooter scooter2("456", "Lime", {2023, 2, 5}, 20, "Victoriei, Bucharest", State::Reserved);

    // Add entities to the repository
    repository.create(std::make_shared<domain::Scooter>(scooter1));
    repository.create(std::make_shared<domain::Scooter>(scooter2));

    // Test updating an existing entity
    domain::Scooter updatedScooter("123", "Bolt", {2023, 1, 3}, 10, "Unirii, Cluj-Napoca", State::Parked);
    bool updated = repository.update(std::make_shared<domain::Scooter>(updatedScooter));
    assert(updated);

    // Retrieve the updated entity
    std::vector<std::shared_ptr<domain::Scooter>> elements = repository.read();
    assert(elements.size() == 2);
    assert(elements[0]->get_Last_Address() == "Unirii, Cluj-Napoca");
    assert(elements[0]->get_actual_state() == State::Parked);

    // Test updating a non-existing entity
    domain::Scooter nonExistingScooter("789", "Scoot", {2023, 3, 7}, 30, "Union Square, New York", State::Parked);
    updated = repository.update(std::make_shared<domain::Scooter>(nonExistingScooter));
    assert(!updated);
}

void test_in_memory_repository::testRemove() {
    repository::InMemoryRepository repository;
    domain::Scooter scooter1("123", "Bolt", {2023, 1, 3}, 10, "Plopilor, Cluj-Napoca", State::Parked);
    domain::Scooter scooter2("456", "Lime", {2023, 2, 5}, 20, "Victoriei, Bucharest", State::Reserved);

    // Add entities to the repository
    repository.create(std::make_shared<domain::Scooter>(scooter1));
    repository.create(std::make_shared<domain::Scooter>(scooter2));

    // Test removing an existing entity
    bool removed = repository.remove(std::make_shared<domain::Scooter>(scooter1));
    assert(removed);

    // Test removing a non-existing entity
    removed = repository.remove(std::make_shared<domain::Scooter>(scooter1));
    assert(!removed);

    // Retrieve the remaining entities
    std::vector<std::shared_ptr<domain::Scooter>> elements = repository.read();
    assert(elements.size() == 1);
    assert(elements[0]->getId() == "456");
}


void test_csv_repo::test_create() {
    CSVFileRepository repo = CSVFileRepository("C:\\Users\\User\\Documents\\Labor7\\repository\\test_storage.txt");
    domain::Scooter scooter0("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Parked);
    domain::Scooter scooter1("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Reserved);
    domain::Scooter scooter2("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::In_Use);
    domain::Scooter scooter3("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::In_Service);
    domain::Scooter scooter4("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Out_of_Order);
    auto shared_sc0 = make_shared<domain::Scooter>(scooter0);
    auto shared_sc1 = make_shared<domain::Scooter>(scooter1);
    auto shared_sc2 = make_shared<domain::Scooter>(scooter2);
    auto shared_sc3 = make_shared<domain::Scooter>(scooter3);
    auto shared_sc4 = make_shared<domain::Scooter>(scooter4);
    assert(repo.create(shared_sc0));
    assert(repo.create(shared_sc1));
    assert(repo.create(shared_sc2));
    assert(repo.create(shared_sc3));
    assert(repo.create(shared_sc4));
}

void test_csv_repo::test_read() {
    CSVFileRepository repo = CSVFileRepository("C:\\Users\\User\\Documents\\Labor7\\repository\\test_storage.txt");
    domain::Scooter scooter1("123", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Parked);
    domain::Scooter scooter2("124","Honda", {2022,4,2},500,"Strada Mamaia 20", State::Parked);
    auto shared_scooter1=make_shared<domain::Scooter>(scooter1);
    auto shared_scooter2=make_shared<domain::Scooter>(scooter2);
    repo.create(shared_scooter1);
    repo.create(shared_scooter2);
    std::vector<shared_ptr<domain::Scooter>> elements = repo.read();
    assert(elements.size()==2);

}

void test_csv_repo::test_update() {
    CSVFileRepository repo = CSVFileRepository("C:\\Users\\User\\Documents\\Labor7\\repository\\test_storage.txt");
    domain::Scooter scooter0("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Parked);
    auto shared_sc0 = make_shared<domain::Scooter>(scooter0);
    repo.create(shared_sc0);
    shared_sc0->set_Last_Address("Strada Ploiesti 19");
    assert(repo.update(shared_sc0));
}

void test_csv_repo::test_remove() {
    CSVFileRepository repo = CSVFileRepository("C:\\Users\\User\\Documents\\Labor7\\repository\\test_storage.txt");
    domain::Scooter scooter0("XYZ", "Honda", {2022, 5, 1}, 291, "Strada Constanta 19-21", State::Parked);
    domain::Scooter scooter1("XYZ", "Honda", {2023, 5, 1}, 291, "Strada Ploiesti 19", State::Reserved);
    vector<shared_ptr<domain::Scooter>> added_elements;
    added_elements = repo.read();
    auto shared_sc0 = make_shared<domain::Scooter>(scooter0);
    auto shared_sc1 = make_shared<domain::Scooter>(scooter1);
    added_elements.push_back(shared_sc0);
    added_elements.push_back(shared_sc1);
    repo.create(shared_sc0);
    repo.create(shared_sc1);
    repo.remove(shared_sc0);
    auto it = find_if(added_elements.begin(), added_elements.end(), [&](const shared_ptr<domain::Scooter> &scooter) {
        return shared_sc0->getId() == scooter->getId();
    });
    if (it != added_elements.end()) {
        added_elements.erase(it);
    }
    auto elements = repo.read();
    assert(elements.size() == added_elements.size());
}

void call_all_tests(){
//    test_controller::test_addScooter();
//    test_controller::test_deleteScooter();
//    test_controller::test_updateScooter();
//    test_controller::test_filterByAge();
//    test_controller::test_filterByLocation();
//    test_controller::test_filterByKMCount();
//    test_controller::test_showByAscendingAgeOrder();
//    test_controller::test_ReserveScooter();
//    test_in_memory_repository::testCreate();
//    test_in_memory_repository::testRead();
//    test_in_memory_repository::testUpdate();
//    test_in_memory_repository::testRemove();
    test_csv_repo::test_create();
//    test_csv_repo::test_update();
    test_csv_repo::test_read();
//    test_csv_repo::test_remove();
}

#pragma once

namespace test_controller{
    void test_addScooter();
    void test_deleteScooter();
    void test_updateScooter();
    void test_filterByAge();
    void test_filterByLocation();
    void test_filterByKMCount();
    void test_showByAscendingAgeOrder();
    void test_ReserveScooter();
}

namespace test_in_memory_repository {
    void testCreate();
    void testRead();
    void testUpdate();
    void testRemove();
}

namespace test_csv_repo{
    void test_create();
    void test_update();
    void test_read();
    void test_remove();
}

void call_all_tests();

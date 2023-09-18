#pragma once
#include "Set.h"

class SetTest
{
public:
    SetTest(MemoryManager &mem) : set(mem), setExtra(mem) {};
    void test_insert(int quantity);
    void test_size_equals_and_same_elements();
    void test_clear_find();
    void test_size_and_max_bites();
    void test_insert_a_lot(int quantity);

private:
    Set set, setExtra;
};

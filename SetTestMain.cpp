#include "SetTest.h"
#include "Mem.h"

int main()
{
    Mem mem(200000);
    SetTest test(mem);

    test.test_insert(10);
    test.test_size_equals_and_same_elements();
    test.test_clear_find();
    test.test_size_and_max_bites();
    test.test_insert_a_lot(1000000);
    return 0;
}
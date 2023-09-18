#pragma once
#include "SetTest.h"
#include "iostream"

using namespace std;

void SetTest::test_insert(int quantity)
{
    cout << "test_insert begin" << endl;

    int check = 0;
    size_t size;
    int* a;
    for (int i = 0; i < quantity; i++)
    {
        int* p_i = new int(i);
        set.insert(p_i, sizeof(*p_i));
    }

    Set::SetIterator* iter = dynamic_cast<Set::SetIterator*>(set.newIterator());
    for (int i = 0; i < quantity; i++)
    {
        a = (int*)iter->getElement(size);
        if (*a % 2 == 0)
        {
            set.remove(iter);
            continue;
        }
        iter->goToNext();
    }

    iter = dynamic_cast<Set::SetIterator*>(set.newIterator());
    for (int i = 0; i < quantity; i++)
    {
        a = (int*)iter->getElement(size);
        iter->goToNext();
        if (*a % 2 == 0)  check++;
    }

    if (check == 0) cout << "test_insert success";

    cout << endl << "test_insert end" << endl << endl;
    set.clear();
}

void SetTest::test_size_equals_and_same_elements()
{
    cout << "test_size_equals_and_same_elements begin" << endl;

    int check = 0;

    int a_1 = 3;
    double b_1 = 3.14;

    int* a = new int(a_1);
    double* b = new double(b_1);

    set.insert(a, sizeof(*a));
    set.insert(b, sizeof(*b));

    size_t size;
    Set::SetIterator* iter = dynamic_cast<Set::SetIterator*>(set.newIterator());
    Set::SetIterator* iter2 = dynamic_cast<Set::SetIterator*>(set.newIterator());
    //cout << "Is Iterators equal: " << iter->equals(iter2) << endl;
    if (iter->equals(iter2) != 1) check++;

    a = (int*)iter->getElement(size);
    iter->goToNext();
    //cout << "int 3: " << *a << " " << endl;
    if (*a != 3) check++;

    b = (double*)iter->getElement(size);
    iter->goToNext();
    //cout << "double 3.14: " << *b << " ";
    if (*b != 3.14) check++;

    int* a_2 = new int(a_1);
	if (set.insert(a_2, sizeof(*a_2)) == 1)
    {
        //cout << endl << "The same element was not added" << endl;
    }
    else
    {
       // cout << endl << "The same element was added" << endl;
       check++;
    }

    //cout << "Is Iterators equal: " << iter->equals(iter2) << endl;
    if (iter->equals(iter2) == 1) check++;

    if (check == 0) cout << "test_size_equals_and_same_elements success" << endl;

    cout << "test_size_equals_and_same_elements end" << endl << endl;
    set.clear();
}

void SetTest::test_clear_find()
{
    cout << "test_clear_find begin" << endl;

    int check = 0;
    setExtra.clear();
    if (!setExtra.empty() || !set.empty())
    {
        cout << "Error in .empty()" << endl;
        check++;
        set.clear();
    }

    int a_1 = 3;
    int* a = new int(a_1);
    set.insert(a, sizeof(*a));
    Container::Iterator* find_element = set.find(a, sizeof(*a));
    if (find_element == nullptr)
    {
        cout << "Error in .find()" << endl;
        check++;
        set.clear();
    }
    set.remove(find_element);
    delete find_element;
    int* a2 = new int(a_1);
    if (set.insert(a2, sizeof(*a2)) == 1)
    {
        cout << "Error in .remove() or .find()" << endl;
        check++;
        set.clear();
    }
    set.clear();
    setExtra.clear();
    if (!set.empty())
    {
        cout << "Error in .clear()" << endl;
        check++;
        set.clear();
    }

    if (check == 0) cout << "test_clear_find success" << endl;

    cout << "test_clear_find end" << endl << endl;
}

void SetTest::test_size_and_max_bites()
{
    cout << "test_size_and_max_bites begin" << endl;

    int check = 0;

    for (int i = 0; i < 10; i++)
    {
        int* p_i = new int(i);
        set.insert(p_i, sizeof(*p_i));
    }

    if (set.size() != 10)
    {
        cout << "Error in .size()" << endl;
        check++;
        set.clear();
    }
    //else cout << "Size of the list must be 10: " << set.size() << endl;

    //cout << "Max bytes: " << set.max_bytes() << endl;

    if (check == 0) cout << "test_size_and_max_bites success" << endl;

    cout << "test_size_and_max_bites end" << endl << endl;
}

void SetTest::test_insert_a_lot(int quantity)
{
    cout << "test_insert_a_lot begin" << endl;

    set.clear();
    double start, finish;
    start = clock();
    for (int i = 0; i < quantity; i++)
    {
        int* p_i = new int(i);
        set.insert(p_i, sizeof(*p_i));
    }
    finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "Time for insert " << quantity << " elements is: " << duration << " seconds" << endl;

    if (duration <= 5) cout << "test_insert_a_lot success" << endl;

    cout << "test_insert_a_lot end" << endl << endl;
}
#pragma once
#include "Set.h"

    void *Set::SetIterator::getElement(size_t &size)
    {
        return pointer->getElement(size);
    }

    bool Set::SetIterator::hasNext()
    {
        if (pointer->hasNext() == true && pointer->getCell()->next->next != nullptr) return true;
        for (int i = listIndex + 1; i < tableSize; i++)
        {
            if (!set->Table[i]->empty()) return true;
        }
        return false;
    }

    void Set::SetIterator::goToNext()
    {
        if (pointer->hasNext() == true && pointer->getCell()->next->next != nullptr)
        {
            pointer->goToNext();
        }
        else
        {
            for (int i = listIndex + 1; i < tableSize; i++)
            {
                if (!set->Table[i]->empty())
                {
                    currentList = set->Table[i];
                    listIndex = i;
                    pointer = (SetList::SetListIterator*)currentList->getListIterator();
                    return;
                }
            }
        }
    }

    bool Set::SetIterator::equals(Iterator *right)
    {
        SetIterator* check = dynamic_cast<SetIterator*>(right);
        size_t rightSize, leftSize;
        void* rightElem, *leftElem;
        rightElem = right->getElement(rightSize);
        leftElem = pointer->getElement(leftSize);
        return leftSize == rightSize && memcmp(rightElem, leftElem, leftSize) == 0 && listIndex == check->listIndex;
    }

int Set::size()
{
    return ElementQuantity;
}

size_t Set::max_bytes()
{
    return _memory.maxBytes();
}

Set::Iterator*Set::find(void* elem, size_t size)
{
    int hash = hash_func(elem, size);
    SetIterator* Iter = new SetIterator((SetList::SetListIterator*)Table[hash]->find(elem, size), Table[hash], hash, this);
    Iter->set = this;
    if (Iter->pointer == nullptr)
    {
        delete Iter;
        Iter = nullptr;
    }
    return Iter;
}

Set::Iterator*Set::newIterator()
{
    for (int i = 0; i < tableSize; i++)
    {
        if (!Table[i]->empty())
        {
            SetIterator* Iter = new SetIterator((SetList::SetListIterator*)Table[i]->getListIterator(), Table[i], i, this);
            return Iter;
        }
    }
    return nullptr;
}

void Set::remove(Iterator* iter)
{
    SetIterator* setIter = dynamic_cast<SetIterator*>(iter);
    setIter->currentList->remove(setIter->pointer);
    if (!setIter->pointer->hasNext()) setIter->goToNext();
    ElementQuantity--;
}

void Set::clear()
{
    for (int i = 0; i < tableSize; i++)
    {
        Table[i]->clear();
    }
    ElementQuantity = 0;
}

bool Set::empty()
{
    if (ElementQuantity == 0) return true;
    return false;
}

int Set::insert(void* elem, size_t size)
{
    int hash = hash_func(elem, size);
    Iterator* iter = find(elem, size);
    if (iter != nullptr)
    {
        delete iter;
        return 1;
    }
    int element = Table[hash]->push_front(elem, size);
    if (element == 1) return 2;
    ElementQuantity++;
    return 0;
}
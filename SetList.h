#pragma once
#include "GroupList.h"

class SetList: public GroupList
{
public:
    SetList(MemoryManager &mem): GroupList(mem) {}

    GroupListIterator* getListIterator() { return new GroupListIterator(beginning); }

    class SetListIterator: public GroupList::GroupListIterator
    {
    public:
        Cell* getCell() { return current; };
    };
};
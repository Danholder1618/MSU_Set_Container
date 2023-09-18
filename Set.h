#pragma once
#include "SetAbstract.h"
#include "SetList.h"

static int tableSize = 200000;
class Set: public AbstractSet
{
public:
    Set(MemoryManager& mem): AbstractSet(mem)
    {
        //Table = new SetList*[tableSize];
        Table = static_cast<SetList**>(mem.allocMem(tableSize * sizeof(SetList*)));
        for (int i = 0; i < tableSize; i++)
        {
            Table[i] = new SetList(mem);
            //SetList temp = SetList(mem);
            //Table[i] = &temp;
            //memcpy(Table[i], &temp, sizeof(temp));
            //Table[i] = static_cast<SetList*>( mem.allocMem( sizeof(SetList) ) );
        }
        ElementQuantity = 0;
    }
    ~Set()
    {
        clear();
        for (int i = 0; i < tableSize; i++)
        {
            Table[i]->~SetList();
            _memory.freeMem(Table[i]);
        }
        delete Table;
    }


    class SetIterator: public Container::Iterator
    {
    public:
        // Указатель на конкретный лист в массиве листов
        SetList::SetListIterator* pointer;
        SetList* currentList;
        int listIndex;
        Set* set;


        SetIterator(SetList::SetListIterator* pointer, SetList* currentList, int listIndex, Set* set):
            pointer(pointer), currentList(currentList), listIndex(listIndex), set(set) {};

        // Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
        // Неявно возвращает размер данных
        void* getElement(size_t& size) override;

        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext() override;

        // Переход к следующему элементу.
        void goToNext() override;

        // проверка на равенство итераторов
        bool equals(Iterator* right) override;
    };


    // Функция возвращает значение, равное количеству элементов в контейнере.
    int size() override;

    // Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
    size_t max_bytes() override;

    // Функция создает в динамической памяти итератор, указывающий на первый найденный
    // в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    Iterator* find(void* elem, size_t size) override;

    // Функция создает в динамической памяти итератор, указывающий на первый элемент
    // контейнера. Если контейнер пустой, возвращается нулевой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    Iterator* newIterator() override;

    // Удаление элемента из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    void remove(Iterator* iter) override;

    // Удаление всех элементов из контейнера.
    void clear() override;

    // Если контейнер пуст возвращает true, иначе false
    bool empty() override;

    // Добавление элемента в контейнер в соответствующую позицию, в соответствии с выбором реализации множества. В случае успешного добавления функция возвращает значение 0, если такой элемент уже есть в контейнере - 1, во всех остальных случаях - 2.
    int insert(void* elem, size_t size) override;

private:
    SetList** Table;
    int ElementQuantity;
};
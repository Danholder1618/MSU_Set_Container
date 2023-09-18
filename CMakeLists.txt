cmake_minimum_required(VERSION 3.24)
project(Set)

set(CMAKE_CXX_STANDARD 17)

add_executable(Set Container.h GroupContainer.h GroupList.h Mem.h MemoryManager.h SetAbstract.h GroupList.cpp GroupList.cpp Set.cpp Set.h GroupContainer.cpp SetTest.cpp SetTest.h SetTestMain.cpp SetList.h)

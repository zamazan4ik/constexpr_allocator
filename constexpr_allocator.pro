TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /home/antoshkka/experiments/constexpr_allocator/include/
SOURCES += /home/antoshkka/experiments/constexpr_allocator/src/stdexcept.cpp
SOURCES += /home/antoshkka/experiments/constexpr_allocator/src/memory.cpp
SOURCES += test.cpp
HEADERS += /home/antoshkka/experiments/constexpr_allocator/include/modif_vector
HEADERS += /home/antoshkka/experiments/constexpr_allocator/include/modif_string
HEADERS += /home/antoshkka/experiments/constexpr_allocator/include/modif_memory
HEADERS += /home/antoshkka/experiments/constexpr_allocator/include/modif_new_destroyer

#QMAKE_CXX = g++-6
QMAKE_CXX = clang++-3.6

QMAKE_CXXFLAGS += -std=c++1z -g -pthread -nostdinc++
LIBS += -pthread


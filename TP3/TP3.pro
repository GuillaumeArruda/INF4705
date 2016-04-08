TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    algorithm.h \
    problem.h \
    solution.h \
    student.h \
    voraceAlgorithm.h

SOURCES += \
    algorithm.cpp \
    main.cpp \
    problem.cpp \
    solution.cpp \
    voraceAlgorithm.cpp

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

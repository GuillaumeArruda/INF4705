TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    algorithm.h \
    problem.h \
    solution.h \
    student.h \
    voracealgorithm.h

SOURCES += \
    algorithm.cpp \
    main.cpp \
    problem.cpp \
    solution.cpp \
    voracealgorithm.cpp \
    randomprobabilitygenerator.cpp

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

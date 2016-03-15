#pragma once

struct Location {
    int id;
    int income;
    int chickenConsommation;
    float cost() { return float(income) / chickenConsommation;}
};
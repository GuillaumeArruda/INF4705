#pragma once

struct Location {
    int id;
    int income;
    int chickenConsommation;
    float cost() { return float(income) / chickenConsommation;}
    bool operator==(const Location& left) const { return id == left.id; }
    bool operator<(const Location& left) const { return id < left.id; }
};
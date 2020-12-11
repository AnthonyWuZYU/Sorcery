#include "card.h"

Card::Card(std::string name, int cost) : name{name}, cost{cost} {}

int Card::get_Cost() const {return cost;}

std::string Card::get_Name() const {return name;}

bool Card::operator==(const Card &other) const {
    if (other.get_Name() == name) {
        return equal(other);
    } else {
        return false;
    }
}

bool Card::operator!=(const Card &other) const {
    if (other.get_Name() == name) {
        return !equal(other);
    } else {
        return true;
    }
}
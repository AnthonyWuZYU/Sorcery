#include "card.h"

Card::Card(std::string name, int cost) : name{name}, cost{cost} {}

int Card::get_Cost() {return cost;}

std::string Card::get_Name() {return name;}

bool Card::operator==(Card &other) {
    if (other.get_Name() == name) {
        return equal(other);
    } else {
        return false;
    }
}
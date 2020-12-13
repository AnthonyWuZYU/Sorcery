#include "card.h"

Card::Card(std::string name, int cost) : name{name}, cost{cost} {}

Card::Card(){}

Card::~Card(){}

void Card::use_ability(){}

void Card::destroy() {}

Card & Card::operator=(const Card & other)  {}

int Card::get_Cost() const {return cost;}

std::string Card::get_Name() const {return name;}

void Card::set_Cost(int c) {cost = c;}

void Card::set_Name(std::string n) {name = n;}

bool Card::operator==(const Card &other) const {
    if (other.get_Name() == name) {
        return true;
    } else {
        return false;
    }
}

bool Card::operator!=(const Card &other) const {
    if (other.get_Name() == name) {
        return false;
    } else {
        return true;
    }
}
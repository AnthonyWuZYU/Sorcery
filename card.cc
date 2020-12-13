#include "card.h"

Card::Card(std::string name, int cost, std::string card_type) : name{name}, cost{cost}, card_type{card_type} {}

Card::Card(){}

Card::~Card(){}

void Card::use_ability(){}

void Card::destroy() {}

Card & Card::operator=(const Card & other)  {}

std::ostream& Card::print(std::ostream& os) const {}

int Card::get_Cost() const {return cost;}

std::string Card::get_Name() const {return name;}

std::string Card::get_type() const {return card_type;}

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



std::ostream& operator<<(std::ostream &os, const Card &card) {
    return card.print(os);
}
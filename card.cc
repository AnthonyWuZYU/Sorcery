#include "card.h"
using namespace std;

Card::Card(std::string name, int cost, std::string card_type) : name{name}, cost{cost}, card_type{card_type} {}

Card::~Card() {}

std::string Card::get_name() const {return name;}

int Card::get_cost() const {return cost;}

std::string Card::get_type() const {return card_type;}

void Card::set_name(std::string name) {this->name = name;}

void Card::set_cost(int cost) {this->cost = cost;}

void Card::set_type(std::string card_type) {this->card_type = card_type;}
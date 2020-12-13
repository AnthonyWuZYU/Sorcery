#include "minion.h"
#include <algorithm>
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, std::string card_type, std::string ability) : 
attack{attack}, defence{defence}, action{0}, Card{name, cost, card_type} {}

Minion::~Minion(){}

Card & Minion::operator=(const Card & other)  {
    const Minion* temp = dynamic_cast<const Minion*>(&other);
    this->set_Name(temp->get_Name());
    this->set_Cost(temp->get_Cost());
    defence = temp->get_defence();
    action = temp->get_action();
    return *this;
}


void Minion::attack_target(Player *player) {
    player->setLife(player->getLife() - attack);

    if (player->getLife() <= 0) {
        //Player loses
    }
}

void Minion::attack_target(Minion *target) {
    target->set_defence(target->get_defence() - attack);

    // Check if target is dead
    if (target->get_defence() <= 0) {
        // target dies
    }
}

void Minion::use_ability() {}

void Minion::destroy() {}

void Minion::set_attack(int a) {attack = a;}

void Minion::set_defence(int d) {defence = d;}

void Minion::set_action(int a) {action = a;}

int Minion::get_attack() const {return attack;}

int Minion::get_defence() const {return defence;}

int Minion::get_action() const {return action;}





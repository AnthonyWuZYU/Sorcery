#include "minion.h"
#include <algorithm>
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, std::string ability) : 
attack{attack}, defence{defence}, action{0}, Card{name, cost} {}

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
    this->set_defence(this->get_defence()- target->get_attack());

    // Check if target is dead
    if (target->get_defence() <= 0) {
        // target dies
    }
}

void Minion::use_ability(Player *player) {
    // Minion Abilities : Activated
    if (description == "Deals damage to all the opponent minions equal to its attack value when it dies") {
        
    } else if (description == "Whenever an opponent's minion enters play, deal 1 damage to it") {

    } else if (description == "At the end of your turn, all your minions gain +0/+1") {

    } 
        // Minion Abilities : Triggered
    else if (description == "1 | Deal 1 damage to target minion") {

    } else if (description == "Summon a 1/1 air elemental") {

    } else if (description == "Summon up to three 1/1 air elementals") {

    }

}

void Minion::destroy() {}

void Minion::set_attack(int a) {attack = a;}

void Minion::set_defence(int d) {defence = d;}

void Minion::set_action(int a) {action = a;}

int Minion::get_attack() const {return attack;}

int Minion::get_defence() const {return defence;}

int Minion::get_action() const {return action;}





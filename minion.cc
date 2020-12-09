#include "minion.h"
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, std::string ability) : 
attack{attack}, defence{defence}, action{0}, Card{name, cost} {}

Minion::~Minion(){}

Card & Minion::operator=(const Card & other) {

}

bool Minion::equal(const Minion &other) {
    Minion temp = other;
    if (temp.get_attack() == attack && temp.get_defence() == defence) {
        return true;
    } else {
        return false;
    }
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

void Minion::set_attack(int a) {attack = a;}

void Minion::set_defence(int d) {defence = d;}

void Minion::set_action(int a) {action = a;}

int Minion::get_attack() {return attack;}

int Minion::get_defence() {return defence;}

int Minion::get_action() {return action;}




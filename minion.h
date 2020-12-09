#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "player.h"
#include <vector>

class Minion : Card {
    int attack;
    int defence;
    int action;
    //vector<Enchantment> minionEnchantments;
    public: 
        // Constructor
        Minion(int a, int d);

        // Deconstructor
        ~Minion();

        //atack(player): Attacks either a minion or player
        void attack(Player *player);

        //attack(minion): Attacks a minion
        void attack(Minion *minion);

        // set_attack(a): sets the minion's attack to int a
        void set_attack(int a);

        // set_defence(d): sets the minion's defence to d
        void set_defence(int d);

        // set_action(a): sets the minion's attack to a
        void set_action(int a);

        // get_attack(): returns the minion's attack
        int get_attack();

        // get_defence(): returns the minion's defence
        int get_defence();

        // get_action(): return's the minion's action value
        int get_action();

        //void use_Ability(); 
}
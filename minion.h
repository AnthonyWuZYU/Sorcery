#ifndef MINION_H
#define MINION_H
#include "ascii_graphics.h"
#include "card.h"
#include "enchant.h"
#include "player.h"
#include <vector>

class Player;

class Enchant;

class Minion : public Card {
    int attack;
    int defence;
    int action;
    int activate_cost;
    Card *target = nullptr;
    std::string ability;
    std::vector<Card*> minionEnchantments;
    public:
        // Constructor
        Minion(std::string name, int cost, int attack, int defence, int activate_cost, std::string ability);

        // Polymorphic Copy Constructor
        Minion(const Card *other);

        // Deconstructor
        ~Minion();

        //Copy Assignment Operator
        Card* operator=(const Card* other) override;

        //atack(player): Attacks either a minion or player
        int attack_target(Player *player);
        int attack_target(Card *other);

        // set_attack(a): sets the minion's attack to int a
        void set_attack(int a);

        // set_defence(d): sets the minion's defence to d
        void set_defence(int d);

        // set_action(a): sets the minion's attack to a
        void set_action(int a);

        // get_attack(): returns the minion's attack
        int get_attack() const;

        // get_defence(): returns the minion's defence
        int get_defence() const;
        
        void enchant(Enchant *enchantment);
        
        // get_action(): return's the minion's action value
        int get_action() const;

        std::string get_ability() const;
        
        std::vector<Card*> get_enchant() const;
        
        int get_activate_cost() const;

        void set_activate_cost(int activate_cost);
        
        void set_enchant(std::vector<Card*> enchants);

        void print(std::ostream &os) const override;

        // use_ability(player, desc): use the minion's ability based on the desc. Ability gets used on target (if applicable)
        bool use_ability( Player *player);
};
#endif

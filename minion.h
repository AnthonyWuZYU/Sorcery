#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "player.h"
#include <vector>

class Player;

class Minion : public Card {
    int attack;
    int defence;
    int action;
    Card *target = nullptr;
    //vector<Enchantment> minionEnchantments;
    public: 
        // Constructor
        Minion(std::string name, int cost, int attack, int defence, std::string card_type, std::string ability="");

        // Deconstructor
        ~Minion();

        // Copy Constructor
        Minion(const Card &other);

        //Copy Assignment Operator
        Card & operator=(const Card & other) override;


        //destroy(): destroys the card
        void destroy() override;

        //atack(player): Attacks either a minion or player
        void attack_target(Player *player);
        void attack_target(Minion *minion);

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

        // get_action(): return's the minion's action value
        int get_action() const;

        std::ostream& print(std::ostream& os) const override;

        // use_ability(player, desc): use the minion's ability based on the desc. Ability gets used on target (if applicable)
        void use_ability( Player *player, std::string desc, Card *target);
};
#endif


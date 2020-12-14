#ifndef ENCHANT_H
#define ENCHANT_H
#include "ascii_graphics.h"
#include "card.h"
#include "player.h"
#include <vector>

class Player;

class Enchant : public Card {
    int addAtk;
    int addDef;
    int mulAtk;
    int mulDef;
    std::string ability;

    public:
        // Constructor
        Enchant(std::string name, int cost, int addAtk, int addDef, int mulAtk, int mulDef, std::string ability="");

        Enchant(const Card *other);

        // Deconstructor
        ~Enchant();


        //Copy Assignment Operator
        Card * operator=(const Card* other) override;

        int get_addAtk() const;

        int get_addDef() const;

        int get_mulAtk() const;

        int get_mulDef() const;
        std::string get_ability() const;

        //destroy(): destroys the card
        void destroy() override;

        void use_ability();

        void print(std::ostream &os) const override;

};
#endif
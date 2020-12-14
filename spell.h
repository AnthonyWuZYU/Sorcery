#ifndef SPELL_H
#define SPELL_H
#include "card.h"
#include "ascii_graphics.h"
#include "player.h"

class Player;

class Spell : public Card {
    public:
        // Constructor
        Spell(std::string name, int cost, std::string ability="");

        Spell(const Card *other);

        // Deconstructor
        ~Spell();

        //Copy Assignment Operator
        Card & operator=(const Card* other) override;

        void destroy() override;

        void use_ability();

        void print(std::ostream &os) const override;
};
#endif

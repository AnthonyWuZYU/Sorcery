#ifndef SPELL_H
#define SPELL_H
#include "card.h"
#include "ascii_graphics.h"
#include "ritual.h"
#include "player.h"
#include <string>

class Player;
class Ritual;

class Spell : public Card {
        std::string ability;
    public:
        // Constructor
        Spell(std::string name, int cost, std::string ability = "");

        Spell(const Card *other);

        // Deconstructor
        ~Spell();

        //Copy Assignment Operator
        Card * operator=(const Card* other) override;

        std::string get_ability() const;

        bool use_ability( Player *player, std::string desc);

        void print(std::ostream &os) const override;
};
#endif


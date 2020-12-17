#include "minion.h"
#include <algorithm>
#include <iostream>
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, int activate_cost, std::string ability) : Card{name, cost, "Minion"}, attack{attack}, defence{defence}, action{0}, activate_cost{activate_cost}, ability{ability} {}

Minion::~Minion()
{
    delete target;
}

Minion::Minion(const Card *other) : Card{other->get_name(), other->get_cost(), other->get_type()}
{
    const Minion *temp = dynamic_cast<const Minion *>(other);
    attack = temp->get_attack();
    defence = temp->get_defence();
    action = temp->get_action();
    activate_cost = temp->get_activate_cost();
    temp = nullptr;
    delete temp;
}

Card *Minion::operator=(const Card *other)
{
    const Minion *temp = dynamic_cast<const Minion *>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    attack = temp->get_attack();
    defence = temp->get_defence();
    action = temp->get_action();
    activate_cost = temp->get_activate_cost();
    temp = nullptr;
    delete temp;
    return this;
}

int Minion::attack_target(Player *player)
{
    if (action != 0)
    {
        player->setLife(player->getLife() - attack);
    }
    else
    {
        cout << "Minion doesn't have any actions" << endl;
    }

    return player->getLife();
}

int Minion::attack_target(Card *other)
{
    Minion *target = dynamic_cast<Minion *>(other);
    if (action != 0)
    {
        target->set_defence(target->get_defence() - attack);
        defence -= target->get_attack();
    }
    else
    {
        cout << "Minion doesn't have any actions" << endl;
    }

    // Returning the target's defence
    int d = target->get_defence();
    target = nullptr;
    delete target;
    return d;
}

bool Minion::use_ability(Player *player)
{
    bool success = true;
    string description = ability;

    // Minion Abilities : Triggered

    if (description == "Deals damage to all the opponent minions equal to its attack value when it dies")
    {
        Player *op = player->getOpp();
        vector<Card *> oppField = op->getBoard()->get_field();
        Board *oppBoard = op->getBoard();

        int length = oppField.size();

        for (int i = 0; i < length; i++)
        {
            Minion *temp = dynamic_cast<Minion *>(player->getOpp()->getBoard()->get_field().at(i));
            temp->set_defence(temp->get_defence() - attack);
            if (temp->get_defence() <= 0)
            {
                op->is_dead(i, oppBoard);
                i--;
                length--;
            }
            else
            {
                oppField.at(i) = temp;
            }
        }
    }
    else if (description == "Whenever an opponent's minion enters play, deal 1 damage to it")
    {
        Player *op = player->getOpp();
        Board *oppBoard = op->getBoard();
        vector<Card *> oppField = oppBoard->get_field();

        Minion *temp = dynamic_cast<Minion *>(oppField.back());
        temp->set_defence(temp->get_defence() - 1);
        oppField.pop_back();
        oppField.emplace_back(temp);
        oppBoard->set_field(oppField);
        op->setBoard(oppBoard);
        player->setOpp(op);
        player->is_dead(oppBoard->get_field().size() - 1, player->getOpp()->getBoard());
    }
    else if (description == "At the end of your turn, all your minions gain +0/+1")
    {
        vector<Card *> field = player->getBoard()->get_field();
        int length = field.size();

        for (int i = 0; i < length; i++)
        {
            Minion *temp = dynamic_cast<Minion *>(field.at(i));
            temp->set_defence(temp->get_defence() + 1);
            field.at(i) = temp;
        }

        Board *temp = player->getBoard();
        temp->set_field(field);

        player->setBoard(temp);
    }
    // Minion Abilities : Activated
    else if (description == "Deal 1 damage to target minion")
    {
        int t;
        cin >> t;
        Player *op = player->getOpp();
        vector<Card *> oppField = op->getBoard()->get_field();
        int length = oppField.size();
        if (length >= t)
        {
            Minion *temp = dynamic_cast<Minion *>(oppField.at(t - 1));
            temp->set_defence(temp->get_defence() - 1);
            op->is_dead(t - 1, op->getBoard());
        }
        else
        {
            cout << "Wrong Index." << endl;
            success = false;
        }
    }
    else if (description == "Summon a 1/1 air elemental")
    {
        vector<Card *> field = player->getBoard()->get_field();

        unsigned int length = field.size();

        if (length < 5)
        {
            Card *summon = new Minion("Air Elemental", 0, 1, 1, 0, "");
            player->getBoard()->add_to_field(player, summon);
            summon = nullptr;
            delete summon;
            Board *temp = player->getBoard();
            temp->set_field(field);

            player->setBoard(temp);
        }

        else
        {
            cout << "Field already full with 5 minions" << endl;
            success = false;
        }
    }
    else if (description == "Summon up to three 1/1 air elementals")
    {
        vector<Card *> field = player->getBoard()->get_field();

        unsigned int length = field.size();
        if (length < 3)
        {
            for (int i = 0; i < 3; i++)
            {
                Card *summon = new Minion("Air Elemental", 0, 1, 1, 0, "");
                player->getBoard()->add_to_field(player, summon);
                summon = nullptr;
                delete summon;
            }
        }
        else if (length < 4)
        {
            for (int i = 0; i < 2; i++)
            {
                Card *summon = new Minion("Air Elemental", 0, 1, 1, 0, "");
                player->getBoard()->add_to_field(player, summon);
                summon = nullptr;
                delete summon;
            }
        }
        else if (length < 5)
        {
            Card *summon = new Minion("Air Elemental", 0, 1, 1, 0, "");
            player->getBoard()->add_to_field(player, summon);
            summon = nullptr;
            delete summon;
        }
        else
        {
            cout << "Field already full with enough minions." << endl;
            success = false;
        }

        //Board *temp = player->getBoard();
        //temp->set_field(field);

        //player->setBoard(temp);
    }
    if (success)
    {
        if (player->getMagic() - activate_cost < 0)
        {
            player->setMagic(0);
        }
        else
        {
            player->setMagic(player->getMagic() - activate_cost);
        }
    }
    return success;
}

void Minion::set_attack(int a) { attack = a; }

void Minion::set_defence(int d) { defence = d; }

void Minion::set_action(int a) { action = a; }

int Minion::get_attack() const { return attack; }

int Minion::get_defence() const { return defence; }

void Minion::print(std::ostream &os) const
{
    std::vector<std::string> card_template_t;
    if (ability == "")
    {
        card_template_t = display_minion_no_ability(this->get_name(), this->get_cost(), this->get_attack(), this->get_defence());
    }
    else if (activate_cost == 0)
    {
        card_template_t = display_minion_triggered_ability(this->get_name(), this->get_cost(),
                                                           this->get_attack(), this->get_defence(), this->get_ability());
    }
    else
    {
        card_template_t = display_minion_activated_ability(this->get_name(), this->get_cost(),
                                                           this->get_attack(), this->get_defence(), this->get_activate_cost(), this->get_ability());
    }

    for (auto it : card_template_t)
    {
        os << it << endl;
    }
}

int Minion::get_action() const { return action; }

std::string Minion::get_ability() const { return ability; }

void Minion::enchant(Enchant *enchantment)
{
    minionEnchantments.emplace_back(enchantment);
    attack = (attack + enchantment->get_addAtk()) * enchantment->get_mulAtk();
    defence = (defence + enchantment->get_addDef()) * enchantment->get_mulDef();

    if (enchantment->get_name() == "Magic Fatigue")
    {
        activate_cost += 2;
    }
}

std::vector<Card *> Minion::get_enchant() const
{
    return minionEnchantments;
}

void Minion::set_enchant(std::vector<Card *> enchants)
{
    minionEnchantments = enchants;
}

int Minion::get_activate_cost() const { return activate_cost; }

void Minion::set_activate_cost(int c) { activate_cost = c; }

#include "spell.h"

using namespace std;

Spell::Spell(string name, int cost, string ability) : Card{name, cost, "Spell"}, ability{ability} {}

Spell::Spell(const Card *other) : Card{other->get_name(), other->get_cost(), other->get_type()} {}

Spell::~Spell() {}

bool Spell::use_ability(Player *player, std::string description)
{
    bool success = true;

    if (description == "Destroy target minion or ritual")
    {
        int p;
        string t;

        cin >> p;
        cin >> t;

        if (p == 1)
        {
            Board *board = player->getBoard();

            if (t == "r")
            {
                Card *ritual = board->get_ritual();
                board->set_ritual(nullptr);

                board->destroy(ritual);
            }
            else
            {
                int index = stoi(t) - 1;
                Card *minion = board->get_card_field(index);
                board->remove_from_field(index);

                board->destroy(minion);
            }

            player->setBoard(board);
            player->setMagic(player->getMagic() - 2);
        }
        if (p == 2)
        {
            Player *op = player->getOpp();
            Board *oppBoard = op->getBoard();

            if (t == "r")
            {
                Card *ritual = oppBoard->get_ritual();
                oppBoard->set_ritual(nullptr);

                oppBoard->destroy(ritual);
            }
            else
            {
                int index = stoi(t) - 1;
                Card *minion = oppBoard->get_card_field(index);
                oppBoard->remove_from_field(index);

                oppBoard->destroy(minion);
            }
            op->setBoard(oppBoard);
            player->setOpp(op);

            player->setMagic(player->getMagic() - 2);
        }
        else
        {
            success = false;
        }
    }
    else if (description == "Return target minion to its owner's hand")
    {
        int p;
        int t;
        cin >> p;
        cin >> t;

        t--;
        if (p == 1)
        {
            Board *board = player->getBoard();

            vector<Card *> oppField = board->get_field();
            int length = oppField.size();
            if (length > t)
            {

                if (board->get_hand()->getSize() == 5)
                {
                    board->destroy(board->remove_from_field(t));
                    cout << "Your Hand is already full. The Card was destroyed." << endl;
                }
                else
                {
                    board->add_to_hand(board->remove_from_field(t));
                    player->setBoard(board);
                    player->setMagic(player->getMagic() - 1);
                }
            }
            else
            {
                cout << "Wrong Index." << endl;
                success = false;
            }
        }

        else if (p == 2)
        {
            Player *op = player->getOpp();
            Board *oppBoard = op->getBoard();

            vector<Card *> oppField = oppBoard->get_field();
            int length = oppField.size();
            if (length > t)
            {
                if (oppBoard->get_hand()->getSize() == 5)
                {
                    oppBoard->destroy(oppBoard->remove_from_field(t));
                    cout << "Opponent's Hand already full. The Card was destroyed." << endl;
                }
                else
                {
                    oppBoard->add_to_hand(oppBoard->remove_from_field(t));
                    op->setBoard(oppBoard);
                    player->setOpp(op);
                    player->setMagic(player->getMagic() - 1);
                }
            }
            else
            {
                cout << "Wrong Index." << endl;
                success = false;
            }
        }
        else
        {
            success = false;
        }
    }
    else if (description == "Your ritual gains 3 charges")
    {
        Board *board = player->getBoard();
        if (board->get_ritual() == nullptr)
        {
            cout << "No ritual to charge." << endl;
            success = false;
        }
        else
        {
            Card *temp = board->get_ritual();
            Ritual *ritual = dynamic_cast<Ritual *>(temp);

            ritual->setCharges(ritual->getCharges() + 3);
            board->set_ritual(ritual);

            player->setBoard(board);
            player->setMagic(player->getMagic() - 1);
        }
    }
    else if (description == "Destroy the top enchant on target minion")
    {
        int p;
        int t;
        cin >> p;
        cin >> t;

        t--;
        if (p == 1)
        {
            Board *board = player->getBoard();
            vector<Card *> field = board->get_field();
            int length = board->get_field().size();
            if (length > t && t >= 0)
            {
                Minion *target = dynamic_cast<Minion *>(field.at(t));
                vector<Card *> enchantments = target->get_enchant();
                if (!enchantments.empty())
                {
                    Card *temp = enchantments.back();

                    Enchant *enchantment = dynamic_cast<Enchant *>(temp);

                    target->set_attack(target->get_attack() / enchantment->get_mulAtk() - enchantment->get_addAtk());
                    target->set_defence(target->get_defence() / enchantment->get_mulDef() - enchantment->get_addDef());
                    if (enchantment->get_name() == "Magic Fatigue")
                    {
                        target->set_activate_cost(target->get_activate_cost() - 2);
                    }
                    enchantments.pop_back();
                    board->destroy(temp);

                    target->set_enchant(enchantments);
                    field.at(t) = target;
                    board->set_field(field);
                    player->setBoard(board);

                    player->is_dead(t, player->getBoard());

                    player->setMagic(player->getMagic() - 1);
                }
                else
                {
                    cout << "No Enchantment to destroy." << endl;
                    success = false;
                }
            }
            else
            {
                cout << "Wrong Index." << endl;
                success = false;
            }
        }
        else if (p == 2)
        {
            Player *op = player->getOpp();
            Board *board = op->getBoard();
            vector<Card *> field = board->get_field();
            int length = board->get_field().size();
            if (length > t && t >= 0)
            {
                Minion *target = dynamic_cast<Minion *>(field.at(t));
                vector<Card *> enchantments = target->get_enchant();
                if (!enchantments.empty())
                {
                    Card *temp = enchantments.back();

                    Enchant *enchantment = dynamic_cast<Enchant *>(temp);

                    target->set_attack(target->get_attack() / enchantment->get_mulAtk() - enchantment->get_addAtk());
                    target->set_defence(target->get_defence() / enchantment->get_mulDef() - enchantment->get_addDef());

                    if (enchantment->get_name() == "Magic Fatigue")
                    {
                        target->set_activate_cost(target->get_activate_cost() - 2);
                    }
                    enchantments.pop_back();
                    board->destroy(temp);

                    target->set_enchant(enchantments);
                    field.at(t) = target;
                    board->set_field(field);
                    op->setBoard(board);
                    player->setOpp(op);

                    player->getOpp()->is_dead(t, player->getOpp()->getBoard());

                    player->setMagic(player->getMagic() - 1);
                }
                else
                {
                    cout << "No Enchantment to destroy." << endl;
                    success = false;
                }
            }
            else
            {
                cout << "Wrong Index." << endl;
                success = false;
            }
        }
        else
        {
            success = false;
        }
    }
    else if (description == "Resurrect the top minion in your graveyard and set its defence to 1")
    {
        Board *board = player->getBoard();

        if (board->get_graveyard()->getSize() == 0)
        {
            cout << "Nothing to resurrect. Graveyard is empty." << endl;
            success = false;
        }

        else
        {
            Card *temp = board->remove_from_graveyard();

            if (board->get_field().size() == 5)
            {
                cout << "Spell failed. Field already full." << endl;
            }

            else
            {
                Minion *alive = dynamic_cast<Minion *>(temp);
                alive->set_defence(1);

                board->add_to_field(player, alive);

                player->setBoard(board);
                player->setMagic(player->getMagic() - 1);
            }
        }
    }
    else if (description == "Deal 2 damage to all minions")
    {
        Player *op = player->getOpp();
        Board *oppBoard = op->getBoard();
        vector<Card *> oppField = oppBoard->get_field();

        Board *board = player->getBoard();
        vector<Card *> field = board->get_field();

        int length_op = oppField.size();

        for (int i = 0; i < length_op; i++)
        {
            Minion *temp = dynamic_cast<Minion *>(player->getOpp()->getBoard()->get_field().at(i));
            temp->set_defence(temp->get_defence() - 2);
            if (temp->get_defence() <= 0)
            {
                op->is_dead(i, oppBoard);
		i--;
		length_op--;
            }
            else
            {
                oppField.at(i) = temp;
            }
        }
	int length = field.size();
        for (int i = 0; i < length; i++)
        {
            Minion *temp = dynamic_cast<Minion *>(player->getBoard()->get_field().at(i));
            temp->set_defence(temp->get_defence() - 2);
            if (temp->get_defence() <= 0)
            {
                player->is_dead(i, board);
		i--;
		length--;
            }
            else
            {
                field.at(i) = temp;
            }
        }


        player->setMagic(player->getMagic() - 3);
    }

    return success;
}

void Spell::print(std::ostream &os) const
{
    std::vector<std::string> card_template_t = display_spell(this->get_name(), this->get_cost(), this->get_ability());
    for (auto it : card_template_t)
    {
        os << it << endl;
    }
}

Card *Spell::operator=(const Card *other)
{
    const Spell *temp = dynamic_cast<const Spell *>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    ability = temp->get_ability();
    return this;
}

string Spell::get_ability() const
{
    return ability;
}


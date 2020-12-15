#include "hand.h"
using namespace std;

int Hand::getSize() const{
    return cards.size();
}

vector<Card*> Hand::getHand() const{
    return cards;
}

Card* Hand::getCard( unsigned int i ) const{
    return cards.at(i);
}

void Hand::add( Card* card ){
    cards.emplace_back(card);
}

void Hand::remove( unsigned int i ) {
    if (i < cards.size()) {
    	cards.erase( cards.begin() + i);
    } else {
    	cerr << "There is no card in the position" << endl;
    }
}

std::ostream& operator<<(std::ostream &os, const Hand &hand) {
    vector<vector<string>> to_print;
    for (auto it : hand.getHand()) {
        if (it->get_type() == "Minion") {
            Minion *temp = dynamic_cast<Minion *>(it);
            string ability = temp->get_ability();
            int activate_cost = temp->get_activate_cost();
            if (ability == "") {
                to_print.emplace_back(display_minion_no_ability(temp->get_name(),temp->get_cost(),temp->get_attack(),temp->get_defence()));
            } else if (activate_cost == 0) {
                to_print.emplace_back(display_minion_triggered_ability(temp->get_name(),temp->get_cost(),
                                          temp->get_attack(),temp->get_defence(), temp->get_ability()));

            } else {
                to_print.emplace_back(display_minion_activated_ability(temp->get_name(),temp->get_cost(),
                                          temp->get_attack(),temp->get_defence(), temp->get_activate_cost(), temp->get_ability()));
            }
            temp = nullptr;
            delete temp;
        } else if (it->get_type() == "Enchant") {
            Enchant *temp = dynamic_cast<Enchant *>(it);
            if (temp->get_ability() == " ") {
                string atk,def;
                if (temp->get_addAtk() > 0) {
                        atk = "+";
                        atk += to_string(temp->get_addAtk());
                } else if (temp->get_addAtk() < 0) {
                        atk = to_string(temp->get_addAtk());
                } else {
                        atk = "*";
                        atk += to_string(temp->get_mulAtk());
                }
                if (temp->get_addDef() > 0) {
                        def = "+";
                        def += to_string(temp->get_addDef());
                } else if (temp->get_addDef() < 0) {
                        def = to_string(temp->get_addDef());
                } else {
                        def = "*";
                        def += to_string(temp->get_mulDef()); 
                }
                to_print.emplace_back(display_enchantment_attack_defence(temp->get_name(),temp->get_cost(),temp->get_ability(), atk, def));
            } else {
                to_print.emplace_back(display_enchantment(temp->get_name(),temp->get_cost(),temp->get_ability()));
            }
            temp = nullptr;
            delete temp;
        } else if (it->get_type() == "Ritual") {
            Ritual *temp = dynamic_cast<Ritual *>(it);
            to_print.emplace_back(display_ritual(temp->get_name(), temp->get_cost(), temp->getActivationCost(), temp->get_ability(), temp->getCharges()));
            temp = nullptr;
            delete temp;
        } else if (it->get_type() == "Spell") {
            Spell *temp = dynamic_cast<Spell *>(it);
            to_print.emplace_back(display_spell(temp->get_name(), temp->get_cost(), temp->get_ability()));
            temp = nullptr;
            delete temp;
        }
    }

    for (int i = 0; i < 11; i++) {
        for (auto it: to_print) {
            os << it[i];
        }
        os << endl;
    }

    return os;
}

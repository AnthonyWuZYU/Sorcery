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

void Hand::remove( unsigned int i ){
    cards.erase( cards.begin() + i);
}

std::ostream& operator<<(std::ostream &os, const Hand &hand) {
    vector<vector<string>> to_print;
    for (auto it : hand.getHand()) {
        if (it->get_type() == "Minion") {
            Minion *temp = dynamic_cast<Minion *>(it);
            string ability = temp->get_ability();
            if (ability == "") {
                to_print.emplace_back(display_minion_no_ability(temp->get_name(),temp->get_cost(),temp->get_attack(),temp->get_defence()));
            } 
            temp = nullptr;
            delete temp;
        } else if (it->get_type() == "Enchant") {
            Enchant *temp = dynamic_cast<Enchant *>(it);
            to_print.emplace_back(display_enchantment(temp->get_name(),temp->get_cost(),temp->get_ability()));
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

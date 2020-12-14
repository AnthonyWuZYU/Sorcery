#include "spell.h"
using namespace std;


Spell::Spell(string name, int cost, string ability): ability{ability}, Card{name, cost, "Spell"}
{}

Spell::Spell(const Card* other) : Card{other->get_name(), other->get_cost(), other->get_type()} {
        const Spell* temp = dynamic_cast<const Spell*>(other);
        ability = temp->get_ability();
}

Spell::~Spell() {

}

Card * Spell::operator=(const Card* other)  {
    const Spell* temp = dynamic_cast<const Spell*>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    ability = temp->get_ability();
    return this;
}

void Spell::destroy() {

}

void Spell::print(std::ostream& os) const {
    std::vector<std::string> card_template_t = display_spell(this->get_name(),this->get_cost(), this->get_ability());
    for (auto it: card_template_t) {
        os << it << endl;
    }
}

string Spell::get_ability() const {
        return ability;
}

void Spell::use_ability() {
}

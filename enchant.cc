#include "enchant.h"
using namespace std;


Enchant::Enchant(string name, int cost, int addAtk, int addDef, int mulAtk, int mulDef, string ability):
        Card{name, cost, "Enchant"}, addAtk{addAtk}, addDef{addDef}, mulAtk{mulAtk}, mulDef{mulDef}, ability{ability}
{}

Enchant::Enchant(const Card* other) : Card{other->get_name(), other->get_cost(), other->get_type()} {
        const Enchant* temp = dynamic_cast<const Enchant*>(other);
        addAtk = temp->get_addAtk();
        addDef = temp->get_addDef();
        mulAtk = temp->get_mulAtk();
        mulDef = temp->get_mulDef();
        ability = temp->get_ability();
}

Enchant::~Enchant() {

}

Card * Enchant::operator=(const Card* other)  {
        const Enchant* temp = dynamic_cast<const Enchant*>(other);
        this->set_name(temp->get_name());
        this->set_cost(temp->get_cost());
        addAtk = temp->get_addAtk();
        addDef = temp->get_addDef();
        mulAtk = temp->get_mulAtk();
        mulDef = temp->get_mulDef();
        ability = temp->get_ability();
        return this;
}       

int Enchant::get_addAtk() const {
        return this->addAtk;
}
    
    
int Enchant::get_addDef() const { 
        return this->addDef; 
}   
    
int Enchant::get_mulAtk() const {
        return this->mulAtk;
}
int Enchant::get_mulDef() const {
        return this->mulDef;
}

string Enchant::get_ability() const {
        return this->ability;
}

void Enchant::use_ability() {
}

void Enchant::print(std::ostream& os) const {
	
	std::vector<std::string> card_template_t = display_enchantment(this->get_name(),this->get_cost(), this->get_ability());
	for (auto it: card_template_t) {
        	os << it << endl;
    	}
}

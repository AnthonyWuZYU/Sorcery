#include "ritual.h"
using namespace std;

Ritual::Ritual( std::string name, int cost, int activation_cost, int charges, std::string card_type, std::string ability ) :
activation_cost{activation_cost}, charges{charges}, ability{ability}, Card{name, cost, "Ritual"} {}

Ritual::~Ritual() {}

Ritual::Ritual(const Card* other) : Card{other->get_name(), other->get_cost(), other->get_type()} {
 const Ritual* temp = dynamic_cast<const Ritual*>(other);
 activation_cost = temp->getActivationCost();
 charges = temp->getCharges();
}

int Ritual::getActivationCost() const{
    return activation_cost;
}

int Ritual::getCharges() const{
    return charges;
}

void Ritual::setCharges( int a ){
    charges = a;
}

void Ritual::use_ability( Player *player, std::string description, Card *target ){
        if (description == "At the start of your turn, gain 1 magic") {
            player->setMagic(player->getMagic() + 1);
            
            charges -= 1;  
        } 
        else if (description == "1 | Whenever a minion enters play under your control, it gains +1/+1") {
            //do something
        }
        else if (description == "Whenever a minion enters play, destroy it") {
            //do something
        }
}

std::string Ritual::get_ability() {
    return ability;
}

void Ritual::destroy() {

}

Card * Ritual::operator=(const Card* other) {

}

void Ritual::print(std::ostream &os) const {

}


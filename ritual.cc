#include "ritual.h"
using namespace std;

Ritual::Ritual( std::string name, int cost, int activation_cost, int charges, std::string ability ) :
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

string Ritual::get_ability() const {
    return ability;
}

void Ritual::use_ability( Player *player, std::string description, Card *target ){
        if (description == "At the start of your turn, gain 1 magic") {
            player->setMagic(player->getMagic() + 1);
            
            charges -= 1;  
        } 
        else if (description == "Whenever a minion enters play under your control, it gains +1/+1") {
        Board *board = player->getBoard();
        vector<Card*> field = board->get_field();
        int length = field.size();

        Minion *temp = new Minion(field.back());
        temp->set_defence( temp->get_defence() + 1 );
        temp->set_attack( temp->get_attack() + 1 );
        field.back() = temp;
        delete temp;

        board->set_field( field );
        player->setBoard( board );
        player->setMagic( player->getMagic() - 1);
        }
        else if (description == "Whenever a minion enters play, destroy it") {
            //do something
        }
}

Card * Ritual::operator=(const Card* other) {
    const Ritual* temp = dynamic_cast<const Ritual*>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    activation_cost = temp->getActivationCost();
    charges = temp->getCharges();
    return this;
}

void Ritual::print(std::ostream &os) const {
        std::vector<std::string> card_template_t = display_ritual(this->get_name(),this->get_cost(), this->getActivationCost(), this->get_ability(), this->getCharges());
        for (auto it: card_template_t) {
                os << it << endl;
        }
}

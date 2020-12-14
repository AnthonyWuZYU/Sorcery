#include "minion.h"
#include <algorithm>
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, std::string card_type, std::string ability) : 
attack{attack}, defence{defence}, action{0}, Card{name, cost, card_type} {}

Minion::~Minion(){
    delete target;
}

Minion::Minion(const Card* other) : Card{other->get_name(), other->get_cost(), other->get_type()} {
 const Minion* temp = dynamic_cast<const Minion*>(other);
 attack = temp->get_attack();
 defence = temp->get_defence();
 action = temp->get_action();
}

Card & Minion::operator=(const Card* other)  {
    const Minion* temp = dynamic_cast<const Minion*>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    defence = temp->get_defence();
    action = temp->get_action();
    return *this;
}


void Minion::attack_target(Player *player) {
    player->setLife(player->getLife() - attack);

    if (player->getLife() <= 0) {
        //Player loses
    }
}

void Minion::attack_target(Minion *target) {
    target->set_defence(target->get_defence() - attack);
    this->set_defence(this->get_defence() - target->get_attack());

    // Check if target is dead
    if (target->get_defence() <= 0) {
        // target dies
    }
}

void Minion::use_ability(Player *player, string description, Card *target) {
    // Minion Abilities : Triggered
    /*
    if (description == "Deals damage to all the opponent minions equal to its attack value when it dies") {
        Player *op = player->getOpp();
        vector<Card> oppField = op->getBoard()->get_field();

        for ( int i = 0; i < oppField.size(); i++ ){
            if( oppField.at(i).get_type() == "Minion"){
            Minion temp = Minion(oppField.at(i));    
            temp.set_defence(temp.get_defence() - attack);
            }
        }

        Board *temp = op->getBoard();
        temp->set_field(oppField);

        op->setBoard( temp );
        player->setOpp( op );

    } else if (description == "Whenever an opponent's minion enters play, deal 1 damage to it") {
        // do something

    } else if (description == "At the end of your turn, all your minions gain +0/+1") {
        vector<Card> field = player->getBoard()->get_field();

        for( int i = 0; i < field.size(); i++ ){

            if(field.at(i).get_type() == "Minion"){
            Minion temp = Minion(field.at(i));    
            temp.set_defence( temp.get_defence() + 1 );
            }
        }

        Board *temp = player->getBoard();
        temp->set_field( field );

        player->setBoard( temp );
    } 
        // Minion Abilities : Activated
    else if (description == "1 | Deal 1 damage to target minion") {
        Player *op = player->getOpp();
        vector<Card> oppField = op->getBoard()->get_field();
        int length = oppField.size();

        for( int i = 0; i < length; i++ ){
            if( oppField.at(i) == *target ){
                if( oppField.at(i).get_type() == "Minion"){
                Minion temp = Minion(oppField.at(i));
                Minion *tempp = dynamic_cast<Minion*> (target);    
                temp.set_defence( tempp->get_defence() - 1 );
                }
            }
        }
        Board *temp = op->getBoard();
        temp->set_field(oppField);

        op->setBoard( temp );
        player->setOpp( op );
        
        player->setMagic( player->getMagic() -1 );

    } else if (description == "Summon a 1/1 air elemental") {
        Card summon = Minion("Air Elemental", 0, 1, 1, "");
        vector<Card>  field = player->getBoard()->get_field();

        if( field.size() < 5 ){
            field.emplace_back(summon);
        }

        Board *temp = player->getBoard();
        temp->set_field( field );

        player->setBoard( temp );
        player->setMagic( player->getMagic() - 1 );

    } else if (description == "Summon up to three 1/1 air elementals") {
        vector<Card> field = player->getBoard()->get_field();

        int length = field.size();
        Card summon = Minion("Air Elemental", 0, 1, 1, "");

        if( length < 3 ){
            for(int i = 0; i < 3; i++){
            field.emplace_back( summon );
            }
        }
        else if( length < 4 ){
            for(int i = 0; i < 2; i++){
            field.emplace_back( summon );
            }           
        }
        else if( length < 5 ){
            field.emplace_back( summon );
        }
        else{
            cout << "Field already full with 5 minions." << endl;
        }

        Board *temp = player->getBoard();
        temp->set_field( field );

        player->setBoard( temp );
        player->setMagic( player->getMagic() - 2 );
    }
    */
}

void Minion::print(std::ostream& os) const {
    std::vector<std::string> card_template_t = display_minion_no_ability(this->get_name(),this->get_cost(), attack, defence);
    for (auto it: card_template_t) {
        os << it << endl;
    }
}

void Minion::destroy() {}

void Minion::set_attack(int a) {attack = a;}

void Minion::set_defence(int d) {defence = d;}

void Minion::set_action(int a) {action = a;}

int Minion::get_attack() const {return attack;}

int Minion::get_defence() const {return defence;}

int Minion::get_action() const {return action;}


#include "minion.h"
#include <algorithm>
#include <iostream>
using namespace std;

Minion::Minion(std::string name, int cost, int attack, int defence, int activate_cost, std::string ability) : 
attack{attack}, defence{defence}, action{0}, activate_cost{activate_cost}, ability{ability}, Card{name, cost, "Minion"} {}

Minion::~Minion(){
    delete target;
}

Minion::Minion(const Card* other) : Card{other->get_name(), other->get_cost(), other->get_type()} {
    const Minion* temp = dynamic_cast<const Minion*>(other);
    attack = temp->get_attack();
    defence = temp->get_defence();
    action = temp->get_action();
    activate_cost = temp->get_activate_cost();
    temp = nullptr;
    delete temp;
}

Card* Minion::operator=(const Card* other)  {
    const Minion* temp = dynamic_cast<const Minion*>(other);
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


int Minion::attack_target(Player *player) {
    if (action != 0) {
        player->setLife(player->getLife() - attack);
    } else {
        cout << "Minion doesn't have any actions" << endl;
    }

    return player->getLife();
}

int Minion::attack_target(Card *other) {
    Minion *target = dynamic_cast<Minion *>(other);
    if (action != 0) {
        target->set_defence(target->get_defence() - attack);
        defence -= target->get_attack();
    } else {
        cout << "Minion doesn't have any actions" << endl;
    }

    // Returning the target's defence
    int d = target->get_defence();
    target = nullptr;
    delete target;
    return d;
}

void Minion::use_ability(Player *player, string description, Card *target) {
    // Minion Abilities : Triggered
    
    if (description == "Deals damage to all the opponent minions equal to its attack value when it dies") {
        Player *op = player->getOpp();
        vector<Card*> oppField = op->getBoard()->get_field();

        for ( int i = 0; i < oppField.size(); i++ ){
            if( oppField.at(i)->get_type() == "Minion"){
            Minion *temp = new Minion(oppField.at(i));    
            temp->set_defence(temp->get_defence() - attack);
            oppField.at(i) = temp;
            delete temp;
            }
        }

        Board *temp = op->getBoard();
        temp->set_field(oppField);

        op->setBoard( temp );
        player->setOpp( op );

    } else if (description == "Whenever an opponent's minion enters play, deal 1 damage to it") {
        Player *op = player->getOpp();
        Board *oppBoard = op->getBoard();
        vector<Card*> oppField = oppBoard->get_field();
        int length = oppField.size();

        Minion *temp = new Minion(oppField.back());
        temp->set_defence( temp->get_defence() - 1 );
        oppField.back() = temp;
        delete temp;

        oppBoard->set_field( oppField );
        op->setBoard( oppBoard );
        player->setOpp( op );       
    }    
        else if (description == "At the end of your turn, all your minions gain +0/+1") {
        vector<Card*> field = player->getBoard()->get_field();

        for( int i = 0; i < field.size(); i++ ){

            if(field.at(i)->get_type() == "Minion"){
            Minion *temp = new Minion(field.at(i));    
            temp->set_defence( temp->get_defence() + 1 );
            field.at(i) = temp;
            delete temp;
            }
        }

        Board *temp = player->getBoard();
        temp->set_field( field );

        player->setBoard( temp );
    } 
        // Minion Abilities : Activated
    else if (description == "1 | Deal 1 damage to target minion") {
        Player *op = player->getOpp();
        vector<Card*> oppField = op->getBoard()->get_field();
        int length = oppField.size();

        for( int i = 0; i < length; i++ ){
            if( oppField.at(i) == target ){
                if( oppField.at(i)->get_type() == "Minion"){
                Minion *temp = new Minion(oppField.at(i));
                Minion *tempp = dynamic_cast<Minion*> (target);    
                temp->set_defence( tempp->get_defence() - 1 );
                oppField.at(i) = temp;
                delete temp;
                }
            }
        }
        Board *temp = op->getBoard();
        temp->set_field(oppField);

        op->setBoard( temp );
        player->setOpp( op );
        
        player->setMagic( player->getMagic() -1 );

    } else if (description == "Summon a 1/1 air elemental") {
        Card *summon = new Minion("Air Elemental", 0, 1, 1, 0);
        vector<Card*>  field = player->getBoard()->get_field();

        unsigned int length = field.size();

        if( length < 5 ){
            field.emplace_back(summon);
        }

        Board *temp = player->getBoard();
        temp->set_field( field );

        player->setBoard( temp );
        player->setMagic( player->getMagic() - 1 );

    } else if (description == "Summon up to three 1/1 air elementals") {
        Card *summon = new Minion("Air Elemental", 0, 1, 1, 0);
        vector<Card*> field = player->getBoard()->get_field();

        unsigned int length = field.size();

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
    
}

void Minion::print(std::ostream& os) const {
    std::vector<std::string> card_template_t = display_minion_no_ability(this->get_name(),this->get_cost(), attack, defence);
    for (auto it: card_template_t) {
        os << it << endl;
    }
}

void Minion::set_attack(int a) {attack = a;}

void Minion::set_defence(int d) {defence = d;}

void Minion::set_action(int a) {action = a;}

int Minion::get_attack() const {
        int atk = this->attack;
        for (auto it: minionEnchantments) {
                Enchant* enchant = dynamic_cast<Enchant *>(it);
		atk = (atk + enchant->get_addAtk() ) * enchant->get_mulAtk();
        }
        return atk;
}

int Minion::get_defence() const {
        int def = this->defence;
        for (auto it: minionEnchantments) {
                Enchant* enchant = dynamic_cast<Enchant *>(it);
		def = (def + enchant->get_addDef() ) * enchant->get_mulDef();
        }
        return def;
}

int Minion::get_action() const {return action;}

std::string Minion::get_ability() const {return ability;}

void Minion::enchant(Enchant *enchantment) {
	minionEnchantments.emplace_back(enchantment);
}

std::vector<Card*> Minion::get_enchant() const {
        return minionEnchantments;
}

void Minion::set_enchant(std::vector<Card*> enchants) {
        minionEnchantments = enchants;
}

int Minion::get_activate_cost() const {return activate_cost;}

void Minion::set_activate_cost(int c) {activate_cost = c;}


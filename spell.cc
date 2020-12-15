#include "spell.h"

using namespace std;

Spell::Spell(string name, int cost, string ability): ability{ability}, Card{name, cost, "Spell"} {}
 
Spell::Spell( const Card* other ): Card{ other->get_name(), other->get_cost(), other->get_type() } {}

Spell::~Spell() {}

bool Spell::use_ability( Player *player, std::string description ) {
bool success = true;

        if (description == "Destroy target minion or ritual") {
            // do something
        } /*else if (description == "Return target minion to its owner's hand") {
            Player *op = player->getOpp();
            Board *oppBoard = op->getBoard();

            vector<Card*> oppField = oppBoard->get_field();

            for( int i = 0; i < oppField.size(); i++ ){
                if( oppField.at(i) == target ){
                    if( oppBoard->get_hand()->getSize() == 5){
                        oppBoard->destroy( oppBoard->remove_from_field(i) );
                        cout << "Opponent's Hand already full. The Card was destroyed." << endl;
                    }
                    else{
                    oppBoard->add_to_hand( oppBoard->remove_from_field( i ) );
                    }
                    break;
                }
            }

            op->setBoard(oppBoard);
            player->setOpp( op );
            player->setMagic( player->getMagic() - 1);

        }*/ else if (description == "Your ritual gains 3 charges") {
            Board* board = player->getBoard();
            Card* temp = board->get_ritual();
            Ritual* ritual = new Ritual( temp );

            ritual->setCharges( ritual->getCharges() + 3 );
            board->set_ritual( ritual );        

            player->setBoard( board );
            player->setMagic( player->getMagic() - 1);
        } else if (description == "Destroy the top enchant on target minion") {
            int p;
            int t;
            cin >> p;
            cin >> t;
            
            if( p == 1 ){
                Board *board = player->getBoard();
                vector<Card *> field = board->get_field();

                Minion *target = dynamic_cast<Minion*> ( field.at(t) );
                vector<Card*> enchantments = target->get_enchant();
                Card *temp = enchantments.back();
                enchantments.pop_back();
                board->destroy( temp );

                target->set_enchant(enchantments);
                field.at(t) = target;
                board->set_field( field );
                player->setBoard( board );

                player->setMagic(player->getMagic() - 1);
            }
            else if( p == 2 ){
                Player *op = player->getOpp();
                Board *board = op->getBoard();
                vector<Card *> field = board->get_field();

                Minion *target = dynamic_cast<Minion*> ( field.at(t) );
                vector<Card*> enchantments = target->get_enchant();
                Card *temp = enchantments.back();
                enchantments.pop_back();
                board->destroy( temp );

                target->set_enchant(enchantments);
                field.at(t) = target;
                board->set_field( field );
                player->setBoard( board );
                player->setOpp( op );   

                player->setMagic(player->getMagic() - 1);
            }
            else{
                success = false;
            }
            
        } else if (description == "Resurrect the top minion in your graveyard and set its defence to 1") {
            Board *board = player->getBoard();
            Card *temp = board->remove_from_graveyard();

            Minion *alive = new Minion( temp );
            alive->set_defence( 1 );
            board->add_to_field( alive );

            player->setBoard( board );
            player->setMagic( player->getMagic() - 1);

        } else if (description == "Deal 2 damage to all minions") {
            Player *op = player->getOpp();
            Board *oppBoard =  op->getBoard();
            vector<Card*> oppField = oppBoard->get_field();

        for ( int i = 0; i < oppField.size(); i++ ){
            if( oppField.at(i)->get_type() == "Minion"){
                Minion *temp = new Minion(oppField.at(i));    
                temp->set_defence(temp->get_defence() - 2);
                oppField.at(i) = temp;
                delete temp;
            }
        }

        oppBoard->set_field( oppField );
        op->setBoard( oppBoard );
        player->setOpp(op);

        player->setMagic( player->getMagic() - 3);
        }

        return success;
}

void Spell::print(std::ostream& os) const {
    std::vector<std::string> card_template_t = display_spell(this->get_name(),this->get_cost(), this->get_ability());
    for (auto it: card_template_t) {
        os << it << endl;
    }
}

Card * Spell::operator=(const Card* other)  {
    const Spell* temp = dynamic_cast<const Spell*>(other);
    this->set_name(temp->get_name());
    this->set_cost(temp->get_cost());
    ability = temp->get_ability();
    return this;
}


string Spell::get_ability() const {
        return ability;
}

void Spell::destroy() {

}

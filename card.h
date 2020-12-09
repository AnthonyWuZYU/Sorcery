#ifndef CARD_H
#define CARD_H
#include <string>


class Card {

    std::string name; // Name of the Card
    int cost; // Magic Cost to use Card
    //Ability ability
    
    public: 
        // Constructor, takes in string Name, int Cost and the name of ability
        // depending on the string ability, we create the associated ability object
        Card(std::string name, int cost);

        // Card deconstructor
        virtual ~Card();

        //Copy Assignment Operator
        virtual Card & operator=(const Card & other);

        //Compare Operator
        bool operator==(Card &other);

        // Equal() returns if the cards are equal
        virtual bool equal(const Card &other);

        //get_Name(): returns the Name of the card
        //get_Name: None -> String
        std::string get_Name();

        //get_Cost(): returns the magic cost of a card
        //get_Cost: None -> Int
        int get_Cost();

        //use_ability(): uses the ability object of the card to perform the ability
        virtual void use_ability();

        //destroy(): destroys the card
        virtual void destroy();
};
#endif
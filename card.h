#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>

// Abstract Class
// Only pointers of Card can be made

class Card {
        std::string name;
        int cost;
        std::string card_type;

    public: 
        // Constructor
        Card(std::string name, int cost, std::string card_type);
        virtual ~Card();
        
        // Get Functions
        std::string get_name() const;
        int get_cost() const;
        std::string get_type() const;

        // Set Functions
        void set_name(std::string name);
        void set_cost(int cost);
        void set_type(std::string card_type);

        // Pure Virtual Functions
        virtual Card * operator=(const Card* other) =0;
        virtual void print(std::ostream &os) const =0;        
};

std::ostream& operator<<(std::ostream &os, const Card &card);
#endif

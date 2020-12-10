#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>

class Deck {
    std::vector<Card> cards; // The Vector that holds all the cards of the deck

    // Temporary Code for Card Database
    std::vector<std::vector<std::string>> minions;

    public:
        // Constructor for Deck. Takes field filename, will be the .deck file to load
        // the cards into the deck.
        Deck(std::string filename);

        // Deconstructor for Deck
        ~Deck();

        // shuffle(): Shuffles the cards in Cards vector
        void shuffle();

        // get_top(): returns the card from the top of deck. Does not remove.
        Card get_top();

        // pop(): returns card from top of deck. Removes card from deck.
        // pop: None -> Card
        Card pop();

        // get_card(name): returns the card that has card.name == name
        // get_card: String -> Card
        Card get_card(std::string name);

        // remove(card): Searches from deck and removes the given card from deck.
        // remove: Card -> None
        void remove(Card card);

        // add(card): Adds inputted card to top of deck
        //add: Card -> None
        void add(std::string cardname);

};

// Loads the minion vector from the minion.csv file
std::vector<std::vector<std::string>> load_data(std::string filename);

// Checks if given str is in the given 2D Vector Data
bool is_in(std::vector<std::vector<std::string>> data, string str);
#endif
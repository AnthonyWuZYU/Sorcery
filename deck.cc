#include "deck.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <stdexcept>

using namespace std;

Deck::Deck(string filename) {
    ifstream infile{ filename };
    string i;

    minions = load_data("minion.csv");

    // Reading the .deck file and adding each card by its name
    while ( true ) {
        infile >> i;
        if ( infile.fail() ) break;
        this->add(i);
    }
}



bool is_in(std::vector<std::vector<std::string>> data, string str) {
    for (auto it = data.begin(); it != data.end(); it++ {
        if (it->at(0) == str) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<std::string>> load_data(std::string filename) {
    std::vector< std::vector< std::string > > data;
    string line = "";
    string temp = "";
    ifstream fin{ filename };

    while (getline(fin, line)) {
        std::vector< std::string > vec;
        stringstream s{line};

        // Parses the line by , and stores the string into the row
        while(getline(s, temp, ',')) {
            vec.emplace_back(temp);
        }

        //adds row to data grid
        data.push_back(vec);
    }
    fin.close();

    return data;
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    for ( int i = 0; i < 1000; i++ ) {
		std::shuffle( cards.begin(), cards.end(), rng );	
	} 
}

Card Deck::get_top() {
    return cards.back();
}

Card Deck::pop() {
    Card temp = cards.back();
    cards.pop_back();
    return temp;
}

void Deck::remove(Card card) {
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if (*it == card) {
            cards.erase(it);
            break;
        }
    }
}

void Deck::add(string cardname) {
    // Check if it is a minion card
    if (is_in(minions, cardname)) {
        
    }
}
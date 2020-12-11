#include "deck.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <sstream>

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

Deck::~Deck() {}

std::vector<std::string> get_info(std::vector<std::vector<std::string>> data, std::string cardname) {
    for (auto it = data.begin(); it != data.end(); it++) {
        if (it->at(0) == cardname) {
            return *it;
        }
    }
    return *data.begin();
}

bool is_in(std::vector<std::vector<std::string>> data, std::string str) {
    for (auto it = data.begin(); it != data.end(); it++) {
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

Card Deck::get_top() const{
    return cards.back();
}

Card Deck::pop() {
    Card temp = cards.back();
    cards.pop_back();
    return temp;
}

void Deck::remove(Card card) {
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if (card == *it) cards.erase(it);
        break;
    }
}

void Deck::add(string cardname) {
    vector<string> info;
    // Check if it is a minion card
    if (is_in(minions, cardname)) {
        info = get_info(minions, cardname);
        // Create the ability
        if (info[4] != "") {
            //Add an activated ability
        } else if (info[5] != "") {
            //Add a triggered ability
        }
        Card temp = Minion{info[0], stoi(info[1]), stoi(info[2]), stoi(info[3])};
        cards.emplace_back(temp);
    }
}

Card Deck::get_card(std::string name) const {
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if (it->get_Name() == name) {
            return *it;
        }
    }
    return *cards.begin();
}

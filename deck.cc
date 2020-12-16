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

Deck::Deck(string filename, bool test) {
    ifstream infile{ filename };
    string i;

    minions = load_data("minion.csv");
    spells = load_data("spells.csv");
    rituals = load_data("rituals.csv");
    enchantments = load_data("enchantments.csv");


    // Reading the .deck file and adding each card by its name
    while ( getline(infile, i) ) {
        this->add(i);
    }
    if (!test) this->shuffle();
}

Deck::~Deck() {
    for (auto& it : cards) {
        delete it;
        it = nullptr;
    }
    cards.erase(std::remove(cards.begin(), cards.end(), nullptr), cards.end());
}

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
        while(getline(s, temp, '|')) {
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

Card* Deck::get_top() const{
    return cards.back();
}

Card* Deck::pop() {
    if (cards.empty()) {
        return nullptr;
    } else {
        Card* temp = cards.back();
        cards.pop_back();
        return temp;
    }
}

void Deck::remove(Card* card) {
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
                string ability = "";
                // Create the ability
                if (info[4] != "") {
                    ability = info[4];
                } else if (info[6] != "") {
                    ability = info[6];
                }
                Card *temp = new Minion{info[0], stoi(info[1]), stoi(info[2]), stoi(info[3]), stoi(info[5]), ability};
                cards.emplace_back(temp);
        } else if (is_in(enchantments, cardname)) {
                info = get_info(enchantments, cardname);
                Card *temp = new Enchant{info[0], stoi(info[1]), stoi(info[2]), stoi(info[3]), stoi(info[4]), stoi(info[5]), info[6]};
                cards.emplace_back(temp);
        } else if (is_in(spells, cardname)) {
                info = get_info(spells, cardname);
                Card *temp = new Spell{info[0], stoi(info[1]), info[2]};
                cards.emplace_back(temp);
        } else if (is_in(rituals, cardname)) {
                info = get_info(rituals, cardname);
                Card *temp = new Ritual{info[0], stoi(info[1]), stoi(info[2]), stoi(info[3]), info[4]};
                cards.emplace_back(temp);
        } else {
        // The card is not of the four types and we should throw an error
                cerr << "Invalid Card in deck" << endl;
        }

}


Card* Deck::get_card(std::string name) const {
    for (auto it : cards) {
        if (it->get_name() == name) {
            return it;
        }
    }
    return nullptr;
}

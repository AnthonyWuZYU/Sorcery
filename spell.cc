#include "spell.h"
using namespace std;


Spell::Spell(string name, int cost, string ability): Card{name, cost, "Spell"}
{}

Spell::~Spell() {

}

void Spell::destroy() {

}

void Spell::use_ability() {
}

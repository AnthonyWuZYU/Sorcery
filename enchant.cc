#include "enchant.h"
using namespace std;


Enchant::Enchant(string name, int cost, int addAtk, int addDef, string ability): addAtk{addAtk}, addDef{addDef}, Card{name, cost}
{}

Enchant::~Enchant() {

}


int Enchant::get_addAtk() {
	return addAtk;
}


int Enchant::get_addDef() {
	return addDef;
}

void Enchant::destroy() {

}

void Enchant::use_ability() {
}

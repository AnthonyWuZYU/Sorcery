#include "ritual.h"
using namespace std;


Ritual::Ritual(string name, int cost, int activate_cost, int charge, string ability): Card{name, cost, "Ritual"}
{}

Ritual::~Ritual() {
}



void Ritual::destroy() {

}

void Ritual::use_ability() {
}

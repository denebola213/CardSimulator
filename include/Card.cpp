#include "Card.hpp"


CardSimulator::Card::~Card(){

}

bool CardSimulator::Card::operator==(const Card &b) {
	return false;
}

void CardSimulator::Card::operator=(const int hoge) {
	number_ = hoge;
}

#include "Card.hpp"


CardSimulator::Card::~Card(){
}
/*void CardSimulator::Card::operator=(const int hoge) {
	number_ = hoge;
}*/

int CardSimulator::Card::getnum() {
	return this->number_;
}

bool CardSimulator::Card::operator<(Card &right) {
	return this->number_ < right.getnum();
}

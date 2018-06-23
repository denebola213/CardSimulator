#include "Deck.hpp"


CardSimulator::Deck::Deck() {
}

CardSimulator::Deck::~Deck(){
}

void CardSimulator::Deck::insert(Card *insert_card){

	this->cards_.emplace_back(std::unique_ptr<Card>(insert_card));
}
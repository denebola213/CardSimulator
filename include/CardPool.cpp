#include "CardPool.hpp"


CardSimulator::CardPool::CardPool() {
}

CardSimulator::CardPool::~CardPool(){
}

void CardSimulator::CardPool::insert(Card *insert_card){

	this->cards_.emplace_back(std::unique_ptr<Card>(insert_card));
}
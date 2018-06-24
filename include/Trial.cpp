#include "Trial.hpp"


CardSimulator::Trial::Trial() {
	this->deck_ = std::unique_ptr<CardPool>(new CardPool());
	this->title_ = "";
	this->numof_picking_ = 0;
	this->cards_total_ = 0;
}

CardSimulator::Trial::~Trial() {
}

void CardSimulator::Trial::SetTitle(std::string title) {
	this->title_ = title;
}

void CardSimulator::Trial::SetNumofPickng(int picking) {
	this->numof_picking_ = picking;
}

void CardSimulator::Trial::SetTotal(int total) {
	this->cards_total_ = total;
}

void CardSimulator::Trial::addCardByMap(const std::map<int, size_t>& cards_map) {
	auto &&cards_map_iterator = cards_map.begin();
	size_t cards_map_size = cards_map.size();
	for (size_t i = 0; i < cards_map_size; i++) {
		for (size_t j = 0; j < cards_map_iterator->second; j++) {
				this->deck_->insert(new Card(cards_map_iterator->first));
		}
		cards_map_iterator++;
	}
}

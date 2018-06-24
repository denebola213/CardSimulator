#include "CardPool.hpp"


CardSimulator::CardPool::CardPool() {
}

CardSimulator::CardPool::~CardPool(){
}

void CardSimulator::CardPool::insert(std::unique_ptr<Card> insert_card){
	this->cards_.emplace_back(std::move(insert_card));
}

void CardSimulator::CardPool::create(const std::map<int, size_t>& cards_map){
	auto &&cards_map_iterator = cards_map.begin();
	size_t cards_map_size = cards_map.size();
	for (size_t i = 0; i < cards_map_size; i++) {
		for (size_t j = 0; j < cards_map_iterator->second; j++) {
				insert(std::unique_ptr<Card>(new Card(cards_map_iterator->first)));
		} 
		cards_map_iterator++;
	}
}

std::unique_ptr<CardSimulator::Card> CardSimulator::CardPool::draw(size_t card_place) {
	std::unique_ptr<CardSimulator::Card> rtn = std::move(this->cards_.at(card_place));
	this->cards_.erase(this->cards_.begin() + card_place);
	this->cards_.shrink_to_fit();

	return std::move(rtn);
}

std::unique_ptr<CardSimulator::Card> CardSimulator::CardPool::pick(size_t card_place){
	std::unique_ptr<Card> rtn(new Card(this->cards_.at(card_place)->getnum()));

	return std::move(rtn);
}

std::unique_ptr<std::map<int, size_t>> CardSimulator::CardPool::count(){
	std::unique_ptr<std::map<int, size_t>> card_pool_map(new std::map<int, size_t>);
	for(auto card = this->cards_.begin(), card_end = this->cards_.end(); card != card_end; card++){
		int this_card_num = card->get()->getnum();
		if(card_pool_map->count(this_card_num) == 0){
			card_pool_map->emplace(this_card_num, 1);
		}
		else{
			size_t numof_this_card = card_pool_map->at(this_card_num) + 1;
			card_pool_map->erase(this_card_num);
			card_pool_map->emplace(this_card_num, numof_this_card);
		}
	}

	return std::move(card_pool_map);
}

size_t CardSimulator::CardPool::size(){
	return this->cards_.size();
}

std::unique_ptr<std::vector<int>> CardSimulator::CardPool::GetCardsNum(){
	std::unique_ptr<std::vector<int>> rtn(new std::vector<int>);
	for(std::unique_ptr<Card>& card : this->cards_) {
		rtn->emplace_back(card->getnum());
	}

	return std::move(rtn);
}

size_t CardSimulator::CardPool::total() {
	size_t total = 0;
	for(auto card = this->cards_.begin(), card_end = this->cards_.end(); card != card_end; card++) {
		total += card->get()->getnum();
	}
	return total;
}
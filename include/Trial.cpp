#include "Trial.hpp"


CardSimulator::Trial::Trial() {
	this->deck_ = std::unique_ptr<CardPool>(new CardPool());
	this->title_ = "";
	this->numof_draw_ = 0;
	this->cards_total_ = 0;
}

void CardSimulator::Trial::SetTitle(std::string title) {
	this->title_ = title;
}

void CardSimulator::Trial::SetNumofDraw(int draw) {
	this->numof_draw_ = draw;
}

void CardSimulator::Trial::SetTotal(int total) {
	this->cards_total_ = total;
}

void CardSimulator::Trial::addCardByMap(const std::map<int, size_t>& cards_map) {
	this->deck_->create(cards_map);
}

std::unique_ptr<std::map<int, size_t>> CardSimulator::Trial::ScrapeDeckToMap(){
	return this->deck_->count();
}

std::string CardSimulator::Trial::GetTitle() {
    return this->title_;
}

size_t CardSimulator::Trial::GetNumofDraw() {
    return this->numof_draw_;
}

size_t CardSimulator::Trial::GetTotal() {
    return this->cards_total_;
}

std::unique_ptr<std::vector<std::unique_ptr<CardSimulator::CardPool>>> CardSimulator::Trial::drow(){
	std::unique_ptr<std::vector<std::unique_ptr<CardPool>>> hands(new std::vector<std::unique_ptr<CardPool>>);
	std::unique_ptr<std::vector<std::vector<size_t>>> drow_list = combination(this->deck_->size(), this->numof_draw_);
	std::set<std::map<int, size_t>> hand_list;
	for(auto list = drow_list->begin(), list_end = drow_list->end(); list != list_end; list++) {
		CardPool a_hand;
		for(auto pick_num = list->begin(), num_end = list->end(); pick_num != num_end; pick_num++) {
			a_hand.insert(this->deck_->pick(*pick_num));
		}
        std::map<int, size_t> a_hand_map = *(a_hand.count());
		if(hand_list.find(a_hand_map) == hand_list.end()) {
			hand_list.emplace(a_hand_map);
		}
	}

	for(auto hand_map : hand_list) {
		std::unique_ptr<CardPool> p_hand(new CardPool);
		p_hand->create(hand_map);
        if(p_hand->total() == this->cards_total_) {
            hands->emplace_back(std::move(p_hand));
        }
	}
	
	return std::move(hands);
}

std::unique_ptr<std::vector<std::vector<size_t>>> CardSimulator::Trial::combination(size_t const n, size_t const r) {
    std::vector<size_t> result;
    std::unique_ptr<std::vector<std::vector<size_t>>> result_list(new std::vector<std::vector<size_t>>);
    
    for(size_t i = 0; i < r; i++) {
        result.emplace_back(i);
    }

    auto result_iterator = result.end() - 1;
    size_t max_val = n;

    result_list->emplace_back(result);
    while(result_iterator != result.begin()) {

        if(result_iterator + 1 == result.end()) {
            max_val = n;
        }
        else {
            max_val = *(result_iterator + 1);
        }

        if(*result_iterator < max_val - 1) {
            *result_iterator = *result_iterator + 1;
            result_list->emplace_back(result);
        }
        else if(*(result_iterator - 1) < *result_iterator - 1) {
            *(result_iterator - 1) = *(result_iterator - 1) + 1;
            *result_iterator = *(result_iterator - 1) + 1;
            while(result_iterator + 1 != result.end() && *result_iterator + 1 < *(result_iterator + 1)) {
                result_iterator++;
                *result_iterator = *(result_iterator - 1) + 1;
            }
            result_list->emplace_back(result);
        }
        else {
            result_iterator--;
        }
    }

    return std::move(result_list);
}

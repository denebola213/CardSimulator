#pragma once
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "Card.hpp"

namespace CardSimulator {
	class CardPool {
		std::vector<std::unique_ptr<Card>> cards_;

	public:
		CardPool();
		~CardPool();

		void insert(std::unique_ptr<Card> insert_card);
		void create(const std::map<int, size_t>& cards_map);
		std::unique_ptr<Card> draw(size_t card_place);
		std::unique_ptr<Card> pick(size_t card_place);
		std::unique_ptr<std::map<int, size_t>> count();
		size_t size();
		std::unique_ptr<std::vector<int>> GetCardsNum();
		size_t total();
	};
}



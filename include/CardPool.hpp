#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Card.hpp"

namespace CardSimulator {
	class CardPool {
		std::vector<std::unique_ptr<Card>> cards_;

	public:
		CardPool();
		~CardPool();

		void insert(Card *insert_card);
	};
}



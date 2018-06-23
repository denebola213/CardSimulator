#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Card.hpp"

namespace CardSimulator {
	class Deck {
		std::vector<std::unique_ptr<Card>> cards_;

	public:
		Deck();
		~Deck();

		void insert(Card *insert_card);
	};
}



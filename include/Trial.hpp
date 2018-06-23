#pragma once
#include <string>
#include <memory>
#include <map>
#include "Deck.hpp"

namespace CardSimulator {
	class Trial {
		std::unique_ptr<Deck> deck_;
		std::string title_;
		size_t numof_picking_;
		size_t cards_total_;

	public:
		Trial(std::string title);
		~Trial();

		void SetTitle(std::string title);
		void SetNumofPickng(int picking);
		void SetTotal(int total);
		void SetDeckForMap(const std::map<int, size_t>& cards_map);
	};
}



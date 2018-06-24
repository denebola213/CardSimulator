#pragma once
#include <string>
#include <memory>
#include <map>
#include <set>

#include "CardPool.hpp"

namespace CardSimulator {
	class Trial {
		std::unique_ptr<CardPool> deck_;
		std::string title_;
		size_t numof_draw_;
		size_t cards_total_;

		std::unique_ptr<std::vector<std::vector<size_t>>> combination(size_t const n, size_t const r);

	public:
		Trial();

		void SetTitle(std::string title);
		void SetNumofDraw(int draw);
		void SetTotal(int total);
		void addCardByMap(const std::map<int, size_t>& cards_map);

		std::string GetTitle();
		size_t GetNumofDraw();
		size_t GetTotal();

		std::unique_ptr<std::map<int, size_t>> ScrapeDeckToMap();
		std::unique_ptr<std::vector<std::unique_ptr<CardPool>>> drow();

		std::string message(){
			return "[" + title_ + "] number of draw: " + std::to_string(numof_draw_) + ". total: " + std::to_string(cards_total_) + ".";
		}
	};
}



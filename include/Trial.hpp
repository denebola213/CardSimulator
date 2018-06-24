#pragma once
#include <string>
#include <memory>
#include <map>
#include "CardPool.hpp"

namespace CardSimulator {
	class Trial {
		std::unique_ptr<CardPool> deck_;
		std::string title_;
		size_t numof_picking_;
		size_t cards_total_;

	public:
		Trial();
		~Trial();

		void SetTitle(std::string title);
		void SetNumofPickng(int picking);
		void SetTotal(int total);
		void addCardByMap(const std::map<int, size_t>& cards_map);

		//debug用
		std::string str(){
			return title_ + ": number of " + std::to_string(numof_picking_) + ". total " + std::to_string(cards_total_) + ".";
		}
	};
}



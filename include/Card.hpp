#pragma once
namespace CardSimulator {

	class Card {
		int number_;

	public:
		Card(int num) :number_(num) {};
		~Card();
		bool operator<(Card &right);

		int getnum();

	};

}


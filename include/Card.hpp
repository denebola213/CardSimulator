#pragma once
namespace CardSimulator {

	class Card {
		int number_;

	public:
		Card(int num) :number_(num) {};
		~Card();
		bool operator==(const Card &hoge);
		void operator=(const int hoge);
	};

}


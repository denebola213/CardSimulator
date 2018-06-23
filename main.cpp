#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "Trial.hpp"



int main(int argc, char const *argv[]) {

	//get name of config file
	std::string conf_name;
	switch (argc){
	case 1:
		conf_name = "cards.conf";
		break;
	case 2:
		conf_name = std::string(argv[1]);
		break;
	default:
		std::cout << "[ERROR] 引数の数が間違っています\n" << std::endl;
		return 1;
		break; 
	}

	std::ifstream ifs(conf_name);
	if (!ifs.fail()) {
		std::string conf_line;

		std::regex re_comment(R"(#.*$)");
		std::regex re_title(R"(\[(\w*)\])");
		std::regex re_numof_cards(R"((\d+):(\d+))");
		std::smatch match_result;

		std::vector<std::unique_ptr<CardSimulator::Trial>> trials;
		CardSimulator::Trial* tmp_trial = nullptr;

		while (getline(ifs, conf_line)) {
			// コメント部分を削除
			conf_line = std::regex_replace(conf_line, re_comment, "");

			// プロセスのタイトル
			if (std::regex_search(conf_line, match_result, re_title)) {
				// 最初の試行コンフィグではない時
				if(tmp_trial != nullptr){
					trials.emplace_back(tmp_trial);
				}
				tmp_trial = new CardSimulator::Trial(match_result.str(1));
			}
			// カードの番号とそれぞれのカードの枚数
			else if (conf_line.find("number_of_cards")) {
				std::map<int, size_t> cards_map;
				for (std::sregex_iterator it(conf_line.begin(), conf_line.end(), re_numof_cards), end; it != end; ++it) {
					auto&& match_result = it->begin();
					++match_result;
					int match_result_cardnum = std::stoi(match_result->str());
					++match_result;
					int match_result_numofcard = std::stoi(match_result->str());

					cards_map.emplace(match_result_cardnum, match_result_numofcard);
				}

				tmp_trial->SetDeckForMap(cards_map);
				
			}
			else if(conf_line.find("number_of_picikng")){

			}
		}
		// 最後の試行コンフィグを追加
		if(tmp_trial != nullptr){
			trials.emplace_back(tmp_trial);
		}
		
	}
	else{
		std::cerr << "[ERROR] can not open the file '" << conf_name << "'" << std::endl;
		return 1;
	}
	return 0;
}
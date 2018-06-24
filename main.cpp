#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <stdexcept>
#include <utility>
#include <memory>

#include "Trial.hpp"

std::vector<std::unique_ptr<CardSimulator::Trial>> ParseConf(std::ifstream const conf_file_iterator);

int main(int argc, char const *argv[]) {

	//get name of config file
	std::string conf_name;
	switch (argc){
	case 1:	//指定なし
		conf_name = "cards.conf";
		break;
	case 2:	//指定あり
		conf_name = std::string(argv[1]);
		break;
	default:
		std::cout << "[ERROR] 引数の数が間違っています\n" << std::endl;
		return 1;
		break; 
	}

	std::ifstream ifs(conf_name);
	if (ifs.fail()){
		throw std::runtime_error("can not open the file. '" + conf_name + "'");
	}

	/** config 解析 **
	 * note:今後、クラスや関数に分ける*/
	std::vector<std::unique_ptr<CardSimulator::Trial>> trials;
	std::string conf_line;
	std::unique_ptr<CardSimulator::Trial> tmp_trial;

	std::regex re_comment(R"(#.*$)");
	std::regex re_title(R"(\[(\w*)\])");
	std::regex re_numof_cards(R"((\d+):(\d+))");
	std::regex re_nomal_num(R"(=\s*(\d+))");
	std::smatch match_result;

	while (getline(ifs, conf_line)) {
		// コメント部分を削除
		conf_line = std::regex_replace(conf_line, re_comment, "");

		// プロセスのタイトル
		if (std::regex_search(conf_line, match_result, re_title)) {
			// 最初の試行コンフィグではない時
			if(tmp_trial.get() != nullptr){
				trials.emplace_back(std::move(tmp_trial));
			}
			tmp_trial.reset(new CardSimulator::Trial());
			tmp_trial->SetTitle(match_result.str(1));
		}
		// カードの番号とそれぞれのカードの枚数
		else if (conf_line.find("number_of_cards") != std::string::npos) {
			std::map<int, size_t> cards_map;
			for (std::sregex_iterator it(conf_line.begin(), conf_line.end(), re_numof_cards), end; it != end; ++it) {
				auto&& match_result = it->begin();
				++match_result;
				int match_result_cardnum = std::stoi(match_result->str());
				++match_result;
				int match_result_numofcard = std::stoi(match_result->str());

				cards_map.emplace(match_result_cardnum, match_result_numofcard);
			}
			tmp_trial->addCardByMap(cards_map);
		}
		// 山札からカードを引く回数
		else if(conf_line.find("number_of_picikng") != std::string::npos){
			std::regex_search(conf_line, match_result, re_nomal_num);
			tmp_trial->SetNumofPickng(std::stoi(match_result.str(1)));
		}
		// 引いたカードの番号の合計
		else if(conf_line.find("cards_total") != std::string::npos){
			std::regex_search(conf_line, match_result, re_nomal_num);
			tmp_trial->SetTotal(std::stoi(match_result.str(1)));
		}
	}
	// 最後の試行コンフィグを追加
	if(tmp_trial != nullptr){
		trials.emplace_back(std::move(tmp_trial));
	}
	/** config 解析 end **/


	for(std::unique_ptr<CardSimulator::Trial>& a_trial : trials){
		std::cout << a_trial->str() << std::endl;
	}
	
	return 0;
}
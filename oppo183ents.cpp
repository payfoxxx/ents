/*https://acmp.ru/index.asp?main=task&id_task=183
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

void add_ents_for_wordsCount(map<int, int>& words_ents, int words_count, int ents_count, int modul) {
	auto it = words_ents.find(words_count);
	if (it == words_ents.end()) 
		words_ents[words_count] = ents_count;
	else
		it->second = (it->second+ents_count) % modul;
}

int get_ents_amount(int max_words_count, int modul) {
	map<int, int> entsAmount_knowWords; //Словарь количества энтов знающих [индекс] слов

	if (modul < 2) {
		return 0;
	}

	

	entsAmount_knowWords[2] = 1; //Первый эльф знает два слова
	for (int words_count = 2; words_count <= max_words_count; words_count++) {
		int amount_ents_know_cur_words = entsAmount_knowWords[words_count]; //Количество энтов знающих текущее количество слов

		int amountWords_willOldEntStudy = (words_count + 1); //Старый эльф узнает еще одно слово (количество слов)
		int amountWords_willYoungEntStudy = (words_count * 2); //Молодой эльф узнает еще в два раза больше слов (количество слов)

		add_ents_for_wordsCount(entsAmount_knowWords,amountWords_willOldEntStudy, amount_ents_know_cur_words, modul);
		add_ents_for_wordsCount(entsAmount_knowWords, amountWords_willYoungEntStudy, amount_ents_know_cur_words, modul);
	}
	return entsAmount_knowWords[max_words_count];
}


int main() {
	ifstream in("INPUT.TXT");
	ofstream out("OUTPUT.TXT");
	int max_words_count, modul;
	in >> max_words_count >> modul;
	out << get_ents_amount(max_words_count, modul);
}

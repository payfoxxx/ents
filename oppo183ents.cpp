/*https://acmp.ru/index.asp?main=task&id_task=183
Использовать нормальные переменные(названия);
оптимизировать, чтобы не жрало память, проблема со словарем map;
нужно примерно оставить это решение
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

int get_amount_ents_for_words(map<int, int>& words_ents, int words_count) {
	auto it = words_ents.find(words_count);
	if (it == words_ents.end()) {
		return 0;
	}
	return it->second;
}

int get_ents_amount(int max_words_count, int modul) {
	map<int, int> entsAmount_knowWords; //Словарь количества энтов знающих [индекс] слов

	if (modul < 2) {
		return 0;
	}

	entsAmount_knowWords[2] = 1; //Первый эльф знает два слова
	for (int words_count = 2; words_count <= max_words_count; words_count++) {
		int amount_ents_know_cur_words = entsAmount_knowWords[words_count]; //Количество энтов знающих текущее количество слов

		int amount_oldEnt_willStudy_words = (words_count + 1); //Старый эльф узнает еще одно слово
		int amount_youngEnt_willStudy_words = (words_count * 2); //Молодой эльф узнает еще в два раза больше слов

		if (amount_oldEnt_willStudy_words <= max_words_count) {
			int amount_oldEnts_know_words = get_amount_ents_for_words(entsAmount_knowWords, amount_oldEnt_willStudy_words);
			entsAmount_knowWords[amount_oldEnt_willStudy_words] = (amount_oldEnts_know_words + amount_ents_know_cur_words) % modul;
		}
		if (amount_youngEnt_willStudy_words <= max_words_count) {
			int amount_youngEnts_know_words = get_amount_ents_for_words(entsAmount_knowWords, amount_youngEnt_willStudy_words);
			entsAmount_knowWords[amount_youngEnt_willStudy_words] = (amount_youngEnts_know_words + amount_ents_know_cur_words) % modul;
		}	
	}
	return entsAmount_knowWords[max_words_count];
}


/*

int get_ents_amount(int max_words_count, int modul) {
	if (modul < 2) {
		return 0;
	}
	vector<int> amountEnts_know_words(max_words_count + 1, 0);
	amountEnts_know_words[2] = 1; //Два слова знает один эльф
	for (int cur_amount_word = 2; cur_amount_word < max_words_count; cur_amount_word++) {
		amountEnts_know_words[cur_amount_word + 1] = (amountEnts_know_words[cur_amount_word + 1] + amountEnts_know_words[cur_amount_word]) % modul;
		if (2 * cur_amount_word <= max_words_count) {
			amountEnts_know_words[2 * cur_amount_word] = amountEnts_know_words[cur_amount_word] % modul; //Удваиваем количество слов
		}
	}
	return amountEnts_know_words[max_words_count];
}
*/
int main() {
	ifstream in("INPUT.TXT");
	ofstream out("OUTPUT.TXT");
	int max_words_count, modul;
	in >> max_words_count >> modul;
	out << get_ents_amount(max_words_count, modul);
}

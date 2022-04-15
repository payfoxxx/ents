/*https://acmp.ru/index.asp?main=task&id_task=183
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

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


int main() {
	ifstream in("INPUT.TXT");
	ofstream out("OUTPUT.TXT");
	int max_words_count, modul;
	in >> max_words_count >> modul;
	out << get_ents_amount(max_words_count, modul);
}

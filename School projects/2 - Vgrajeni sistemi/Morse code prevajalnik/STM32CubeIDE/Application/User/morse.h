#include <string.h>
#include "stm32h7xx_hal.h"
extern uint8_t prevedeno[36];
int TABLE_SIZE = 35;
extern uint8_t trenutno[10];
extern uint8_t morse_prevod[100];

void clearT(uint8_t t[]);

typedef struct {
	uint8_t morse[10];
	uint8_t ascii;
} morse_table_t;


//tabela vseh moznih vnosov v morse
morse_table_t table[] = { { ".-", 'A' },
		{ "-...", 'B' }, { "-.-.", 'C' }, {
		"-..", 'D' }, { ".", 'E' }, { "..-.", 'F' }, { "--.", 'G' }, { "....",
		'H' }, { "..", 'I' }, { ".---", 'J' }, { "-.-", 'K' }, { ".-..", 'L' },
		{ "--", 'M' }, { "-.", 'N' }, { "---", 'O' }, { ".--.", 'P' }, { "--.-",
				'Q' }, { ".-.", 'R' }, { "...", 'S' }, { "-", 'T' }, { "..-",
				'U' }, { "...-", 'V' }, { ".--", 'W' }, { "-..-", 'X' }, {
				"-.--", 'Y' }, { "--..", 'Z' }, { ".----", '1' },
		{ "..---", '2' }, { "...--", '3' }, { "....-", '4' }, { ".....", '5' },
		{ "-....", '6' }, { "--...", '7' }, { "---..", '8' }, { "----.", '9' },
		{ "-----", '0' },

};

//funkcija za prevod iz morse v ASCII text
void morseToText(uint8_t beseda[]) {
	//indekse nastavimo na 0
	//indeks crke uporabljamo v koncni tabeli prevod
	int crke = 0;
	//indeks i nam kaze na trenutni znak v vhodni tabeli
	int i = 0;
	//indeks j pa kaze na znak v trenutni crki
	int j = 0;
	clearT(trenutno);
	//sprehajamo se skozi besedo, ki je v morse
	while (beseda[i] != 0) {
		//Ce je znak . ali - ga dodamo trenutni crki, nato crko primerjamo z vsemi v tabeli.
		//Ce se znak v tabeli ujema z trenutno crki ga dodamo tabeli, ce se pa ne pa dodamo tabeli znak '?'
		if (beseda[i] == '.' || beseda[i] == '-') {
			trenutno[j] = beseda[i];
			int check = 0;
			for (int l = 0; l < TABLE_SIZE; l++) {
				if (!strcmp(trenutno, table[l].morse)) {
					prevedeno[crke] = table[l].ascii;
					check = 1;
					break;
				}
			}
			if(!check){
				prevedeno[crke] = '?';
			}
			//Ce znak ni . ali - preverimo se ali je ' '
			//Ce je pocistimo trenutno crko, nastavimo njen indeks na 0, povecamo indeks i in crke
		} else if (beseda[i] == ' ' || beseda[i + 1] == 0) {
			clearT(trenutno);
			j = 0;
			i++;
			crke++;
			continue;
			//Ce pa je znak '/' dodamo v tabelo prelom vrstice in povecamo indeksa i in crke
		} else if (beseda[i] == '/') {
			prevedeno[crke] = '\n';
			crke++;
			i++;
			continue;
		}
		i++;
		j++;
	}
}

//funkcija za prevod iz ASCII texta v morse
void textToMorse(uint8_t buffer[]) {
	//pocistimo/resetiramo prejsen vnos
	int i = 0;
	clearT(morse_prevod);
	//sprehajamo se skozi vhodno tabelo dokler v njen ne najdemo znak 0
	while (buffer[i] != 0) {
		//primerjamo crko v ASCII z tabelo vseh moznih vnosov,
		//ce najdemo enako dodamo v koncno tabelo njen zapis v morse
		for (int l = 0; l < TABLE_SIZE; l++) {
			if (buffer[i] == table[l].ascii) {
				strcat(morse_prevod, table[l].morse);
			}
		}
		//ce nismo na koncu vhoda dodamo " "
		if (buffer[i + 1] != 0)	strcat(morse_prevod, " ");
		i++;
	}
}

//funkcija za brisanje tabel
void clearT(uint8_t t[]) {
	for (int i = 0; t[i] != 0; i++) {
		t[i] = 0;
	}
}

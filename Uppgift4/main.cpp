#include <iostream>
#include <cctype>
#include <array>

using namespace std;

struct LETTER
{
    char letter;
    int amount;
};

const int ANTAL_BOKSTAVER = 26;  //A-Z

void berakna_histogram_abs(string input, LETTER letter[ANTAL_BOKSTAVER]);

void skriv_histogram_abs(LETTER pLetter[26]);

int main()
{
    string input;
    LETTER letter[ANTAL_BOKSTAVER];

    cout << "Ge en rad med text: \n";
    getline(cin, input);
    berakna_histogram_abs(input, letter);

   skriv_histogram_abs(letter);

    return 0;
}

void skriv_histogram_abs(LETTER letter[ANTAL_BOKSTAVER]) {
    int num_of_letters = 0;

    //Går igenom listan och summerar ihop antalet bokstäver
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        num_of_letters += letter[i].amount;
    }

    cout <<"\n";
    cout << "Resultat för bokstäverna A-Z \n";

    cout <<"Totala antalet bokstäver: "<< num_of_letters <<"\n";
    cout << "Bokstavsfördelning:\n \n";

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        cout << letter[i].letter << " : " <<letter[i].amount << "\n";
    }
}

void berakna_histogram_abs(string input, LETTER letter[ANTAL_BOKSTAVER]) {

    //Går igenom hela listan och sätter position 0 till A, position 1 till B osv.
    //Sätter även alla amount till 0
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        letter[i].amount = 0;
        letter[i].letter = (char)(65 + i);
    }

    //Går igenom hela inputen
    for (char i : input) {

        //För varje input går vi igenom letter listan
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {

            //Om bokstaven finns med så plussar vi på amount med +1
            if (letter[j].letter == (char) toupper( i)) {
                letter[j].amount++;
                break;
            }
        }
    }
}

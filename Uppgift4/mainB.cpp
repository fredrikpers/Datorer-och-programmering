//
// Created by Fredrik Pettersson on 2021-07-20.
//

#include "mainB.h"
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct LETTER
{
    char letter;
    double amount;
};

const int ANTAL_BOKSTAVER = 26;
const int ANTAL_SPRAK = 4;

const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
        {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77,
                 7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
                 0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
                 1.89,0.03},
         {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75,
                 7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
                 1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
                 0.30,0.15},
         {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,
                 3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
                 0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
                 0.45,0.00},
         {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79,
                 8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
                 0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
                 0.69,1.24}};

void berakna_histogram_abs(string input, LETTER letter[ANTAL_BOKSTAVER]);

void abs_till_rel(LETTER letter[ANTAL_BOKSTAVER], LETTER letter_rel[ANTAL_BOKSTAVER]);

void setToDefault(LETTER array[ANTAL_BOKSTAVER]);

void plotta_histogram_rel(LETTER letter_rel[ANTAL_BOKSTAVER]);


int main(){

    string input;

    LETTER letter[ANTAL_BOKSTAVER];
    LETTER letter_rel[ANTAL_BOKSTAVER];

    cout << "Ge en rad med text: \n";
    getline(cin, input);
    berakna_histogram_abs(input, letter);
    abs_till_rel(letter, letter_rel);
    plotta_histogram_rel(letter_rel);



    return 0;
}
//Går igenom hela listan och sätter position 0 till A, position 1 till B osv.
//Sätter även alla amount till 0
void setToDefault(LETTER array[ANTAL_BOKSTAVER]){

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        array[i].amount = 0;
        array[i].letter = (char) (65 + i);
    }
}



void abs_till_rel(LETTER letter[ANTAL_BOKSTAVER], LETTER letter_rel[ANTAL_BOKSTAVER]){
    int num_of_letters = 0;
    setToDefault(letter_rel);

    //Går igenom listan och summerar ihop antalet bokstäver
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        num_of_letters += letter[i].amount;
    }

    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        letter_rel[i].amount = round((letter[i].amount/num_of_letters) *1000)/10.0;
    }

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        cout << letter_rel[i].letter << " : " <<letter_rel[i].amount << "\n";
    }

}

void plotta_histogram_rel(LETTER letter_rel[ANTAL_BOKSTAVER]){

    for(int i=0; i<ANTAL_BOKSTAVER; i++){
        cout << letter_rel[i].letter << " ";

        double j = letter_rel[i].amount;

        while(j >= 0.5) {
            cout << "*";
            j -= 0.5;
        }
        cout <<"\n";

    }
}

void berakna_histogram_abs(string input, LETTER letter[ANTAL_BOKSTAVER]) {

    setToDefault(letter);

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

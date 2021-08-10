//
// Created by Fredrik Pettersson on 2021-08-09.
//

#include "inlamn5B.h"



#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;


const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
        {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
          7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
          0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
          1.89,0.03},
         {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
          7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
          1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
          0.30,0.15},
          {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
           3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
           0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
           0.45,0.00},
           {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
            8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
            0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
            0.69,1.24}};


class Text{
private:
    string text;
    int absHist[ANTAL_BOKSTAVER];
    double relHist[ANTAL_BOKSTAVER];
    int nrOfLetters;

public:
    Text();
    void setText( const string &nyText);
    bool beraknaHistogramAbs();
    void skrivHistogramAbs();
    void absTillRel();
    void plottaHistogramRel();
    void beraknaHistogram();
    string tolka();
};

string namn_pa_fil(string input);

string inlasning(string textfile);

int main()
{
    string input;
    string textfile;
    string text;
    Text minText;

    cout << "Ange filnamn: \n";
    getline( cin, input );
    textfile = namn_pa_fil(input);
    text = inlasning(textfile);

    minText.setText(text);
    minText.beraknaHistogram();
    minText.plottaHistogramRel();
    minText.tolka();
    return 0;
}

Text::Text(){
    text = "";
    nrOfLetters = 0;

    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        absHist[i] = 0;
        relHist[i] = 0;
    }
}

void Text::setText(const string &nyText) {
    text = nyText;
}

bool Text::beraknaHistogramAbs() {

    char bokstav = 'A';


    for(char i : text){

        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            if((char) toupper(i) == bokstav){
                absHist[j] ++;
                nrOfLetters++;
            }
            bokstav ++;
        }
        bokstav = 'A';
    }

    if(nrOfLetters == 0)
        return false;
    return true;
}

void Text::skrivHistogramAbs() {
    cout <<"\n";
    cout << "Resultat för bokstäverna A-Z \n";
    cout <<"Totala antalet bokstäver: "<< nrOfLetters <<"\n";
    cout << "Bokstavsfördelning:\n \n";

    char bokstav = 'A';
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        cout << bokstav << ": "<< absHist[i] << endl;
        bokstav ++;
    }
}

void Text::absTillRel() {

    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        relHist[i] = (((double)absHist[i])/nrOfLetters) *100;
    }

}

void Text::plottaHistogramRel() {
    char bokstav = 'A';

    cout << "Bokstavsfördelning:\n \n";

    for(int i=0; i<ANTAL_BOKSTAVER; i++){
        cout << bokstav << " ";

        double j = relHist[i];

        while(j >= 0.5) {
            cout << "*";
            j -= 0.5;
        }
        cout <<"\n";
        bokstav++;
    }

}

void Text::beraknaHistogram() {

    if(beraknaHistogramAbs())
        absTillRel();
}

string Text::tolka() {
    double highest_freq = std::numeric_limits<int>::max();
    double freq = 0;
    int indexLanguage = 0;
    string language[4] = {"Engelska","Franska","Svenska","Tyska"};

    cout << "\nResultat för bokstäverna A-Z\n\n";
    cout << "Totala antalet bokstäver: " << nrOfLetters <<"\n";

    for(int i = 0; i < ANTAL_SPRAK; i++){

        for(int j = 0; j < ANTAL_BOKSTAVER; j++){
            freq += (TOLK_HJALP[i][j] - relHist[j]) * (TOLK_HJALP[i][j] - relHist[j]);
        }

        if(freq < highest_freq){
            highest_freq = freq;
            indexLanguage = i;
        }
        cout << language[i] <<" har kvadratsumma= " << freq <<"\n";
        freq = 0;
    }
    cout << "Det är mest troligt att språket är " << language[indexLanguage]+ "\n\n";
}


string inlasning(string textfile){

    string row;
    string fullText = "";
    string path = "/Users/fredrikpettersson/CLionProjects/Datorer-och-programmering/Uppgift5/"+textfile;

    ifstream fin(path.c_str());

    if ( !fin )
    {
        cout << "Det finns ingen fil med namnet " << textfile;
        exit( EXIT_FAILURE );
    }

    while(getline(fin,row)){
        fullText += row;
    }

    return fullText;
}

string namn_pa_fil(string input){

    if (input.rfind(".txt") == string::npos){
        input.append(".txt");
    }

    return input;
}

/*
// -------------------------------------------------------
// Rapport om uppgiften

=================================
Testdata 1
=================================

Ange filnamn:
doyle
Bokstavsfördelning:

A ****************
B **
C ******
D *******
E ************************
F ****
G **
H ************
I ***************
J
K *
L *******
M *****
N ************
O ***************
P ***
Q
R ***********
S ************
T ******************
U *****
V **
W ****
X
Y ****
Z

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 12885
Engelska har kvadratsumma= 1.75771
Franska har kvadratsumma= 96.1956
Svenska har kvadratsumma= 73.3371
Tyska har kvadratsumma= 116.072
Det är mest troligt att språket är Engelska

=================================
Testdata 2
=================================

Ange filnamn:
goethe.txt
Bokstavsfördelning:

A **********
B ***
C *******
D *********
E *********************************
F **
G ******
H ***********
I *****************
J
K **
L ******
M ******
N *********************
O ****
P
Q
R ************
S *************
T ***********
U *******
V *
W ***
X
Y *
Z **

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 14027
Engelska har kvadratsumma= 107.856
Franska har kvadratsumma= 85.205
Svenska har kvadratsumma= 160.318
Tyska har kvadratsumma= 1.04313
Det är mest troligt att språket är Tyska


=================================
Testdata 3
=================================

Ange filnamn:
lagerlof
Bokstavsfördelning:

A **********************
B *
C **
D ***********
E *******************
F ****
G ********
H *******
I ********
J **
K ******
L **********
M *******
N ******************
O ********
P **
Q
R **************
S *************
T *****************
U ***
V ******
W
X
Y
Z

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 12221
Engelska har kvadratsumma= 86.6804
Franska har kvadratsumma= 145.722
Svenska har kvadratsumma= 8.88258
Tyska har kvadratsumma= 170.223
Det är mest troligt att språket är Svenska


=================================
Testdata 4
=================================

Ange filnamn:
verne.txt
Bokstavsfördelning:

A ****************
B **
C *******
D ********
E **********************************
F *
G **
H *
I *************
J
K
L **********
M *****
N ***************
O **********
P *****
Q *
R *************
S ****************
T *************
U ***********
V **
W
X *
Y
Z

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 11417
Engelska har kvadratsumma= 112.425
Franska har kvadratsumma= 0.885142
Svenska har kvadratsumma= 149.256
Tyska har kvadratsumma= 90.491
Det är mest troligt att språket är Franska

=================================
Testdata 5
=================================

Ange filnamn:
abc
Det finns ingen fil med namnet abc.txt


 */

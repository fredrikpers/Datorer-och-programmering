

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
    int nrOfLetters;

public:
    Text();
    void setText( const string &nyText);
    bool beraknaHistogramAbs();
    void skrivHistogramAbs();
};

int main()
{

  string text;
  Text minText;

  cout <<"Ge en rad med text:" << endl;
  getline(cin,text);

  minText.setText(text);
  minText.beraknaHistogramAbs( );
  minText.skrivHistogramAbs( );
  return 0;
}

Text::Text(){
    text = "";
    nrOfLetters = 0;

    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        absHist[i] = 0;
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

/* Redovisning av uppgiften i ord.

=================================
Testdata 1
=================================

Ge en rad med text:
AbCdNNooPPwXyZ

Resultat för bokstäverna A-Z
Totala antalet bokstäver: 14
Bokstavsfördelning:

A : 1
B : 1
C : 1
D : 1
E : 0
F : 0
G : 0
H : 0
I : 0
J : 0
K : 0
L : 0
M : 0
N : 2
O : 2
P : 2
Q : 0
R : 0
S : 0
T : 0
U : 0
V : 0
W : 1
X : 1
Y : 1
Z : 1

=================================
Testdata 2
=================================

Ge en rad med text:
1234ddddacccbb!?

Resultat för bokstäverna A-Z
Totala antalet bokstäver: 10

Bokstavsfördelning:

A : 1
B : 2
C : 3
D : 4
E : 0
F : 0
G : 0
H : 0
I : 0
J : 0
K : 0
L : 0
M : 0
N : 0
O : 0
P : 0
Q : 0
R : 0
S : 0
T : 0
U : 0
V : 0
W : 0
X : 0
Y : 0
Z : 0

=================================
Testdata 3
=================================

Ge en rad med text:
Denna rad innehåller ett å!

Resultat för bokstäverna A-Z
Totala antalet bokstäver: 20
Bokstavsfördelning:

A : 2
B : 0
C : 0
D : 2
E : 4
F : 0
G : 0
H : 1
I : 1
J : 0
K : 0
L : 2
M : 0
N : 4
O : 0
P : 0
Q : 0
R : 2
S : 0
T : 2
U : 0
V : 0
W : 0
X : 0
Y : 0
Z : 0

=================================
Testdata 4
=================================

Ge en rad med text:


Resultat för bokstäverna A-Z
Totala antalet bokstäver: 0
Bokstavsfördelning:

A : 0
B : 0
C : 0
D : 0
E : 0
F : 0
G : 0
H : 0
I : 0
J : 0
K : 0
L : 0
M : 0
N : 0
O : 0
P : 0
Q : 0
R : 0
S : 0
T : 0
U : 0
V : 0
W : 0
X : 0
Y : 0
Z : 0
 */
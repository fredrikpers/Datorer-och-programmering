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
//Går igenom hela listan och sätter position 0 till A, position 1 till B osv.
//Sätter även alla amount till 0
void setToDefault(LETTER array[ANTAL_BOKSTAVER]){

  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
      array[i].amount = 0;
      array[i].letter = (char) (65 + i);
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
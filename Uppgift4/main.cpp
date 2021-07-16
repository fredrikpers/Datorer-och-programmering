#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

void berakna_histogram_abs(string basicString);

int main()
{
   string input;

    cout << "Enter a string \n";
    cin >> input;

    berakna_histogram_abs(input);

    return 0;
}

void berakna_histogram_abs(string input) {

    char letters[ANTAL_BOKSTAVER];
    int count[ANTAL_BOKSTAVER];


    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
        letters[i] = ' ';

    for (int i = 0; i < input.size(); i++) {

        for (int j = 0; j < sizeof(letters); j++) {

            if (letters[j] == (char) tolower( input[i])) {
                count[j]++;
                break;
            }
            else if (letters[j] == ' ') {
                letters[j] = input[i];
                count[j]++;
                break;
            }
        }
    }


    int i = 0;
    while(letters[i] != ' ') {
        cout << letters[i] << " -> " << count[i] << "\n";
        i++;
    }
}

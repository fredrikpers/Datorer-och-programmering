#include <iostream>

void skrivInfo();

int lasEttTal();

char lasOp();

void ordna(int &tal1, int &tal2);

int berakna(int tal1, int tal2, char op);

void skrivResultat(int svar);

using namespace std;

int main() {

    int tal1;
    int tal2;
    char op;
    int svar;

    skrivInfo();

    tal1 = lasEttTal();

    tal2 = lasEttTal();

    op = lasOp();

    ordna(tal1, tal2);

    svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}

void skrivResultat(int svar) {
    cout << "Svaret är: " << svar << "\n";
}

int berakna(int tal1, int tal2, char op) {
    int res = 0;

    if(op == 'a'){
        while(tal1 <= tal2){
            res += tal1;
            tal1++;
        }
    }

    if(op == 'm'){
        res = 1;
        while(tal1 <= tal2){
            res *= tal1;
            tal1++;
        }
    }

    if(op == 'k'){
        while(tal1 <= tal2){
            res += tal1 * tal1;
            tal1++;
        }
    }

    return res;
}

void ordna(int &tal1, int &tal2) {

    int temp;
    if(tal1 > tal2){
        temp = tal2;
        tal2 = tal1;
        tal1 = temp;
    }
}

char lasOp() {
    char op;

    while(true){
        cout << "Skriv in vilken beräkning du vill använda \n";
        cout << "a för addition, m för multiplikation eller k för kvadratsumman \n";
        cin >> op;
        if(op == 'a' || op == 'm' || op == 'k')
            break;
        cout << "Mata in en giltlig beräkning. \n";
    }

    if(op == 'a')
        cout << "Du valde addition som beräkningsstyp \n \n";
    if(op == 'm')
        cout << "Du valde multiplikation som beräkningsstyp \n \n";
    if(op == 'k')
        cout << "Du valde kvadratsumma som beräkningsstyp\n \n";

    return op;
}

int lasEttTal() {
    int tal;
    cout << "Mata in ett tal \n";
    cin >> tal;
    cout << "Valt tal: " << tal << "\n \n";

    return tal;
}

void skrivInfo() {
    cout << "Detta program hanterar enkla beräkningar. Det finns tre olika sorters beräkningar som kan göras, addition, multiplikation eller kvadratsumman.\n";
    cout << "Programmet tar emot två tal och vald beräkningssort. Därefter beräknas resultatet från den minsta talet till det största. \n";
    cout << "Exempel: mata in 3 och 5 samt a, då blir svaret 12 då 3+4+5 = 12. \n \n";

}
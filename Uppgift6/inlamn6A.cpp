//
// Created by Fredrik Pettersson on 2021-08-10.
//

#include "inlamn6A.h"
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

class Transaktion
        {
        private:
            string datum;
            string typ;
            string namn;
            double belopp;
            int    antal_kompisar;
            string kompisar[MAX_PERSONER];

        public:
            Transaktion();
            ~Transaktion();

            string hamtaNamn();
            double hamtaBelopp();
            int    hamtaAntalKompisar();
            bool   finnsKompis(const string &namnet);
            bool   lasIn(istream &is);
            void   skrivUt(ostream &os);
            void   skrivTitel(ostream &os);
            void skrivUtKompisar();
};

class Person
        {
        private:
            string namn;
            double betalat_andras; // ligger ute med totalt
            double skyldig;        // skyldig totalt

        public:
            Person();
            Person(const string &namn, double betalat_andras, double skyldig);
            string hamtaNamn();
            double hamtaBetalat();
            double hamtaSkyldig();
            void   skrivUt(ostream &os);
        };

class PersonLista
        {
        private:
            int antal_personer;
            Person personer[MAX_PERSONER];

        public:
            PersonLista();
            ~PersonLista();
            void laggTill(Person ny_person);
            void skrivUtOchFixa(ostream &os);
            double summaSkyldig();
            double summaBetalat();
            bool finnsPerson(const string &namn);
        };

class TransaktionsLista
        {
        private:
            int antal_transaktioner;
            Transaktion transaktioner[MAX_TRANSAKTIONER];

        public:
            TransaktionsLista();
            ~TransaktionsLista();
            void   lasIn(istream & is);
            void   skrivUt(ostream & os);
            void   laggTill(Transaktion & t);
            double totalKostnad();
            double liggerUteMed(const string &namnet);
            double arSkyldig(const string &namnet);
            PersonLista FixaPersoner();

        };

int main()
{
    cout << "Startar med att läsa från en fil." << endl;

    TransaktionsLista transaktioner;
    std::ifstream     is("/Users/fredrikpettersson/CLionProjects/Datorer-och-programmering/Uppgift6/resa2.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
            case 1:
            {
                transaktioner.skrivUt(cout);
                break;
            }
            case 2:
            {
                Transaktion transaktion;
                cout << "Ange transaktion i följande format" << endl;
                transaktion.skrivTitel(cout);
                transaktion.lasIn(cin);
                transaktioner.laggTill(transaktion);
                break;
            }
            case 3:
            {

                cout << "Den totala kostnanden för resan var "
                    << transaktioner.totalKostnad() << endl;
                break;
            }
            case 4:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ar_skyldig = transaktioner.arSkyldig(namn);
                if (ar_skyldig == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " är skyldig " << ar_skyldig << endl;
                break;
            }
            case 5:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ligger_ute_med = transaktioner.liggerUteMed(namn);
                if (ligger_ute_med == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " ligger ute med " << ligger_ute_med << endl;
                break;
            }
            case 6:
            {
                cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
                PersonLista lista = transaktioner.FixaPersoner();
                lista.skrivUtOchFixa(cout);
                break;
            }
        }
    }

    std::ofstream os("/Users/fredrikpettersson/CLionProjects/Datorer-och-programmering/Uppgift6/transaktioner2.txt");
    transaktioner.skrivUt(os);

    return 0;
}

Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    antal_kompisar = 0;

    for(auto & i : kompisar){
        i = "";
    }
}

Transaktion::~Transaktion() {}

string Transaktion::hamtaNamn() {
    return namn;
}

double Transaktion::hamtaBelopp() {
    return belopp;
}

int Transaktion::hamtaAntalKompisar() {
    return antal_kompisar;
}



bool Transaktion::finnsKompis(const string &namnet) {

    for(int i = 0; i <antal_kompisar; i++){
        if(kompisar[i] == namnet){
            return true;
        }
    }
    return false;
}

bool Transaktion::lasIn(istream &is) {

    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    for(int i = 0; i < antal_kompisar; i++){
        is >> kompisar[i];
    }
    return !is.eof();
}

void Transaktion::skrivUtKompisar(){
    for(int i = 0; i < antal_kompisar; i++){
        cout << kompisar[i] << "\t";
    }
    cout << endl;


}

void Transaktion::skrivUt(ostream &os) {

    os << datum << " \t"<< typ << " \t";
    os << namn;
    if(namn.size() < 4)
      os << " \t";
    if(namn.size () > 3)
       os << "\t";
    os << belopp << " \t" << antal_kompisar << "\t";

    for(int i = 0; i < antal_kompisar; i++){
        os << kompisar[i] << "\t";
    }

    os << endl;
    
}

void Transaktion::skrivTitel(ostream &os) {
    os << "Datum " << '\t'<< "Typ " << '\t';
    os << "Namn " << '\t' << "Belopp" << '\t';
    os << "Antal och lista av kompisar";
    os << endl;
}

Person::Person()
    : namn(""), betalat_andras(0), skyldig(0)
    {}

Person::Person(const string &namn, double betalat_andras, double skyldig)
    : namn(namn), betalat_andras(betalat_andras), skyldig(skyldig)
    {}

string Person::hamtaNamn() {
    return namn;
}

double Person::hamtaBetalat() {
    return betalat_andras;
}

double Person::hamtaSkyldig() {
    return skyldig;
}

void Person::skrivUt(ostream &os) {
    cout << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". ";
    if( (betalat_andras-skyldig) == 0)
        cout << "Skall inte ha eller lägga till någonting från potten! \n";
    if( (betalat_andras-skyldig) > 0)
        cout << "Skall ha " << betalat_andras-skyldig << " från potten! \n";
    if( (betalat_andras-skyldig) < 0)
        cout << "Skall lägga " << fabs(betalat_andras-skyldig) << " till potten! \n";
}

PersonLista::PersonLista()
    : antal_personer(0)
    {}

PersonLista::~PersonLista() {}

void PersonLista::laggTill(Person ny_person) {
    personer[antal_personer++] = ny_person;
}

void PersonLista::skrivUtOchFixa(ostream &os) {

    for(int i = 0; i < antal_personer; i++)
        personer[i].skrivUt(os);

    cout << "\n";
    if(summaBetalat() == summaSkyldig())
        cout << "Potten stämmer! ";
    if(summaBetalat() != summaSkyldig())
        cout << "Potten stämmer inte! ";
}

double PersonLista::summaSkyldig() {
    double skyldig = 0;

    for(int i = 0; i < antal_personer; i++)
        skyldig += personer[i].hamtaSkyldig();
    return skyldig;
}

double PersonLista::summaBetalat() {
    double betalat = 0;

    for(int i = 0; i < antal_personer; i++)
        betalat += personer[i].hamtaBetalat();
    return betalat;
}

bool PersonLista::finnsPerson(const string &namn) {

    for(int i = 0; i < antal_personer; i++){
        if(personer[i].hamtaNamn() == namn)
            return true;     
    }
    return false;
}

TransaktionsLista::TransaktionsLista() {
    antal_transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista() {}

void TransaktionsLista::lasIn(istream &is) {
      Transaktion t;

    while (t.lasIn(is))
        laggTill(t);
}

void TransaktionsLista::skrivUt(ostream &os) {
    os << "Antal trans = " << antal_transaktioner << "\n";

    Transaktion transaktion;
    transaktion.skrivTitel(cout);
    for(int i = 0; i < antal_transaktioner; i++)
        transaktioner[i].skrivUt(os);

}

void TransaktionsLista::laggTill(Transaktion &t) {
    transaktioner[antal_transaktioner++] = t;
}

double TransaktionsLista::totalKostnad() {
    double totKostnad = 0;

    for(int i = 0; i < antal_transaktioner; i++)
        totKostnad += transaktioner[i].hamtaBelopp();
    
    return totKostnad;
}

double TransaktionsLista::liggerUteMed(const string &namnet) {
    double summan = 0;

    for(int i = 0; i < antal_transaktioner; i++){
        if(transaktioner[i].hamtaNamn() == namnet)
            summan += transaktioner[i].hamtaBelopp() *
                    (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    }
    return summan;
}

double TransaktionsLista::arSkyldig(const string &namnet) {
    double skyldig = 0;
    for(int i = 0; i < antal_transaktioner; i++){
        if(transaktioner[i].finnsKompis(namnet)){
            skyldig += transaktioner[i].hamtaBelopp() / ( transaktioner[i].hamtaAntalKompisar() + 1) ;
        }
    }
    return skyldig;
}

PersonLista TransaktionsLista::FixaPersoner() {

    PersonLista personLista;
    string namn;
    double liggerUte;
    double skyldigAndra;

    for(int i = 0; i < antal_transaktioner; i++){
         namn = transaktioner[i].hamtaNamn();
         if(!personLista.finnsPerson(namn)){
             namn = transaktioner[i].hamtaNamn();
             liggerUte = liggerUteMed(namn);
             skyldigAndra = arSkyldig(namn);
             Person person(namn, liggerUte, skyldigAndra);
             personLista.laggTill(person);
         }
    }
    return personLista;
}
/*
// -------------------------------------------------------
// Rapport om uppgiften

=================================
Testdata 1
=================================

Startar med att läsa från en fil.

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
1

Antal trans = 10
Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar
190615 	transp 	Eva 	6000 	5	Bosse	Kristin	Paul	Torsten	Stina
190721 	mat 	Eva 	300 	2	Bosse	Kristin
190721 	mat 	Paul	400 	2	Torsten	Stina
190721 	transp 	Bosse	5000 	3	Eva	Kristin	Paul
190721 	transp 	Stina	5000 	1	Torsten
190722 	boende 	Kristin	200 	1	Eva
190722 	mat 	Eva 	300 	2	Kristin	Bosse
190723 	mat 	Torsten	300 	2	Paul	Stina
190724 	mat 	Paul	200 	1	Stina
190725 	transp 	Eva 	600 	3	Bosse	Kristin	Paul

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
6

Nu skapar vi en personarray och reder ut det hela!
Eva ligger ute med 5850 och är skyldig 1350. Skall ha 4500 från potten!
Paul ligger ute med 366.667 och är skyldig 2500. Skall lägga 2133.33 till potten!
Bosse ligger ute med 3750 och är skyldig 1350. Skall ha 2400 från potten!
Stina ligger ute med 2500 och är skyldig 1333.33. Skall ha 1166.67 från potten!
Kristin ligger ute med 100 och är skyldig 2600. Skall lägga 2500 till potten!
Torsten ligger ute med 200 och är skyldig 3633.33. Skall lägga 3433.33 till potten!

Potten stämmer inte!
Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
2

Ange transaktion i följande format
Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar
190726
mat
Kristin
500
3
Bosse Eva Torsten

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
6

Nu skapar vi en personarray och reder ut det hela!
Eva ligger ute med 5850 och är skyldig 1475. Skall ha 4375 från potten!
Paul ligger ute med 366.667 och är skyldig 2500. Skall lägga 2133.33 till potten!
Bosse ligger ute med 3750 och är skyldig 1475. Skall ha 2275 från potten!
Stina ligger ute med 2500 och är skyldig 1333.33. Skall ha 1166.67 från potten!
Kristin ligger ute med 475 och är skyldig 2600. Skall lägga 2125 till potten!
Torsten ligger ute med 200 och är skyldig 3758.33. Skall lägga 3558.33 till potten!

Potten stämmer inte!
Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
1

Antal trans = 11
Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar
190615 	transp 	Eva 	6000 	5	Bosse	Kristin	Paul	Torsten	Stina
190721 	mat 	Eva 	300 	2	Bosse	Kristin
190721 	mat 	Paul	400 	2	Torsten	Stina
190721 	transp 	Bosse	5000 	3	Eva	Kristin	Paul
190721 	transp 	Stina	5000 	1	Torsten
190722 	boende 	Kristin	200 	1	Eva
190722 	mat 	Eva 	300 	2	Kristin	Bosse
190723 	mat 	Torsten	300 	2	Paul	Stina
190724 	mat 	Paul	200 	1	Stina
190725 	transp 	Eva 	600 	3	Bosse	Kristin	Paul
190726 	mat 	Kristin	500 	3	Bosse	Eva	Torsten

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
3

Den totala kostnanden för resan var 18800

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
4

Ange personen: Eva
Eva är skyldig 1475

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
5

Ange personen: Eva
Eva ligger ute med 5850

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
0

Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar

Process finished with exit code 0

=================================
Testdata 2
=================================

Startar med att läsa från en fil.

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
1

Antal trans = 4
Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar
190721 	mat 	Eva 	200 	1	Bosse
190722 	mat 	Eva 	400 	1	Bosse
190725 	transp 	Eva 	600 	1	Bosse
190725 	mat 	Bosse	200 	1	Eva

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
6

Nu skapar vi en personarray och reder ut det hela!
Eva ligger ute med 600 och är skyldig 100. Skall ha 500 från potten!
Bosse ligger ute med 100 och är skyldig 600. Skall lägga 500 till potten!

Potten stämmer!
Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Skriv ut information om alla transaktioner.
2. Läs in en transaktion från tangentbordet.
3. Beräkna totala kostnaden.
4. Hur mycket ärr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA
0

Datum 	Typ 	Namn 	Belopp	Antal och lista av kompisar

Process finished with exit code 0

 */
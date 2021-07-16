#include <iostream>

using namespace std;

struct TIME
{
    int seconds;
    int minutes;
    int hours;
};

int calcDiff(TIME time, TIME time1);

int main () {
    int comp_counter = 0;
    int best_start_number;
    int temp_start_number;
    int temp_time;
    int best_time = std::numeric_limits<int>::max();

    struct TIME t1, t2;

    cout << "Startnummer? ";
    cin >> temp_start_number;
    best_start_number = temp_start_number;

    while (temp_start_number >= 1) {
        comp_counter++;
        cout << "Starttid? ";
        cin >> t1.hours >> t1.minutes >> t1.seconds;

        cout << "Måltid? ";
        cin >> t2.hours >> t2.minutes >> t2.seconds;

        temp_time = calcDiff(t1, t2);

        if (temp_time < best_time) {
            best_start_number = temp_start_number;
            best_time = temp_time;
        }

        cout << "Startnummer? ";
        cin >> temp_start_number;
    }

    if(comp_counter == 0)
        cout << "Inga tävlande";
    if(comp_counter > 0) {
        int hour = best_time / 3600;
        int minute = (best_time % 3600) / 60;
        int second = best_time % 60;

        cout << "Vinnare är startnr: " << best_start_number << "\n";
        cout << "Tim: " << hour << " Min: " << minute << " Sek: " << second << " \n";
        cout << "Antal tävlande: " << comp_counter << "\n";
        cout << "Programmet avslutas" << endl;
    }
    return 0;
}

int calcDiff(TIME t1, TIME t2) {

    int tot_diff = 0;
    int counter = 0;

    while(1) {

        if(t1.hours == t2.hours && t1.minutes == t2.minutes && t1.seconds == t2.seconds)
            break;

        tot_diff++;
        t1.seconds++;
        if(t1.seconds == 60){
            t1.minutes++;

            if(t1.minutes == 60){
                t1.hours++;
                t1.minutes = 0;

                if(t1.hours == 24){
                    t1.hours = 0;
                }
            }
            t1.seconds = 0;
        }
        counter ++;
    }

    return tot_diff;
}


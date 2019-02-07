#include <iostream>
#include <cstdlib>
#include <queue>
#include "officehours_Revised.h"

using namespace std;

averager waiting_time_average;
averager service_time_average;
averager extended_professor_time_average;

int random_number() {
    return ((rand() % 14) + 5); // service time is between 5 - 15 minutes per student
}

void office_hours_func(double prob, unsigned int total_time) {
    queue<unsigned int> service_times;
    queue<unsigned int> wait_times; //arrival_times
    unsigned int next;
    bool_source arrival(prob);

    officehours office_hour;
    averager current_wait_times;
    averager current_service_times;
    unsigned int current_time;

    for (current_time = 1; current_time <= total_time; ++current_time) {
        if (arrival.query()){
            int service_time = random_number();
            service_times.push(service_time);
            wait_times.push(current_time);

            current_service_times.next_number(service_time);
            service_time_average.next_number(service_time);
        }
        if ((!office_hour.is_busy()) && (!service_times.empty())) {
            next = service_times.front();
            service_times.pop();

            int wait_time = wait_times.front();
            wait_times.pop();
            current_wait_times.next_number(current_time - wait_time);
            waiting_time_average.next_number(current_time - wait_time);

            office_hour.start(next);
        }
        office_hour.one_second();
    }

    while(!service_times.empty()) {
        if (!office_hour.is_busy()) {
            next = service_times.front();
            service_times.pop();

            int wait_time = wait_times.front();
            wait_times.pop();
            current_wait_times.next_number(current_time - wait_time);
            waiting_time_average.next_number(current_time - wait_time);

            office_hour.start(next);
        }
        office_hour.one_second();
        current_time++;
    }
    extended_professor_time_average.next_number(current_time-total_time);
}

int main()
{
    int runs; // 100
    double prob; // 0.2

    cout << "Enter number of office hours to run: " <<endl;
    cin >> runs;
    cout <<endl;
    cout << "Enter probability of a student arriving in any given second: " <<endl;
    cin >> prob;

    for (int i=1; i<=runs; i++) {
        office_hours_func(prob, 60);
    }

    cout << "After running " << runs << " rounds " << endl;
    cout.precision(5);
    cout << "Average time a student waits: " << waiting_time_average.average() << " seconds" << endl;
    cout << "Average time a student meets with professor: " << service_time_average.average() << " seconds" << endl;
    cout << "Average time professor stays after 60 seconds: " << extended_professor_time_average.average() << " seconds"<< endl;


    return 0;
}


#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

/*
Author: Teghveer Ateliey
Date created: Jan 18, 2023
Last modified: Jan 18, 2023
Purpose: To prove the birthday paradox by calculating experiments at using various sizes of groups of people
*/

// function declaration
void birthdayParadox();
bool duplicateBDay(int bDays[], int day, int length);

// birthdayParadox function takes no inputs, runs 100 experiments for various numbers of people and prints results
// results are printed in the format: "number of people", "experiments with duplicate bDay", "measured probability"
void birthdayParadox() {
    int experiments = 100;
    // number of people in experiment starts at 5 and increases by 5 until 100
    for (int n = 5; n <= 100; n+=5) {
        // sameBDay records how many experiments resulted in a duplicate birthday for each number of people
        int sameBDay = 0;
        int bDays[n];
        // repeats the experiment 100 times for each number of people and records results
        for (int i = 0; i < experiments; i++) {
            // iterates through the array of birthdays and sets each index to random day of the year
            for (int j = 0; j < n; j++) {
                // randomly chooses a day in a standard year, plus 1 prevents getting a "day 0"
                int day = rand() % 365 + 1;
                bDays[j] = day;
            }
            // iterates through array and checks each index for duplicates
            for (int k = 0; k < n; k++) {
                // if index k has a duplicate value in the array then terminate the loop and increment sameBDay counter
                if (duplicateBDay(bDays, k, n)) {
                    sameBDay++;
                    break;
                }
            }
        }
        // calculates measured probability and prints results of all 20 experiments
        double measuredProbability = (double)sameBDay / experiments;
        cout << n << "," << sameBDay << "," << measuredProbability << endl;
    }
} // end of birthdayParadox function

// duplicateBDay function takes int array of birthdays, int day, and int length of bDays as input
// function returns true only if value in array bDays at index day is also found in another index in the array
bool duplicateBDay(int bDays[], int day, int length) {
    // iterates through list and returns true if the values at both indexes match
    for (int i = 0; i < length; i++) {
        if (bDays[i] == bDays[day] && i != day) {
            // will not return true if indexes are the same
            return true;
        }
    }
    // returns false if value was not found in array
    return false;
} // end of duplicateBDay function

// start of main function
int main() {
    // ensures that rand() function consistently returns random numbers
    srand(time(0));
    birthdayParadox();

    return EXIT_SUCCESS;
} // end of main function
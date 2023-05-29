/*
*********************************************************************************
Name: Ayush Prasai
Student ID: 113515209
Email: Aprasai@myseneca.ca
Date of Completion: 2023-05-28
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
*********************************************************************************
*/
#ifndef SDDS_TIMER_H__
#define SDDS_TIMER_H__
#include <iostream>
#include <chrono>
using namespace std;

namespace sdds {
    class Timer {
        std::chrono::time_point<std::chrono::steady_clock> begin;

    public:
        void start();
        long long stop();
    };
}

#endif 
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include "Timer.h"
using namespace std::chrono;

namespace sdds {
   void Timer::start() {
      begin = steady_clock::now();
   }
   long long Timer::stop() {   //measure elapsed time: https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
      auto end = steady_clock::now();
      auto duration = duration_cast<nanoseconds>(end - begin);
      return duration.count();
   }
}
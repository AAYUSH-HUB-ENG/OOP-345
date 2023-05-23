/*
*********************************************************************************
NAME: Ayush Prasai
Student ID: 113515209
Email: Aprasai@myseneca.ca
Date of Completion: 2023-05-20
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
*********************************************************************************
*/
#ifndef CARADS_H
#define CARADS_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"iomanip"
#include <cstring>
extern double g_taxrate;
extern double g_discount;

namespace sdds {
	void listArgs(int argc, char* argv[]);
	class Cars {
		char m_brand[11]{};
		char m_model[16]{};
		int m_year{};
		double m_price{};
		char m_status{};
		bool m_discount{};
	public:
		Cars();
		void read(std::istream& is);
		void display(bool reset) const;
		char getStatus() const;
	};
}
#endif
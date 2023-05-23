/*
*********************************************************************************
NAME: Ayush Prasai
Student ID: 113515209
Email: Aprasai@myseneca.ca
Date of Completion: 2023-05-20 4:40 pm
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
*********************************************************************************
*/
#include "carads.h"
double g_taxrate;
double g_discount;

namespace sdds {
	void listArgs(int argc, char* argv[]) {

		std::cout << "Command Line:" << std::endl;
		std::cout << "--------------------------" << std::endl;
		for (int i = 0; i < argc; i++) {
			std::cout << "  " << i + 1 << ": " << argv[i] << std::endl;
		}
		std::cout << "--------------------------" << std::endl << std::endl;
	}

	Cars::Cars() {
		m_brand = nullptr;
		m_model[0] = '\0';
		m_year = 0;
		m_price = 0.0;
		m_status = ' ';
		m_discount = false;
	}

	void Cars::read(std::istream& is) {
		std::string temp;
		if (is.good())
		{
			deallocator();
			is >> m_status;
			is.ignore();
			std::getline(is, temp, ',');
			m_brand = new char[temp.length() + 1];
			strcpy(m_brand, temp.c_str());

			is.getline(m_model, 16, ',');
			is >> m_year;
			is.ignore();
			is >> m_price;
			is.ignore();
			char Temp;
			is >> Temp;
			if (Temp == 'Y') {
				m_discount = true;
			}
			else
			{
				m_discount = false;
			}
			is.ignore();
		}
	}

	void Cars::display(bool reset) const {
		static int counter = 1;
		if (reset) {
			counter = 1;
		}
		if (strlen(m_brand) == 0)
		{
			std::cout << std::setw(2) << counter << ". No Car" << std::endl;
		}
		else {
			std::cout << std::setw(2) << std::left << counter << ". ";
			std::cout << std::left << std::setw(10) << m_brand << "| ";
			std::cout << std::left << std::setw(15) << m_model << "| ";
			std::cout << std::left << std::setw(4) << m_year << " |";
			std::cout << std::fixed << std::setprecision(2) << std::right << std::setw(12) << m_price * (1 + g_taxrate) << "|";

			if (m_discount)
			{
				std::cout << std::setw(12) << std::right << m_price * (1 + g_taxrate) * (1 - g_discount);
			}
		}
		std::cout << std::endl;
		++counter;


	}

	char Cars::getStatus() const {
		return m_status;
	}
	void Cars::deallocator() {
		delete[] m_brand;
	}

	Cars::~Cars() {
		deallocator();
	}

	Cars::Cars(const Cars& car) {
		
		if (car.m_brand != nullptr) {
			m_brand = new char[strlen(car.m_brand) + 1];
			strcpy(m_brand, car.m_brand);
			strcpy(m_model, car.m_model);
			m_year = car.m_year;
			m_price = car.m_price;
			m_status = car.m_status;
			m_discount = car.m_discount;
		}
		else {
			m_brand = nullptr;
		}
	}

	Cars& Cars::operator=(const Cars& car) {
		if (this != &car) {
			deallocator();
			if (car.m_brand != nullptr) {
				m_brand = new char[strlen(car.m_brand) + 1];
				strcpy(m_brand, car.m_brand);
				strcpy(m_model, car.m_model);
				m_year = car.m_year;
				m_price = car.m_price;
				m_status = car.m_status;
				m_discount = car.m_discount;
			}
			else {
				m_brand = nullptr;
			}
		}
		return *this;
	}

	Cars::operator bool() const {
		return m_status == 'N';
	}

	std::istream& operator>>(std::istream& is, Cars& car) {
		car.read(is);
		return is;
	}

	void operator>>(const Cars& car1, Cars& car2) {
		car2 = car1;
	}


}//namespace sdds



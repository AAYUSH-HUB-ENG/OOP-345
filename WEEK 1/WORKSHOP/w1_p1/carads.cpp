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
#include "carads.h"
double g_taxrate;
double g_discount;
//comment
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
		m_brand[0] = '\0';
		m_model[0] = '\0';
		m_year = 0;
		m_price = 0.0;
		m_status = ' ';
		m_discount = false;
	}

	void Cars::read(std::istream& is) {
		if (is.good())
		{
			is >> m_status;
			is.ignore();
			is.getline(m_brand, 11, ',');
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
			std::cout << std::left << std::setw(15) << m_model <<"| ";
			std::cout << std::left << std::setw(4) << m_year << " |";
			std::cout << std::fixed << std:: setprecision(2) <<std::right << std::setw(12) << m_price * (1 + g_taxrate) << "|";
			
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
}

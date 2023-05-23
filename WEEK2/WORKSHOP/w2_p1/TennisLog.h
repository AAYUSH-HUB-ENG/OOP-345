/*
*********************************************************************************
Name: Ayush Prasai
Student ID: 113515209
Email: Aprasai@myseneca.ca
Date of Completion: 2023-05-18
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
*********************************************************************************
*/
#ifndef TENNISLOG_H
#define TENNISLOG_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS

namespace sdds {
	struct TennisMatch {
		std::string m_tournament_id{};
		std::string m_tournament_name {};
		unsigned int m_match_id{};
		std::string m_winner {};
		std::string m_loser {};

		friend std::ostream& operator<<(std::ostream& os, const TennisMatch& match);
		TennisMatch& operator = (const TennisMatch& match);
	};

    class TennisLog {
		TennisMatch* m_matches{};
		size_t m_numOfMatches{};

    public:
        TennisLog();
        ~TennisLog();
		TennisLog(const std::string filename);
		void addMatch(const TennisMatch& match);
		TennisLog findMatches(const std::string& playerName);
		const TennisMatch& operator[](size_t index) const;
		operator size_t() const;
    };
	
}




#endif
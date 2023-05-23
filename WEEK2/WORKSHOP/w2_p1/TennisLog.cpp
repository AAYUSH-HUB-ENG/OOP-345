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
#include "TennisLog.h"

namespace sdds {
    std::ostream& operator<<(std::ostream& os, const TennisMatch& match) {
        if (match.m_tournament_id.empty() || match.m_tournament_name.empty() || match.m_match_id <= 0 ||
            match.m_winner.empty() || match.m_loser.empty()) {
            os << "Empty Match";
        }
        else {
            os << std::right << std::setw(20) << std::setfill('.') << "Tourney ID";
            os << " :";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_tournament_id << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Match ID";
            os << " :";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_match_id << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Tourney";
            os << " :";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_tournament_name << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "m_winner";
            os << " :";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_winner << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "m_loser";
            os << " :";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_loser << std::endl;
        }
        return os;
    }
    TennisLog::TennisLog() : m_matches(nullptr), m_numOfMatches(0) {}

    TennisLog::~TennisLog() { delete[] m_matches; }

    TennisLog::TennisLog(const std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            std::getline(file, line); // Skip the first line

            // Count the number of matches in the file
            while (std::getline(file, line)) {
                m_numOfMatches++;
            }

            file.clear();
            file.seekg(0, std::ios::beg); // Reset file position to the beginning

            // Dynamically allocate memory for the array based on the m_numOfMatches
            m_matches = new TennisMatch[m_numOfMatches];

            int matchIndex = 0;

            std::getline(file, line); // Skip the first line

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string token;

                // Read each field separated by commas
                std::getline(iss, token, ',');
                m_matches[matchIndex].m_tournament_id = token;

                std::getline(iss, token, ',');
                m_matches[matchIndex].m_tournament_name = token;

                std::getline(iss, token, ',');
                m_matches[matchIndex].m_match_id = std::stoi(token);

                std::getline(iss, token, ',');
                m_matches[matchIndex].m_winner = token;

                std::getline(iss, token, ',');
                m_matches[matchIndex].m_loser = token;

                // Call the default constructor explicitly to initialize the string members
                m_matches[matchIndex] = TennisMatch();

                matchIndex++;
            }

            file.close();
        }
        else {
            std::cout << "Error Opening file: " << filename << std::endl;
        }
    }




    TennisMatch& TennisMatch::operator = (const TennisMatch& match) {
        if (this != &match) {
            m_tournament_id = match.m_tournament_id;
            m_tournament_name = match.m_tournament_name;
            m_match_id = match.m_match_id;
            m_winner = match.m_winner;
            m_loser = match.m_loser;
        }
        return *this;
    }

    void TennisLog::addMatch(const TennisMatch& match) {
        TennisMatch* newMatches = new TennisMatch[m_numOfMatches + 1];

        for (size_t i = 0; i < m_numOfMatches; ++i) {
            newMatches[i] = m_matches[i];
        }
        m_matches[m_numOfMatches] = match;

        delete[] m_matches;

        m_matches = newMatches;
        m_numOfMatches++;
    }

    TennisLog TennisLog::findMatches(const std::string& playerName) {
        TennisLog log;
        for (size_t i = 0; i < m_numOfMatches; ++i) {
            if (m_matches[i].m_winner == playerName || m_matches[i].m_loser == playerName) {
                log.addMatch(m_matches[i]);
            }
        }
        return log;
    }

    
    const TennisMatch& TennisLog::operator[](size_t index) const {
        if (index < m_numOfMatches) {
            return m_matches[index];
        }
        else {
            static TennisMatch emptyMatch;  // Empty TennisMatch object
            return emptyMatch;
        }
    }

    TennisLog::operator size_t() const {
        return m_numOfMatches;
    }
}//namespace sdds
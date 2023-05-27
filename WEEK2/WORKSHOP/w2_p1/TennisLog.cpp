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
            //if the TennisMatch Object is empty
            os << "Empty Match";
        }
        else {
            os << std::right << std::setw(20) << std::setfill('.') << "Tourney ID";
            os << " : ";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_tournament_id << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Match ID";
            os << " : ";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_match_id << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Tourney";
            os << " : ";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_tournament_name << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Winner";
            os << " : ";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_winner << std::endl;
            os << std::right << std::setw(20) << std::setfill('.') << "Loser";
            os << " : ";
            os << std::left << std::setw(30) << std::setfill('.') << match.m_loser << std::endl;
        }
        return os;
    }


    TennisLog::TennisLog() {
        m_numOfMatches = 25001;
        m_matches = new TennisMatch[m_numOfMatches];
        for (int i = 0; i < m_numOfMatches; i++) {
            m_matches->m_tournament_id = "";
            m_matches->m_tournament_name = "";
            m_matches->m_match_id = 0;
            m_matches->m_winner = "";
            m_matches->m_loser = "";
        }
    }



    TennisLog::TennisLog(const std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;

            // count the number of matches in the file
            while (std::getline(file, line)) {
                m_numOfMatches++;
            }
            m_numOfMatches -= 1; //this doesnt count the fist line of the file.

            file.clear();
            file.seekg(0, std::ios::beg); //https://stackoverflow.com/questions/5343173/returning-to-beginning-of-file-after-getline
            // dynamically allocate memory for the array based on the m_numofmatches
            m_matches = new TennisMatch[m_numOfMatches];

            int matchindex = 0;

            std::getline(file, line); // skip the first line

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string token;

                // read each field separated by commas
                std::getline(iss, token, ',');
                m_matches[matchindex].m_tournament_id = token;

                std::getline(iss, token, ',');
                m_matches[matchindex].m_tournament_name = token;

                std::getline(iss, token, ',');
                m_matches[matchindex].m_match_id = std::stoi(token);

                std::getline(iss, token, ',');
                m_matches[matchindex].m_winner = token;

                std::getline(iss, token, ',');
                m_matches[matchindex].m_loser = token;

                // call the default constructor explicitly to initialize the string members
                //m_matches[matchindex] = TennisMatch();

                matchindex++;
            }

            file.close();
        }
        else {
            return;
        }
    }


    void TennisLog::addMatch(const TennisMatch& match) {
        if (m_matches->m_tournament_id.empty()) {
            m_numOfMatches = 0;
        }
        m_matches[m_numOfMatches].m_tournament_id = match.m_tournament_id;
        m_matches[m_numOfMatches].m_tournament_name = match.m_tournament_name;
        m_matches[m_numOfMatches].m_match_id = match.m_match_id;
        m_matches[m_numOfMatches].m_winner = match.m_winner;
        m_matches[m_numOfMatches].m_loser = match.m_loser;
        m_numOfMatches++;
    }

    //void TennisLog::addMatch(const TennisMatch& match) {
    //    TennisMatch* newMatches = new TennisMatch[m_numOfMatches + 1];
    //    for (size_t i = 0; i < m_numOfMatches; ++i) {
    //        newMatches[i] = m_matches[i];
    //    }
    //    m_matches[m_numOfMatches] = match;
    //    delete[] m_matches;
    //    m_matches = newMatches;
    //    m_numOfMatches++;
    //}

    TennisLog TennisLog::findMatches(const std::string& playerName) {
        TennisLog log;
        log.m_numOfMatches = 0;
        for (int i = 0; i < m_numOfMatches; ++i) {
            if (m_matches[i].m_winner == playerName || m_matches[i].m_loser == playerName) {
                log.addMatch(m_matches[i]);
            }
        }
        return log;
    }


    const TennisMatch& TennisLog::operator[](size_t index) const {
        if (index < static_cast<size_t>(m_numOfMatches)) {
            return m_matches[index];
        }
        else {
            return m_matches[0];
        }
    }

    TennisLog::operator size_t() const {
        return m_numOfMatches;
    }

    TennisLog::~TennisLog() { delete[] m_matches; m_matches = nullptr; }
}//namespace sdds

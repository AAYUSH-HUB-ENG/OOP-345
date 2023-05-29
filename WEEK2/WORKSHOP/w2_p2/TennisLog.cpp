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
#include "TennisLog.h"
using namespace std;
namespace sdds {

    ostream& operator<< (ostream& os, const TennisMatch& N) {
        if (N.m_match_id != 0) {   //If a given TennisMatch object is in an empty state
            os << setfill('.') << right << setw(20) << "Tourney ID" << " : " << setfill('.') << left << setw(30) << N.m_tournament_id << endl;
            os << setfill('.') << right << setw(20) << "Match ID" << " : " << setfill('.') << left << setw(30) << N.m_match_id << endl;
            os << setfill('.') << right << setw(20) << "Tourney" << " : " << setfill('.') << left << setw(30) << N.m_tournament_name << endl;
            os << setfill('.') << right << setw(20) << "winner" << " : " << setfill('.') << left << setw(30) << N.m_winner << endl;
            os << setfill('.') << right << setw(20) << "loser" << " : " << setfill('.') << left << setw(30) << N.m_loser << endl;
        }
        else {
            os << "Empty Match";
        }
        return os;
    }
    

    TennisLog::TennisLog() {
        m_matches = nullptr;
    }

    TennisLog::TennisLog(const char* filename) {
        m_numOfMatches = 0;
        std::ifstream in(filename);
        string line;
        while (getline(in, line)) {   //go through the file line by line 
            m_numOfMatches++;
        }
        m_numOfMatches -= 1;    //don't count the heading line in the file
        m_matches = new TennisMatch[m_numOfMatches];   //allocate dynamic memory for the array of matches based on the number found

        //How to rewind an ifstream object after hitting the end of file? Use seekg sets the cursor position. https://stackoverflow.com/questions/28331017/rewind-an-ifstream-object-after-hitting-the-end-of-file
        in.clear();
        in.seekg(0);   //reread the file from the beginning by seekg(0): https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/#:~:text=seekg()%20is%20a%20function,stream%20from%20a%20given%20file.

        //In a .csv file, the cells are separated by ',', while the rows end with a '\n', the rest is like a regular .txt file
        in.ignore(256, '\n');   //ignore until the end of the first line
        int i = 0;
        while (getline(in, line)) {   //go through the file line by line 
            stringstream sstr(line);
            string c_m_tournament_id, c_m_tournament_name, c_m_match_id, c_m_winner, c_m_loser;

            getline(sstr, c_m_tournament_id, ',');
            getline(sstr, c_m_tournament_name, ',');
            getline(sstr, c_m_match_id, ',');
            getline(sstr, c_m_winner, ',');
            getline(sstr, c_m_loser);

            m_matches[i].m_tournament_id = c_m_tournament_id;
            m_matches[i].m_tournament_name = c_m_tournament_name;
            m_matches[i].m_match_id = stoi(c_m_match_id);
            m_matches[i].m_winner = c_m_winner;
            m_matches[i].m_loser = c_m_loser;

            i++;
        }

        in.close();
    }

    void TennisLog::addMatch(const TennisMatch& TM) {
        TennisMatch* temp = new TennisMatch[m_numOfMatches];
        for (size_t i = 0; i < m_numOfMatches; i++) {
            temp[i] = m_matches[i];
        }
        delete[] m_matches;
        m_matches = new TennisMatch[m_numOfMatches + 1];

        for (size_t i = 0; i < m_numOfMatches; i++) {
            m_matches[i] = temp[i];
        }
        delete[] temp;
        m_matches[m_numOfMatches].m_tournament_id = TM.m_tournament_id;
        m_matches[m_numOfMatches].m_tournament_name = TM.m_tournament_name;
        m_matches[m_numOfMatches].m_match_id = TM.m_match_id;
        m_matches[m_numOfMatches].m_winner = TM.m_winner;
        m_matches[m_numOfMatches].m_loser = TM.m_loser;
        m_numOfMatches++;

    }

    TennisLog TennisLog::findMatches(const char* playerName) {
        TennisLog allMatchings;
        allMatchings.m_numOfMatches = 0;
        for (size_t i = 0; i < m_numOfMatches; i++) {
            if (playerName == m_matches[i].m_winner || playerName == m_matches[i].m_loser) {
                allMatchings.addMatch(m_matches[i]);
            }
        }
        return allMatchings;
    }

    const TennisMatch TennisLog::operator[](size_t index) const {

        if (index < m_numOfMatches) {
            return m_matches[index];
        }
        TennisMatch temp;
        return temp;
    }

    TennisLog::operator size_t() const {
        return m_numOfMatches;
    }

    //rule-of-five
    TennisLog::TennisLog(const TennisLog& TL) {
        *this = TL;
    }

    TennisLog::TennisLog(TennisLog&& TL) noexcept {
        *this = move(TL);
    }

    TennisLog& TennisLog::operator=(const TennisLog& TL) {

        if (this != &TL) {
            delete[] m_matches;
            m_numOfMatches = TL.m_numOfMatches;
            m_matches = new TennisMatch[m_numOfMatches];
            for (size_t i = 0; i < m_numOfMatches; i++) {
                m_matches[i] = TL.m_matches[i];
            }
        }

        return *this;
    }

    TennisLog& TennisLog::operator=(TennisLog&& TL) noexcept {

        if (this != &TL) {
            delete[] m_matches;
            m_numOfMatches = TL.m_numOfMatches;
            TL.m_numOfMatches = 0;
            m_matches = TL.m_matches;
            TL.m_matches = nullptr;
        }

        return *this;
    }

    TennisLog::~TennisLog() {
        delete[] m_matches;
        m_matches = nullptr;
    }
}//namespace sdds
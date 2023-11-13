#ifndef SHIP_HPP
#define SHIP_HPP


#include <iostream>
#include <string>
#include <vector>

#include "utility.hpp"

using namespace std;

struct Ship {
    Ship(unsigned int t_size, char t_ID)
    {
        m_size = t_size;
        m_ID = t_ID;
    }
    void setPosition(unsigned int t_row, unsigned int t_col, char t_orientation)
    {
        m_row = t_row;
        m_column = t_col;
        m_orientation = t_orientation;
        m_lives = m_size;
    }
    void printPosition()
    {
        cout << "Position: "<< endl;
        cout << "row: " << m_row << " | column: " << m_column  << " | orientation: " << m_orientation << endl;
        cout << "Identifier: " << m_ID << " | Lives: " << m_lives << endl;
    }
    unsigned int m_size;
    unsigned int m_lives;
    unsigned int m_row;
    unsigned int m_column;
    char m_orientation;
    char m_ID;
};

#endif // SHIP_HPP

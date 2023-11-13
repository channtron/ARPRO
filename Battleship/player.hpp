#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "ship.hpp"
#include "utility.hpp"

using namespace std;



struct Player {

    Player() // NPC
    {
        vector<char> row;
        row.resize(m_numberColumns);
        for (auto &cell : row)
            cell = '~';
        for (auto index = 0; index < m_numberRows; index++)
            m_grid.push_back(row);

        m_oponentGrid = m_grid;

    }
    void fillGrid( char man = 'n')
    {
        if (m_human && man == 'y')
            fillManGrid();
        else
            fillRandomGrid();
    }
    pair <unsigned int, unsigned int> getImpact()
    {
        if (m_human)
            return getManualImpact();
        return getRandomImpact();
    }
    bool checkImpact (pair <unsigned int, unsigned int> coordinates){
        if (m_grid[coordinates.first][coordinates.second] == '~')
        {
            m_grid[coordinates.first][coordinates.second] = 'x';
            return false;
        }
        else
        {
            m_grid[coordinates.first][coordinates.second] = 'o';
            m_lives--;
            return true;
            // TODO switch case for taking a live from ship
        }
    }
    void recordImpact(const bool impact){
        if (impact == true)
            m_oponentGrid[m_lastImpact.first][m_lastImpact.second] = 'o';
        else
            m_oponentGrid[m_lastImpact.first][m_lastImpact.second] = 'x';
    }
    void printYourGrid(){plotBoard(m_grid);}
    void printOponentGrid(){plotBoard(m_oponentGrid);}
    unsigned int getLives() {return m_lives;}
    bool isHuman() {return m_human;}
    void setHuman() {m_human = true;}
    void setNPC() {m_human = false;}

    string m_ID{""};

private :
    void emptyGrid()
    {
        for (auto &row : m_grid)
        {
            for (char &cell : row)
                cell = '~';
        }
    }
    int placeShip(Ship t_ship)
    {
        if (t_ship.m_orientation == 'h')
        {
            if ((t_ship.m_size + t_ship.m_column)-1 < m_numberColumns) // Test limit situation (AC in colum 5)
            {
                for (auto i = 0; i<t_ship.m_size; i++)
                {
                    if(m_grid[t_ship.m_row][t_ship.m_column + i] != '~')
                        return -1; // Invalid position
                }
                for (auto i = 0; i<t_ship.m_size; i++)
                    m_grid[t_ship.m_row][t_ship.m_column + i] =t_ship.m_ID;

            }
            else
                return -1;// ERROR
        }
        else
        {
            if ((t_ship.m_size + t_ship.m_row)-1 < m_numberRows) // Test limit situation (AC in colum 5)
            {
                for (auto i = 0; i<t_ship.m_size; i++)
                {
                    if(m_grid[t_ship.m_row + i][t_ship.m_column] != '~')
                        return -1; // Invalid position
                }
                for (auto i = 0; i<t_ship.m_size; i++)
                    m_grid[t_ship.m_row + i][t_ship.m_column] =t_ship.m_ID;

            }
            else
                return -1;// ERROR
        }
        return 0;
    }
    void getRandomPlace(Ship &t_ship)
    {
        int horizontal;
        int row;
        int column;
        horizontal = getRandomInt(1);
        if (horizontal == 1)
        {
            row = getRandomInt(m_numberRows-1);
            column = getRandomInt(m_numberColumns-t_ship.m_size);
            t_ship.setPosition(row, column, 'h');
        }
        else
        {
            row = getRandomInt(m_numberRows-t_ship.m_size);
            column = getRandomInt(m_numberColumns-1);
            t_ship.setPosition(row, column, 'v');
        }
    }
    void fillManGrid()
    {
        emptyGrid();
        int row;
        int col;
        char orient;
        cout << "\033c";
        plotBoard(m_grid);
        //Set A ship
        do {
            cout << "Introduce a valid row number, column number and orientation (h/v) for " << m_aircraftCarrier.m_ID;
            cin >> row >> col >> orient;
            m_aircraftCarrier.setPosition(row, col, orient);
        }while (placeShip(m_aircraftCarrier) == -1);
        cout << "\033c";
        plotBoard(m_grid);
        do {
            cout << "Introduce a valid row number, column number and orientation (h/v) for " << m_cruiser.m_ID;
            cin >> row >> col >> orient;
            m_cruiser.setPosition(row, col, orient);
        }while (placeShip(m_cruiser) == -1);
        cout << "\033c";
        plotBoard(m_grid);
        do {
            cout << "Introduce a valid row number, column number and orientation (h/v) for " << m_destroyer.m_ID;
            cin >> row >> col >> orient;
            m_destroyer.setPosition(row, col, orient);
        }while (placeShip(m_destroyer) == -1);
        cout << "\033c";
        plotBoard(m_grid);
        do {
            cout << "Introduce a valid row number, column number and orientation (h/v) for " << m_submarine.m_ID;
            cin >> row >> col >> orient;
            m_submarine.setPosition(row, col, orient);
        }while (placeShip(m_submarine) == -1);
        cout << "\033c";
        plotBoard(m_grid);
        do {
            cout << "Introduce a valid row number, column number and orientation (h/v) for " << m_mineSwepper.m_ID;
            cin >> row >> col >> orient;
            m_mineSwepper.setPosition(row, col, orient);
        }while (placeShip(m_mineSwepper) == -1);
    }
    void fillRandomGrid()
    {
        emptyGrid();
        //Set A ship
        do {
        getRandomPlace(m_aircraftCarrier);
        }while (placeShip(m_aircraftCarrier) == -1);
        do {
        getRandomPlace(m_cruiser);
        }while (placeShip(m_cruiser) == -1);
        do {
        getRandomPlace(m_destroyer);
        }while (placeShip(m_destroyer) == -1);
        do {
        getRandomPlace(m_submarine);
        }while (placeShip(m_submarine) == -1);
        do {
        getRandomPlace(m_mineSwepper);
        }while (placeShip(m_mineSwepper) == -1);
    }
    pair <unsigned int, unsigned int> getManualImpact()
    {
        cout << "Select your coordinates for your next strike: (row, col) ";
        cin >> m_lastImpact.first >> m_lastImpact.second;
        return  m_lastImpact;
    }
    pair <unsigned int, unsigned int> getRandomImpact()
    {
        if (m_oponentGrid[m_lastImpact.first][m_lastImpact.second] == 'o')
        {
            do{
            m_lastImpact.first += 1;
            }while (m_oponentGrid[m_lastImpact.first][m_lastImpact.second] != '~');
        }else
        {
            do{
            m_lastImpact.first = getRandomInt(m_numberRows-1);
            m_lastImpact.second = getRandomInt(m_numberColumns-1);
            }while (m_oponentGrid[m_lastImpact.first][m_lastImpact.second] != '~');
        }
        return  m_lastImpact;
    }

    std::vector<std::vector<char>> m_grid;
    std::vector<std::vector<char>> m_oponentGrid;
    Ship m_aircraftCarrier = {5,'A'};
    Ship m_cruiser = {4,'C'};
    Ship m_destroyer = {3,'D'};
    Ship m_submarine = {3,'S'}; 
    Ship m_mineSwepper = {2,'M'};
    unsigned int m_lives = 17;
    pair <unsigned int, unsigned int> m_lastImpact{};
    pair <unsigned int, unsigned int> m_previousImpact{};
    bool m_human{false};

    const unsigned int m_numberRows = ROWS;
    const unsigned int m_numberColumns = COLUMNS;
};

void playerFillGrid(Player t_player)
{
    char null;
    if (t_player.isHuman())
    {
        char manual;
        cout << "\033c \n\n\n\n" <<  t_player.m_ID << ", do you want to fill the grid manually? (y/n)\n";
        cin >> manual;
        t_player.fillGrid(manual);
    }
}

void playerTurn(Player t_player)
{
    char null;
    if (t_player.isHuman())
    {
        if (t_player.m_ID != "")
        {
            cout << "\033c \n\n\n\n" <<  t_player.m_ID << " press intro when you are ready.\n";
            cin.get();
            cin.ignore();
        }
        cout << "\033c";
        t_player.printOponentGrid();
        cout << "-------------------------------" << endl;
        t_player.printYourGrid();
    }
}

#endif // PLAYER_HPP

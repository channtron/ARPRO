#include <iostream>
#include <vector>
#include <random>

#include "player.hpp"
#include "utility.hpp"


using namespace std;


void placeShip(vector<vector<char>> &matrix, int size, int rowIndex, int colIndex, int horizontal)
{
    for (auto i = 0; i<size; i++)
    {
        if (horizontal == '1')
            matrix[rowIndex+i][colIndex]='x';
        else
            matrix[rowIndex][colIndex+i]='x';
    }
}

int main()
{
    int numberPlayers;
    string ID_P1{}, ID_P2{};
    cout << "Welcome to BATTLESHP" << "\n\n" << "1 or 2 players?: ";
    cin >> numberPlayers;

    Human player1;
    NPC player2;
    numberPlayers = 1;
    if (numberPlayers > 1){
        player1.setHuman();
        player1.m_ID = "Player1";
        player2.setHuman();
        player2.m_ID = "Player2";
    } else {
        player1.setHuman();
    }


    if (player1.isHuman())
    {
        char manual;
        cout << "\033c \n\n\n\n" <<  player1.m_ID << ", do you want to fill the grid manually? (y/n)\n";
        cin >> manual;
        player1.fillGrid(manual);
    }
    if (player2.isHuman())
    {
        char manual;
        cout << "\033c \n\n\n\n" <<  player2.m_ID << ", do you want to fill the grid manually? (y/n)\n";
        cin >> manual;
        player2.fillGrid(manual);
    }


    while (player1.getLives() > 0 & player2.getLives() > 0)
    {
        if (player1.isHuman())
        {
            if (player1.m_ID != "")
            {
                cout << "\033c \n\n\n\n" <<  player1.m_ID << " press intro when you are ready.\n";
                cin.get();
                cin.ignore();
            }
            cout << "\033c";
            player1.printOponentGrid();
            cout << "-------------------------------" << endl;
            player1.printYourGrid();
        }
        player1.recordImpact(player2.checkImpact(player1.getImpact()));

        if (player2.isHuman())
        {
            if (player2.m_ID != "")
            {
                cout << "\033c \n\n\n\n" <<  player2.m_ID << " press intro when you are ready.\n";
                cin.get();
                cin.ignore();
            }
            cout << "\033c";
            player2.printOponentGrid();
            cout << "-------------------------------" << endl;
            player2.printYourGrid();
        }
        player2.recordImpact(player1.checkImpact(player2.getImpact()));
    }
    if (player1.getLives() == 0)
        cout << "GAME OVER <- YOU LOOSE";
    else
        cout << "GAME OVER <- YOU WIN!!!";

    cout << endl;
    player1.printYourGrid();
    cout << endl;
    player2.printYourGrid();
    return 0;

}

/*
 * Safe random placement
 * Place all ships
 * Player interaction
 *
 * std algorithms
 * Code layout
 */

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
    Player player1, player2;
    int numberPlayers;
    string ID_P1{}, ID_P2{};
    cout << "Welcome to BATTLESHP" << "\n\n" << "1 or 2 players?: ";
    cin >> numberPlayers;

    if (numberPlayers > 1){
        player1.setHuman();
        player1.m_ID = "Player1";
        player2.setHuman();
        player2.m_ID = "Player2";
    } else {player1.setHuman();}


    playerFillGrid(player1);
    playerFillGrid(player2);


    while (player1.getLives() > 0 & player2.getLives() > 0)
    {
        playerTurn(player1);
        player1.recordImpact(player2.checkImpact(player1.getImpact()));


        playerTurn(player2);
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

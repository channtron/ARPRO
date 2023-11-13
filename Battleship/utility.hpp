#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <string>
#include <vector>

#include <random>
//#include <chrono>
#include <time.h>


using namespace std;

#define ROWS 10
#define COLUMNS 10

int getRandomInt (const unsigned int t_max = 9)
{
//    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

//    std::default_random_engine generator(seed);
//    std::uniform_int_distribution<int> distribution(0, t_max);
//    return distribution(generator);

    srand(clock());

    return rand() % (t_max +1);
}


void plotBoard(vector<vector<char>> matrix)
{
    cout << "/  0  1  2  3  4  5  6  7  8  9" << endl;
    for (auto i=0;i < matrix.size(); i++)
    {
        cout << i << "  ";
        for (const auto &cell : matrix[i])
        {
            cout << cell << "  ";
        }
        cout << endl;
    }
}


#endif // UTILITY_HPP

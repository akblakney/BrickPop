#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <cmath>
#include "brickPop.hpp"
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::map;
using std::find;
using std::abs;
int main(){

    //get colors and number of colors being used
    int numColors;
    string colorList;
    map<char, unsigned char>colors;
    cout << "How many colors?" << std::endl;
    cin >> numColors;
    cout << "Which colors?" << std::endl;
    cin >> colorList;

    //initialized colors, which is a map that maps chars to unsigned
    for(int i=0; i<colorList.size(); i++){
        colors[colorList[i]] = i;
    }

    //create original gameboard, oBoard
    cout << "Enter grid: \n" << std::endl;
    int r = 0;
    string temp;
    GameBoard oBoard;
    while(cin >> temp){
        for(int c = 0; c<10; c++){
            oBoard.grid[r][c] = colors[temp[c]];
        }
        r++;
    }
    int headIndex = 0;
    vector<int>indices;

    //start making moves
    createGroups(oBoard);
    makeMove(oBoard, indices);
 
    cout << "in main" << std::endl;
    for(auto i = indices.begin(); i != indices.end(); i++){
        cout << *i << std::endl;
    }
            
        
    



    


}//main
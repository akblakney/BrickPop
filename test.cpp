#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <cmath>
#include "brickPop.hpp"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::getline;
using std::istringstream;
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
    int times = 0;
    string colorList;
    map<char, unsigned char>colors;
    map<unsigned char, char>rColors;
    cout << "How many colors?" << std::endl;
    cin >> numColors;
    cout << "Which colors?" << std::endl;
    cin >> colorList;

    //initializes colors, which is a map that maps chars to unsigned
    //initializes rColors, which is a map from unsigned char to char
    for(unsigned char i=0; i<colorList.size(); i++){
        colors[colorList[i]] = i;
        rColors[i] = colorList[i];
    }
    colors['o'] = 8;
    
    rColors[8] = 'o';
    rColors[9] = 'x';

    //create original gameboard, oBoard
    cout << "By which method? \nr = reverse, n = normal, s = small first, l = large first, i = isolated last" << std::endl;
    char command;
    cin >> command;

    cout << "Enter filename: \n" << std::endl;
    string fileName;
    cin >> fileName;
    int r = 0;
    string temp;
    GameBoard oBoard;
/*    while(cin >> temp){
        for(int c = 0; c<10; c++){
            oBoard.grid[r][c] = colors[temp[c]];
        }
        r++;
    }
*/

    //reading from file
    ifstream infile(fileName);
    string line;
    while(getline(infile, line)){
        istringstream iss(line);
        for(int c=0; c<10; c++){
            oBoard.grid[r][c] = colors[line[c]];
        }
        r++;
    }

    cout << "yes" << std::endl;
    vector<int> *indices;
    vector<int> yee;
    yee.push_back(0);
    yee.clear();
    indices = &yee;
    cout << "size " << indices->size() << std::endl;
    //indices->clear();
    cout << "test" << std::endl;
    //start making moves
    createGroups(oBoard, command);

    cout << "yee" << makeMove(oBoard, indices, times, command) << std::endl;
    cout << "size: " << indices->size() << std::endl;

  
    
    //print out solution
    cout << std::endl;
    for(int i=0; i<indices->size(); i++){
        string temp;
        cin >> temp;
        cout << "Iteration: " << i << " " << oBoard.groups.size() << "groups" << std::endl;
        fakeRemove(oBoard, oBoard.groups[indices->at(i)], rColors);
        removeGroup(oBoard, oBoard.groups[indices->at(i)]);
        createGroups(oBoard, command);
        cout << std::endl;
    }    


    


}//main
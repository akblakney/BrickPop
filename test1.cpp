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
#include <time.h>
#include <chrono>
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

    
    int numColors;
    int times = 0;
    string colorList;
    map<char, unsigned char>colors;
    map<unsigned char, char>rColors;
    cout << "Optimize score? (y or n)" << std::endl;
    char optimize1;
    cin >> optimize1;
    bool optimize = false;
    if(optimize1 == 'y'){
        optimize = true;
    }
    int untilWhen;
    if(optimize){
        cout << "How many iterations?" << std::endl;
        cin >> untilWhen;
    }
    else{
        untilWhen = 0;
    }
    cout << "How many colors?" << std::endl;
    cin >> numColors;
    cout << "Which colors?" << std::endl;
    cin >> colorList;

    
    
    for(unsigned char i=0; i<colorList.size(); i++){
        colors[colorList[i]] = i;
        rColors[i] = colorList[i];
    }
    colors['o'] = 8;
    
    rColors[8] = 'o';
    rColors[9] = 'x';

    
    cout << "By which method? \nr = reverse, n = normal, s = small first, l = large first, i = isolated last" << std::endl;
    char command;
    cin >> command;

    cout << "Enter filename: \n" << std::endl;
    string fileName;
    cin >> fileName;
    int r = 0;
    string temp;
    GameBoard oBoard;

    ifstream infile(fileName);
    string line;
    while(getline(infile, line)){
        istringstream iss(line);
        for(int c=0; c<10; c++){
            oBoard.grid[r][c] = colors[line[c]];
        }
        r++;
    }
    auto start = std::chrono::high_resolution_clock::now();

    cout << "yes" << std::endl;
    vector<int> *optimalScore;
    vector<int> nah;
    nah.push_back(0);
    nah.clear();
    optimalScore = &nah;
    vector<int> *indices;
    vector<int> yee;
    yee.push_back(0);
    yee.clear();
    indices = &yee;
    cout << "size " << indices->size() << std::endl;
    cout << "test" << std::endl;
    createGroups(oBoard, command);
    int score = 0;
    int bestScore = 0;
    cout << "yee" << makeMove(oBoard, indices, times, command, optimalScore, score, bestScore, optimize, untilWhen) << std::endl;
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "time stuff: " << microseconds << std::endl;
    cout << "size: " << indices->size() << std::endl;
    if(optimize){
        cout << "Optimal indices: " << std::endl;
        for(int i=0; i<optimalScore->size(); i++){
            cout << optimalScore->at(i) << " ";
        }
        cout << "Score: " << bestScore << std::endl;
    }
  
    
    if(optimize){
        cout << std::endl;
        for(int i=0; i<optimalScore->size(); i++){
            string temp;
            cin >> temp;
            cout << "Iteration: " << i << " " << oBoard.groups.size() << "groups" << std::endl;
            fakeRemove(oBoard, oBoard.groups[optimalScore->at(i)], rColors);
            removeGroup(oBoard, oBoard.groups[optimalScore->at(i)]);
            createGroups(oBoard, command);
            cout << std::endl;
        }
    }   
    else{
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
    } 


    


}//main

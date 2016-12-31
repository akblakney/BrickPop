#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <cmath>

struct Group{
    unsigned char color;
    std::vector<std::pair<int, int>>coords;
};
inline bool operator==(Group lhs, Group rhs){
    return lhs.color == rhs.color && lhs.coords == rhs.coords;
}
struct GameBoard{
    unsigned char grid[10][10];
    std::vector<Group>groups;
    std::vector<std::pair<int, int>>accounted;

    void orderGroups(char command);
    int getIsolated(unsigned char c);
};
void addToGroup(GameBoard &board, Group &g, std::pair<int, int>p);
bool isEmpty(GameBoard board);
void removeGroup(GameBoard &board, Group group);
void createGroups(GameBoard &board, char command);
bool makeMove(GameBoard board, std::vector<int> *indices, int &times, char command, std::vector<int> *optimalScore, int &score, int &bestScore, bool optimize, int untilWhen);
void printGrid(GameBoard board, std::map<unsigned char, char>rColors);
int elements(GameBoard board);
void fakeRemove(GameBoard board, Group group, std::map<unsigned char, char>rColors);
void performAction(std::vector<int> *indices, int action);
void prioritizeMoves(GameBoard &board);

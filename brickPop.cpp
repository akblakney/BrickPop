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

int GameBoard::getIsolated(unsigned char c){
    int blocksInGroups = 0;
    int totalBlocks = 0;
    for(int i=0; i<groups.size(); i++){
        if(groups[i].color == c){
            blocksInGroups += groups[i].coords.size();
        }
    }
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            if(grid[r][c] == c){
                totalBlocks ++;
            }
        }
    }
    return totalBlocks - blocksInGroups;

}

void GameBoard::orderGroups(char command){
    if(command == 's'){
        for(int j=0; j<groups.size(); j++){
            
            int minIndex = 0;
            int minSize = 100;
            for(int i=j; i<groups.size(); i++){
                if(groups[i].coords.size() < minSize){
                    minIndex = i;
                    minSize = groups[i].coords.size();
                }
            }
            
            Group temp = groups[j];
            groups[j] = groups[minIndex];
            groups[minIndex] = temp;
        } 

    }
    if(command == 'n'){

    }
    if(command == 'l'){

    }
    if(command == 'i'){
        map<unsigned char, int>colorList;
        for(int i=0; i<groups.size(); i++){
            colorList[groups[i].color] = getIsolated(groups[i].color);
        }

        
        for(int i=0; i<groups.size(); i++){
            int minIsolated = 0;
            for(int j=0; j<groups.size(); j++){
                
            }
        }
    }
}

void performAction(std::vector<int> *indices, int action){
    if(action == 1){
        indices->push_back(0);
    }
    if(action == 2){
        indices->at(indices->size()-1)++;
    }
    if(action == 3){
        indices->pop_back();
    }
}

int elements(GameBoard board){
    int sum = 0;
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            if(board.grid[r][c] != 8){
                sum++;
            }
        }
    }
    return sum;
}

void addToGroup(GameBoard &board, Group &g, pair<int, int>p){
    
    int &r = p.first;
    int &c = p.second;
    for(int r1=0; r1<10; r1++){
        for(int c1=0; c1<10; c1++){
            if((abs(r1-r) == 1 && abs(c1-c) == 0) || (r1 == r && abs(c1-c) == 1) ){
                
                pair<int, int>p2 = make_pair(r1, c1);
                bool yeah = (board.grid[r1][c1] == board.grid[r][c]);
                if(board.grid[r1][c1] == g.color && find(board.accounted.begin(), board.accounted.end(), p2) == board.accounted.end()){
                    g.coords.push_back(p2);
                    board.accounted.push_back(p2);
                 }
             }       
         }
    }
    
}

bool isEmpty(GameBoard board){
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            if(board.grid[r][c] != 8){
                return false;
            }
        }
    }
    return true;
}
void removeGroup(GameBoard &board, Group group){
    for(int c=0; c<10; c++){
        
        vector<int>blocks;
        for(int i=0; i<group.coords.size(); i++){
            if(group.coords[i].second == c){
                blocks.push_back(group.coords[i].first);
            }
        }
        for(int r=0; r<10; r++){
            if(find(blocks.begin(), blocks.end(), r) != blocks.end()){
                for(int r1=r; r1 > 0; r1--){
                    board.grid[r1][c] = board.grid[r1-1][c];
                }
                board.grid[0][c] = 8;
            }
        }
    }

    for(int c=8; c>=0; c--){
        bool empty = true;
        for(int r=0; r<10; r++){
            if(board.grid[r][c] != 8){
                empty = false;
                break;
            }
        }
        if(empty){
            for(int c1 = c; c1 < 9; c1++){
                for(int r=0; r<10; r++){
                    board.grid[r][c1] = board.grid[r][c1+1];
                }
            }
            for(int r=0; r<10; r++){
                board.grid[r][9] = 8;
            }

        }


    }
    board.groups.erase(std::remove(board.groups.begin(), board.groups.end(), group), board.groups.end());

}
void createGroups(GameBoard& board, char command){
    
    
    board.groups.clear();
    board.accounted.clear();
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            pair<int, int> p = make_pair(r,c);
            if(find(board.accounted.begin(), board.accounted.end(), p) == board.accounted.end() && board.grid[r][c] != 8){
                Group g;
                g.color = board.grid[r][c];
                g.coords.push_back(p);
                board.accounted.push_back(p);

                for(int i=0; i<g.coords.size(); i++){
                    addToGroup(board, g, g.coords[i]);
                }
                if(g.coords.size() > 1){
                    board.groups.push_back(g);
                }
            }
        }
    }
    board.orderGroups(command);

}
    
bool makeMove(GameBoard board, vector<int> *indices, int &times, char command, vector<int> *optimalScore, int &score, int &bestScore, bool optimize, int untilWhen){   
    if(times%1000000 == 0){
        cout << times << " times" << std::endl;
    }
    if(optimize && times > untilWhen){
        return true;
    }
    
    bool last;
    times++;
    if(board.groups.size() == 0){
        if (isEmpty(board)){
            if(optimize){
                if(score > bestScore){
                    *optimalScore = *indices;
                    int score1 = score;
                    bestScore = score1;
                }
                
                score = 0;
                indices->pop_back();
                return false;

            }
           else{
               cout << "final indices: ";
                for(int i=0; i<indices->size(); i++){
                cout << indices->at(i) << " ";
                }
                cout << std::endl;
                      
                return true;
           }
        }

        else{
            if(optimize){
                score = 0;
            }
            indices->pop_back();
            return false;
        }
    } 
 
    for(int i=0; i<board.groups.size(); i++){
        if(i==0){indices->push_back(0);}
        else{indices->push_back(i);}
        int score1;
        if(optimize){
            int sizeOfGroup = board.groups[i].coords.size();
            score1 = score + (sizeOfGroup * (sizeOfGroup - 1));

        }
        bool last1 = (i == board.groups.size()-1);
        GameBoard nBoard = board;
        removeGroup(nBoard, nBoard.groups[i]);
        createGroups(nBoard, command);
        
        if(makeMove(nBoard, indices, times, command, optimalScore, score1, bestScore, optimize, untilWhen)){
            return true;
        }
    }
    indices->pop_back();
   
    return false;
}
void printGrid(GameBoard board, map<unsigned char, char>rColors){
    rColors[8] = 'o';
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            cout << rColors[board.grid[r][c]];
        }
        cout << std::endl;
    }
}
void fakeRemove(GameBoard board, Group group, map<unsigned char, char>rColors){
    
    for(int i=0; i<group.coords.size(); i++){
        int &r = group.coords[i].first;
        int &c = group.coords[i].second;
        board.grid[r][c] = 9;
    }

    printGrid(board, rColors);
}

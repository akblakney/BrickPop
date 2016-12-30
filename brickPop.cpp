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

void GameBoard::orderGroups(char command){
    if(command == 'r'){
        for(int i=0; i<groups.size()/2; i++){
            Group temp = groups[i];
            groups[i] = groups[groups.size()-i-1];
            groups[groups.size()-i-1] = temp;
        }
    }
    if(command == 's'){
        for(int j=0; j<groups.size(); j++){
            
            //set minIndex to index of the minimum size
            int minIndex = 0;
            int minSize = 100;
            for(int i=j; i<groups.size(); i++){
                if(groups[i].coords.size() < minSize){
                    minIndex = i;
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

    }
}

//p is a particular pair of coords in Group g
//check all boundaries of p and add to g.coords if it should be in Group g
void performAction(std::vector<int> *indices, int action){
    if(action == 1){
        indices->push_back(0);
    }
    if(action == 2){
        indices->at(indices->size()-1)++;
    }
    if(action == 3){
        indices->pop_back();
 //       indices->at(indices->size()-1)++;
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
            //if on boundary of point p and same color (aka belongs in group)
            if((abs(r1-r) == 1 && abs(c1-c) == 0) || (r1 == r && abs(c1-c) == 1) ){
                
                pair<int, int>p2 = make_pair(r1, c1);
                bool yeah = (board.grid[r1][c1] == board.grid[r][c]);
                if(board.grid[r1][c1] == g.color && find(board.accounted.begin(), board.accounted.end(), p2) == board.accounted.end()){
                    //add coords to Group g
                    //add coords to board.accounted for
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
    //cycle thru columns and do all down motions
    for(int c=0; c<10; c++){
        
        //fill blocks with all r values to be removed in that column
        vector<int>blocks;
        for(int i=0; i<group.coords.size(); i++){
            if(group.coords[i].second == c){
                blocks.push_back(group.coords[i].first);
            }
        }
        //cycle through column, starting at top, and if member of block is met:
        //shift everything down one; block at r=0 to 0
        for(int r=0; r<10; r++){
            //if this r level must be removed
            if(find(blocks.begin(), blocks.end(), r) != blocks.end()){
                //shift all above r down
                for(int r1=r; r1 > 0; r1--){
                    board.grid[r1][c] = board.grid[r1-1][c];
                }
                //set r = 0 to 0
                board.grid[0][c] = 8;
            }
        }
    }

    //do all left-motion
    for(int c=8; c>=0; c--){
        //check if all rows of column c are 0
        bool empty = true;
        for(int r=0; r<10; r++){
            if(board.grid[r][c] != 8){
                empty = false;
                break;
            }
        }
        //if given column is empty
        if(empty){
            //shift cols left
            for(int c1 = c; c1 < 9; c1++){
                for(int r=0; r<10; r++){
                    board.grid[r][c1] = board.grid[r][c1+1];
                }
            }
            //make col 9 be all 0
            for(int r=0; r<10; r++){
                board.grid[r][9] = 8;
            }

        }


    }
    //remove the group from board.groups
    board.groups.erase(std::remove(board.groups.begin(), board.groups.end(), group), board.groups.end());

}
void createGroups(GameBoard& board, char command){//fills board.groups with Groups
    
    //sets up board.groups with all groups in board
    
    board.groups.clear();
    board.accounted.clear();
    for(int r=0; r<10; r++){
        for(int c=0; c<10; c++){
            pair<int, int> p = make_pair(r,c);
            if(find(board.accounted.begin(), board.accounted.end(), p) == board.accounted.end() && board.grid[r][c] != 8){
                //create a group and set color and add the coords
                //also add to board.accounted
                Group g;
                g.color = board.grid[r][c];
                g.coords.push_back(p);
                board.accounted.push_back(p);

                //add the rest of the coords that should be in Group g
                //cycle through g.coords and check boundaries on all of the pairs inside
                //if the color matches, add to g.coords
                //cycle through again after each addition
                for(int i=0; i<g.coords.size(); i++){
                    addToGroup(board, g, g.coords[i]);
                }
                if(g.coords.size() > 1){
                    board.groups.push_back(g);
                }
            }//if
        }//for2
    }//for1
    board.orderGroups(command);

}//createGroups
    
bool makeMove(GameBoard board, vector<int> *indices, int &times, char command){   
    cout << std::endl << times << " times" << std::endl;
    for(int i=0; i<indices->size(); i++){
        cout << indices->at(i) << " ";
    }
    
    
    bool last;
    times++;
  //  cout << "makMove " << indices->size() << " , " << board.groups.size() << " groups" <<std::endl;
    //check if win or loss, based on urrent board
    if(board.groups.size() == 0){
        if (isEmpty(board)){
           cout << "final indices: ";
           for(int i=0; i<indices->size(); i++){
               cout << indices->at(i) << " ";
           }
           cout << std::endl;
           
            return true;
        }
        else{
            indices->pop_back();
            return false;
        }
    } 
 
    for(int i=0; i<board.groups.size(); i++){
        cout << board.groups.size() << std::endl;
        cout << "in for loop " << i << std::endl; 
        if(i==0){indices->push_back(0);}
        else{indices->push_back(i);}
        bool last1 = (i == board.groups.size()-1);
        GameBoard nBoard = board;
        removeGroup(nBoard, nBoard.groups[i]);//alters board
        createGroups(nBoard, command);//also alters board
        
        if(makeMove(nBoard, indices, times, command)){
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
    
    //set all elements in group to display as 'x'
    for(int i=0; i<group.coords.size(); i++){
        int &r = group.coords[i].first;
        int &c = group.coords[i].second;
        board.grid[r][c] = 9;
    }

    //print out display
    printGrid(board, rColors);
}

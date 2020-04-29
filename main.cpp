#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using std::cout;
using std::vector;
using std::fstream;
using std::istringstream;
using std::string;

//custom type "State" empty or obstacle
enum class State{kEmpty, kObs, kClosed};

// Function to read and parse string stream
vector<State> ParseLine(string line) {
    istringstream sline(line);
    int num;
    char ch;
    vector<State> rw;
    while (sline >> num >> ch && ch == ',') {
        if(num == 0){
            rw.push_back(State::kEmpty);
        }else{
            rw.push_back(State::kObs);
        }
      
    }
    return rw;
}

// Fill board from file content
auto ReadFromfile(string path){
    vector<vector<State>> b{};

//file open and stream
    fstream my_file;
    my_file.open(path);

    if(my_file){
        cout<<"The stream has been created \n";
        string line;
        vector<State> srow;
        while(getline(my_file, line)){
            srow = ParseLine(line);
            b.push_back(srow);
        }
    }
    return b;
}

// Write function to compare the f-value of two nodes here
bool Compare(const vector<int> n1, const vector<int> n2){
	int f1 = n1[2]+n1[3];
  	int f2 = n2[2]+n2[3];
  	bool compare = f1 > f2 ? true : false;
  	
  return compare;
}


// Add heuristic function - calculate the manhattan distance

int Heuristic(int x1, int y1, int x2, int y2){
  	
  	int diffx = abs(x2-x1);
  	int diffy = abs(y2-y1);
  	
  	int sumdiff = diffx + diffy;
    
    return sumdiff;
}

/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid) {
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

// write search function
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]){
	cout << "No path found!" << "\n";
  	return std::vector<vector<State>> {};
}

string CellString(State cell) {
  switch(cell) {
    case State::kObs: return "⛰️   ";
    default: return "0   "; 
  }
}

// function to print 2D board vector 
void PrintBoard(const vector<vector<State>> board){
    for(int i = 0; i<board.size(); i++){
        for (int j = 0; j<board[i].size(); j++){
            cout<<CellString(board[i][j])<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    // initialize board elements
    //vector<vector<int>> board{{1,2},{3,4},{5,6}};
    int init[2]{0, 0}; // start point
    int goal[2]{4, 5}; // destination

    auto board = ReadFromfile("board.txt");

    // Call search function
    auto solution = Search(board, init, goal);
    // print the board
    PrintBoard(solution);

    return 0;
}
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


// Function to read and parse string stream
vector<int> ParseLine(string line) {
    istringstream sline(line);
    int num;
    char ch;
    vector<int> rw;
    while (sline >> num >> ch && ch == ',') {
      rw.push_back(num);
    }
    return rw;
}

// Fill board from file content
auto ReadFromfile(string path){
    vector<vector<int>> b{};

//file open and stream
    fstream my_file;
    my_file.open(path);

    if(my_file){
        cout<<"The stream has been created \n";
        string line;
        vector<int> srow;
        while(getline(my_file, line)){
            srow = ParseLine(line);
            b.push_back(srow);
        }
    }
    return b;
}

// function to print 2D board vector 
void PrintBoard(const vector<vector<int>> board){
    for(int i = 0; i<board.size(); i++){
        for (int j = 0; j<board[i].size(); j++){
            cout<<board[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    // initialize board elements
    //vector<vector<int>> board{{1,2},{3,4},{5,6}};

    auto board = ReadFromfile("board.txt");

    // print the board
    PrintBoard(board);
    
    return 0;
}
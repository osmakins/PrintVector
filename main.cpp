#include<iostream>
#include<vector>
#include<fstream>

using std::cout;
using std::vector;
using std::fstream;

// function to print 2D board vector 
void PrintBoard(const vector<vector<int>> b){
    for(int i = 0; i<b.size(); i++){
        for (int j = 0; j<b[i].size(); j++){
            cout<<b[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    // initialize board elements
    vector<vector<int>> board{{1,2},{3,4},{5,6}};

    // print the board
    PrintBoard(board);

    //file open and print
    fstream my_file;
    my_file.open("board.txt");

    if(my_file){
        cout<<"The stream has been created \n";
        std::string line;
        while(getline(my_file, line)){
            cout<<line<<"\n";
        }
    }

    return 0;
}
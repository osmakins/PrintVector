#include <iostream>

#include "functions.cpp"

int main()
{
  // initialize board elements
  //vector<vector<int>> board{{1,2},{3,4},{5,6}};
  int init[2]{0, 0}; // start point
  int goal[2]{4, 5}; // destination

  Car car; // Car object
  auto board = car.ReadFromfile("board.txt");

  // Call search function
  auto solution = Search(board, init, goal);

  // print the board
  car.PrintBoard(solution);

  return 0;
}
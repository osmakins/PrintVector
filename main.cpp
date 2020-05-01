#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // for sort

using std::abs;
using std::cout;
using std::fstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;

//custom type "State" empty or obstacle
enum class State
{
  kEmpty,
  kObs,
  kClosed,
  kPath
};

// Function to read and parse string stream
vector<State> ParseLine(string line)
{
  istringstream sline(line);
  int num;
  char ch;
  vector<State> rw;
  while (sline >> num >> ch && ch == ',')
  {
    if (num == 0)
    {
      rw.push_back(State::kEmpty);
    }
    else
    {
      rw.push_back(State::kObs);
    }
  }
  return rw;
}

// Fill board from file content
auto ReadFromfile(string path)
{
  vector<vector<State>> b{};

  //file open and stream
  fstream my_file;
  my_file.open(path);

  if (my_file)
  {
    cout << "The stream has been created \n";
    string line;
    vector<State> srow;
    while (getline(my_file, line))
    {
      srow = ParseLine(line);
      b.push_back(srow);
    }
  }
  return b;
}

// Write function to compare the f-value of two nodes here
bool Compare(const vector<int> n1, const vector<int> n2)
{
  int f1 = n1[2] + n1[3];
  int f2 = n2[2] + n2[3];
  bool compare = f1 > f2 ? true : false;

  return compare;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v)
{
  sort(v->begin(), v->end(), Compare);
}

// Add heuristic function - calculate the manhattan distance

int Heuristic(int x1, int y1, int x2, int y2)
{

  int diffx = abs(x2 - x1);
  int diffy = abs(y2 - y1);

  int sumdiff = diffx + diffy;

  return sumdiff;
}

// TODO: Write CheckValidCell here.

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
  // Check that (x,y) coordinatea pair is on the grid
  bool x_on_grid = x > 0 && x < grid.size() ? true : false;
  bool y_on_grid = y > 0 && y < grid[0].size() ? true : false;

  // Check that the grid at (x,y) is kEmpty
  if (x_on_grid && y_on_grid)
    return grid[x][y] == State::kEmpty;
  return false;
}

/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid)
{
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

// write search function
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{
  // TODO: while open vector is non empty {
  // TODO: Sort the open list using CellSort, and get the current node.

  // TODO: Get the x and y values from the current node,
  // and set grid[x][y] to kPath.

  // TODO: Check if you've reached the goal. If so, return grid.

  // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
  // ExpandNeighbors

  //} // TODO: End while loop

  vector<vector<int>> open{};

  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);

  AddToOpen(x, y, g, h, open, grid);
  while (open.size() > 0)
  {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

    // Check if we're done.
    if (x == goal[0] && y == goal[1])
    {
      return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    // ExpandNeighbors
  }

  // We've run out of new nodes to explore and haven't found a path.

  cout << "No path found!"
       << "\n";
  return std::vector<vector<State>>{};
}

string CellString(State cell)
{
  switch (cell)
  {
  case State::kObs:
    return "⛰️   ";
  case State::kPath:
    return "🚗   ";
  default:
    return "0   ";
  }
}

// function to print 2D board vector
void PrintBoard(const vector<vector<State>> board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      cout << CellString(board[i][j]) << " ";
    }
    cout << "\n";
  }
}

int main()
{
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
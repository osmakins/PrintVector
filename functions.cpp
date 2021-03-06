#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort

using std::abs;
using std::cout;
using std::sort;
using std::string;
using std::vector;

#include "classes.cpp"

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

// Write function to compare the f-value of two nodes here
bool Compare(const vector<int> n1, const vector<int> n2)
{
  int f1 = n1[2] + n1[3]; // f1 = g1 + h1
  int f2 = n2[2] + n2[3]; // f2 = g2 + h2
  return f1 > f2;
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
  return abs(x2 - x1) + abs(y2 - y1);
}

// TODO: Write CheckValidCell here.

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
  // Check that (x,y) coordinatea pair is on the grid
  bool x_on_grid = (x >= 0 && x < grid.size());
  bool y_on_grid = (y >= 0 && y < grid[0].size());

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

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */

void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &openlist, vector<vector<State>> &grid)
{
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++)
  {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid))
    {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{
  vector<vector<int>> open{};

  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, grid);

  // write A* search algorithm in function
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
      // TODO: Set the init grid cell to kStart, and
      // set the goal grid cell to kFinish before returning the grid.
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;
      return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    // ExpandNeighbors
    ExpandNeighbors(current, goal, open, grid);
  }

  // We've run out of new nodes to explore and haven't found a path.
  cout << "No path found!"
       << "\n";
  return std::vector<vector<State>>{};
}

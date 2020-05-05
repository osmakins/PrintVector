#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

//custom type "State" empty or obstacle
enum class State
{
  kEmpty,
  kObs,
  kClosed,
  kPath,
  kStart,
  kFinish
};

class Car
{

public:
  string CellString(State cell)
  {
    switch (cell)
    {
    case State::kObs:
      return "⛰️   ";
    case State::kPath:
      return "🚗   ";
    case State::kStart:
      return "🚦   ";
    case State::kFinish:
      return "🏁   ";
    default:
      return "0   ";
    }
  }

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
  vector<vector<State>> ReadFromfile(string path)
  {
    vector<vector<State>> b{};
    //file open and stream
    ifstream my_file(path);
    if (my_file)
    {
      cout << "The stream has been created \n";
      string line;
      while (getline(my_file, line))
      {
        vector<State> srow = ParseLine(line);
        b.push_back(srow);
      }
    }
    return b;
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
};
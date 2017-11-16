#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 10;  // maximum grid size: 10 x 10
const int MIN_SIZE = 3;  // maximum grid size: 3 x 3


// win(grid, gridSize) checks for the winner and returns '?' if none.
char win(vector< vector<char> > &grid, const int gridSize) {
  char winner;

  // check rows
  for (int row = 0; row < gridSize; ++row) {
    winner = grid[row][0];
    if (winner == '?') continue;
    for (int col = 1; col < gridSize; ++col) {
      if (winner != grid[row][col]) break;
      else if (col == gridSize - 1) return winner;
    }
  }

  // check columns
  for (int col = 0; col < gridSize; ++col) {
    winner = grid[0][col];
    if (winner == '?') continue;
    for (int row = 1; row < gridSize; ++row) {
      if (winner != grid[row][col]) break;
      else if (row == gridSize - 1) return winner;
    }
  }

  // check top-left to bottom-right diagonal line
  winner = grid[0][0];
  if (winner != '?') {
    for (int i = 1; i < gridSize; ++i) {
      if (winner != grid[i][i]) break;
      else if (i == gridSize - 1) return winner;
    }
  }

  // check top-right to bottom-left diagonal line
  winner = grid[0][gridSize - 1];
  if (winner != '?') {
    for (int i = 1; i < gridSize; ++i) {
      if (winner != grid[i][gridSize - 1 - i]) break;
      else if (i == gridSize - 1) return winner;
    }
  }

  return '?';
}


// readCoordinates(player, gridSize) reads and returns a pair of valid coordinates.
vector<int> readCoordinates(char player, int gridSize) {
  vector<int> coordinates;
  int x, y;

  // read x
  cout << "Player " << player << ", please choose a x-coordinate: ";
  while (!(cin >> x)) cerr << "ERROR: Invalid input type. Please try again." << endl;
  while (x < 1 || x > gridSize) {
    cerr << "ERROR: Invalid input range. Please try again." << endl;
    while (!(cin >> x)) cerr << "ERROR: Invalid input type. Please try again." << endl;
  }

  // read y
  cout << "Player " << player << ", please choose a y-coordinate: ";
  while (!(cin >> y)) cerr << "ERROR: Invalid input type. Please try again." << endl;
  while (y < 1 || y > gridSize) {
    cerr << "ERROR: Invalid input range. Please try again." << endl;
    while (!(cin >> x)) cerr << "ERROR: Invalid input type. Please try again." << endl;
  }

  coordinates.push_back(x - 1);
  coordinates.push_back(y - 1);
  return coordinates;
}


// printGrid(grid, gridSize) prints grid as a table
void printGrid(vector< vector<char> > &grid, int gridSize) {
  for (int row = 0; row < gridSize * 2 + 3; ++row) { cout << "-"; }
  cout << endl;

  for (int row = 0; row < gridSize; ++row) {
    cout << "| ";
    for (int col = 0; col < gridSize; ++col) { cout << grid[row][col] << ' '; }
    cout << '|' << endl;
  }

  for (int row = 0; row < gridSize * 2 + 3; ++row) { cout << "-"; }
  cout << endl;
}


int main() {
  int gridSize;
  char player;
  bool tie;

  cout << "Welcome to the N-in-A-Row game!" << endl;
  cout << "Rule: Two player alternately claim points in a nxn grid." << endl;
  cout << "      The player who claims n consecutive points in a line first wins the game." << endl << endl;

  // read grid gridSize input
  cout << "Please provide a grid size between " << MIN_SIZE << " and " << MAX_SIZE << " (inclusive): ";
  while (true) {
    if (cin >> gridSize) {
      if (MAX_SIZE >= gridSize && MIN_SIZE >= MIN_SIZE) break;
    } else {
      cerr << "ERROR: Your input is out of the valid range. Please try again." << endl;
    }
  }

  // create a grid
  vector<char> row (gridSize, '?');
  vector< vector<char> > grid (gridSize, row);

  cout << "Game starts!" << endl;
  int count = 0;
  char winner = win(grid, gridSize);
  while (winner == '?') {
    if (count == gridSize * gridSize) {
      tie = true;
      break;
    }

    // decide players' turns
    if (count % 2 == 0) player = 'A';
    else player = 'B';

    // read player's chosen coordinates
    vector<int> coordinates = readCoordinates(player, gridSize);
    while (grid[coordinates[0]][coordinates[1]] != '?') {
      cerr << "ERROR: The space you chose has already been taken. Please try again." << endl;
      coordinates = readCoordinates(player, gridSize);
    }
    grid[coordinates[0]][coordinates[1]] = player;

    // print updated grid
    printGrid(grid, gridSize);
    // check for winner
    winner = win(grid, gridSize);
    // update counter
    ++count;
  }

  if (tie) cout << "Game over! It's a tie." << endl;
  else cout << "Game over! Player " << player << " won. " << endl;
}

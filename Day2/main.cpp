#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 12 red, 13 green, 14 blue

int main() {
  string filename = "games.txt";
  ifstream file(filename);

  if(!file.is_open()) {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }

  string line;

  unordered_map<string, int> colors;

  int sum = 0;
  
  while(getline(file, line)) {
    int currGame, number;
    string color;
    
    // reset map for new line
    colors["red"] = 0;
    colors["green"] = 0;
    colors["blue"] = 0;
    
    istringstream iss(line);

    // skip game
    iss.ignore(5);

    // get game number
    iss >> currGame;

    // skip comma and space
    iss.ignore(2);

    // get number and color
    while(iss >> number >> color) {

      // lambda function to remove extra characters
      color.erase(std::remove_if(color.begin(), color.end(), 
        [](unsigned char x) { return x == ',' || x == ';'; }), color.end());
      
      if(colors[color] < number) {
        colors[color] = number;
      }
      if(iss.peek() == ',' || iss.peek() == ';') {
        iss.ignore();
      }
    }
    /* part 1 solution
    if(colors["red"] <= 12 && colors["green"] <= 13 && colors["blue"] <= 14) {
      sum += currGame;
    }
    */
    // part 2 solution
    int power = colors["red"] * colors["green"] * colors["blue"];
    sum += power;
    colors.clear();
  }

  cout << sum << endl;
}

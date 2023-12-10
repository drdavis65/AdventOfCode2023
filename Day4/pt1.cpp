#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

int main() {
  std::ifstream file("scratch.txt");
  std::string line;

  int sum = 0;

  while (getline(file, line)) {
    std::unordered_set<int> winningNums;

    std::istringstream iss(line);

    while (iss.peek() != ':')
      iss.ignore();

    iss.ignore();
    int num;
    int count = 0;
    while (count != 10 && iss >> num) {
      winningNums.insert(num);
      count++;
    }
    iss.ignore();
    iss.ignore();
    if (!iss)
      std::cout << "error" << std::endl;

    int matches = 0;
    while (iss >> num) {
      if (winningNums.find(num) != winningNums.end()) {
        matches++;
      }
    }
    if (matches > 0)
      sum += pow(2, matches - 1);
  }
  std::cout << "Sum: " << sum << std::endl;
}

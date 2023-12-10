#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
  std::ifstream file("scratch.txt");
  std::string line;
  std::unordered_map<int, int> cards;
  int lineNum = 1;
  while (getline(file, line)) {
    if (cards.find(lineNum) == cards.end()) {
      cards[lineNum] = 1;
    } else {
      cards[lineNum] += 1;
    }

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

    for (int i = lineNum + 1; i <= lineNum + matches; i++) {
      if (cards.find(i) == cards.end()) {
        cards[i] = 1 * cards[lineNum];
      } else {
        cards[i] += 1 * cards[lineNum];
      }
    }

    lineNum++;
  }
  int sum = 0;
  for (auto card : cards)
    sum += card.second;
  std::cout << "Cards Total: " << sum << std::endl;
  return 0;
}

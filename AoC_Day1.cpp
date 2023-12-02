#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string filename = "calibration.txt";
  ifstream file(filename);
  vector<string> numStr = {"one", "two",   "three", "four", "five",
                           "six", "seven", "eight", "nine"};
  vector<int> numInt = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int sum = 0;
  if (!file.is_open()) {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }
  string line;
  while (getline(file, line)) {
    int first = -1, last = -1;
    for (int i = 0; i < line.length(); i++) {

      if (isdigit(line[i])) {
        first = line[i] - '0';
        break;
      }
      else {
        for (int j = 0; j < numStr.size(); j++) {
          if (line.substr(i, numStr[j].length()) == numStr[j]) {
            first = numInt[j];
            break;
          }
        }
      }
      if(first != -1) break;
      
    }

    for (int i = line.length() - 1; i >= 0; i--) {

      if (isdigit(line[i])) {
        last = line[i] - '0';
        break;
      }

      for (int j = 0; j < numStr.size(); j++) {
        if (line.substr(i, numStr[j].length()) == numStr[j]) {
          last = numInt[j];
          break;
        }
      }
      if(last != -1) break;
    }

    int two_digit = first * 10 + last;
    cout << two_digit << endl;
    sum += two_digit;
  }
  cout << "Sum of all two-digit numbers: " << sum << endl;
  file.close();
  return 0;
}

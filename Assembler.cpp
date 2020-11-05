#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string replaceFirstOccurrence(string& s, const string& toReplace,
                              const string& replaceWith) {
  size_t pos = s.find(toReplace);
  if (pos == string::npos) return s;
  return s.replace(pos, toReplace.length(), replaceWith);
}

void replaceWithOpCode(string& aS) {
  aS = replaceFirstOccurrence(aS, "MOV", "000000");
  aS = replaceFirstOccurrence(aS, "MVI", "000100");
  aS = replaceFirstOccurrence(aS, "LOAD", "010100");
  aS = replaceFirstOccurrence(aS, "STORE", "011100");
  aS = replaceFirstOccurrence(aS, "ADD", "100000");
  aS = replaceFirstOccurrence(aS, "SUB", "101000");
  aS = replaceFirstOccurrence(aS, "AND", "110000");
  aS = replaceFirstOccurrence(aS, "OR", "111000");
  aS = replaceFirstOccurrence(aS, "ADI", "100100");
  aS = replaceFirstOccurrence(aS, "SUI", "101100");
  aS = replaceFirstOccurrence(aS, "ANI", "110100");
  aS = replaceFirstOccurrence(aS, "ORI", "111100");
}
void replaceWithRegAddress(string& aS) {
  for (int i = 32; i >= 1; --i) {
    aS = replaceFirstOccurrence(aS, "R" + to_string(i),
                                bitset<5>(i - 1).to_string());
  }
}

void replaceImmVal(string& aS) {
  for (int i = 65536; i >= 0; --i) {
    aS = replaceFirstOccurrence(aS, "#" + to_string(i),
                                bitset<16>(i - 1).to_string());
  }
}

string assemble(string s) {
  string aS = s;
  replaceWithOpCode(aS);
  replaceWithRegAddress(aS);
  replaceImmVal(aS);
  aS.erase(remove(aS.begin(), aS.end(), ' '), aS.end());
  while (aS.size() < 32) {
    aS.push_back('0');
  }
  cout << aS << "==\n";

  // reverse(aS.begin(), aS.end());
  bitset<32> set(aS);  
  stringstream hexAS;
  hexAS << hex << uppercase << set.to_ulong();
  return hexAS.str();
}

int main() {
  vector<string> bitCode;
  int N;
  cout << "Total number of lines:";
  cin >> N;
  string s;
  cin.ignore(256, '\n');
  for (int i = 0; i < N; ++i) {
    getline(cin, s);
    bitCode.push_back(assemble(s));
  }

  for (int i = 0; i < N; ++i) {
    cout << bitCode[i] << "\n";
  }
}
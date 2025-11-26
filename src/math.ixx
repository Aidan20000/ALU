#include <iostream>
#include <string>
#include <algorithm>

export module math;  // name of the module

export std::pair<int, int> halfAdd(int num1, int num2);
export std::pair<int, int> fullAdd(int num1, int num2, int carry);
export std::pair<int, int> halfSubtract(int num1, int num2);
export std::pair<int, int> fullSubtract(int num1, int num2, int borrow);
export std::string addBinary(std::string num1, std::string num2);
export std::string subtractBinary(std::string num1, std::string num2);
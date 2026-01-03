#pragma once
#include <string>
#include <utility>

std::pair<int, int> halfAdd(int num1, int num2);
std::pair<int, int> fullAdd(int num1, int num2, int carry);

std::pair<int, int> halfSubtract(int num1, int num2);
std::pair<int, int> fullSubtract(int num1, int num2, int borrow);

std::string addBinary(std::string num1, std::string num2);
std::string subtractBinary(std::string num1, std::string num2);
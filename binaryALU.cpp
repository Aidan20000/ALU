#include <iostream>
#include <string>
#include <algorithm>

// Half and full adder function
std::pair<int, int> halfAdd(int num1, int num2){
    //Initializes sum and carry variables
    int sum = 0, carry = 0;

    //Handles determining the sum for the two binary digits 
    //This is an xor gate along with an and gate for carry
    if(num1 == 1 || num2 == 1){
        sum = 1;
    }
    if(num1 == 1 && num2 == 1){
        sum = 0;
        carry = 1;
    }

    return {sum, carry};
}

std::pair<int, int> fullAdd(int num1, int num2, int carry){
    int newCarry = 0;
    int insideSum, insideCarry;
    std::tie(insideSum, insideCarry) = halfAdd(num1, num2);
    int secondInsideCarry;
    std::tie(insideSum, secondInsideCarry) = halfAdd(insideSum, carry);

    if(insideCarry == 1 || secondInsideCarry == 1){
        newCarry = 1;
    }
    return {insideSum, newCarry};
}
////Half Subtractor and full subtractor function
std::pair<int, int> halfSubtract(int num1, int num2){
    //This does num1 - num2
    int diff = 0, borrow = 0;
    if(num1 == 1 || num2 == 1){
        diff = 1;
    }
    if(num1 == 1 && num2 == 1){
        diff = 0;
    }

    //A not gate for num1
    if(num1 == 1){
        num1 = 0;
    }else {
        num1 = 1;
    }

    //Sets borrow to 1 if youre subtracting 1 from 0
    if(num1 == 1 && num2 == 1){
        borrow = 1;
    }
    return {diff, borrow};
}

std::pair<int, int> fullSubtract(int num1, int num2, int borrow){
    //This does num1 - (num2 + borrow)
    int finalDiff, secondBorrow, finalBorrow;
    int firstDiff, firstBorrow;
    std::tie(firstDiff, firstBorrow) = halfSubtract(num1, borrow);
    std::tie(finalDiff, secondBorrow) = halfSubtract(num1, borrow);

    if(firstBorrow == 1 || secondBorrow == 1){
        finalBorrow = 1;
    }

    return {finalDiff, finalBorrow};
}

//Adding and subtracting functions using adders and subtractors
std::string addBinary(std::string num1, std::string num2){
    //If both numbers are the same amount of bits then this function adds them
    //We set the current index to the last bit in the input sting and add the two numbers at that index
    //This is line addition
    //We use the half adder at first and then full adders and incriment the selected index every time we add 2 digits
    if(num1.size() == num2.size()){
        int newSum, newCarry;
        std::string finalAnswer = "";
        int currIndex = num1.size();

        // Subtracting by '0' converts the character of num[index] to an int that half and full adders use
        std::tie(newSum, newCarry) = halfAdd((num1[currIndex]-'0'), (num2[currIndex]-'0'));
        currIndex--;
        finalAnswer += char(newSum);

        while(currIndex >= 0){
            std::tie(newSum, newCarry) = fullAdd((num1[currIndex] - '0'), (num2[currIndex] - '0'), char(newCarry));
            finalAnswer += (newSum + '0');
            currIndex--;
        }
        
        if(newCarry == 1){
            finalAnswer += '1';
        }

        std::reverse(finalAnswer.begin(), finalAnswer.end());

        return finalAnswer;
    }
    return "";
}

int main() {
    std::cout << addBinary("", "") << std::endl;
    return 0;
}
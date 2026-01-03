#include "math.hpp"

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
    //Replicates one instance of line division with 2 one digit numbers and a carry that will be 0 or 1
    //depending on the result of the last addition

    //This function is repeatedly used to add a binary number
    int newCarry = 0;
    int sum, insideCarry;
    std::tie(sum, insideCarry) = halfAdd(num1, num2);
    int secondInsideCarry;
    std::tie(sum, secondInsideCarry) = halfAdd(sum, carry);

    if(insideCarry == 1 || secondInsideCarry == 1){
        newCarry = 1;
    }
    return {sum, newCarry};
}
////Half Subtractor and full subtractor function
std::pair<int, int> halfSubtract(int num1, int num2){
    //This does num1 - num2
    int diff = 0, borrow = 0;
    if(num1 == 0 && num2 == 1){
        borrow = 1;
    } else {
        borrow = 0;
    }

    if(!(num1 == 1 && num2 == 1) && (num1 == 1 || num2 == 1)){
        diff = 1;
    }
    return {diff, borrow};
}

std::pair<int, int> fullSubtract(int num1, int num2, int borrow){
    //This does num1 - (num2 + borrow)
    //Can be used repeatedly to subtract actual numbers just like full adder function
    int firstDiff, firstBorrow, secondBorrow, finalDiff, finalBorrow = 0;
    std::tie(firstDiff, firstBorrow) = halfSubtract(num1, borrow);
    std::tie(finalDiff, secondBorrow) = halfSubtract(firstDiff, num2);

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
    if(num1.size() == num2.size() && num1.size() > 0){
        int newSum, newCarry;
        std::string finalAnswer = "";
        int currIndex = num1.size() - 1;

        // Subtracting by '0' converts the character of num[index] to an int that half and full adders use
        std::tie(newSum, newCarry) = halfAdd((num1[currIndex]-'0'), (num2[currIndex]-'0'));
        finalAnswer += (newSum + '0');
        currIndex--;

        while(currIndex >= 0){
            std::tie(newSum, newCarry) = fullAdd((num1[currIndex] - '0'), (num2[currIndex] - '0'), newCarry);
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
};

std::string subtractBinary(std::string num1, std::string num2){
    //If the input binary is the same length this function will use the full and half subtractors to do line subtraction
    //It starts with the last digit of the input and subtracts it and goes from last digit to first digit
    //Adding '0' turns an int to a char and opposite with subtracting '0'
    //This function has error checking and will return an error code when neccessary
    if(num1.size() == num2.size()){
        std::string finalAnswer = "";
        int lastDiff, lastBorrow;
        int currIndex = num1.size() - 1;
        std::tie(lastDiff, lastBorrow) = halfSubtract(num1[currIndex] - '0', num2[currIndex] - '0');
        finalAnswer += (lastDiff + '0');
        currIndex--;
        while(currIndex >= 0){
            std::tie(lastDiff, lastBorrow) = fullSubtract(num1[currIndex] - '0', num2[currIndex] - '0', lastBorrow);
            finalAnswer += (lastDiff + '0');
            currIndex--;
        }

        if(lastBorrow == 1){
            return "ERROR - Negative Result";
        }

        std::reverse(finalAnswer.begin(), finalAnswer.end());

        return finalAnswer;
    }
    return "ERROR - Input strings must be same length";
}
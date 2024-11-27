/*
Number Extractor
Description: Takes in a string and outputs the double form of that string
Inputs: A string
Outputs: A double
Author: Matthew Eagleman
Date Created: 11/27/2024
*/

//Imports
#include <iostream>
#include <iomanip>
#include <string>

//NameSpaces
using namespace std;

//Functions
double extractNumeric(const string& str);
double power(int num, int power);
bool isDigit(char chr);
bool isValid(char chr);
int getDecimalPlace(const string& str);
int charToNum(char chr);
int getSign(const string& str);
int getPlace(int decimalPos, int index);

//Main function
int main(){
    //Run the program
    string input;
    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;
        if (input == "END") break;
        double number = extractNumeric(input);
        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        }
        else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}

bool isDigit(char chr){
    //Return whether or not the given character is a digit
    string digits = "0123456789";
    for (int i = 0; i < digits.length(); i++){
        if (digits[i] == chr) return true;
    }
    return false;
}
int charToNum(char chr){
    //Take a character and convert it to an integer
    switch (chr)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            throw runtime_error("Not a digit");
    }
}
double power(int num, int power){
    //Return a number taken to the given power
    double truNum = num;
    double result = num;
    if (power == 0) return 1;
    if (power < 0){
        power *= -1;
        result = 1/result;
        truNum = result;
    }
    for (int i = 0; i< power - 1; i++){
        result *= truNum;
    }
    return result;
}
int getSign(const string& str){
    //Return a integer representing whether the string is positive or negative
    for (int i = 1; i<str.length();i++){
        if (str[i] == '+' || str[i] == '-') {
            throw runtime_error("Sign must only be at the very front");
        }
    }
    if (str[0] == '-') return -1;
    else return 1;
}
bool isValid(char chr){
    string valid = "0123456789+-.";
    for (int i = 0; i<valid.length(); i++){
        if (chr == valid[i]){
            return true;
        }
    }
    return false;
}
int getPlace(int decimalPos, int index){
    if (index <=  decimalPos) return decimalPos - index - 1;
    else if (index >= decimalPos) return decimalPos - index;
}
double extractNumeric(const string& str){
    double num = 0;
    int decimalPos;
    try{
        int decimalPos = getDecimalPlace(str);
        int sign = getSign(str);
        for (int i = 0; i < str.length(); i++){
            if (isValid(str[i])){
                if (isDigit(str[i])){
                    int place = getPlace(decimalPos, i);
                    num += charToNum(str[i]) * power(10,place);
                }
            }
            else{
                throw runtime_error("There is an invalid symbol in your input");
            }
        }
        return num * sign;
    }
    catch (const exception& e){
        return -999999.99;
    }
}
int getDecimalPlace(const string& str){
    int place = str.length();
    bool found = false;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == '.'){
            if (!found){
                place = i;
                found = true;
            }
            else {
                throw runtime_error("Can't have more than one decimal place");
            }
        }
    }
    return place;
}

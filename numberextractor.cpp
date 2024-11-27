#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double extractNumeric(const string& str);
int getDecimalPlace(const string& str);
int charToNum(char chr);

bool isDigit(char chr){
    string digits = "0123456789";
    for (int i = 0; i < digits.length(); i++){
        if (digits[i] == chr){
            return true;
        }
    }
    return false;
}

int charToNum(char chr){
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
    double pow = num;
    if (power > 0){
        for (int i = 0; i< power - 1; i++){
            pow *= pow;
        }
    }
    else if (power == 0){
        pow = 1;
    }
    else if (power < 0){
        power *= -1;
        pow = 1/pow;
        for (int i = 0; i< power - 1; i++){
            pow *= 1/pow;
        }
    }
    return pow;
}

int getSign(const string& str){
    for (int i = 1; i<str.length();i++){
        if (str[i] == '+' || str[i] == '-'){
            throw runtime_error("Sign must only be at the very front");
        }
    }
    if (str[0] == '-'){
        return -1;
    }
    else{
        return 1;
    }
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

double extractNumeric(const string& str){
    double num = 0;
    int decimalPos;
    try{
        int decimalPos = getDecimalPlace(str);
        int sign = getSign(str);
        for (int i = 0; i < str.length(); i++){
            if (isValid(str[i])){
                int place = decimalPos - i - 1;
                if (isDigit(str[i])){
                    num += charToNum(str[i]) * power(10,place);
                }
            }
        }
        return num;
    }
    catch (const exception& e){
        return -999999.99;
    }
}

int getDecimalPlace(const string& str){
    int place;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == '.'){
            if (place == NULL){
                place = i;
            }
            else {
                throw runtime_error("Can't have more than one decimal place");
            }
        }
    }
    return place;
}

int main(){
    string input;
    
    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;
        if (input == "END") 
        {
            break;
        }
        double number = extractNumeric(input);
        if (number != -999999.99)
        {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } 
        else 
        {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}
/*
 * File:        CS112_A2_T3_SectionNum_20230455_20230382_20230603.cpp
 *
 * Purpose:     Fraction Calculator (Summation, Subtraction, Multiplication and Division)
 *
 * Author:      Hady Mohammed Meawad Mohammed           20230455        meawad.hady@gmail.com
 *              Marwan Hussein Mohamed Mohamed          20230382        marawanlabana649@gmail.com
 *              Mahmoud Abdelaziz Mahmoud               20230603        20230603@stud.fci-cu.edu.eg
 *
 * Lab Number:  S19, S20
 * TA:          Eng. Yomna Fathy
 *
 * Emails:      20230455:   meawad.hady@gmail.com
 *              20230382:   marawanlabana649@gmail.com
 *              20230603:   20230603@stud.fci-cu.edu.eg
 *
 * ID1:         20230455 – Input Validation, Program Switch Case, Simplification Function, and Multiplication
 *
 * ID2:         20230382 – Improper Fraction Validation, Subtraction, Summation
 *
 * ID3:         20230603 – Division function, Algorithm and Pseudocode
 *
 * Algorithm:   https://drive.google.com/drive/folders/1URdyDh9vbw2zpuUzoEvHvnBzi_S7382c?usp=sharing
 *
 * GitHub:      https://github.com/HadyMohamed2004/Fraction_Calculator_T3
*/


#include <iostream>
#include <string>
#include <regex>

using namespace std;


// Function to simplify a fraction represented by an integer array of size 2
void simplify(long long c[2]) {
    // Determine the sign of the fraction
    int sign = (c[0] < 0) ? -1 : 1;
    int sign_d = (c[1] < 0) ? -1 : 1;

    // Ensure the numerator is positive
    c[0] *= (c[0] < 0) ? -1 : 1;
    c[1] *= (c[1] < 0) ? -1 : 1;

    // Check if the numerator and denominator are equal
    if (c[0] == c[1]) {
        cout << "= " << 1 * sign * sign_d << endl; // Print 1
    } else {

        // Find the smallest divisor to simplify the fraction
        int divisor = (c[0] < c[1]) ? c[0] : c[1];
        for (int i = divisor; i > 0; i--) {
            // Check if both numerator and denominator are divisible by the current divisor
            if (c[0] % i == 0 && c[1] % i == 0) {
                // Simplify the fraction by dividing both numerator and denominator by the divisor
                c[0] /= i;
                c[1] /= i;
                // Exit the loop after finding the greatest common divisor
                break;
            }
        }
        // Output the simplified fraction
        cout << "= ";
        if (c[1] == 1 || c[0] == 0) {
            // Output the numerator with sign if the denominator is 1 or numerator is 0
            cout << c[0] * sign << endl;
        } else {
            // Output the simplified fraction in the form of numerator/denominator with sign
            cout << c[0] * sign * sign_d << "/" << c[1] << endl;
        }
    }
}


/*
 * Fractions Format Used in Calculations
 * a[0]: first numerator
 * a[1]: first denominator
 * b[0]: second numerator
 * b[1]: second denominator
*/

// Function to multiply two fractions represented by integer arrays of size 2
void multiply(long long a[2], long long b[2]) {
    // Declare an array to store the result of multiplication
    long long c[2];
    // Multiply numerators and denominators separately
    c[0] = a[0] * b[0]; // Multiply numerators
    c[1] = a[1] * b[1]; // Multiply denominators

    // Simplify the resulting fraction
    simplify(c);
}

// Function to divide two fractions represented by integer arrays of size 2
void divide(long long a[2], long long b[2]) {
    // Declare an array to store the result of division
    long long c[2];  // the array of result fraction

    // Multiply the first numerator by the second denominator to get the numerator of the result
    c[1] = a[1] * b[0];
    // Multiply the first denominator by the second numerator to get the denominator of the result
    c[0] = a[0] * b[1];

    // Check if denominator is "0" Return Math Error
    if (c[1] == 0) {
        cout << "Math Error!" << endl;
        // Simplify the resulting fraction
    } else {
        simplify(c);
    }
}

// Function to add two fractions represented by integer arrays of size 2
void sum(long long a[2], long long b[2]) {
    // Declare an array to store the result of addition
    long long c[2];
    // Calculate the numerator of the result by cross-multiplying and adding
    c[0] = a[0] * b[1] + a[1] * b[0];
    // Calculate the denominator of the result by multiplying the denominators
    c[1] = a[1] * b[1];
    // Simplify the resulting fraction
    simplify(c);
}


// Function to subtract two fractions represented by integer arrays of size 2
void sub(long long a[2], long long b[2]) {
    // Declare an array to store the result of subtraction
    long long c[2];
    // Calculate the numerator of the result by cross-multiplying and subtracting
    c[0] = a[0] * b[1] - a[1] * b[0];
    // Calculate the denominator of the result by multiplying the denominators
    c[1] = a[1] * b[1];
    // Simplify the resulting fraction
    simplify(c);
}


int main() {
    // Declare variables for two fractions, a symbol, and input strings
    long long f1[2], f2[2];
    char symbol;
    string fraction1, fraction2;

    // Display welcome message
    cout << "Welcome to the Fractions Calculator." << endl;

    // Main loop for calculator operations
    while (true) {

        // Prompt user for input fraction format
        cout << "Expressions must be written like this: a/b [-+*/] c/d" << endl;
        cout << "Enter fractions to calculate or exit:";


        cin >> fraction1;
        for (char &x: fraction1) {
            x = tolower(x);
        }
        if (fraction1 == "exit") {
            cout << "Thank you for using our Fraction Calculator" << endl;
            break;
        }
        cin >> symbol >> fraction2;


        // Ensure fractions have denominators
        if (fraction1.find('/') == string::npos)
            fraction1 += "/1";
        if (fraction2.find('/') == string::npos)
            fraction2 += "/1";

        // Declaring mathematical Symbols
        string symbols = "+-/*";

        // Using regex check for fraction patterns in each string to Validate the format of input fractions using regular expressions
        if (!regex_match(fraction1, regex("[-+]?[0-9]+/[-+]?[0]?[1-9]+"))) {        // Check first fraction format
            cout << "Invalid operation. Try again" << endl;
            continue;
        } else if (!regex_match(fraction2, regex("[-+]?[0-9]+/[-+]?[0]?[1-9]+"))) { // Check Second fraction format
            cout << "Invalid operation. Try again" << endl;
            continue;
        } else if (symbols.find(symbol) ==
                   string::npos) {      // if entered symbol isn't valid, Re-prompt user to enter the expression correctly
            cout << "Invalid operand" << endl;
            continue;
        }

        // convert strings to fraction, each fraction in an array, where f1[0] is the nominator and f1[1] is the denominator.
        // Dividing the string based on "/" position
        f1[0] = stoi(fraction1.substr(0, fraction1.find('/')));
        f1[1] = stoi(fraction1.substr(fraction1.find('/') + 1));
        f2[0] = stoi(fraction2.substr(0, fraction2.find('/')));
        f2[1] = stoi(fraction2.substr(fraction2.find('/') + 1));



        // Perform the appropriate calculation based on the operation symbol using a switch statement
        switch (symbol) {
            case '/': {
                divide(f1, f2);
                continue;   // Continue to next iteration
            }
            case '*': {
                multiply(f1, f2);
                continue;   // Continue to next iteration
            }
            case '+': {
                sum(f1, f2);
                continue;   // Continue to next iteration
            }
            case '-': {
                sub(f1, f2);
                continue;   // Continue to next iteration
            }
        }

    }

    return 0;
}
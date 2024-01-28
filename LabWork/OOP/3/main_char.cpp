//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <vector>

using namespace std;

// MARK: - Main
int main()
{
    vector<char> userStr;

    cout << "Write your str : ";
    char c;
    while (cin.get(c) and c != '\n')
    {
        userStr.push_back(c);
    }

    vector<vector<char>> words; // vector with words
    vector<char> word;           // word

    // getter word's from user str
    for (char c : userStr)
    {
        if (c == ' ' && !word.empty()) // if need ignore punctuation marks use :
        {                              // or c == '!' or c == '?' or c == ',' or c == '.'
            words.push_back(word);
            word.clear();
        }
        else if (c != ' ') // also to use if, if need ignore punctuation marks
        {
            word.push_back(c);
        }
    }

    // add last word
    if (!word.empty())
    {
        words.push_back(word);
    }

    // calculation and print result
    cout << endl << "Inverted string with a sequence of words : ";

    userStr.clear();

    for (auto it = words.rbegin(); it != words.rend(); ++it)
    {
        for (char c : *it)
        {
            userStr.push_back(c);
        }
        userStr.push_back(' ');
    }

    cout << string(userStr.begin(), userStr.end()) << endl;

    return 0;
} // int main

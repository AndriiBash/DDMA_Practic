//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// MARK: - Main
int main()
{
    string *userStr = new string();

    cout << "Write your str : ";
    getline(cin, *userStr);
    
    vector<string> *words = new vector<string>; // vector with words;
    string *word = new string();                // word
    
    // getter word's from user str
    for (char c : *userStr)
    {
        if (c == ' ' and !word->empty())        // if need ignore punctuation marks use :
        {                                       // or c == '!' or c == '?' or c == ',' or c == '.'
            words->push_back(*word);
            word->clear();
        }
        else if (c != ' ')                      // also to use if, if need ignore punctuation marks
        {
            *word += c;
        }
    }
    
    // add last word
    if (!word->empty())
    {
        words->push_back(*word);
    }
    
    // calculation and print result
    cout << endl <<"Inverted string with a sequence of words : " ;
    
    userStr->clear();
    
    for (auto it = words->rbegin(); it != words->rend(); ++it)
    {
        *userStr += *it + " ";
    }
    
    cout << *userStr << endl;
    
    // finnaly!🥳
    delete words;
    delete userStr;

    return 0;
}// int main

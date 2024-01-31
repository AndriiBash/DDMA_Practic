//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    string userStr;
    
    cout << "Write your str: ";
    getline(cin, userStr);

    vector<string> words;

    // Use lib function for processing string
    size_t start = 0;
    size_t end = userStr.find(' ');
    
    while (end != string::npos)
    {
        string word = userStr.substr(start, end - start);
        words.push_back(word);
        start = end + 1;
        end = userStr.find(' ', start);
    }

    string lastWord = userStr.substr(start);
    if (!lastWord.empty())
    {
        words.push_back(lastWord);
    }

    // Resers word and cout result
    cout << "Inverted string with a sequence of words: ";
    
    for_each(words.rbegin(), words.rend(), [](const string& word)
    {
        cout << word << ' ';
    });

    cout << endl;
    return 0;
}

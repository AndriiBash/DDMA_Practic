//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <iomanip>

using namespace std;

struct Person
{
    string fullName;
    bool hasSiblings;
    int dayOfBirth;
    int monthOfBirth;
    int yearOfBirth;
    double weight;

    // constructor
    Person(const string& name, bool siblings, int day, int month, int year, double weight)
        : fullName(name), hasSiblings(siblings), dayOfBirth(day), monthOfBirth(month), yearOfBirth(year), weight(weight) {}

    // Додамо метод для зміни ваги
    void changeWeight(double newWeight)
    {
        weight = newWeight;
    }

    // Метод для виведення статусу особи в залежності від ваги
    void printStatus() const
    {
        if (weight < 60)
            cout << "Underweight" << endl;
        else if (weight >= 60 && weight <= 80)
            cout << "Normal weight" << endl;
        else
            cout << "Overweight" << endl;
    }
}; // struct Person

void printInfo(const Person& person)
{
    cout << "Full Name : " << person.fullName << endl;
    cout << boolalpha << "Has Siblings : " << person.hasSiblings << endl;
    cout << "Date of Birth : " << person.dayOfBirth << "." << person.monthOfBirth << "." << person.yearOfBirth << endl;
    cout << "Weight : " << person.weight << " kg" << endl;
}

int main()
{
    // init Person
    Person person = {"John Doe", true, 15, 3, 1990, 70.5};

    // count person info
    printInfo(person);

    // Set new Weight and cout status
    person.changeWeight(75.0);
    cout << "Updated Weight: " << person.weight << " kg" << endl;
    person.printStatus();

    // Entet new info to Person from user
    cout << "\nEnter new information:\n";
    cout << "Full Name: ";
    getline(cin, person.fullName);

    cout << "Has Siblings (true/false): ";
    cin >> boolalpha >> person.hasSiblings;

    cout << "Day of Birth: ";
    cin >> person.dayOfBirth;

    cout << "Month of Birth: ";
    cin >> person.monthOfBirth;

    cout << "Year of Birth: ";
    cin >> person.yearOfBirth;

    cout << "Weight: ";
    cin >> person.weight;

    // Print new info
    printInfo(person);
    person.printStatus();

    return 0;
}

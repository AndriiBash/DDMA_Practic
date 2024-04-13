#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Person
{
private:
    string fullName;
    bool hasSiblings;
    int dayOfBirth;
    int monthOfBirth;
    int yearOfBirth;
    double weight;

public:
    // constructor
    Person(const string& name, bool siblings, int day, int month, int year, double weight)
        : fullName(name), hasSiblings(siblings), dayOfBirth(day), monthOfBirth(month), yearOfBirth(year), weight(weight) {}

    // constructor for data from file
    Person(const string& filename)
    {
        ifstream inFile(filename);
        
        if (inFile.is_open())
        {
            getline(inFile, fullName);
            inFile >> boolalpha >> hasSiblings;
            inFile >> dayOfBirth >> monthOfBirth >> yearOfBirth;
            inFile >> weight;
            inFile.close();
        }
        else
        {
            cout << "Error : Unable to open file for reading." << endl;
        }
    }

    // destructor for save data
    ~Person()
    {
        ofstream outFile("person_data.txt");
        
        if (outFile.is_open())
        {
            outFile << fullName << endl;
            outFile << boolalpha << hasSiblings << endl;
            outFile << dayOfBirth << " " << monthOfBirth << " " << yearOfBirth << endl;
            outFile << weight << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    // setters
    void setFullName(const string& name) { fullName = name; }
    void setHasSiblings(bool siblings) { hasSiblings = siblings; }
    void setDayOfBirth(int day) { dayOfBirth = day; }
    void setMonthOfBirth(int month) { monthOfBirth = month; }
    void setYearOfBirth(int year) { yearOfBirth = year; }
    void setWeight(double newWeight) { weight = newWeight; }
    
    double getWeight() const { return weight; }
    string getFullName() const { return fullName; }
    bool getHasSiblings() const { return hasSiblings; }
    int getDayOfBirth() const { return dayOfBirth; }
    int getMonthOfBirth() const { return monthOfBirth; }
    int getYearOfBirth() const { return yearOfBirth; }

    void printStatus() const
    {
        if (weight < 60)
        {
            cout << "Underweight" << endl;
        }
        else if (weight >= 60 && weight <= 80)
        {
            cout << "Normal weight" << endl;
        }
        else
        {
            cout << "Overweight" << endl;
        }
    }

    void printInfo() const
    {
        cout << "Full Name : " << fullName << endl;
        cout << boolalpha << "Has Siblings : " << hasSiblings << endl;
        cout << "Date of Birth : " << dayOfBirth << "." << monthOfBirth << "." << yearOfBirth << endl;
        cout << "Weight : " << weight << " kg" << endl;
    }
};

int main()
{
    // init Person from file
    Person person("person_data.txt");

    cout << "Data from file\n";
    person.printInfo();

    // Set new Name and Weight from user input
    cout << "\nEnter new information:\n";

    cout << "New Full Name: ";
    string newName;
    getline(cin >> ws, newName);

    cout << "New Weight: ";
    double newWeight;
    cin >> newWeight;

    // Update Person's data
    person.setFullName(newName);
    person.setWeight(newWeight);

    // Print updated info
    cout << "\nUpdated Information:\n";
    person.printInfo();
    person.printStatus();

    return 0;
}

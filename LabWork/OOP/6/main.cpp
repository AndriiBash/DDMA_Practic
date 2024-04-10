#include <iostream>
#include <iomanip>

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

    // setters
    void setFullName(const string& name) { fullName = name; }
    void setHasSiblings(bool siblings) { hasSiblings = siblings; }
    void setDayOfBirth(int day) { dayOfBirth = day; }
    void setMonthOfBirth(int month) { monthOfBirth = month; }
    void setYearOfBirth(int year) { yearOfBirth = year; }
    void setWeight(double newWeight) { weight = newWeight; }
    
    double getWeight() const { return weight; }

    // Метод для виведення статусу особи в залежності від ваги
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

    // Додамо метод для виведення інформації про особу
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
    // init Person
    Person person("John Doe", true, 15, 3, 1990, 70.5);

    // count person info
    person.printInfo();

    // Set new Weight and cout status
    person.setWeight(75.0);
    cout << "Updated Weight: " << person.getWeight() << " kg" << endl;
    person.printStatus();

    // Entet new info to Person from user
    cout << "\nEnter new information:\n";
    cout << "Full Name: ";
    string name;
    getline(cin, name);
    person.setFullName(name);

    cout << "Has Siblings (true/false): ";
    bool siblings;
    cin >> boolalpha >> siblings;
    person.setHasSiblings(siblings);

    cout << "Day of Birth: ";
    int day;
    cin >> day;
    person.setDayOfBirth(day);

    cout << "Month of Birth: ";
    int month;
    cin >> month;
    person.setMonthOfBirth(month);

    cout << "Year of Birth: ";
    int year;
    cin >> year;
    person.setYearOfBirth(year);

    cout << "Weight: ";
    double weight;
    cin >> weight;
    person.setWeight(weight);

    // Print new info
    person.printInfo();
    person.printStatus();

    return 0;
}

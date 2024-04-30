#include <iostream>
#include <string>

using namespace std;

// Base class for Lifting Equipment
class LiftingEquipment 
{
protected:
    string name;
    double maxLoad;
public:
    // Constructor
    LiftingEquipment(string _name, double _maxLoad) : name(_name), maxLoad(_maxLoad) {}

    // Function to display information about the lifting equipment
    void showInfo() const 
    {
        cout << "Lifting Equipment: " << name << endl;
        cout << "Maximum Load: " << maxLoad << " tons" << endl;
    }

    // Virtual function for lifting load
    virtual void liftLoad(double weight)
    {
        cout << "Lifting load using the lifting equipment" << endl;
    }
};

// Derived class Crane
class Crane : public LiftingEquipment
{
private:
    double boomLength;
public:
    // Constructor
    Crane(string _name, double _maxLoad, double _boomLength)
        : LiftingEquipment(_name, _maxLoad), boomLength(_boomLength) {}

    // Overridden function to display information about the crane
    void showInfo() const  
    {
        LiftingEquipment::showInfo();
        cout << "Boom Length: " << boomLength << " meters" << endl;
    }

    // Overridden function for lifting load with the crane
    void liftLoad(double weight) override 
    {
        cout << "Lifting load using the crane" << endl;
        
        if (weight <= maxLoad)
        {
            cout << "Load lifted successfully" << endl;
        }
        else
        {
            cout << "Exceeded maximum load" << endl;
        }
    }
};

// Derived class for Portal Crane
class PortalCrane : public Crane 
{
private:
    double span;
public:
    // Constructor
    PortalCrane(string _name, double _maxLoad, double _boomLength, double _span)
        : Crane(_name, _maxLoad, _boomLength), span(_span) {}

    // Overridden function to display information about the portal crane
    void showInfo() const
    {
        Crane::showInfo();
        cout << "Span: " << span << " meters" << endl;
    }
};

int main() 
{
    // Create objects of the classes
    LiftingEquipment equipment1("Crane", 10);
    Crane crane1("Gantry Crane", 20, 30);
    PortalCrane portalCrane1("Portal Crane", 25, 40, 50);

    // Call member functions to perform operations on the objects
    equipment1.showInfo();
    equipment1.liftLoad(5);
    cout << endl;

    crane1.showInfo();
    crane1.liftLoad(25);
    cout << endl;

    portalCrane1.showInfo();
    portalCrane1.liftLoad(30);

    return 0;
}

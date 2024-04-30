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

    // Virtual destructor
    virtual ~LiftingEquipment() {}

    // Function to display information about the lifting equipment
    virtual void showInfo() const
    {
        cout << "Lifting Equipment: " << name << endl;
        cout << "Maximum Load: " << maxLoad << " tons" << endl;
    }

    // Pure virtual function for lifting load
    virtual void liftLoad(double weight) = 0;
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
    void showInfo() const override
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
    void showInfo() const override
    {
        Crane::showInfo();
        cout << "Span: " << span << " meters" << endl;
    }
};

int main()
{
    // Create pointers to objects of the classes
    LiftingEquipment* equipmentPtr = new Crane("Gantry Crane", 20, 30);
    Crane* cranePtr = new Crane("Gantry Crane", 20, 30);
    PortalCrane* portalCranePtr = new PortalCrane("Portal Crane", 25, 40, 50);

    // Call member functions through pointers
    equipmentPtr->showInfo();
    equipmentPtr->liftLoad(5);
    cout << endl;

    cranePtr->showInfo();
    cranePtr->liftLoad(25);
    cout << endl;

    portalCranePtr->showInfo();
    portalCranePtr->liftLoad(30);

    // Delete pointers
    delete equipmentPtr;
    delete cranePtr;
    delete portalCranePtr;

    return 0;
}

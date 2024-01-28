//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>

using namespace std;

struct apartment
{
    string owner;
    int number;
    
    // constructor
    apartment(const string& ownerName, int flatNumber) : owner(ownerName), number(flatNumber) {}
};// struct apartment


struct apartmentStack
{
    int size;
    int capacity;
    apartment **aptArray;
    
    // constructor
    apartmentStack(int maxCapacity) : size(0), capacity(maxCapacity), aptArray(new apartment*[maxCapacity])
    {
        for (int i = 0; i < maxCapacity; i++)
        {
            aptArray[i] = nullptr;
        }
    } // apartmentStack(int maxCapacity) : size(0), capacity(maxCapacity), aptArray(new apartment*[maxCapacity])

    
    void append(const apartment *apPtr)
    {
        if (size < capacity)
        {
            aptArray[size++] = new apartment(*apPtr);
        }
        else
        {
            cout << "Stack overflow!\n";
        }
    }// void append(apartment *apPtr)
    
    
    void removeByIndex(int index)
    {
        if (index >= 0 and index < size)
        {
            delete aptArray[index]; // Delete memory for seacred struct
            
            // Move last sturct to position (if this not last)
            if (index < size - 1)
            {
                aptArray[index] = aptArray[size - 1];
            }
            
            --size; // Minus size stack
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }// void remove(int index)
    
    // Function to search for an apartment by index
    apartment* searchByIndex(int index) const
    {
        if (index >= 0 and index < size)
        {
            return aptArray[index];
        }
        else
        {
            cout << "Invalid index.\n";
        }
        return nullptr;
    }// apartment* searchByIndex(int index) const

    
    void editByIndex(int index, const string& newOwner = "", int newNumber = -1)
    {
        if (index >= 0 and index < size)
        {
            if (!newOwner.empty())
            {
                aptArray[index]->owner = newOwner;
            }
            if (newNumber != -1)
            {
                aptArray[index]->number = newNumber;
            }
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }// void editByIndex(int index, const string& newOwner = "", int newNumber = -1)
    
    
    // Overloaded function to edit an apartment by index with a single parameter
    void editByIndex(int index, int newNumber)
    {
        editByIndex(index, "", newNumber);
    }// void editByIndex(int index, int newNumber)

    
    // Function to split the stack into multiple identical stacks
    apartmentStack* split() const
    {
        int newCapacity = capacity / 2;
        apartmentStack* newStack = new apartmentStack(newCapacity);

        // Copy elements from the original stack to the new stack
        for (int i = 0; i < size; ++i)
        {
            newStack->append(aptArray[i]);
        }

        return newStack;
    }

    
    // Function to split the stack into two identical stacks
    pair<apartmentStack*, apartmentStack*> splitToTwo() const
    {
        int newCapacity = capacity / 2;
        apartmentStack* newStack1 = new apartmentStack(newCapacity);
        apartmentStack* newStack2 = new apartmentStack(newCapacity);

        // Copy elements from the original stack to the new stacks
        for (int i = 0; i < size; ++i)
        {
            if (i < newCapacity)
            {
                newStack1->append(aptArray[i]);
            }
            else
            {
                newStack2->append(aptArray[i]);
            }
        }

        return make_pair(newStack1, newStack2);
    }// pair<apartmentStack*, apartmentStack*> split() const
    
    
    ~apartmentStack()
    {
        for (int i = 0; i < size; i++)
        {
            delete aptArray[i]; // clear memory for [i] struct
        }
        delete[] aptArray; // clear array prt
    }// ~apartmentStack()
    
}; // struct apartmentStack
    

// MARK: - Main

int main()
{
    //MARK: -  Create a stack with a capacity of 4
    apartmentStack myStack(8);

    //MARK: -  Append apartments to the stack
    myStack.append(new apartment("John Bringo", 101));
    myStack.append(new apartment("Jane Does", 202));
    myStack.append(new apartment("Bob Smith", 303));
    myStack.append(new apartment("Alice Johnson", 404));
    myStack.append(new apartment("Charlie Brown", 505));
    myStack.append(new apartment("Eva Green", 606));
    myStack.append(new apartment("Frank White", 707));
    myStack.append(new apartment("Grace Miller", 808));

    // Print elements in the original stack
    cout << "Original Stack:\n";
    for (int i = 0; i < myStack.size; i++)
    {
        cout << "Owner: " << myStack.aptArray[i]->owner << ", Number: " << myStack.aptArray[i]->number << endl;
    }

    //MARK: -  Search for an apartment by index and print details
    int searchIndex = 2;
    cout << "\nSearching for apartment at index " << searchIndex << ":\n";
    
    apartment* searchedApartment = myStack.searchByIndex(searchIndex);
    
    if (searchedApartment != nullptr)
    {
        cout << "Owner: " << searchedApartment->owner << ", Number: " << searchedApartment->number << endl;
    }
    
    //MARK: - Edit an apartment by index
    int editIndex = 1;
    cout << "\nEditing apartment at index " << editIndex << ":\n";
    
    myStack.editByIndex(editIndex, "New Owner", 999);
    
    cout << "Updated apartment details:\n";
    
    for (int i = 0; i < myStack.size; ++i)
    {
        cout << "Owner: " << myStack.aptArray[i]->owner << ", Number: " << myStack.aptArray[i]->number << endl;
    }
    
    //MARK: -  Remove an apartment by index
    int removeIndex = 0;
    cout << "\nRemoving apartment at index " << removeIndex << ":\n";
    
    myStack.removeByIndex(removeIndex);
    
    cout << "Updated stack after removal:\n";
    
    for (int i = 0; i < myStack.size; ++i)
    {
        cout << "Owner: " << myStack.aptArray[i]->owner << ", Number: " << myStack.aptArray[i]->number << endl;
    }

    //MARK: -  Split the stack into two identical stacks
    auto [newStack1, newStack2] = myStack.splitToTwo();

    //MARK: -  Print elements in the new stacks
    cout << "\nNew Stack 1:\n";
    for (int i = 0; i < newStack1->size; ++i)
    {
        cout << "Owner: " << newStack1->aptArray[i]->owner << ", Number: " << newStack1->aptArray[i]->number << endl;
    }

    cout << "\nNew Stack 2:\n";
    for (int i = 0; i < newStack2->size; ++i)
    {
        cout << "Owner: " << newStack2->aptArray[i]->owner << ", Number: " << newStack2->aptArray[i]->number << endl;
    }

    //MARK: - Finnaly clean up memory, uha-ha-ha i need break all memory!
    delete newStack1;
    delete newStack2;

    return 0;
}// int main() {}

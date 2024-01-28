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
};

struct Node
{
    apartment* apt;
    Node* next;

    // constructor
    Node(apartment* aptr) : apt(aptr), next(nullptr) {}
};

struct apartmentList
{
    int size;
    Node* head;

    // constructor
    apartmentList() : size(0), head(nullptr) {}

    void append(apartment* aptr)
    {
        Node* newNode = new Node(aptr);

        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        size++;
    }

    void removeByIndex(int index)
    {
        if (index >= 0 && index < size)
        {
            if (index == 0)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            else
            {
                Node* temp = head;
                for (int i = 0; i < index - 1; i++)
                {
                    temp = temp->next;
                }

                Node* toRemove = temp->next;
                temp->next = toRemove->next;
                delete toRemove;
            }

            size--;
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }

    // Function to search for an apartment by index
    apartment* searchByIndex(int index) const
    {
        if (index >= 0 and index < size)
        {
            Node* temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->apt;
        }
        else
        {
            cout << "Invalid index.\n";
            return nullptr;
        }
    }

    void editByIndex(int index, const string& newOwner = "", int newNumber = -1)
    {
        if (index >= 0 and index < size)
        {
            if (!newOwner.empty())
            {
                head = head->next;
                apartment* newApt = new apartment(newOwner, newNumber);
                append(newApt);
            }
            if (newNumber != -1)
            {
                head->apt->number = newNumber;
            }
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }

    // Function to split the list into multiple lists
    pair<apartmentList*, apartmentList*> splitToTwo() const
    {
        int newCapacity = size / 2;
        apartmentList* newStack1 = new apartmentList();
        apartmentList* newStack2 = new apartmentList();

        Node* temp = head;
        for (int i = 0; i < size; ++i)
        {
            if (i < newCapacity)
            {
                newStack1->append(temp->apt);
            }
            else
            {
                newStack2->append(temp->apt);
            }
            temp = temp->next;
        }

        return make_pair(newStack1, newStack2);
    }

    // Function to split the list into two or three lists based on parity
    pair<apartmentList*, pair<apartmentList*, apartmentList*>> split() const
    {
        int newCapacity = (size % 2 == 0) ? size / 2 : (size / 2) + 1;
        apartmentList* newStack1 = new apartmentList();
        apartmentList* newStack2 = new apartmentList();
        apartmentList* newStack3 = (size % 2 == 0) ? nullptr : new apartmentList();

        Node* temp = head;
        for (int i = 0; i < size; ++i)
        {
            if (i < newCapacity)
            {
                newStack1->append(temp->apt);
            }
            else if (i >= newCapacity && i < 2 * newCapacity && temp)
            {
                newStack2->append(temp->apt);
            }
            else if (newStack3 && temp)
            {
                newStack3->append(temp->apt);
            }
            if (temp)
            {
                temp = temp->next;
            }
        }

        return make_pair(newStack1, make_pair(newStack2, newStack3));
    }

    ~apartmentList()
    {
        Node* temp = head;
        while (temp)
        {
            Node* nextNode = temp->next;

            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }

}; // struct apartmentList

// MARK: - Main

int main()
{
    //MARK: -  Create a list
    apartmentList myList;

    //MARK: -  Append apartments to the list
    myList.append(new apartment("John Bringo", 101));
    myList.append(new apartment("Jane Does", 202));
    myList.append(new apartment("Bob Smith", 303));
    myList.append(new apartment("Alice Johnson", 404));
    myList.append(new apartment("Charlie Brown", 505));
    myList.append(new apartment("Eva Green", 606));
    myList.append(new apartment("Frank White", 707));
    myList.append(new apartment("Grace Miller", 808));

    // Print elements in the original list
    cout << "Original List:\n";
    Node* temp = myList.head;
    while (temp)
    {
        cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
        temp = temp->next;
    }

    //MARK: -  Search for an apartment by index and print details
    int searchIndex = 2;
    cout << "\nSearching for apartment at index " << searchIndex << ":\n";

    apartment* searchedApartment = myList.searchByIndex(searchIndex);

    if (searchedApartment != nullptr)
    {
        cout << "Owner: " << searchedApartment->owner << ", Number: " << searchedApartment->number << endl;
    }

    //MARK: - Edit an apartment by index
    int editIndex = 1;
    cout << "\nEditing apartment at index " << editIndex << ":\n";

    myList.editByIndex(editIndex, "New Owner", 999);

    cout << "Updated apartment details:\n";

    temp = myList.head;
    while (temp)
    {
        cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
        temp = temp->next;
    }

    //MARK: -  Remove an apartment by index
    int removeIndex = 0;
    cout << "\nRemoving apartment at index " << removeIndex << ":\n";

    myList.removeByIndex(removeIndex);

    cout << "Updated list after removal:\n";

    temp = myList.head;
    while (temp)
    {
        cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
        temp = temp->next;
    }

    //MARK: -  Split the list into two or three lists based on parity
    auto [newList1, newLists23] = myList.split();

    //MARK: -  Print elements in the new lists
    cout << "\nNew List 1:\n";
    temp = newList1->head;
    while (temp)
    {
        cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
        temp = temp->next;
    }

    if (newLists23.first)
    {
        cout << "\nNew List 2:\n";
        temp = newLists23.first->head;
        while (temp)
        {
            cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
            temp = temp->next;
        }
    }

    if (newLists23.second)
    {
        cout << "\nNew List 3:\n";
        temp = newLists23.second->head;
        while (temp)
        {
            cout << "Owner: " << temp->apt->owner << ", Number: " << temp->apt->number << endl;
            temp = temp->next;
        }
    }

    //MARK: - Finally clean up memory
    delete newList1;
    delete newLists23.first;
    delete newLists23.second;

    return 0;
}

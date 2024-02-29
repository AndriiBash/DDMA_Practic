//
//  main.cpp
//  LabWork
//
//  Created by Андрiй on 01.01.2024.
//

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class BinaryFileWriter
{
private:
    unique_ptr<string> filePath;
    unique_ptr<string> fileName;

public:
    BinaryFileWriter(const string& path, const string& name) : filePath(make_unique<string>(path)), fileName(make_unique<string>(name)) {} // init

    ~BinaryFileWriter()
    {
        filePath.reset();
        fileName.reset();
    }// destructor

    void setFilePath(const string& dir)
    {
        *filePath = dir;
    }// void setFilePath(const string &dir)

    void setFileName(const string& name)
    {
        *fileName = name;
    }// void setFileName(const string &name)

    void writeText(const string& text)
    {
        if (filePath == nullptr)
        {
            cerr << "Error: File path is not set." << endl;
            return;
        }

        ofstream binaryFile(*filePath + *fileName, ios::binary);

        if (binaryFile.is_open())
        {
            binaryFile.write(reinterpret_cast<const char*>(&text[0]), sizeof(text));
            binaryFile.close();

            cout << "Text successfully written to the binary file!" << endl;
        }
        else
        {
            cerr << "Error: Opening binary file for writing." << endl;
        }
    }// void writeText(const string& text)

    unique_ptr<string> readText()
    {
        ifstream binaryFile(*filePath + *fileName, ios::binary | ios::in);
        unique_ptr<string> result = make_unique<string>();

        if (binaryFile.is_open())
        {
            binaryFile.seekg(0, ios::end);
            size_t fileSize = binaryFile.tellg();
            binaryFile.seekg(0, ios::beg);

            char* buffer = new char[fileSize];
            binaryFile.read(buffer, fileSize);
            binaryFile.close();

            result->assign(buffer, fileSize);

            delete[] buffer;

            cout << "Text successfully read from the binary file!" << endl;
        }
        else
        {
            cerr << "Error: Opening binary file for reading." << endl;
        }

        return result;
    }// unique_ptr<string> readText()
    
    void writeIntArray(const int *data, size_t size)
    {
        if (filePath == nullptr)
        {
            cerr << "Error: File path is not set." << endl;
            return;
        }
        
        ofstream binaryFile(*filePath + *fileName, ios::binary | ios::out);
        
        if (binaryFile.is_open())
        {
            binaryFile.write(reinterpret_cast<const char *>(data), size * sizeof(int));
            binaryFile.close();
            
            cout << "Int array successfully written to the binary file!" << endl;
        }
        else
        {
            cerr << "Error: Opening binary file for writing." << endl;
        }
    }// void writeIntArray(const int *data, size_t size)

    vector<int> readIntArray(size_t size)
    {
        vector<int> result;
        
        if (filePath == nullptr)
        {
            cerr << "Error: File path is not set." << endl;
            return result;
        }

        ifstream binaryFile(*filePath + *fileName, ios::binary | ios::in);

        if (binaryFile.is_open())
        {
            binaryFile.seekg(0, ios::end);
            size_t fileSize = binaryFile.tellg();
            binaryFile.seekg(0, ios::beg);

            result.resize(size);

            binaryFile.read(reinterpret_cast<char *>(result.data()), size * sizeof(int));
            binaryFile.close();
            
            cout << "Int array successfully read from the binary file!" << endl;
        }
        else
        {
            cerr << "Error: Opening binary file for reading." << endl;
        }

        return result;
    }// vector<int> readIntArray(size_t size)
};// class BinaryFileWriter


string *getUserDesktopPath()
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == nullptr)
    {
        cerr << "Error getting user information." << endl;
        exit(EXIT_FAILURE);
    }
    
    string *desktopPath = new string(pw->pw_dir);
    *desktopPath += "/Desktop";

    return desktopPath;
}// string getUserDesktopPath()


int main()
{
    string *desktopPath = getUserDesktopPath();
    cout << "Desktop dir: " << *desktopPath << endl;
    
    string* fileName = new string();
    
    cout << "Write file name : ";
    getline(cin, *fileName);
    
    string* userText = new string();
    
    cout << "Write text (char) to file : ";
    getline(cin, *userText);
    
    // Create object BinaryFileWriter with dir to desktop and fileName
    BinaryFileWriter binaryWriter(*desktopPath, "/" + *fileName + ".bin");

    // write in binary file
    binaryWriter.writeText(*userText);
    
    // read from binary file
    unique_ptr<string> readResult = binaryWriter.readText();
    cout << "Read result: " << *readResult << endl;
    
    
    
    
    cout << "Example to write array : ";
    binaryWriter.setFileName("arrayFile");
    
    int intArray[] = {1, 2, 3, 4, 5};
    size_t arraySize = sizeof(intArray) / sizeof(int);

    binaryWriter.writeIntArray(intArray, arraySize);

    vector<int> readIntArrayResult = binaryWriter.readIntArray(arraySize);

    cout << "Read result:" << endl;
    for (int value : readIntArrayResult)
    {
        cout << value << " ";
    }
    cout << endl;

    
    
    
    // free!
    delete desktopPath;
    readResult.reset();
    
    return 0;
}

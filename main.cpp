#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <stdio.h>
#include <vector>
using namespace std;

void spaceRemoval(string&, vector<char>&);
void recordOrganizer(string&, vector<string>&);
void duplicateRemoval(vector<string>&);
void print(vector<string>&, string);
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: removeduplicated input=input1.txt output=output1.txt" << endl;
        return -1;
    }
    else
    {
        //Step 1: Load content from files into char and then into vector
        ArgumentManager am(argc, argv);
        const string input = am.get("input");//Will now be equal to "input#.txt"
        const string output = am.get("output");//Will now be equal to "output.txt"
        cout << "input=" << input << " output=" << output << endl;
        ifstream ifs;
        ifs.open(input);//open whichever file the user put into the program call
        if(ifs.is_open())
        {
            char A;
            vector<char> charRecords;
            while (!ifs.eof())
            {
                A = ifs.get();
                charRecords.push_back(A);
            }
            ifs.close();
            string data;
            vector<string> records;
            spaceRemoval(data, charRecords);
            recordOrganizer(data, records);
            duplicateRemoval(records);
            print(records, output);
        }
        else
        {
            cerr << "Unable to open file." << endl;
        }
    }
    return 0;
}
void spaceRemoval(string& newString, vector<char>& vec)
{
    //load vector into string, strip away the spaces at same time
    for(unsigned int i = 0; i < vec.size()-1; i++)
    {
        if(vec[i] != ' ' && vec[i] != '\n')
        {
            newString += vec[i];
        }
    }
}
void recordOrganizer(string& newData, vector<string>& vec)
{
    //Use temp variable to isolate one record at a time, then load that record into a single index w/in vector
    //Doing this makes removing duplicates a great deal easier later
    string temp;
    for(int i = 0; i < newData.length(); i++)
    {
        if (newData[i] != '}')
        {
            temp += newData[i];
        }
        else if (newData[i] == '}')
        {
            temp += newData[i];//Add in the final closing curly brace
            vec.push_back(temp);//push the whole record into index i of the vector
            temp = "";//clear out the temporary string for reuse
        }
    }
}
void duplicateRemoval(vector<string>& vec)
{
    //Remove duplicates by comparing record[i] to record[j], then deleting and resizing if they're the same
    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = i+1; j < vec.size(); j++)
        {
            if(vec[i] == vec[j])
            {
                vec.erase(vec.begin()+j);
                j--;
            }
        }
    }
}
void print(vector<string>& vec, const string fileName)
{
    //print the contents of the edited vector to text file
    ofstream ofs;
    ofs.open(fileName);
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        ofs << vec[i] << endl;
    }
    ofs.close();
}
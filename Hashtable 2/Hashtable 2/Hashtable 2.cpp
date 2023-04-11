#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Employee.h"


using namespace std;

int stringToInt(string s) {
    int integer = 0;
    for (int i = 0; i < s.length(); i++) {
        integer += (int)(s[i]) * (i + 1); // cast the character to an integer to get its ASCII value
    }
    return integer;
}


int main(int argc, char** argv)
{
    //Check for command line error
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }

    //Check for file
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // Get value of m
    string value;
    getline(ifs, value);
    int m = stoi(value);

    // Get number of records
    string line;
    getline(ifs, line);
    int n = stoi(line);

    //using an array
    //for part 1 and 2
    auto employee = new Employee * [m];
    const double A = (sqrt(5) - 1) / 2;

    // Vector for part 3
    vector<vector<Employee*>> v(m);
    for (int i = 0; i < m; i++) {
        v[i] = vector<Employee*>();
    }

    // Pre-populate with NULL
    for (int i = 0; i < m; i++) {
        employee[i] = NULL;
    }


    //Variables
    int collision = 0;

    //loop for employee info
    for (int i = 0; i < n; i++) {
        int age;
        int id;
        int year;
        string name;
        string job;
        string ids;
        string a;
        string y;
        getline(ifs, name, '|');
        getline(ifs, ids, '|');
        getline(ifs, a, '|');
        getline(ifs, job, '|');
        getline(ifs, y);
        id = stoi(ids);
        age = stoi(a);
        year = stoi(y);
        Employee* emp = new Employee(name, id, age, job, year);


        //division method
        int key = stringToInt(name) % m;

        v[key].push_back(emp); //add to the array
        if (v[key].size() > 1) { //count collision if the number of key is greater than 1
        }
        cout << "Adding " << name << " to table at index " << key << " ( " << v[key].size() - 1 << " collisions) " << endl;

    }
    // Ignore ***
    string ignore;
    getline(ifs, ignore);

    // Get how many queries
    string queries;
    getline(ifs, queries);
    int q = stoi(queries);

    // Lookup queries
    for (int j = 0; j < q; j++) {
        // Get names
        string name;
        getline(ifs, name);
        int value = stringToInt(name) % m;

        // Loop through vector and check collisions
        for (int i = 0; i < v[value].size(); i++) {
            auto employee = v[value][i];
            if (employee->getName() == name) {
                // Print out names
                cout << "Found " << name << " after " << i << " collisions at index " << value << " in the hashtable." << endl;
                cout << "COMPLETE RECORD: " << employee->saveFile();
                break;
            }
            collision += i++;
        }
    }
    // Print total collisions
    cout << "Total collisions to resolve: " << collision << endl;
}
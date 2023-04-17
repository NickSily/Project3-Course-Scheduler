#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Course{
private:
    std::string name; // Data Structure and Alg..
    std::string id; // COP_3530
    std::unordered_set<std::string> requiredForMajors; // requredForMahor = (CS, Math, Bio, ...)
    int credits;
    std::unordered_set<std::string> preReqs;

public:
    Course(/* args */);
    ~Course();
};

class Graph{
        

};


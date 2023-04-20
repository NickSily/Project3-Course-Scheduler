#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include "Graph.h"

using namespace std;

void examineChar(char c){
	if(c=='\n')
		std::cout << "\\n";
	else if(c=='\r')
		std::cout << "\\r";
	else if(c=='\b')
		std::cout << "\\b";
	else if(c=='\t')
		std::cout << "\\t";
	else if(c=='\a')
		std::cout << "\\a";
	else if(c=='\v')
		std::cout << "\\v";
	else if(c=='\0')
		std::cout << "\\0";
	else
		std::cout << c;
}

void examineString(string s){
	if(s!="")
	    for(int i=0;i<s.length();i++)
			examineChar(s[i]);
}

void readCSV(string filename, Graph& graph){
    // Open csv file
    std::ifstream inFile("inputFiles/" + filename);
    if(!inFile.is_open()){
        std::cout << "Error Opening file." << std::endl;
    }


    string line, id, name, credits, preReqList;

    vector<std::string> preReqs;
    string nopreeq;

    // Get the header
    getline(inFile, line);

    // Get the values
    while (std::getline(inFile, id, ',')) {
        std::getline(inFile, name, ',');
        std::getline(inFile,credits,',');
        std::getline(inFile,preReqList);

        if(preReqList.empty()){
            preReqList = "None";
        }
        // Remove the "" characters if needed
         else if(preReqList.at(0) == '\"'){
            preReqList = preReqList.substr(1, preReqList.size() - 3);
            // Convert to Stream
            std::stringstream preReqs_sstream(preReqList);
            std::string preReq;
            // std::cout << "printing all preReqs: " << std::endl;
            while (std::getline(preReqs_sstream, preReq, ','))
            {
                // examineString(preReq);
                // std::cout << " ";
                preReqs.push_back(preReq);
            }
            // std::cout << std::endl;
        }
        else if (preReqList != "\r"){
            // std::cout << "printing all preReqs: " << std::endl;
            if (preReqList.at(preReqList.size() -1 ) == '\r'){preReqList = preReqList.substr(0, preReqList.size() - 1);}
            // examineString(preReqList);
            // std::cout << std::endl;
            preReqs.push_back(preReqList);
        }

        graph.insertCourse(id, name, credits, preReqs);

        preReqs.clear();
    }

    inFile.close();
}

void courseSelection(Graph courseGraph, std::vector<Course> availableCourses){

}

int main()
{
    Graph Graph;
    int numSemesters,numCredits, currentSemester = 1, creditCount = 0;
    string course;
    cout << "How many semesters do you wish to take: " << endl;
    cin >> numSemesters;
    cout << "How many credits each semester do you wish to take: " << endl;
    cin >>  numCredits;
    cout << endl;
    readCSV("TestCourses.csv", Graph);


    // Load Values from file into test Graph
    while(currentSemester <= numSemesters &&  creditCount < numCredits){
        cout <<  "Please select any courses you'd like to include in semester " <<  currentSemester <<  endl;
        cout <<  "____________________________________________________________" <<  endl;

        //print possible courses
        // Graph.topSort();
        std::vector<Course> availableCourses;
        courseSelection(Graph, availableCourses); 
        // This will be the function that prints available courses and get's input from user
        

        cout <<  "____________________________________________________________" <<  endl;

        while(creditCount < numCredits){
            cin >> course;
            cout << endl;
            creditCount += Graph.getCredit(course);

        }

        currentSemester++;

    }




    // Print the graph
    // testGraph.print();
    std::vector<std::vector<Course>>result(Graph.topSort());



    return 0;
}

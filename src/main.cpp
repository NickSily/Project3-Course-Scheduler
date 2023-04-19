#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include "Graph.h"

using namespace std;

void examineChar(char c){
	if(c=='\n')
		std::cout<<"\\n";
	else if(c=='\r')
		std::cout<<"\\r";
	else if(c=='\b')
		std::cout<<"\\b";
	else if(c=='\t')
		std::cout<<"\\t";
	else if(c=='\a')
		std::cout<<"\\a";
	else if(c=='\v')
		std::cout<<"\\v";
	else if(c=='\0')
		std::cout<<"\\0";
	else
		std::cout<<c;
}

void examineString(std::string s){
	int i;
	if(s!="")
	    for(i=0;i<s.length();i++)
			examineChar(s[i]);
}

void readCSV(std::string filename, Graph& graph){
    // Open csv file
    std::ifstream inFile("inputFiles/" + filename);
    if(!inFile.is_open()){std::cout << "Error Opening file." << std::endl;}

    std::string line, id, name, credits, preReqList;

    std::vector<std::string> preReqs;

    // Get the header
    std::getline(inFile, line);

    // Get the values
    while (std::getline(inFile, id, ',')){
        std::cout << "Id: ";
        examineString(id);
        std::cout << std::endl;

        std::getline(inFile,name,',');
        std::cout << "name: ";
        examineString(name);
        std::cout << std::endl;

        std::getline(inFile,credits,',');
        std::cout << "Credits: ";
        examineString(credits);
        std::cout << std::endl;

        // Read all preReqs
        std::getline(inFile,preReqList);

        // Remove the "" characters if needed
        if(preReqList.at(0) == '\"'){
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

        std::cout << "PreRequisites: ";
        for (auto &&i : preReqs)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        graph.insertCourse(id, name, credits, preReqs);
        preReqs.clear();
    }

    inFile.close();
}

void printResult(std::vector<std::vector<Course>>& result){
    int count = 1;
    for (auto &&row : result){

        std::cout << "Semester " << count << ":" << std::endl;
        for (auto &&course : row){
            std::cout << "--> " << course.name << "(" << course.id << ")" << std::endl; 
        }
        count++;
    }
    

}

int main(int argc, char const *argv[])
{
    Graph testGraph;

    // Load Values from file into test Graph
    readCSV("TestCourses.csv", testGraph);

    // Print the graph
    // testGraph.print();

    std::vector<std::vector<Course>> result(testGraph.topSort());

    printResult(result);
    




    return 0;
}

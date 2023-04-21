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

void printSemesterPlan(std::vector<std::vector<Course>>& finalSemesterPlan){
    /*  FIX ME*/
    // This function just prints the contents of our semester planner
    // Let's try to make it look pretty as it's the final output of our program
    // Print all the courses in each semester
    /*
    example:
        Semester 1:
            * Geomtry
            * Calculus 1
        Semester 2:
            * Prog 1
            * Calculus 2
        (or some shit like that)
    */
}

void runProgram(Graph CourseGraphcopy){
    //Makes copy of original graph so that no info is lost (That is why we didn't pass by reference)

    // Keep a vector of vector of courses, keeping track of all selected in each semester
    std::vector<std::vector<Course>> finalCourseSchedule;

    // ask user to input Total number of credits
    int numSemesters,numCredits, totalCredits ,currentSemester = 1;
    string course;
    cout << "How many semesters do you wish to take: " << endl;
    cin >> numSemesters;
    cout << "How many credits each semester do you wish to take: " << endl;
    cin >>  numCredits;
    cout << endl;

    totalCredits = numCredits* numSemesters;

    while(currentSemester <= numSemesters){
        //Get available courses and put them into the vector
        std::vector<Course> availableCourses(getAvaliableCourses(CourseGraphcopy));

        // print the Available Courses to the user, and let him pick the courses he wants
        // The courses he wants will be removed from the first vector and added to a second one
        std::vector<Course> selectedCourses(selectFromAvailableCourses(availableCourses, numCredits));


        // let's just add the current semester's courses to our result so we have it for later
        finalCourseSchedule.push_back(selectedCourses);

        // Great, now our graph is updated and we can move on to the next semester's available courses. so let's loop
    }

    // Great now our student has built his model semester plan, so let's show the final result
    // We've been storing all the semester into on big vector of vectors, so let's just print that 
    printSemesterPlan(finalCourseSchedule);


    // Now after we show the student the semester plan he has built:
    // We are actually going to further optimize the selected courses, and offer him a revised semster
    // plan, that just tries to minimize the number of semesters in total
    // we do that by simply running the TopSort() on the Courses contained in the FinalCourseSchedule vector
    // So for that we will need to:
    // first: Loop throguh vector and create a graph with only those courses
    // run top sort on that graph, and grab the resulting vector
    // just print the resulting vector and see if the student likes it.



}


std::vector<Course> getAvaliableCourses(Graph& courseGraph){
    /*
    FIX ME
    Get the available courses for the current semester, here's how:
    loop through the Graph:
        if course indegree is 0 (no preReqs):
           Add it to the vector
    return the vector
    */
    std::vector<Course> result;
    return result;
}

std::vector<Course> selectFromAvailableCourses(std::vector<Course>& availableCourses){
    /*Fix me */ // This may be the biggest and most important method so patience here.

    // print out all available courses (name + id + credits)

    /*
    Keep getting input from the user until, either:
        num Credits in the semester is hit
        no more available courses

        GEt the input from the user and add the corresponding course to the vector
            update the total credit count for the semester

    Return the vector with the selected courses for the semester
    */


    std::vector<Course> selectedCourses;

    return selectedCourses;
    /* 
    Now that we have the courses the user will take on the semester, we can remove them from the graph
    That way we can calculate the available courses next semester
    */
}



int main()
{
    Graph myGraph;

    // Read the Data and create a graph with it
    readCSV("TestCourses.csv", myGraph);

    // runs the program 
    runProgram(myGraph);

    return 0;
}

#include<iostream>
#include <iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<string.h>
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

    unordered_set<std::string> preReqs;
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
                preReqs.insert(preReq);
            }
            // std::cout << std::endl;
        }
        else if (preReqList != "\r"){
            // std::cout << "printing all preReqs: " << std::endl;
            if (preReqList.at(preReqList.size() -1 ) == '\r'){preReqList = preReqList.substr(0, preReqList.size() - 1);}
            // examineString(preReqList);
            // std::cout << std::endl;
            preReqs.insert(preReqList);
        }

        graph.insertCourse(id, name, credits, preReqs);

        preReqs.clear();
    }

    inFile.close();
}

void printSemesterPlan(std::vector<std::vector<Course>>& finalSemesterPlan){

    int semester = 1;
    for (auto plan : finalSemesterPlan) {
        cout <<endl<< setw(11) << "Semester " << semester << "\n";
        cout << "----------------" << "\n";
        cout << "Course" << setw(9) << "Credits" << "\n";
        for (int i = 0; i < plan.size(); i++) {
            cout << plan[i].id << setw(8) << plan[i].credits << "\n";
        }
        semester++;
    }
}

std::vector<Course> selectFromAvailableCourses(std::vector<Course>& availableCourses, int credits){


    std::vector<Course> selectedCourses;
    int currentCredit=0;
    //return empty vector if available courses is empty
    if(availableCourses.empty()){
        return selectedCourses;
    }

    //print available courses
    for(auto & availableCourse : availableCourses){
        cout << availableCourse.id << ", " << availableCourse.name << "  Credits: "<< availableCourse.credits <<endl;
    }

    cout<< "_________________________________"<<endl;

    int accumulatedCredits=0;
    // temp course to add to selected vector
    Course temp;
    bool limitReached = false, classFound;
while(!limitReached){
        classFound = false;
        //selection = selected class
        string selection;
        getline(cin >> ws,selection);
        for(auto & course : availableCourses){
            //insert selected course into return vector
            if(course.id == selection && (course.credits + currentCredit) <= credits){
                selectedCourses.push_back(course);
                currentCredit += course.credits;
                classFound = true;
                break;
            }
            // credit limit reached
            else if(course.id == selection){
                cout << "Cannot add "<< course.id <<", will exceed "<< credits <<" credits"<<endl;
                cout<<endl;
                limitReached = true;
                classFound = true;
                break;
            }

        }
        //all possible classes selected
        if(availableCourses.size() == selectedCourses.size()){
            cout << endl;
            limitReached = true;
        }
        //invalid class selection
        else if(!classFound){
            cout << "Invalid Course, please try again"<<endl;
            classFound = false;
        }
        //semester credit limit reached
        if (currentCredit == credits) {
            break;
        }
    }

    return selectedCourses;

}


void runProgram(Graph& originalGraph){
    //Make a copy of original graph so that no info is lost 
    Graph graphCopy(originalGraph);

    // Keep a vector of vector of courses, keeping track of all selected in each semester
    std::vector<std::vector<Course>> finalCourseSchedule;
    std::vector<std::vector<Course>> optimizedCourseSchedule;

    // ask user to input Total number of credits
    int numSemesters,numCredits ,currentSemester = 1;
    string course;
    cout << "How many semesters do you wish to take: " << endl;
    cin >> numSemesters;
    cout << "How many credits each semester do you wish to take: " << endl;
    cin >>  numCredits;
    cout << endl;

    while(currentSemester <= numSemesters){
        //Get available courses and put them into the vector
        cout<< "Please select from the following list of courses for semester "<< currentSemester<<endl;

        std::vector<Course> availableCourses(graphCopy.getAvaliableCourses(originalGraph));
        std::vector<Course> selectedCourses(selectFromAvailableCourses(availableCourses, numCredits));

        if(selectedCourses.empty()){
            cout<<"No more available classes"<<endl;
        }
        // remove selected courses from graph
        for(auto & selectedCourses : selectedCourses ){
            graphCopy.removeCourse(selectedCourses.id);
        }

        // add current selection to model semester plan
        finalCourseSchedule.push_back(selectedCourses);
        currentSemester++;

    }

    // print semester model plan
    printSemesterPlan(finalCourseSchedule);


    // Now after we show the student the semester plan he has built:
    // We are actually going to further optimize the selected courses, and offer him a revised semster
    // plan, that just tries to minimize the number of semesters in total
    // we do that by simply running the TopSort() on the Courses contained in the FinalCourseSchedule vector
    // So for that we will need to:
    // first: Loop throguh vector and create a graph with only those courses
    // run top sort on that graph, and grab the resulting vector
    // just print the resulting vector and see if the student likes it.

    //new graph of only classes that were selected by user
    Graph optimizedSchedule;

    for(auto & courseVector: finalCourseSchedule){
        for(auto & course: courseVector){
            //convert int back to string
            stringstream s;
            s<<course.credits;
            string credits = s.str();
            optimizedSchedule.insertCourse(course.id, course.name, credits, course.preReqs);
        }
    }

    optimizedCourseSchedule = optimizedSchedule.topSort(numSemesters, numCredits);

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

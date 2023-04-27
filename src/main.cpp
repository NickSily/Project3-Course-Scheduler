#include <iomanip>
#include<string>
#include <iostream>
#include <vector>
#include<fstream>
#include<sstream>
#include "Graph.h"

using namespace std;

void readCSV(string filename, Graph& graph){
    // Open csv file
    std::ifstream inFile("inputFiles/" + filename);
    if(!inFile.is_open()){
        std::cout << "Error Opening file." << std::endl;
    }


    string line, id, name, credits, preReqList;

    unordered_set<std::string> preReqs;

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
            preReqList = preReqList.substr(1, preReqList.size() - 2);
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
        cout <<endl<< setw(12) << "Semester " << semester << "\n";
        cout << "----------------" << "\n";
        cout << "Course" << setw(10) << "Credits" << "\n";
        for (int i = 0; i < plan.size(); i++) {
            cout << plan[i].id << setw(8) << plan[i].credits << "\n";
        }
        semester++;
    }
}

std::vector<Course> selectFromAvailableCourses(std::vector<Course>& availableCourses, int credits){
    std::vector<Course> selectedCourses;
    int currentCredit = 0; int selectionNum;

    //print available courses
    int count = 1;
    for(auto & availableCourse : availableCourses){
        cout << count << ". " << availableCourse.id << ", " << availableCourse.name << "| Credits: "<< availableCourse.credits <<endl;
        count++;
    }
    cout<< "___________________________________________"<<endl;

    // While 
    // temp course to add to selected vector
    Course temp;
    bool limitReached = false, classFound;
    while(!limitReached){
        classFound = false;
        //selection = selected class
        string selection;
        getline(cin >> ws,selection);
        selectionNum = stoi(selection);

        for(int x =0; x<availableCourses.size(); x++){
            //insert selected course into return vector
            if(selectionNum == x && (availableCourses[selectionNum-1].credits + currentCredit) <= credits){
                selectedCourses.push_back(availableCourses[selectionNum-1]);
                currentCredit += availableCourses[selectionNum-1].credits;
                classFound = true;
                cout << availableCourses[selectionNum-1].id <<" has been added your total credit count is "<< currentCredit <<" credits."<<endl;

                break;
            }
                // credit limit reached
            else if(selectionNum == x){
                cout << "Cannot add "<< availableCourses[selectionNum-1].id <<", will exceed "<< credits <<" credits."<<endl;
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
            cout << "Invalid Course, please try again."<<endl;
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
    cout << "How many semesters do you wish to take: ";
    cin >> numSemesters;
    cout << "How many credits each semester do you wish to take: ";
    cin >>  numCredits;

    while(currentSemester <= numSemesters){
        //Get available courses and put them into the vector
        cout<<endl<< "Please select from the following list of courses for semester "<< currentSemester << ":" <<endl;

        std::vector<Course> availableCourses(graphCopy.getAvailableCourses(originalGraph));
        std::vector<Course> selectedCourses(selectFromAvailableCourses(availableCourses, numCredits));

        if(selectedCourses.empty()){
            cout<<"No more available classes."<<endl;
        }
        // remove selected courses from graph
        for(auto & selectedCourses : selectedCourses){
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

    std::cout << "\nHere is an optimized semester plan: \n";
    printSemesterPlan(optimizedCourseSchedule);
}



int main()
{
    Graph myGraph;

    // Read the Data and create a graph with it
    readCSV("CourseData.csv", myGraph);

    // runs the program
    runProgram(myGraph);

    return 0;
}
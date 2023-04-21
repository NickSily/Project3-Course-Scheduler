#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(std::unordered_map<std::string, Course> &adjList)
{
    this->adjList = adjList;
}

void Graph::insertCourse(std::string id, std::string name, std::string credits, std::vector<std::string> &preReqs)
{
    adjList[id] = Course(id, name, credits, preReqs);
}

void Graph::removeCourse(std::string id)
{
    /*FIX ME*/
    // Removes the course with corresponding id from the graph
    /*
    But remember, we must also loop thorugh the graph and
    remove any ocurrence of the guy beeing removed, from anyone's pre-reqs
    */
}

std::vector<std::vector<Course>> Graph::topSort()
{
    // Make a copy of Graph so as not to lose original data
    std::unordered_map<std::string, Course> tempAdjList = this->adjList;

    std::vector<std::vector<Course>> result;
    std::vector<Course> row;

    int maxLoops = tempAdjList.size();
    int numLoops = 0;
    while(!tempAdjList.empty()){
        if(numLoops > maxLoops){throw std::runtime_error("Cycle Detected in Graph");}

        // Push All preReqs = 0 into the row
//        std::cout << "List not empty" << std::endl;
        for(auto v = tempAdjList.begin(); v != tempAdjList.end(); v++){
//            std::cout << v->first << " preReqs: " << v->second.preReqs.size() << std::endl;
            // v->first = courseID | V->second = CourseObj
            // push original value (from adjList) to the vector
            if(v->second.preReqs.size() == 0){
//                std::cout << "Found " << v->first << "with indegree = 0" << std::endl;
//                std::cout << "Adding " << v->first << " to the row" << std::endl;
                row.push_back(adjList.at(v->first));
            }
        }
        // Update the Inlinks of Neighbours
        //For every element in the row
        for (auto i : row){
//            std::cout << std::endl;
//            std::cout << "===== Step 2 =========" << std::endl;
//            std::cout << "Checking all elements in row:" << std::endl;
//            std::cout << std::endl;

            // Check every vertex(v) to see if they have current row element(i) in their preReqs
            for(auto v = tempAdjList.begin(); v != tempAdjList.end(); v++){

                if (v->second.preReqs.find(i.id) != v->second.preReqs.end()){
                    // Found element in inlinks, so remove it
//                    std::cout << "Found " << v->second.name << "With " << i.id << "in indegree" << std::endl;
//                    std::cout << "Erasing " << i.id << "from " << v->second.name << "preReqs" << std::endl;
                    v->second.preReqs.erase(i.id);
                }
            }

//            std::cout << "Removing " << i.id << "from graph." << std::endl;
            // Remove i from the Graph
            tempAdjList.erase(i.id);
        }

//        std::cout << "Pushing row to vector " << std::endl;
        //Add row to vector
        result.push_back(row);
//        std::cout << "clearing row" << std::endl;
        row.clear();
        numLoops++;
    }

    return result;
}

std::vector<Course> Graph::getAvaliableCourses(Graph& ogGraph){
    /*
    FIX ME
    Get the available courses for the current semester, here's how:
    loop through the Graph:
        if course indegree is 0 (no preReqs):
           Add it to the vector
    return the vector
    */
   // 0 indegre -> 
    // push_back(ogGraph.getCourse(courseId))
   


    std::vector<Course> result;
    return result;
}

int Graph::getCredit(string course) {

    // Finds the Course in the map and returns it's number of credits
    for(auto v = adjList.begin(); v != adjList.end(); v++){
        if(v->second.id == course){
            return v->second.credits;
        }
    }
    return 0;
}

Course Graph::getCourse(string id){
    /*Find the Course in the graph, and return it*/
}
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
    //remove as preReq for any classes
    for(auto & course : adjList){
        if(!course.second.preReqs.empty()){
            for(auto & preReq: course.second.preReqs){
                if(preReq == id){
                    course.second.preReqs.erase(id);
                    break;
                }
            }
        }
    }
    adjList.erase(id);

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

    std::vector<Course> result;
    for (auto iter : adjList) {
        if (iter.second.preReqs.empty()) {
            result.push_back(ogGraph.getCourse(iter.first));
        }
    }
    return result;
}

Course Graph::getCourse(string id){
    /*Find the Course in the graph, and return it*/
    return adjList[id];
}
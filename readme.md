# Folders
##  bin
Machine Code files

## src
Source files ( .cpp and .h or .hpp)

## test-unit
Cache Test Module for testing. 

## Makefile
To run Program Type "make" in Linux terminal
To run test type "make test" in Terminal

# Graph Class
## Variables
The Graph class contains an Directed Acyclic Graph of Course Objects. Implemented as an adjacency list that maps the course ID to a course object.

Course Objects contain, a ID(string), Name(string), Credits(int) and PreRequisites (unordered set of courses).

## Methods
### Topological Sort
The topological sort method will go through the DAG and place all items into a 2d vector, where each row represents a subsequent semester and the courses contained in that row are able to be taken at that semester.

# Main
The main.cpp file contains a method for reading data from a CSV. The CSV will contain all course information obtained from UF's website.

During main's execution, the CSV file's courses are loaded into the map, then topological sort if performed to output a list of classes per semester that takes into account all pre-requisited.



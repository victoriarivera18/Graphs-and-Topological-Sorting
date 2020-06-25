// V. Rivera Casanova
// CSCE 221
// Leyk 199
# include <iostream>
# include <string>
# include <sstream>
# include <vector>
# include <list>
# include <queue>
# include <fstream>
using namespace std;

#include "graph.h"

// to be implemented

  // destructor
  Graph::~Graph() // constant O(1)
  {
    //deallocate memory for list<int>*
    adj_list.clear();
    adj_list.empty();
  }


  // build a graph
  void Graph::buildGraph(ifstream &input)  // O(V + E)
  {
    stringstream ss;
    string line;
    int vertex, edge;


    while(!input.eof()){ // O(V) where V is the number of vertices 
      getline(input, line);
      ss << line;
      ss >> vertex;
      Vertex first(vertex);
      node_list.push_back(first); // vertex
      
      list<int>* newListPtr = new list<int>();
      adj_list.push_back(newListPtr);  // pushing back address of newList

      ss >> edge;
      while (edge != -1){  // O(E), E is number of edges
        (*newListPtr).push_back(edge);
        ss >> edge;
      }
      ss.clear();
    }
  }


  // display the graph
  void Graph::displayGraph()  // O(V * E)
  {
    for(size_t i = 0; i < node_list.size(); i++){  // O(V)
      cout << node_list.at(i).label << ": ";
      list<int> myList = (*adj_list.at(i));

      list<int>::iterator it;
      for(it=myList.begin(); it!=myList.end(); ++it){  // O(E)
        cout << *it << " ";
      }
      cout << endl;
    }
  }


  // topological sort
  void Graph::topological_sort() // O(|V| + |E|)
  {
    queue <Vertex> q;  // stl queue
    int counter = 0;

    for(size_t i = 0; i < node_list.size(); i++){
      if(node_list.at(i).indegree == 0){
        q.push(node_list.at(i));  // enqueue
      }
    }

    while(!q.empty()){ 
      Vertex v = q.front(); // dequeue 
      q.pop(); // delete front
      v.top_num = ++counter; // Assign next number


      list<int> myList = (*adj_list.at(v.label - 1));  // problem
      list<int>::iterator it;
      for(it=myList.begin(); it!=myList.end(); ++it){  // O(E)
        //for each Vertex w adjacent to v 
          if(--node_list.at(*it -1).indegree == 0){
            q.push(node_list.at(*it -1)); // enqueue
          }
      }
      //cout << "Top num "<< v.top_num << " number "<< v.label << endl;
      node_list.at(v.label -1).top_num = v.top_num;  // assign correct top num 
    }

    if(counter != node_list.size()){  //excpetion handling 
      throw CycleFoundExcpetion("Cycle Found! Not DAG!");
    }

  }


  // find indegree
  void Graph::compute_indegree() // // O(V * E) (because nested for loop)
  {
    cout << "In-degree: "<< endl;
    for(size_t i = 0; i < node_list.size(); i++){  // set all indegrees to 0 initially
      node_list.at(i).indegree = 0;
    }

    for(size_t j = 0; j < node_list.size(); j++){  // for all vertices j 
      list<int> myList = (*adj_list.at(j));  // get that vertex's adjacency list
      list<int>::iterator it;  // iterator
      for(it=myList.begin(); it!=myList.end(); it++){  // for every vertex it adjacent to j
        node_list.at((*it)-1).indegree ++; // add 1 to indegree
      }
    }

    for(size_t k = 0; k < node_list.size(); k++){  // print indegrees
      cout << k + 1 << ": " << node_list.at(k).indegree << endl;
    }

  }


  // print topological sort
  void Graph::print_top_sort()  // O(V), where V is the numver of vertices
  {
    cout << "Topological Sort: ";
    int sizeList = 0;
    int index = 0;
    int current = 1;

    while(current <= node_list.size()){ // size of node_list
      if(node_list.at(index).top_num == current){
        cout << node_list.at(index).label << " ";
        current ++;
        index = 0;
      } else {
        index++;
      }
    }
    cout << endl;
  }
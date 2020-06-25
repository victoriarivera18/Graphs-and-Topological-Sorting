// main function

#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, const char * argv[])
{
  if ( argc != 2 ) {
    cout << "usage: " << argv[0] << " input filename\n";
    exit(1);
  }

  string input_name = argv[1];
  ifstream input(input_name);
  if (!input) {
    cout << "Wrong or nonexisting input file\n";
    exit(1);
  }
  
  Graph graph;
  graph.buildGraph(input);
  graph.displayGraph();
  cout << endl;
  graph.compute_indegree(); // Part 2
  cout << endl;
  graph.topological_sort(); // Part 2
  graph.print_top_sort();   // Part 2
  return 0;
}
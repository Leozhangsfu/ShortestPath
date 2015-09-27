//Authors: Leo Zhang, 301209995, zhzhang@sfu.ca , Yu Cao, 301266893, yca226@sfu.ca

#pragma once

 

#include <stdexcept>

#include <iostream>

#include<map>
#include<iterator>
#include <math.h>
#include <cmath>

using namespace std;

class Node
{
public:

	Node();// default constructor

	Node(int NodeNum, double xCord, double yCord, double Key, int ParentNum); // constructor for creating leaf node

	int NodeNumber; // value stored in the leaf node

	double KeyValue; // the key value stored in the node, which is the shortest distance from source + the estimate distance to destination

	int parentNode; // A is the parent node of B if there is an directed edge from A to B

	double xCordinate; // x cordinate of the node on the graph

	double yCordinate; // y cordinate of the node on the graph

	bool visited;

}; 

class Heap

{

public:

      Heap(void); // Default constructor


      Heap(int n); // Constructor (int)


      ~Heap(void); // Destructor

 

      // Inserts node into heap

      void insert(int nodeNum, double xCordin, double yCordin, double key, int parentNumber);

 

      // Removes and returns root of heap

      Node* remove();


	  double calculateDist(int startNode, int endNode); // return the straight line distance from startNode to endNode


      bool empty() {return size == 0;}; // Returns true iff heap is empty


	  void decreaseKey(int NodeNum, double newKey); //decreasekey method


	  double Dijkstra(int start, int end); // Dijkstra algorithm, start and end denote the node number of source and destination


	  map<int,int> VertexIndex; // stored the index of vertices in the priority queue


	  Node** arr; // array used for the heap


	  map<int,Node*> NodeInfo; // map storing the information of every node, including x and y coordinate


	  map<int, map<int, int> > adjList; // map used as adjacent list


	  double Astar(int start, int end);// A* algorithm


	  int visitedNode; // count the number of nodes visited by djkstra algorithm and A* algorithm

private:

	  map<int, int>::iterator it; // map iterator

	  map<int,int> VisitedNodes; // stores the node numbers of nodes being poped out from the priority queue

	  int visitedNodeAstar; // count the number of nodes visited by A* algorithm

      int max_size; // max_size of the heap array

      int size; // number of nodes being stored in the heap

	  double realDistance[1000]; // used to store the distance of each node

 

      // bubbleUp method, fixes partial ordering from i to root

      void bubbleUp(int i);

 

      // bubbleDown method, fixes partial ordering from i to leaf

      void bubbleDown(int i);

};
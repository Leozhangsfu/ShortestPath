//Authors: Leo Zhang, 301209995, zhzhang@sfu.ca , Yu Cao, 301266893, yca226@sfu.ca
#include "Heap.h"


#include <iomanip>

 

// Default constructor

// PRE:

// POST: creates and empty heap of size 1000

Heap::Heap(void)

{

      max_size = 1000;

      arr = new Node*[max_size];

      size = 0;

	  for (int i=0; i < 1000; i++)
		  realDistance[i] = 1000;

}

 

// Constructor (int)

// PRE:

// PARAM: n - size of the heap

// POST: creates and empty heap of size n

Heap::Heap(int n)

{

      max_size = n;

      arr = new Node*[max_size];

      size = 0;

}

 

// Destructor

// PRE:

// POST: de-allocates memory associtaed with arr

Heap::~Heap(void)

{

      delete[] arr;

}

 

// Inserts int into heap

// PRE: Underlying array is not full

// POST: inserts node with node number, x and y coordinate and distance into heap, maintaining the heap

void Heap::insert(int nodeNum, double xCordin, double yCordin, double key, int parentNumber)

{

      if(size == max_size){

            throw runtime_error("heap is full");

      }

      // Insert node newVertex

	  Node* newVertex = new Node(nodeNum, xCordin,yCordin,key,parentNumber);

      arr[size] = newVertex;

	  VertexIndex.insert(make_pair(nodeNum, size));

      bubbleUp(size++);

}

 

// Removes and returns root of heap

// PRE: arr is not empty

// POST: removes and returns root, maintaining the heap

//       properties - throws exception if heap is empty

Node* Heap::remove()

{

      if(size == 0){

            throw runtime_error("heap is empty");

      }

      Node* temp = arr[0];

      arr[0] = arr[--size];

      bubbleDown(0);   

      return temp;

}

 

// Fixes partial ordering from i to root

// PRE:

// PARAM: i is index to be bubbled up from

// POST: swaps i with parent if arr[i] < parent

void Heap::bubbleUp(int i)

{

      int parent = (i - 1)/2;

      // Check to see if partial ordering is violated

	  while(i > 0 && arr[parent]->KeyValue > arr[i]->KeyValue){

            // Swap

            Node* temp = arr[parent];

            arr[parent] = arr[i];

			it = VertexIndex.find(arr[parent]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = parent;
			}

            arr[i] = temp;


			it = VertexIndex.find(arr[i]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = i;
			}
            // Set index values

            i = parent;

            parent = (i - 1)/2;

      }

}


// Fixes partial ordering from i to leaf

// PRE:

// PARAM: i is index to be bubbled down from

// POST: swaps i with parent if arr[i] > larger child

void Heap::bubbleDown(int i)

{
	if(i >= size)
	{
		return;
	}

	Node* temp;
	int ch1 = 2 * i +1;
	int ch2 = 2 * i +2;

	if(ch1 <size && ch2 <size)
	{
		if(arr[ch1]->KeyValue < arr[i]->KeyValue && arr[ch1]->KeyValue < arr[ch2]->KeyValue)
		{
			temp = arr[i];
			arr[i] = arr[ch1];

			it = VertexIndex.find(arr[i]->NodeNumber);
			if (it != VertexIndex.end())
			{
				it->second = i;
			}

			arr[ch1] = temp;

			it = VertexIndex.find(arr[ch1]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = ch1;
			}

			i = ch1;
			bubbleDown(i);
		}

		else if(arr[ch2]->KeyValue < arr[i]->KeyValue)
		{
			temp = arr[i];
			arr[i] = arr[ch2];

			it = VertexIndex.find(arr[i]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = i;
			}

			arr[ch2] = temp;

			it = VertexIndex.find(arr[ch2]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = ch2;
			}

			i = ch2;
			bubbleDown(i);
		}
	}

	else if(ch1 <size)
	{
		if(arr[ch1]->KeyValue < arr[i]->KeyValue)
		{
			temp = arr[i];
			arr[i] = arr[ch1];

			it = VertexIndex.find(arr[i]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = i;
			}

			arr[ch1] = temp;

			it = VertexIndex.find(arr[ch1]->NodeNumber); 
			if (it != VertexIndex.end())
			{
				it->second = ch1;
			}

			i = ch1;
			bubbleDown(i);
		}
	}

      // Child nodes are 2 * i + 1 and 2 * i + 2

}


// Decrease key method

// PRE:

// PARAM: NodeNum: node number of the node decreaseKey will be performed on
//        newKey : the new key of the node

// POST: decrease the key of the node and maintain the heap
void Heap::decreaseKey(int NodeNum, double newKey)
{
	it = VertexIndex.find(NodeNum);

	if(it != VertexIndex.end())
	{
		arr[it->second]->KeyValue = newKey;
		bubbleUp(it->second);
	}
	else if(it == VertexIndex.end())
	{
		cout<<"it is not in the priority queue"<<endl;
	}
}


// Dijkstra algorithm

// PRE:

// PARAM: start: node number of the source
//        end : node number of the termination

// POST: computes the shortest path of start to end using dijkstra algorithm
double Heap:: Dijkstra(int start, int end)
{
	map<int,Node*>:: iterator it;

	map<int,map<int, int>>:: iterator intIt;

	map<int,int>:: iterator edges;

	Node* pop;

	Node* newNode;

	double distance;

	it = NodeInfo.find(start);

	pop = it->second;

	insert(pop->NodeNumber,pop->xCordinate,pop->yCordinate,0,pop->parentNode);

	visitedNode = 1;

	//cout<<"breakpoint 1"<<endl;

	while(!empty())
	{

		//cout<<"remaining size: "<<size<<endl;
		pop = remove();
		VertexIndex.erase(pop->NodeNumber);

		

		//cout<<"remaining size after remove: "<<size<<endl;
		//cout<<"visited node number: "<<pop->NodeNumber<<endl;

		if(pop->NodeNumber == end)
		{
			//erase vertexIndex and visited Node
			VertexIndex.clear();
			VisitedNodes.clear();
			distance = pop->KeyValue;
			delete pop;

			for(int i = 0; i< size; i++)
			{
				delete arr[i];
				arr[i] = NULL;
			}

			size = 0;

			//cout<<"visited: "<<visitedNode<<" nodes "<<endl;
			return distance;
		}

		intIt = adjList.find(pop->NodeNumber);

		if(intIt != adjList.end())
		{
			edges = intIt->second.begin();
		}

		while(intIt != adjList.end() && edges != intIt->second.end())
		{
		
			newNode = NodeInfo.find(edges->first)->second;
			
			distance = calculateDist(pop->NodeNumber,newNode->NodeNumber);

			//cout<<"Distance from Node "<< pop->NodeNumber<<" to Node "<< newNode->NodeNumber<<" is: "<<distance<<endl << setprecision(10);
			
			
			if(VisitedNodes.find(newNode->NodeNumber) == VisitedNodes.end() && VertexIndex.find(newNode->NodeNumber) == VertexIndex.end())
			{
				insert(newNode->NodeNumber,newNode->xCordinate,newNode->yCordinate,(pop->KeyValue + distance),pop->NodeNumber);
				visitedNode++;
			}

			else if(VisitedNodes.find(newNode->NodeNumber) == VisitedNodes.end() && VertexIndex.find(newNode->NodeNumber) != VertexIndex.end())
			{
				if(arr[VertexIndex.find(newNode->NodeNumber)->second]->KeyValue > pop->KeyValue + distance)
				{
					decreaseKey(newNode->NodeNumber,pop->KeyValue + distance);
				}
			}

			edges++;
		}

		VisitedNodes.insert(make_pair(pop->NodeNumber, pop->KeyValue));
		delete pop;
		//may be you can delete the node in the pointer right here to prevent memory leak;

	}// end of while priority queue is empty;


	VertexIndex.clear();
	VisitedNodes.clear();
	return 1000; // return 1000 if the endvertex is not found during the search
}

// calculate the straight line distance between startNode and endNote

// PRE:

// PARAM: startNode: node number of the source
//        endNode : node number of the termination

// POST: returns the straight line distance

double Heap::calculateDist(int startNode, int endNode)
{
	map<int,Node*>::iterator iter;

	iter = NodeInfo.find(startNode);

	double x1 = iter->second->xCordinate;

	double y1 = iter->second->yCordinate;

	iter = NodeInfo.find(endNode);

	double x2 = iter->second->xCordinate;

	double y2 = iter->second->yCordinate;

	double Dist = (sqrt(pow((x2-x1),2) + pow((y2-y1),2)));

	return Dist;

}

// A* algorithm

// PRE:

// PARAM: start: node number of the source
//        end : node number of the termination

// POST: computes the shortest path of start to end using A* algorithm
double Heap::Astar(int start, int end)
{

	map<int,Node*>:: iterator it;

	map<int,map<int, int>>:: iterator intIt;

	map<int,int>:: iterator edges;

	Node* pop;

	Node* newNode;

	double distance;
	double rem;

	it = NodeInfo.find(start);

	pop = it->second;

	realDistance[pop->NodeNumber - 1] = 0;

	insert(pop->NodeNumber,pop->xCordinate,pop->yCordinate,0,pop->parentNode);

	visitedNode = 1;

	while(!empty())
	{
		pop = remove();
		VertexIndex.erase(pop->NodeNumber);

		if(pop->NodeNumber == end)
		{
			//erase vertexIndex and visited Node
			VertexIndex.clear();
			VisitedNodes.clear();
			distance = realDistance[pop->NodeNumber - 1];
			delete pop;

			for(int i = 0; i< size; i++)
			{
				delete arr[i];
				arr[i] = NULL;
			}

			size = 0;
			return distance;
		}

		intIt = adjList.find(pop->NodeNumber);

		if(intIt != adjList.end())
		{
			edges = intIt->second.begin();
		}

		while(intIt != adjList.end() && edges != intIt->second.end())
		{
		
			newNode = NodeInfo.find(edges->first)->second;
			
			distance = calculateDist(pop->NodeNumber,newNode->NodeNumber);
			
			if(VisitedNodes.find(newNode->NodeNumber) == VisitedNodes.end() && VertexIndex.find(newNode->NodeNumber) == VertexIndex.end())
			{
				realDistance[newNode->NodeNumber - 1] = realDistance[pop->NodeNumber -1 ] + distance;
				rem = calculateDist(newNode->NodeNumber, end);
				insert(newNode->NodeNumber,newNode->xCordinate,newNode->yCordinate,(realDistance[newNode->NodeNumber - 1] + rem),pop->NodeNumber);
				visitedNode++;
			}

			else if(VisitedNodes.find(newNode->NodeNumber) == VisitedNodes.end() && VertexIndex.find(newNode->NodeNumber) != VertexIndex.end())
			{
				if(realDistance[newNode->NodeNumber - 1] > realDistance[pop->NodeNumber -1] + distance)
				{
					realDistance[newNode->NodeNumber - 1] = realDistance[pop->NodeNumber -1] + distance;
					rem = calculateDist(newNode->NodeNumber, end);
					decreaseKey(newNode->NodeNumber,realDistance[newNode->NodeNumber - 1] + rem);
				}
			}

			edges++;
		}

		VisitedNodes.insert(make_pair(pop->NodeNumber, pop->KeyValue));
		delete pop;

	}// end of while priority queue is empty;


	VertexIndex.clear();
	VisitedNodes.clear();
	return 1000; // return 1000 if the endvertex is not found during the search
}



Node:: Node() // default constructor
{
	 NodeNumber = 0; 

	 KeyValue = 1000; // treating 1000 as infinity

	 parentNode = 0; 

	 xCordinate = 0; 

	 yCordinate = 0;

	 visited = false;
}

Node:: Node(int NodeNum, double xCord, double yCord, double Key, int ParentNum) // constructor for creating leaf node
{
	 NodeNumber = NodeNum; 

	 KeyValue = Key; 

	 parentNode = ParentNum; 

	 xCordinate = xCord; 

	 yCordinate = yCord;

	 visited = false;


}


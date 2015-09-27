//Authors: Leo Zhang, 301209995, zhzhang@sfu.ca , Yu Cao, 301266893, yca226@sfu.ca


#include <iostream>
#include <map>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <iomanip>

#include "Heap.h"

 

using namespace std;

void heapTest();

 

 

int main()

{

      heapTest();

      return 0;

}

 

void heapTest()

{

      Heap hp;

	  string line;
	  Node* temp;
	  int i = 0;
	  double x, y;
	  
		
	  ifstream myfile ("graph1000.txt");
		
	  if (myfile.is_open()) {
		
		  while ( i < 1000 ) {
			  getline (myfile,line);
			  stringstream ss(line);

			  string a, b, c;
			  
			  ss >> i >> a >> b >> c;

			  x = stod(b);
			  y = stod(c);

			  temp = new Node(i,x,y,1000,0);
			
			  hp.NodeInfo.insert(make_pair(i,temp));

		  }

		  getline(myfile,line);
		  i = 0;

		  while (i < 1000) {
			  getline (myfile,line);
			  stringstream ss(line);

			  string a;
			  map<int,int> list1;

			  ss >> i;
			  ss >> a;

			  while (ss >> a) 
			  {
				  list1.insert(make_pair(stoi(a),1000));
			  }

			  hp.adjList.insert(make_pair(i,list1));
			  list1.clear();
		  }
    
		  myfile.close();
  
	  }

  
	  else {
		  cout << "Unable to open file";
		  return; 
	  }

 



      cout << endl;


	  int a, b;
	  double tmp;
	  int sum1 = 0, sum2 = 0;
	  srand(time(0));

	  ofstream outfile ("output.txt");
  
	  if (outfile.is_open())
	  {
    
		  for (int i=0; i < 20; i++) {
		  
			  a = rand() % 1000 + 1;
		  
			  b = rand() % 1000 + 1;

			  tmp = hp.Dijkstra(a,b);
			  cout << "Dijkstra distance from " << a << " to " << b << " is :"<< tmp <<endl << setprecision(10);
			  outfile << "Dijkstra distance from " << a << " to " << b << " is :"<< tmp <<endl << setprecision(10);
		
			  sum1 += hp.visitedNode;
		
			  cout << "Node visited : " << hp.visitedNode << endl << endl;
			  outfile << "Node visited : " << hp.visitedNode << endl << endl;
			
			  tmp = hp.Astar(a,b);
			  cout << "A* distance from " << a << " to " << b << " is :"<< tmp << endl << setprecision(10);
			  outfile << "A* distance from " << a << " to " << b << " is :"<< tmp << endl << setprecision(10);
		
			  sum2 += hp.visitedNode;
		
			  cout << "Node visited : " << hp.visitedNode << endl << endl << endl;
			  outfile << "Node visited : " << hp.visitedNode << endl << endl << endl;
		  }
	  
		  cout << "Dijkstra average node visisted : " << sum1/20 << endl << endl;
		  outfile << "Dijkstra average node visisted : " << sum1/20 << endl << endl;
	  
		  cout << "A* average node visisted : " << sum2/20 << endl << endl;
		  outfile << "A* average node visisted : " << sum2/20 << endl << endl;
	  
		  cout << "Average saving : " << (sum1 - sum2) / 20 << endl;
		  outfile << "Average saving : " << (sum1 - sum2) / 20 << endl;

		  outfile.close();
	  }
	  else cout << "Unable to open file";  
}
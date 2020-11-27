#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
public:
	Graph(int v);
	~Graph();

	void ReadMS(int**, int);
	void ReadMI(vector<vector<int>>&, int);
	void ReadSS(vector<list<int>>&, int);
	void PrintMS(int**, int);
	void PrintMI(vector<vector<int>>&, int);
	void PrintSS(vector<list<int>>&, int);
	void MStoSS(int**, vector<list<int>>&, int);
	void SStoMS(int**, vector<list<int>>&, int);
	void MItoSS(vector<vector<int>>&, vector<list<int>>&, int);
	void SStoMI(vector<vector<int>>&, vector<list<int>>&, int);

private:
	int vertices;
	int **MS;
	int edges;
	vector<vector<int>> MI;
	vector<list<int>> SS;
	vector<list<int>> SS1;
};

#endif

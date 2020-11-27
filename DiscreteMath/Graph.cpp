#include "Graph.h"

Graph::Graph(int v) {
	edges = 0;
	vertices = v;
	MS = new int*[vertices];
	MI.reserve(vertices * vertices);
	SS.reserve(vertices);
	SS1.reserve(vertices);
	for (int i = 0; i < vertices; i++) {
		MS[i] = new int[vertices];
	}
}

Graph::~Graph() {
	for (int i = 0; i < vertices; i++)
		delete[] MS[i];
	delete[] MS;
}

void Graph::ReadMS(int** MS, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Vertex " << i + 1 << ": ";
		for (int j = 0; j < size; j++) {
			cin >> MS[i][j];
		}
	}
}

void Graph::ReadMI(vector<vector<int>>&MI, int vertices) {
	char c = ',';
	int i = 0, val;
	cout << "After each line put ',', if it's end, put '.' " << endl;
	while (c == ',') {
		cout << "e" << i + 1 << ": ";
		for (int j = 0; j < vertices; j++) {
			cin >> val;
			MI[edges].push_back(val);
		}
		edges++;
		cin >> c;
		i++;
	}
}

void Graph::ReadSS(vector<list<int>>& SS, int vertices) {
	int val = 1;
	for (int i = 0; i < vertices; i++) {
		cout << "V" << i + 1 << " - ";
		while (val != 0) {
			cin >> val;
			SS[i].push_back(val);
		}
		val = 1;
	}
}

void Graph::MStoSS(int** MS, vector<list<int>>& SS, int vertices) {

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			if (MS[i][j] == 1)
				SS[i].push_back(j + 1);
}

void Graph::SStoMS(int** MS, vector<list<int>>& SS, int vertices) {
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			MS[i][j] = 0;
	for (int i = 0; i < vertices; i++) {
		for (list<int>::iterator it = SS[i].begin(); it != SS[i].end(); ++it) {
			if (*it != 0)
				MS[i][*it - 1] = 1;
		}
	}
}

void Graph::MItoSS(vector<vector<int>>&MI, vector<list<int>>& SS, int vertices) {
	int flag = 0;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < edges; j++) {
			if (MI[j][i] == -1) {
				for (int k = 0; k < vertices; k++) {
					if (MI[j][k] == 1) {
						SS[i].push_back(k + 1);
						k = vertices;
					}
				}
			}
			if (MI[j][i] == 2)
				SS[i].push_back(i + 1);
		}
	}
	for (int i = 0; i < vertices; i++) {
		SS[i].sort();
		SS[i].push_back(0);
	}
}

void Graph::SStoMI(vector<vector<int>>& MI, vector<list<int>>& SS, int vertices) {
	for (int i = 0; i < vertices * vertices; i++)
		MI[i].resize(vertices);
	int row = 0;
	for (int i = 0; i < vertices; i++) {
		list<int>::iterator it = SS[i].begin();
		while (*it != 0) {
			if (*it - 1 == i)
				MI[row][i] = 2;
			else {
				MI[row][i] = -1;
				MI[row][*it - 1] = 1;
			}
			row++;
			it++;
		}
	}
	edges = row;
}



void Graph::PrintMS(int** MS, int size) {
	for (int i = 0; i < size; i++) {
		cout << "V" << i + 1 << ": ";
		for (int j = 0; j < size; j++) {
			cout << MS[i][j] << ends;
		}
		cout << endl;
	}
}

void Graph::PrintMI(vector<vector<int>>& MI, int vertices) {

	for (int i = 0; i < edges; i++) {
		cout << "e" << i + 1 << ": ";
		for (int j = 0; j < vertices; j++) {
			cout << MI[i][j] << ends;
		}
		cout << endl;
	}
}

void Graph::PrintSS(vector<list<int>>& SS, int vertices) {
	for (int i = 0; i < vertices; i++) {
		cout << i + 1 << " - ";
		for (list<int>::iterator it = SS[i].begin(); it != SS[i].end(); ++it) {
			cout << *it << ends;
		}
		cout << endl;
	}
}

#include <iostream>
#include <list>
#include <vector>
#include "Graph.h"
using namespace std;

int edges = 0;

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

int main() {
	int vertices;
	cout << "Nember of vertices: ";
	cin >> vertices;



	int **MS = new int* [vertices];
	vector<vector<int>> MI(vertices * vertices);
	vector<list<int>> SS(vertices), SS1(vertices);
	for (int i = 0; i < vertices; i++) {
		MS[i] = new int[vertices];
	}

	//ReadMS(MS, vertices);
	//PrintMS(MS, vertices);
	//MStoSS(MS, SS1, vertices);
	
	//ReadMI(MI, vertices);
	//PrintMI(MI, vertices);
	//MItoSS(MI, SS, vertices);

	ReadSS(SS, vertices);
	PrintSS(SS, vertices);
	SStoMI(MI, SS, vertices);
	PrintMI(MI, vertices);
	//SStoMS(MS, SS, vertices);
	//PrintMS(MS, vertices);

	for (int i = 0; i < vertices; i++)
		delete[] MS[i];
	delete[] MS;

	system("pause");
	return 0;
}

void ReadMS(int** MS, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Vertex " << i + 1 << ": ";
		for (int j = 0; j < size; j++) {
			cin >> MS[i][j];
		}
	}
}

void ReadMI(vector<vector<int>>&MI, int vertices) {
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

void ReadSS(vector<list<int>>& SS, int vertices) {
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

void MStoSS(int** MS, vector<list<int>>& SS, int vertices) {

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			if (MS[i][j] == 1) 
				SS[i].push_back(j + 1);
}

void SStoMS(int** MS, vector<list<int>>& SS, int vertices) {
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

void MItoSS(vector<vector<int>>&MI, vector<list<int>>& SS, int vertices) {
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

void SStoMI(vector<vector<int>>& MI, vector<list<int>>& SS, int vertices) {
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



void PrintMS(int** MS, int size) {
	for (int i = 0; i < size; i++) {
		cout << "V" << i + 1 << ": ";
		for (int j = 0; j < size; j++) {
			cout << MS[i][j] << ends;
		}
		cout << endl;
	}
}

void PrintMI(vector<vector<int>>& MI, int vertices) {
	
	for (int i = 0; i < edges; i++) {
		cout << "e" << i + 1 << ": ";
		for (int j = 0; j < vertices; j++) {
			cout << MI[i][j] << ends;
		}
		cout << endl;
	}
}

void PrintSS(vector<list<int>>& SS, int vertices) {
	for (int i = 0; i < vertices; i++) {
		cout << i + 1 << " - ";
		for (list<int>::iterator it = SS[i].begin(); it != SS[i].end(); ++it) {
			cout << *it << ends;
		}
		cout << endl;
	}
}

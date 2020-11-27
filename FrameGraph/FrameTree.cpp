#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> *SS, *SS1;
vector <int> queue, queue1, marked;
int amOfV, amOfA, Vn;


void ReadSS() {
	int val = 1;
	for (int i = 1; i <= amOfV; i++) {
		cout << "V" << i << " - ";
		while (val != 0) {
			amOfA++;
			cin >> val;
			SS[i].push_back(val);
			SS1[i].push_back(val);
		}
		val = 1;
	}
}


int main(){
	cout << "Enter number of vertices: ";
	cin >> amOfV;

	SS = new vector <int>[amOfV + 1];
	SS1 = new vector <int>[amOfV + 1];
	marked.assign(amOfV + 1, 0);

	amOfA = 0;
	ReadSS();
	cout << "Start from: ";
	cin >> Vn;
	queue.push_back(Vn);
	marked[Vn] = 1;
	int i = 1;

	while (find(marked.begin() + 1, marked.end(), 0) != marked.end()) {
		for (int j = 0; j < SS[queue.front()].size() - 1; j++) {
			if (!marked[SS[queue.front()][j]]) {
				queue1.push_back(SS[queue.front()][j]);
				marked[SS[queue.front()][j]] = 1;
			}
		}
	}


	return 0;
}
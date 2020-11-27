#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Vn, Vk, V, i, j, k, last;
int inf = 2147483647;
vector <int> fMin[100] = {};
vector <int> fMax[100] = {};
vector <int> queue;
int H[100][100] = {};
int MS[100][100] = {};

void ReadMS() {
	for (i = 1; i <= V; i++) {
		cout << "Weights of arcs for vertex #" << i << ": ";
		for (j = 1; j <= V; j++) {
			cin >> MS[i][j];
		}
	}
}

void FordMin() {
	for (i = 1; i <= V; i++) {
		if (i != Vn)
			H[0][i] = inf;
		else
			H[0][i] = 0;
	}

	if (!queue.empty())
		queue.clear();

	queue.push_back(Vn);
	
	int prev, current;

	while (!queue.empty()) {
		prev = queue.front() - 1;
		current = queue.front();
		for (i = 1; i <= V; i++) {
			if (MS[current][i] != 0 && find(queue.begin(), queue.end(), i) == queue.end())
				queue.push_back(i);
		}
		for (j = 1;  j <= V; j++) {
			if (find(queue.begin(), queue.end(), j) != queue.end()) {
				if (MS[current][j] != 0) {
					if (H[prev][j] == inf) {
						H[current][j] = H[prev][current] + MS[current][j];
					}
					else if (H[prev][j] - H[prev][current] <= MS[current][j]) {
						H[current][j] = H[prev][j];
					}
					else {
						H[current][j] = H[prev][current] + MS[current][j];
					}
				}
				else {
					H[current][j] = H[prev][j];
				}
			}
			else
				H[current][j] = H[prev][j];
		}
		queue.erase(queue.begin());
		if (current == V)
			queue.clear();
	}
	current = last = 1;
	fMin[1].push_back(Vk);
	while (current <= last && fMin[last].back() != Vn) {
		queue.push_back(fMin[current].back());
		while (queue.back() != Vn)
		{
			k = 0;
			for (i = 1; i <= V; i++) {
				if (MS[i][queue.front()] != 0 && H[V][queue.front()] - H[V][i] == MS[i][queue.front()]) {
					if (!k) {
						queue.push_back(i);
						fMin[current].push_back(i);
						k = 1;
					}
					else {
						last++;
						fMin[last] = fMin[current];
						fMin[last].pop_back();
						fMin[last].push_back(i);
					}
				}
			}
			queue.erase(queue.begin());
		}
		queue.clear();
		current++;
	}
	i = 1;
	cout << "Final weights: ";
	for (j = 1; j <= V; j++)
		cout << H[V][j] << ends;
	cout << endl << "Min path = " << H[V][V];
	while (fMin[i].size() > 0) {
		cout << endl << "Path#" << i << ": ";
		for (j = fMin[i].size() - 1; j >= 0; j--)
			cout << fMin[i][j] << ends;
		i++;
	}

}

void FordMax() {
	for (i = 1; i <= V; i++) {
		if (i != Vn)
			H[0][i] = -inf;
		else
			H[0][i] = 0;
	}

	if (!queue.empty())
		queue.clear();

	queue.push_back(Vn);

	int prev, current;

	while (!queue.empty()) {
		prev = queue.front() - 1;
		current = queue.front();
		for (i = 1; i <= V; i++) {
			if (MS[current][i] != 0 && find(queue.begin(), queue.end(), i) == queue.end())
				queue.push_back(i);
		}
		for (j = 1; j <= V; j++) {
			if (find(queue.begin(), queue.end(), j) != queue.end()) {
				if (MS[current][j] != 0) {
					if (H[prev][j] == -inf) {
						H[current][j] = H[prev][current] + MS[current][j];
					}
					else if (H[prev][j] - H[prev][current] >= MS[current][j]) {
						H[current][j] = H[prev][j];
					}
					else {
						H[current][j] = H[prev][current] + MS[current][j];
					}
				}
				else {
					H[current][j] = H[prev][j];
				}
			}
			else
				H[current][j] = H[prev][j];
		}
		queue.erase(queue.begin());
		if (current == V)
			queue.clear();
	}

	current = last = 1;
	fMax[1].push_back(Vk);
	while (fMax[last].back() != Vn && current <= last) {
		queue.push_back(fMax[current].back());
		while (queue.front() != Vn) {
			k = 0;
			for (i = 1; i <= V; i++) {
				if (MS[i][queue.front()] && H[V][queue.front()] - H[V][i] == MS[i][queue.front()]) {
					if (!k) {
						queue.push_back(i);
						fMax[current].push_back(i);
						k = 1;
					}
					else {
						last++;
						fMax[last] = fMax[current];
						fMax[last].pop_back();
						fMax[last].push_back(i);
					}
				}
			}
			queue.erase(queue.begin());
		}
		queue.clear();
		current++;

	}

	i = 1;
	cout << "Final weights: ";
	for (j = 1; j <= V; j++)
		cout << H[V][j] << ends;
	cout << endl << "Max path = " << H[V][V];
	while (fMax[i].size() > 0) {
		cout << endl << "Path#" << i << ": ";
		for (j = fMax[i].size() - 1; j >= 0; j--)
			cout << fMax[i][j] << ends;
		i++;
	}

}

int main() {
	freopen("input1.txt", "r", stdin);
	cout << "Number of vertexes: ";
	cin >> V;
	cout << "Start from V# ";
	cin >> Vn;
	cout << "Finish at V#  ";
	cin >> Vk;
	ReadMS();
	cout << "Ford min: " << endl;
	FordMin();
	cout << "\nFord max: " << endl;
	FordMax();
	return 0;
}
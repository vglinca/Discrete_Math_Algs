#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

int Vn, Vk, V, i, j, k, current, previous, last;
int inf = 20000000;
vector <vector<int> > Vmin(100, vector<int>(100));
vector <vector<int> > Vmax(100, vector<int>(100));
vector<int> ansMinBK[100], ansMaxBK[100];
vector <int> minVec, maxVec, queue;
int H[100][100] = {};
int MS[100][100] = {};



void ReadMS() {
	for (i = 1; i <= V; i++) {
		cout << "Weights of arcs for vertex #" << i << ": ";
		for (j = 1; j <= V; j++) {
			cin >> MS[i][j];
		}
	}
	for (i = 1; i <= V; i++)
		for (j = 1; j <= V; j++) {
			if (i == j)
				MS[i][j] = 0;
			if (MS[i][j] == 0 && i != j)
				MS[i][j] = inf;
		}
}

void BKmin() {

	for (i = 1; i <= V; i++) {
		if (MS[i][Vk] && MS[i][Vk] != inf)
			Vmin[0][i] = MS[i][Vk];
		else if (i == Vk)
			Vmin[0][i] = 0;
		else
			Vmin[0][i] = inf;
	}

	previous = 0;
	k = current = 1;
	while (Vmin[previous] != Vmin[current]) {
		
		for (j = 1; j <= V; j++) {
			for (i = 1; i <= V && j != Vk; i++)
				if (i != j)
					minVec.push_back(MS[j][i] + Vmin[k - 1][i]);
			vector<int>::iterator min = min_element(minVec.begin(), minVec.end());
			if (j != Vk)
				Vmin[k][j] = *min;
			else
				Vmin[k][j] = 0;
			if (!minVec.empty())
				minVec.clear();
		}
		current = k;
		previous = current - 1;
		k++;
	}

	ansMinBK[1].push_back(Vn);
	current = last = 1;
	while (ansMinBK[last].back() != Vk && current <= last) {
		queue.push_back(ansMinBK[current].back());
		while (queue.front() != Vk) {
			k = 0;
			for (i = 1; i <= V; i++) {
				if (MS[queue.front()][i] != 0 && MS[queue.front()][i] != inf &&
					MS[queue.front()][i] == Vmin[previous][queue.front()] - Vmin[previous][i]) {
					if (!k) {
						ansMinBK[current].push_back(i);
						queue.push_back(i);
						k = 1;
					}
					else {
						last++;
						ansMinBK[last] = ansMinBK[current];
						ansMinBK[last].pop_back();
						ansMinBK[last].push_back(i);
					}
				}
			}
			queue.erase(queue.begin());
		}
		if (!queue.empty())
			queue.clear();
		current++;
	}

	i = 1;
	cout << "Lmin (V" << Vn << "-V" << Vk << ") = " << Vmin[previous][1] << endl;
	while (ansMinBK[i].size() > 0) {
		cout << endl << "Path #" << i << ": ";
		for (j = 0; j < ansMinBK[i].size(); j++)
			cout << ansMinBK[i][j] << ends;
		i++;
	}
	
}

void BKmax() {

	for (i = 1; i <= V; i++)
		for (j = 1; j <= V; j++)
			if (MS[i][j] == inf)
				MS[i][j] *= (-1);

	for (i = 1; i <= V; i++) {
		if (MS[i][Vk] && MS[i][Vk] != -inf)
			Vmax[0][i] = MS[i][Vk];
		else if (i == Vk)
			Vmax[0][i] = 0;
		else
			Vmax[0][i] = -inf;
	}

	previous = 0;
	k = current = 1;
	while (Vmax[previous] != Vmax[current]) {

		for (j = 1; j <= V; j++) {
			for (i = 1; i <= V && j != Vk; i++)
				if (i != j)
					maxVec.push_back(MS[j][i] + Vmax[k - 1][i]);
			vector<int>::iterator max = max_element(maxVec.begin(), maxVec.end());
			if (j != Vk)
				Vmax[k][j] = *max;
			else
				Vmax[k][j] = 0;
			if (!maxVec.empty())
				maxVec.clear();
		}
		current = k;
		previous = current - 1;
		k++;
	}

	ansMaxBK[1].push_back(Vn);
	current = last = 1;
	while (ansMaxBK[last].back() != Vk && current <= last) {
		queue.push_back(ansMaxBK[current].back());
		while (queue.front() != Vk) {
			k = 0;
			for (i = 1; i <= V; i++) {
				if (MS[queue.front()][i] != 0 && MS[queue.front()][i] != -inf &&
					MS[queue.front()][i] == Vmax[previous][queue.front()] - Vmax[previous][i]) {
					if (!k) {
						ansMaxBK[current].push_back(i);
						queue.push_back(i);
						k = 1;
					}
					else {
						last++;
						ansMaxBK[last] = ansMaxBK[current];
						ansMaxBK[last].pop_back();
						ansMaxBK[last].push_back(i);
					}
				}
			}
			queue.erase(queue.begin());
		}
		if (!queue.empty())
			queue.clear();
		current++;
	}

	i = 1;
	cout << "Lmax (V" << Vn << "-V" << Vk << ") = " << Vmax[previous][1] << endl;
	while (ansMaxBK[i].size() > 0) {
		cout << endl << "Path #" << i << ": ";
		for (j = 0; j < ansMaxBK[i].size(); j++)
			cout << ansMaxBK[i][j] << ends;
		i++;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	cout << "Amount of vertices: ";
	cin >> V;
	cout << "Start from: ";
	cin >> Vn;
	cout << "Finish at: ";
	cin >> Vk;
	ReadMS();
	cout << endl << "Bellman-Kalaba min path(s): " << endl;
	BKmin();
	cout << endl << "Bellman-Kalaba max path(s): " << endl;
	BKmax();
	system("pause");
	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int i, j, v, tmp, in, vertex;
	cout << "Number of vertices: ";
	cin >> v;
	vector <int> *SS, *SS1, stack, queue, visited, visited1;
	SS = new vector<int>[v];
	SS1 = new vector<int>[v];

	visited.assign(v + 1, 0);
	visited1.assign(v + 1, 0);

	cout << "Enter contiguity list: " << endl;
	for (int i = 0; i < v; i++) {
		cout << i + 1 << " - ";
		cin >> tmp;
		while (tmp) {
			SS[i].push_back(tmp);
			SS1[i].push_back(tmp);
			cin >> tmp;
		}
	}
	cout << "Start DFS from: " << endl << "1 - 1st vertex" << endl << "2 - Another vertex" << endl << "ans :";
	cin >> in;
	switch (in)
	{
	case 1:
		break;
	case 2:
		cout << "start from X vertex, X = ";
		cin >> vertex;
		stack.push_back(vertex);
		break;
	default:
		break;
	}
	
	cout <<endl << "DFS path: ";
	i = 0;
	while (i <= v) {
		if (stack.empty()) {
			for (j = 0; j < v; j++) {
				if (SS[j].size() > 0) {
					stack.push_back(j + 1);
					visited[j + 1] = 1;
					cout << j + 1 << ends;
					i++;
					break;
				}
			}
		}
		if (!SS[stack.back() - 1].empty()) {
			if (!visited[SS[stack.back() - 1].front()]) {
				stack.push_back(SS[stack.back() - 1].front());
				visited[stack.back()] = 1;
				cout << stack.back() << ends;
				i++;
			}
			else
				SS[stack.back() - 1].erase(SS[stack.back() - 1].begin());
		}
		else if (SS[stack.back() - 1].empty()) {
			if (!visited[stack.back()]) {
				visited[stack.back()] = 1;
				cout << stack.back() << ends;
				i++;
			}
			stack.pop_back();
		}
		if (stack.empty())
			break;
	}

	cout << endl<< "BFS path: ";
	for (i = 0; i < v; i++) {
		if (SS1[i].size() > 0) {
			queue.push_back(i + 1);
			visited1[i + 1] = 1;
			cout << i + 1 << ends;
			break;
		}
	}
	while (!queue.empty()) {
		while (!SS1[queue.front() - 1].empty()) {
			if (!visited1[SS1[queue.front() - 1].front()]) {
				queue.push_back(SS1[queue.front() - 1].front());
				visited1[SS1[queue.front() - 1].front()] = 1;
				cout << SS1[queue.front() - 1].front() << ends;
				SS1[queue.front() - 1].erase(SS1[queue.front() - 1].begin());
			}
			else
				SS1[queue.front() - 1].erase(SS1[queue.front() - 1].begin());
		}
		if (SS1[queue.front() - 1].empty()) {
			if (!visited1[queue.front()]) {
				visited1[queue.front()] = 1;
			}
			queue.erase(queue.begin());
		}
	}

	system("pause");
}
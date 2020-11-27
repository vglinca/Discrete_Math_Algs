#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, Vn, Vk, ans = 0;
int *visit;
int **Capacity, **currentCapacity;
vector <int> stack, queue, minVec, section;
vector < vector <int> > SS(100, vector <int>(1));
vector <int> ::iterator it;

void ReadSS(int vertices) {
	int tmpV, tmpW;
	for (int i = 1; i <= vertices; i++) {
		cout << "Enter vertex adjiacent to vertex " << i << ": ";
		cin >> tmpV;
		while (tmpV) {
			cout << "Enter arc's weight from vertex " << i << "To vertex " << tmpV << ": ";
			cin >> tmpW;
			Capacity[i][tmpV] = tmpW;
			SS[i].push_back(tmpV);
			cout << "Enter vertex adjiacent to vertex " << i << ": ";
			cin >> tmpV;
		}
	}
}

void maxFlow() {
	vector <int> I(V + 1);
	I.assign(V + 1, 1);

	cin >> Vn;
	cin >> Vk;

	stack.push_back(Vn);
	visit[Vn] = 1;
	int m = 0;
	int p = 0;
	while (!stack.empty()) { //finding all paths in right direction
		if (!stack.empty()) {
			while (stack.back() != Vk)
			{
				if (I[stack.back()] < SS[stack.back()].size()) {
					if (!visit[SS[stack.back()].at(I[stack.back()])] &&
					currentCapacity[stack.back()][SS[stack.back()].at(I[stack.back()])] < Capacity[stack.back()][SS[stack.back()].at(I[stack.back()])]) {

						I[stack.back()]++;
						stack.push_back(SS[stack.back()].at(I[stack.back()] - 1));
						visit[stack.back()] = 1;
					}
					else {
						I[stack.back()]++;
					}
				}
				else {
					visit[stack.back()] = 0;
					I[stack.back()] = 0;
					stack.pop_back();
					if (stack.empty())
						break;
				}
			}
			if (!stack.empty()) {
				for (int i = 0; i < stack.size() - 1; i++) {
					if (currentCapacity[stack[i]][stack[i + 1]] < Capacity[stack[i]][stack[i + 1]]) {//if arc isn't saturated
						minVec.push_back(Capacity[stack[i]][stack[i + 1]] - currentCapacity[stack[i]][stack[i + 1]]);
					}
				}

				if (minVec.size() == stack.size() - 1) {
					it = min_element(minVec.begin(), minVec.end());
					for (int j = 0; j < stack.size() - 1; j++) {
						if (currentCapacity[stack[j]][stack[j + 1]] < Capacity[stack[j]][stack[j + 1]]) {//if arc isn't saturated
							currentCapacity[stack[j]][stack[j + 1]] += *it;
						}
					}
					cout << "Path #" << ++p << ": ";
					for (int k = 0; k < stack.size(); k++) {
						cout << stack[k] << ends;
					}
					cout << endl;
				}

				minVec.clear();
				visit[stack.back()] = 0;
				I[stack.back()] = 0;
				stack.pop_back();
				int i;
				for (i = 0; i < stack.size() - 1; i++) {
					if (currentCapacity[stack[i]][stack[i + 1]] == Capacity[stack[i]][stack[i + 1]])
						break;
				}
				m = stack.size() - 1;
				while (m != i) {
					visit[stack.back()] = 0;
					I[stack.back()] = 0;
					stack.pop_back();
					m--;
				}
			}
		}
	}

	for (int i = 0; i <= V; i++)
		visit[i] = 0;

	I.assign(V + 1, 1);
	stack.push_back(Vn);
	visit[Vn] = 1;
	int flag = 0;

	while (!stack.empty()){
		if (!stack.empty()) {
			while (stack.back() != Vk) {
				if (I[stack.back()] < SS[stack.back()].size()) {
					flag = 0;
					if (!visit[SS[stack.back()].at(I[stack.back()])] &&
					currentCapacity[stack.back()][SS[stack.back()].at(I[stack.back()])] < Capacity[stack.back()][SS[stack.back()].at(I[stack.back()])]) {
						I[stack.back()]++;
						stack.push_back(SS[stack.back()].at(I[stack.back()] - 1));
						visit[stack.back()] = 1;
						flag = 1;
					}
					else {
						I[stack.back()]++;
					}
				}
				else {
					if (!flag) {
						flag = 1;
						for (int i = 1; i <= V; i++) {
							if (Capacity[i][stack.back()] && currentCapacity[i][stack.back()] > 0 && !visit[i]) {
								stack.push_back(i);
								visit[i] = -1;
								break;
							}
						}
					}
					else {
						if (visit[stack.back()] != -1)
							visit[stack.back()] = 0;
						I[stack.back()] = 0;
						stack.pop_back();
						flag = 0;
						if (stack.empty())
							break;
					}
				}
			}
			if (!stack.empty()) {
				for (int i = 0; i < stack.size() - 1; i++) {
					if (visit[stack[i + 1]] == 1) {//if we came to vertice in right direction
						if (currentCapacity[stack[i]][stack[i + 1]] < Capacity[stack[i]][stack[i + 1]]) {//if arc isn't saturated
							minVec.push_back(Capacity[stack[i]][stack[i + 1]] - currentCapacity[stack[i]][stack[i + 1]]);
						}
					}
					if (visit[stack[i + 1]] == -1) {
						if (currentCapacity[stack[i + 1]][stack[i]] > 0)
							minVec.push_back(currentCapacity[stack[i + 1]][stack[i]]);
					}
				}
				if (minVec.size() == stack.size() - 1) {
					it = min_element(minVec.begin(), minVec.end());
					for (int j = 0; j < stack.size() - 1; j++) {
						if (visit[stack[j + 1]] == 1) {//if arc isn't saturated
							currentCapacity[stack[j]][stack[j + 1]] += *it;
						}
						if (visit[stack[j + 1]] == -1) {
							currentCapacity[stack[j + 1]][stack[j]] -= *it;
						}
					}
					cout << "Path #" << ++p << ": ";
					for (int k = 0; k < stack.size(); k++) {
						cout << stack[k] << ends;
					}
					cout << endl;
					flag = 0;
					

				}
				minVec.clear();

				visit[stack.back()] = 0;
				I[stack.back()] = 0;
				stack.pop_back();
				int i;
				for (i = 0; i < stack.size() - 1; i++) {
					if (currentCapacity[stack[i]][stack[i + 1]] == Capacity[stack[i]][stack[i + 1]] && visit[i + 1] == 1)
						break;
				}
				m = stack.size() - 1;
				while (m != i) {
					visit[stack.back()] = 0;
					I[stack.back()] = 0;
					stack.pop_back();
					m--;
				}
			}
		}
	}

	for (int i = 0; i <= V; i++)
		visit[i] = 0;
	queue.push_back(Vn);
	visit[Vn] = 1;
	flag = 0;

	while (!queue.empty()) {
		flag = 0;
		for (int j = 1; j < SS[queue.front()].size(); j++) {
			if (currentCapacity[queue.front()][SS[queue.front()][j]] < Capacity[queue.front()][SS[queue.front()][j]]) {
				flag = 1;
				if (!visit[SS[queue.front()][j]]) {
					queue.push_back(SS[queue.front()][j]);
					visit[SS[queue.front()][j]] = 1;
				}
			}
			
		}
		for (int x = 1; x <= V; x++) {
			if (currentCapacity[x][queue.front()] && Capacity[x][queue.front()] > 0  &&
				Capacity[x][queue.front()] != currentCapacity[x][queue.front()] && !visit[x]) {
				queue.push_back(x);
				visit[x] = 1;
			}
		}

		queue.erase(queue.begin());
	}

	cout << endl << "A = {";
	for (int i = 1; i <= V; i++) {
		if (!visit[i]) {
			section.push_back(i);
			cout << i << ends;
		}
	}
	
	cout << "}" << endl << "w-(A) = {";
	for (int i = 1; i <= V; i++) {
		if (visit[i]) {
			for (int j = 1; j <= V; j++) {
				if (!visit[j]) {
					if (Capacity[i][j] && Capacity[i][j] == currentCapacity[i][j]) {
						cout << "(" << i << ", " << j << ") ";
						ans += Capacity[i][j];
					}
				}
			}
		}
	}
	cout << "}" << endl << "c(w-(A)) = " << ans << endl << "Max fx" << Vk << " = " << ans << endl;
}

int main() {
	freopen("input2.txt", "r", stdin);
	cout << "Number of vertices: ";
	cin >> V;
	visit = new int[V + 1];
	Capacity = new int* [V + 1];
	currentCapacity = new int* [V + 1];

	for (int i = 0; i <= V + 1; i++) {
		visit[i] = 0;
		Capacity[i] = new int[V + 1];
		currentCapacity[i] = new int[V + 1];
		for (int j = 0; j <= V + 1; j++)
			currentCapacity[i][j] = 0;
	}

	ReadSS(V);
	maxFlow();

	return 0;
}
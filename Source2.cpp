#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<iomanip>
using namespace std;

void menu() {
	cout << "Choose an action (number without .)" << endl;
	cout << "1. Input from terminal" << endl;
	cout << "2. Input from file" << endl;
	cout << "3. Graph representation" << endl;
	cout << "4. Node adding" << endl;
	cout << "5. Node removal" << endl;
	cout << "6. Vertice adding" << endl;
	cout << "7. Vertice removal" << endl;
	cout << "8. Graph deletion" << endl;
	cout << "9. Liking" << endl;
	cout << "10. The most likely path" << endl;
	cout << "11. Largest component" << endl;
	cout << "12. Influence" << endl;
	cout << "13. Exit" << endl;


};
int Index(string a, string* names, int num) {
	for (int i = 0; i < num; i++) {
		if (names[i] == a) {
			return i;
			cout << i << endl;
		}
	}
	return -1;
}
int loadnum(ifstream& file) {
	int num;
	string line;

	if (getline(file, line)) {
		stringstream ss(line);
		ss >> num;
		return num;
	}
	else {
		return -1;
	}

}
string* loadnames(ifstream& file, int num) {
	string* names = new string[21];
	string line;
	if (getline(file, line)) {
		istringstream ss(line);
		for (int i = 0; i < num; i++) {
			ss >> names[i];
		}
		return names;
	}
}
float** load(ifstream& file, int num, int e, string* names) {
	float** matrix = new float* [100];
	for (int i = 0; i < 100; i++) {
		matrix[i] = new float[100];
	}
	for (int i = 0;i < num;i++) {
		for (int j = 0;j < num;j++) {
			matrix[i][j] = 0.00;

		}
	}

	string a, b, line; float weight;
	for (int i = 0; i < e; i++) {
		getline(file, line);
		istringstream ss(line);
		ss >> a >> b >> weight;

		int from = Index(a, names, num);
		int to = Index(b, names, num);
		matrix[from][to] = weight;
	}
	return matrix;
	file.close();


}
float** verticeAdding(int& e, string* names, float**& matrix, int& num) {
	string line, a, b; float weight;
	for (int i = 0; i < e; i++) {
		cout << "Write in this format: Node a Node b weight" << endl;
		cin >> a >> b >> weight;
		int from = Index(a, names, num);
		int to = Index(b, names, num);
		if (matrix[from][to] == 0.00) {
			matrix[from][to] = weight;
		}
		else {
			cout << "Vertice exists." << endl;
		}
	}
	return matrix;

}
float** nodeAdding(int& num, string* names, float**& matrix) {
	float weight;
	string name, line, a, b;
	cout << "Write a name you want to add:" << endl;
	cin >> name;
	cin.ignore();
	names[num] = name;
	num++;
	float** newMatrix = new float* [num];
	for (int i = 0; i < num; i++) {
		newMatrix[i] = new float[num];
	}
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - 1; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < num; i++) {
		newMatrix[i][num - 1] = 0.00;
		newMatrix[num - 1][i] = 0.00;
	}
	cout << "Write number of vertices you want to add:" << endl;
	int ver;
	cin >> ver;
	cin.ignore();
	for (int i = 0; i < num - 1; ++i) {
		delete[] matrix[i];
	}
	matrix = verticeAdding(ver, names, newMatrix, num);
	return matrix;
}
float** nodeRemove(int& num, string* names, float**& matrix) {
	string name;
	cout << "Write name you want to remove?" << endl;
	cin >> name;
	cin.ignore();
	int j = Index(name, names, num);
	for (int i = j; i < num - 1; i++) {
		names[i] = names[i + 1];

	}
	float** newMatrix = new float* [num - 1];
	for (int i = 0; i < num - 1; i++) {
		newMatrix[i] = new float[num - 1];
	}
	int newRow = 0;
	for (int i = 0; i < num; i++) {
		if (i == j) continue;
		int newCol = 0;
		for (int k = 0; k < num; k++) {
			if (k == j) continue;
			newMatrix[newRow][newCol] = matrix[i][k];
			newCol++;
		}
		newRow++;
	}
	for (int i = 0; i < num; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	num--;
	matrix = newMatrix;
	cout << "Removed" << endl;
	return matrix;
}
float** verticeRemove(int& num, float**& matrix, string* names) {
	string a, b, line;
	cin.ignore();
	cout << "Write in this format: Node a Node b" << endl;
	getline(cin, line);
	istringstream s(line);
	s >> a >> b;
	int from = Index(a, names, num);
	int to = Index(b, names, num);
	matrix[from][to] = 0.00;

	cout << "Removed" << endl;
	return matrix;
}
void Delete(int num, float**& matrix, string* names) {
	if (matrix != nullptr) {
		for (int i = 0; i < num;i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
		delete[] names;
		names = nullptr;
	}

	cout << "Deleted" << endl;
}
void Liking(int num, string* names, float**& matrix) {
	string a, b;
	cout << "Write names under one another:" << endl;
	cin >> a;
	cin >> b;
	int from = Index(a, names, num);
	int to = Index(b, names, num);
	if (matrix[from][to] != 0.00) {
		matrix[from][to] += 0.1;
		cout << "Liked" << endl;
	}
	else {
		cout << "Cannot be liked" << endl;
	}

	cin.ignore();
}
float** transpose(float**& matrix, int& num) {
	float** mat1 = new float* [num];
	for (int i = 0; i < num; i++) {
		mat1[i] = new float[num];
		for (int j = 0; j < num; j++) {
			mat1[i][j] = matrix[j][i];
		}
	}
	return mat1;
}
void dfs2(int node, bool* visit, int* component, int& size, int& num, float**& trans) {
	int stack[1000];
	int top = -1;
	stack[++top] = node;
	visit[node] = true;
	component[size++] = node;
	while (top >= 0) {
		int curr = stack[top--];
		for (int neighbor = 0; neighbor < num; neighbor++) {
			if (trans[curr][neighbor] != 0.0 && !visit[neighbor]) {
				visit[neighbor] = true;
				component[size++] = neighbor;
				stack[++top] = neighbor;
			}
		}
	}
}
void dfs(int num, float**& matrix, int node, bool* visit, int* doneStack, int& donetop) {
	int stack[1000];
	int top = -1;
	int size = 0;
	stack[++top] = node;
	bool proc[1000] = { false };
	while (top >= 0) {
		int curr = stack[top];
		if (!visit[curr]) {
			visit[curr] = true;
		}

		bool flag = false;
		for (int neighbor = 0; neighbor < num; neighbor++) {
			if (matrix[curr][neighbor] != 0.00 && !visit[neighbor]) {
				stack[++top] = neighbor;
				flag = true;
				break;
			}
		}
		if (!flag) {
			if (!proc[curr]) {
				proc[curr] = true;
				doneStack[donetop++] = curr;
			}
			top--;
		}
	}
}
void largestComponent(int num, float**& matrix, string* names) {
	bool visit[1000] = { false };
	int doneStack[1000];
	int donetop = 0;
	int count = 0;
	string maxSize[1000];
	int max = 0;

	for (int i = 0; i < num; i++) {
		if (!visit[i]) {
			dfs(num, matrix, i, visit, doneStack, donetop);

		}
	}
	float** trans = transpose(matrix, num);
	for (int i = 0; i < num;i++) {
		visit[i] = false;
	}
	for (int i = donetop - 1; i >= 0;i--) {
		int node = doneStack[i];
		if (!visit[node]) {
			int component[1000];
			int size = 0;
			dfs2(node, visit, component, size, num, trans);

			if (size > max) {
				for (int j = 0; j < size; j++) {
					maxSize[j] = names[component[j]];
					max = size;
				}
			}
		}
	}
	if (max != 1) {
		for (int j = 0; j < max; j++) {
			cout << maxSize[j] << " ";
		}
	}
	else {
		cout << "No strongly connected nodes" << endl;
	}
	cout << endl;

	for (int i = 0; i < num; i++) {
		delete[] trans[i];
	}
	delete[] trans;
}


float** terminalInput(int& num, string* names, float**& matrix, int& e) {
	string nodes[100];
	cout << "Number of nodes:" << endl;
	while (!(cin >> num)) {
		cout << "MUST BE INTEGER, try again:" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	cout << "Number of vertices:" << endl;
	while (!(cin >> e)) {
		cout << "MUST BE INTEGER, try again:" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cout << "Names of nodes (write them under one another):" << endl;
	for (int i = 0; i < num; i++) {
		cin >> names[i];
	}
	cin.ignore();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			matrix[i][j] = 0.00;
		}
	}
	return matrix;
}
void Path(int num, string* names, float**& matrix) {
	string line, a, b;
	cin.ignore();
	cout << "Write the path you want:" << endl;
	getline(cin, line);
	istringstream s(line);
	s >> a >> b;
	int from = Index(a, names, num);
	int to = Index(b, names, num);

	float* d = new float[num];
	int* t = new int[num];
	int* path = new int[num];
	bool* visited = new bool[num];
	for (int i = 0; i < num; i++) {
		visited[i] = false;
	}
	visited[from] = true;
	int n = 0;
	path[n] = from;
	n++;
	for (int i = 0; i < num; i++) {
		d[i] = matrix[from][i];
		if (matrix[from][i] != 0.00) {
			t[i] = from;

		}
		else {
			t[i] = -1;
		}
	}
	d[from] = 1.0;
	int maxindex = 0;

	for (int k = 0; k < num; k++) {
		float max = 0.00;
		for (int i = 0; i < num; i++) {
			if (d[i] > max && !visited[i]) {
				max = d[i];
				maxindex = i;
			}
		}
		path[n] = maxindex;
		n++;
		visited[maxindex] = true;
		for (int j = 0;j < num;j++) {
			if (!visited[j]) {
				if (d[maxindex] * matrix[maxindex][j] > d[j]) {
					d[j] = d[maxindex] * matrix[maxindex][j];
					t[j] = maxindex;
				}
			}
		}

	}
	int* fullPath = new int[num];
	int current = to;
	int pathIndex = 0;

	while (current != from && current != -1) {
		fullPath[pathIndex++] = current;
		current = t[current];
	}
	if (current == -1) {
		cout << "Invalid path" << endl;
		delete[] d;
		delete[] t;
		delete[] visited;
		delete[] fullPath;
		return;
	}
	fullPath[pathIndex++] = from;


	for (int i = pathIndex - 1; i > 0; --i) {
		cout << names[fullPath[i]] << "-(" << matrix[fullPath[i]][fullPath[i - 1]] << ")";
		if (i != 0) {
			cout << " -> ";
		}
	}
	cout << names[fullPath[0]] << endl;

	delete[] d;
	delete[] t;
	delete[] visited;
	delete[] fullPath;

}
double dijkstra(int& num, float**& matrix, int node) {
	int size = 0;
	double best;
	double dist[1000];
	bool visit[1000];

	for (int i = 0; i < num; i++) {
		dist[i] = 0.00;
		visit[i] = false;
	}
	dist[node] = 1.00;
	for (int i = 0; i < num; i++) { //prolazim sve cvorove
		int n = -1;
		double max = 0.00;
		for (int neigbor = 0; neigbor < num; neigbor++) { //trazim komsiju kojeg nisam posetila sa najvecom vrv
			if (dist[neigbor] > max && !visit[neigbor]) {
				max = dist[neigbor];
				n = neigbor;
			}
		}
		if (n == -1) {
			break;
		}
		visit[n] = true;
		for (int j = 0; j < num; j++) { //trazim da li do j moze bolje preko n
			if (matrix[j][n] != 0.00 && !visit[j]) {
				double prob = dist[n] * matrix[j][n];
				if (prob > dist[j]) {
					dist[j] = prob;
				}
			}
		}
	}
	double sum = 1.0;
	for (int i = 0; i < num; i++) {
		if (i != node && dist[i] > 0.0) {
			sum *= dist[i];
			size++;
		}
	}

	if (size == 0 || size != num - 1) return 0.00;
	return sum / size;

}
void Influence(int& num, float**& matrix, string* names) {
	double size;
	float prob;
	double Sizes[1000];
	string SizesName[1000];
	double temp;
	string temps;
	for (int node = 0; node < num; node++) {
		size = dijkstra(num, matrix, node);
		Sizes[node] = size;
		SizesName[node] = names[node];
	}

	for (int i = 0; i < num - 1; i++) {
		for (int j = i + 1; j < num; j++) {
			if (Sizes[i] < Sizes[j]) {
				temp = Sizes[i];
				Sizes[i] = Sizes[j];
				Sizes[j] = temp;
				temps = SizesName[i];
				SizesName[i] = SizesName[j];
				SizesName[j] = temps;
			}
		}
	}
	int k;
	cout << "Enter k-th user:" << endl;
	cin >> k;
	if (Sizes[k - 1] == 0.00) {
		cout << "Doesnt have influence on every user." << endl;
		return;
	}
	cout << SizesName[k - 1] << endl;
}
void graphRepresentation(int& num, string* names, float**& matrix) {
	int maxNameLen = 0;
	for (int i = 0; i < num; i++) {
		if ((int)names[i].length() > maxNameLen)
			maxNameLen = names[i].length();
	}
	int width = maxNameLen + 1;
	if (matrix != nullptr) {
		cout << setw(width) << " ";

		for (int i = 0; i < num; i++) {
			cout << setw(width) << left << names[i];
		}
		cout << endl;


		for (int i = 0; i < num; i++) {
			cout << setw(width) << left << names[i];
			for (int j = 0; j < num; j++) {
				cout << setw(width) << left << matrix[i][j];
			}
			cout << endl;
		}
	}
	else {
		cout << "Deleted" << endl;
	}
}

int main() {
	int num = 0, e = 0;
	int choice;
	float** matrix = new float* [1000];
	for (int i = 0; i < 1000; i++) {
		matrix[i] = new float[1000];
	}
	string* names = new string[20];



	while (true) {
		menu();
		cin >> choice;

		switch (choice) {
		case 1: {
			terminalInput(num, names, matrix, e);
			verticeAdding(e, names, matrix, num);
			break;
		}
		case 2: {
			string txt;
			cout << "File name (including extension):" << endl;
			cin >> txt;
			cin.ignore();
			string line;

			ifstream file(txt);


			if (file) {
				num = loadnum(file);
				e = loadnum(file);
				names = loadnames(file, num);
				matrix = load(file, num, e, names);
			}
			else {
				cout << "No file found" << endl;
			}
			break;
		}
		case 3: {
			graphRepresentation(num, names, matrix);
			break;
		}
		case 4: {
			matrix = nodeAdding(num, names, matrix);
			break;
		}
		case 5: {
			matrix = nodeRemove(num, names, matrix);
			break;
		}
		case 6: {
			int t = 1;
			verticeAdding(t, names, matrix, num);
			break;
		}
		case 7: {
			verticeRemove(num, matrix, names);
			break;
		}
		case 8: {
			Delete(num, matrix, names);
			break;
		}
		case 9: {
			Liking(num, names, matrix);
			break;
		}
		case 10: {
			Path(num, names, matrix);
			break;
		}
		case 11: {
			largestComponent(num, matrix, names);
			break;
		}
		case 12: {
			Influence(num, matrix, names);
			break;
		}
		case 13: {
			exit(0);
		}
		}
	}
	return 0;
}
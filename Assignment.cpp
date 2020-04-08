#include<iostream>
#include <string>
#include<Queue>
#include <stack>
using namespace std;
struct Node {
	int state;
	int action;
	int cost;
	Node* parent;
	Node(int state, int action, int cost, Node* parent) {
		this->state = state;
		this->action = action;
		this->cost = cost + parent->cost;
		this->parent = parent;
	}
	Node() {
		state = -1;
		action = -1;
		cost = 0;
		parent = nullptr;
	}
};

string* arrStates;
string* arrActions;
int** TransitionMatrix;
int** arrTest;


bool goalTest(Node *start, int goal) {
	if (start->state == goal)
		return true;
	else
		return false;

}
bool child_goal = false;
bool parent_goal = false;
//function breathFirstSearch
Node *breathFirstSeach(string strt, string gol, int m, int n, int ** transitionModel, string *states) {
	int start = 0;
	int goal = 0;
	for (int i = 0; i < 8; i++)
	{
		if (states[i] == strt)
		{
			start = i;
		}
		if (states[i] == gol)
		{
			goal = i;
		}
	}
	Node* s = new Node;
	s->state = start;
	queue<Node*> frontial;
	//cout << s->state;
	Node* result = nullptr;
	Node* child = nullptr;
	bool* ArrCheck = new bool[m];
	for (int i = 0; i < m; i++) {
		ArrCheck[i] = 0;
	}
	frontial.push(s);
	ArrCheck[s->state] = 1;
	while (!frontial.empty()) {
		s = frontial.front();
		frontial.pop();
		parent_goal = goalTest(s, goal);
		if (parent_goal) {
			result = s;
			break;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (ArrCheck[transitionModel[s->state][i]] == 0) {
					child = new Node;
					ArrCheck[s->state] = 1;
					child->state = transitionModel[s->state][i];
					child->action = i;
					child->parent = s;
					child->cost = child->parent->cost + 1;
					child_goal = goalTest(child, goal);
					if (child_goal) {
						result = child;
						break;
					}
					frontial.push(child);
				}
			}
		}
		if (child_goal)
			break;
	}
	return result;
}
void findPath(Node* result, string*actions) {
	stack<int> store;

	if (child_goal) {
		while (result->parent != nullptr)
		{
			store.push(result->action);
			result = result->parent;
		}
		string final;
		while (!store.empty())
		{
			final += actions[store.top()];
			final += "->";
			store.pop();
		}
		final = final.substr(0, final.length() - 2);
		cout << final << endl;
		child_goal = false;
	}
	else if (parent_goal) {
		cout << "ROBOT IS IN ITS POSITION\n";
		parent_goal = false;
	}
	else
		cout << "NO SOLUTION EXISTS\n";
}
int main() {
	int m = 0;
	int n = 0;
	int t = 0;
	cout << "Enter Number of States : ";
	cin >> m;
	cout << "Enter Number of Actions : ";
	cin >> n;
	cout << "Enter Number of Test Cases : ";
	cin >> t;
	int ** graph = new int *[m];
	for (int i = 0; i < m; i++)
	{
		graph[i] = new int[n];
	}
	cout << "*******************************\n";
	cout << "Sample State space\n";
	cout << "\n  2 0 4 3 1 5 2 2 6 3 3 7 5 0 4  5 1 5 7 2 6 7 3 7\n";
	cout << "*******************************\n";
	cout << "Enter transition table\n";
	cout << "(You can copy paste the above state space)\n";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> graph[i][j];
			while (graph[i][j]<0 || graph[i][j]>m - 1)
			{
				cout << "Invalid input\n";
				cin >> graph[i][j];
			}
		}
	}
	cout << "Given state space is\n";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	string *states = new string[m];
	cout << "*******************************\n";
	cout << "Sample actions\n";
	cout << "a\nb\nc\nd\ne\nf\ng\nh\n";
	cout << "*******************************\n";
	cin.ignore();
	cout << "Enter states\n";
	cout << "(You can copy paste the above states)\n";
	for (int i = 0; i < m; i++)
	{
		getline(cin, states[i]);
	}
	cout << endl;
	cout << "States are\n";
	for (int i = 0; i < m; i++)
	{
		cout << states[i] << "  ";
	}
	cout << endl;
	string *actions = new string[n];
	cout << "*******************************\n";
	cout << "Sample Actions\n";
	cout << "Clean\nMove to Room 1\nMove to room 2\n";
	cout << "*******************************\n";
	cout << "\tEnter Actions\n";
	cout << "(You can copy paste the above acions)\n";
	for (int i = 0; i < n; i++)
	{
		getline(cin, actions[i]);
	}
	cout << endl;
	cout << "Actions are\n";
	for (int i = 0; i < n; i++)
	{
		cout << actions[i] << "  ";
	}
	cout << endl;

	Node* result = new Node;
	cin.ignore();
	string start;
	string goal;
	system("cls");
	for (int i = 0; i < m; i++)
	{

		cout << states[i] << "  |  ";
		for (int j = 0; j < n; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	cin.ignore();
	for (int i = 0; i < t; i++) {
		cout << "\tTEST CASE " << i << endl;
		cout << "Enter start state : ";
		cin >> start;

		cout << "Enter goal state : ";
		cin >> goal;
		cout << "*******************************\n";
		result = breathFirstSeach(start, goal, m, n, graph, states);
		findPath(result, actions);
		cout << "*******************************\n";
	}
	system("pause");
	return 0;
}
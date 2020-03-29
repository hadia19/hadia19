#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<typeinfo>
#include<stack>
using namespace std;

string actions[3] = { "Clean","MoveToRoom1","MoveToRoom2" };
int transitionModel[8][3];

class Node {
public:
	Node * parent;
	int state;
	int action;
	int cost;
	Node()
	{
	}
	void display()
	{
		cout << "Parent : " << parent << endl;
		cout << "State : " << state << endl;
		cout << "Action : " << action << endl;
		cout << "Cost : " << cost << endl;
		cout << "####################################\n";
	}
	bool goalTest(int a)
	{
		if (this->state == a)
		{
			return true;
		}
		return false;
	}
	/*bool operator< (const Node& other) const {
		return cost < other.cost;
	}*/
};
queue<Node>frontier;
set<int>exploredSet;
bool exp(int a)
{
	set<int>::iterator it;
	for (auto it = exploredSet.begin(); it != exploredSet.end(); it++)
	{
		if (*it == a)
		{
			return false;
		}
	}
	return true;
}
bool front(int a)
{
	return true;
}
Node search(string startState, string finalState,int ** transitionModel,string*states)
{
	bool array[8];
	for (int i = 0; i < 8; i++)
	{
		array[i] = false;
	}
	int goal = 0;
	Node n;
	for (int i = 0; i < 8; i++)
	{
		if (startState == states[i])
		{
			n.state = i;
			n.action = -1;
			n.cost = 0;
			n.parent = NULL;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (finalState == states[i])
		{
			goal = i;
		}
	}
	if (n.goalTest(goal))
	{
		return n;
	}
	else
	{
		frontier.push(n);
		array[n.state] = true;
	}
	Node child;
	do {
		exploredSet.insert(frontier.front().action);
		frontier.pop();
		for (int i = 0; i < 3; i++)
		{

			child.state = transitionModel[n.state][i];
			child.cost = n.cost + 1;
			child.action = i;
			child.parent = &n;
			if (child.goalTest(goal))
			{
				return child;
			}
			else
			{
				if (!array[child.state])
				{
					frontier.push(child);
					array[child.state] = true;
				}
			}
		}
		n = frontier.front();
	} while (!frontier.empty());
}
void display(string startState, string finalState, int ** transitionModel,string *states)
{
	Node result;
	result = search(startState, finalState,transitionModel,states);
	if (result.action == -1)
	{
		cout << "Robot is already in its Position\n";
	}
	else
	{
		set<int>::iterator it;
		for (auto it = exploredSet.begin(); it != exploredSet.end(); it++)
		{
			if ((*it == 0))
				cout << "Clean ->";
			if (*it == 1)
				cout << "Move to Room 1 ->";
			if (*it == 2)
				cout << "Move to Room 2 ->";
		}
		if (result.action == 0)
			cout << "Clean";
		if (result.action == 1)
			cout << "Move to Room 1";
		if (result.action == 2)
			cout << "Move to Room 2";
	}
	cout << endl;
}
int main()
{

	int M = 0;
	int N = 0;
	int T = 0;
	cout << "Enter M : ";
	cin >> M;
	cout << "Enter N : ";
	cin >> N;
	cout << "Enter T : ";
	cin >> T;
	int ** graph = new int *[M];
	
	for (int i = 0; i < M; i++)
	{
		graph[i] = new int[N];
	}
	cout << "\n  2 0 4 3 1 5 2 2 6 3 3 7 5 0 4  5 1 5 7 2 6 7 3 7\n";
	cout << "Enter transition table\n";
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//cout<<"enter value of "<<i<<" "<<j<<" : ";
			cin >> graph[i][j];
		}
	}
	cout << "Given state space is\n";
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	string *states = new string[M];
	cin.ignore();
	cout << "Enter states\n";
	for (int i = 0; i < M; i++)
	{
		getline(cin, states[i]);
	}
	cout << endl;
	cout << "States are\n";
	for (int i = 0; i < 8; i++)
	{
		cout << states[i] << "  ";
	}
	cout << endl;
			int test = 0;
			string startState;
			string finalState;
			//cin.ignore();
			cout << "Enter start state : ";
			getline(cin, startState);
			cout << "Enter final state : ";
			getline(cin, finalState);
			display(startState, finalState,graph,states);
	system("pause");
	return 0;
}
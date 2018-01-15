#include <iostream>
#include <limits.h>
#include <vector>

#define INF INT_MAX
using namespace std;

class Router
{
  public:
	vector<int> distance;
	vector<int> next;

	Router(int n)
	{
		distance = vector<int>(n, INF);
		next = vector<int>(n, 0);
	}
};

vector<Router> *DistanceVector(vector<vector<int>> adj, int n)
{
	auto routers = new vector<Router>(n, Router(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			routers->at(i).distance.at(j) = adj.at(i).at(j);
			routers->at(i).next.at(j) = j;
		}
	int count;
	do
	{
		count = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k)
					if (routers->at(k).distance.at(j) != INF &&
						adj.at(i).at(k) != INF &&
						routers->at(i).distance.at(j) > adj.at(i).at(k) + routers->at(k).distance.at(j))
					{
						routers->at(i).distance.at(j) = adj.at(i).at(k) + routers->at(k).distance.at(j);
						routers->at(i).next.at(j) = k;
						count++;
					}
	} while (count != 0);
	return routers;
}
vector<vector<int>> *getArray(int m, int n)
{
	auto tmp = new vector<vector<int>>();
	for (int i = 0; i < m; ++i)
		tmp->push_back(vector<int>(n, INF));
	return tmp;
}

int main()
{
	int n, e;
	cout << "NOTE: Use zero based node numbering.\n";

	cout << "Enter the number of nodes: ";
	cin >> n;

	cout << "Enter the number of edges: ";
	cin >> e;

	auto adj = *(getArray(n, n));

	cout << "Enter (p, q, d) where distance from p to q is d\n";
	for (int i = 0; i < e; ++i)
	{
		int f, t, d;
		cin >> f >> t >> d;
		adj.at(f).at(t) = d;
		adj.at(t).at(f) = d;
	}

	for (int i = 0; i < n; ++i)
		adj.at(i).at(i) = 0;

	auto routers = *(DistanceVector(adj, n));

	for (int i = 0; i < n; ++i)
	{
		auto r = routers.at(i);
		cout << "Table for Router " << i << ":\n";
		cout << "Dest.\tNext\tDist.\n";
		for (int j = 0; j < n; ++j)
			cout << (char)(j + 65) << '\t' << (char)(r.next.at(j) + 65) << '\t' << r.distance.at(j) << endl;
	}
}

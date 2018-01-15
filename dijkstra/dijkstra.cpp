#include <iostream>
#include <vector>
#include <limits.h>

#define INF INT_MAX
using namespace std;

vector<vector<int>> * getArray(int m, int n)
{
	auto tmp = new vector<vector<int>>();
	for(int i=0;i<m; ++i)
		tmp->push_back(*(new vector<int>(n, INF)));
	return tmp;
	cout << "done";
}
vector<int> * dijkstra(vector<vector<int>> adj, int n, int source)
{
	auto visited = new vector<bool>(n, false);
	auto dist = new vector<int>(n, INF);

	dist->at(source) = 0;

	for(int t = 0; t < n - 1; ++t)
	{
		//Choose node with minimum 'dist' which has not been visited.
		int min = INF, minAt = 0;
		for(int i=0; i<n;++i)
		{
			if(!visited->at(i) && dist->at(i) < min)
			{ min = dist->at(i); minAt = i; }
		}

		visited->at(minAt) = true;	
		//Update 'dist' array values.
		for(int i=0;i<n;++i)
		{
			if(!visited->at(i) &&
				adj.at(minAt).at(i) != INF &&
				dist->at(i) > dist->at(minAt) + adj.at(i).at(minAt))
				dist->at(i) = dist->at(minAt) + adj.at(i).at(minAt);
		}
	}

	delete visited;
	return dist;
}
int main()
{
	cout << "Use zero based notation for nodes (0 to n-1 nodes).\n" ;

	int n, e;
	cout << "Enter the number of nodes in the graph: ";
	cin >> n;

	auto adj = *(getArray(n, n));

	cout << "Enter the number of edges: ";
	cin >> e;
	for(int i=0;i<e;++i)
	{
		int f, t, d;
		cout << "Enter (p, q, d): Distance from node p to q: ";
		cin >> f >> t >> d;
		adj.at(f).at(t) = d;
		adj.at(t).at(f) = d;
	}

	cout << "Enter the source node: ";
	int s;
	cin >> s;

	auto dist = *(dijkstra(adj, n, s));

	cout << "Distance to all nodes from node " << s << ":\n";
	for(int i=0;i<n; ++i)
		cout << s << " --> " << i << " = " << dist.at(i) << endl;
}

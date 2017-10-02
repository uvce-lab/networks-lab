#include <iostream>
#include <limits.h>
#include <stdlib.h>

using namespace std;

#define INF (INT_MAX)

class Dijkstra
{
	int **adjacencyMatrix, n;

  public:
	Dijkstra(int **adj, int n)
	{
		this->adjacencyMatrix = adj;
		this->n = n;
	}

	//adjacencyMatrix: The adjacency matrix
	//n: Number of nodes in the graph
	//source: The source node (Zero based indexing)
	int *dijkstra(int source)
	{
		int min, minAt;

		//Set to keep track of selected nodes in the Minimal Spannnf Tree
		bool *sptSet = new bool[n];
		for (int i = 0; i < n; ++i)
			sptSet[i] = false;

		//Array to help select the next node and which will hold the minimum distances
		int *d = new int[n];
		for (int i = 0; i < n; ++i)
			d[i] = INF;

		//So that source node is selected first
		d[source] = 0;

		for (int i = 0; i < n - 1; ++i)
		{
			//Pick vertex with minimum key and which has not been visited
			min = INF;
			for (int i = 0; i < n; i++)
			{
				if (sptSet[i] == false && d[i] < min)
				{
					min = d[i];
					minAt = i;
				}
			}
			//min contains the node be to selected for insertion in MST
			sptSet[minAt] = true;

			//Update the key values to the weight of the selected node to its adjacent node if it is less.
			for (int i = 0; i < n; ++i)
			{
				if (!sptSet[i]
					&& (adjacencyMatrix[minAt][i] != INF)
					&& (d[i] > d[minAt] + adjacencyMatrix[minAt][i]))
				{
					d[i] = d[minAt] + adjacencyMatrix[minAt][i];
				}
			}
		}
		delete sptSet;
		return d;
	}
};

class Utilities
{
	static int **createArray2D(int row, int col, int init = 0)
	{
		int i, j;
		int **arr = new int *[row];
		for (i = 0; i < row; ++i)
			arr[i] = new int[col];

		for (i = 0; i < row; ++i)
		{
			for (j = 0; j < col; ++j)
			{
				arr[i][j] = init;
			}
		}
		return arr;
	}

  public:
	static void demo()
	{
		int n, i, edges, from, to, source, dist;

		cout << "\nEnter number of nodes in the graph: ";
		cin >> n;
		int **graph = createArray2D(n, n, INF);

		cout << "\nEnter the number of edges: ";
		cin >> edges;
		cout << "Enter edges (from - to - distance):\n";
		for (i = 0; i < edges; ++i)
		{
			cin >> from >> to >> dist;
			graph[from][to] = graph[to][from] = dist;
		}

		cout << "Enter the source node (Zero based indexing): ";
		cin >> source;

		Dijkstra *d = new Dijkstra(graph, n);
		int *minDist = d->dijkstra(source);

		cout << "The distance to all the notes from " << source << endl;
		for (i = 0; i < n; ++i)
		{
			cout << source << " - " << i << '\t' << minDist[i] << endl;
		}
	}
};

int main()
{
	Utilities::demo();
}

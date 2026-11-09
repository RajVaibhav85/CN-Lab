
#include <iostream>
using namespace std;

#define MAX 10
#define INF 999

int cost[MAX][MAX];
int dist[MAX];
int visited[MAX];
int nextHop[MAX];

int n;

// Dijkstra Algorithm
void dijkstra(int src)
{
    // Initialize
    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[src][i];
        visited[i] = 0;

        if (cost[src][i] != INF && i != src)
            nextHop[i] = i;
        else
            nextHop[i] = -1;
    }

    dist[src] = 0;
    nextHop[src] = src;

    // Find shortest paths
    for (int count = 0; count < n; count++)
    {
        int min = INF;
        int u = -1;

        // Find nearest unvisited router
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        // Update neighboring routers
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                cost[u][v] != INF &&
                dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];

                if (u == src)
                    nextHop[v] = v;
                else
                    nextHop[v] = nextHop[u];
            }
        }
    }
}

// Display routing tables
void display()
{
    for (int i = 0; i < n; i++)
    {
        dijkstra(i);

        cout << "\nRouter " << char('A' + i) << endl;

        cout << "Destination\tCost\tNext Hop\n";

        for (int j = 0; j < n; j++)
        {
            cout << char('A' + j) << "\t\t";

            if (dist[j] == INF)
                cout << "INF\t";
            else
                cout << dist[j] << "\t";

            if (nextHop[j] == -1)
                cout << "-";
            else
                cout << char('A' + nextHop[j]);

            cout << endl;
        }
    }
}

int main()
{
    cout << "Enter number of routers: ";
    cin >> n;

    cout << "Enter adjacency matrix (0 = no link):\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;

            if (i == j)
                cost[i][j] = 0;
            else if (x == 0)
                cost[i][j] = INF;
            else
                cost[i][j] = x;
        }
    }

    cout << "\nInitial Routing Tables:\n";

    display();

    // Change network topology
    int u, v, newCost;

    cout << "\nEnter routers to modify (0 to "
         << n - 1 << "): ";
    cin >> u >> v;

    cout << "Enter new link cost (0 to remove link): ";
    cin >> newCost;

    if (newCost == 0)
        cost[u][v] = cost[v][u] = INF;
    else
        cost[u][v] = cost[v][u] = newCost;

    cout << "\nUpdated Routing Tables:\n";

    display();

    return 0;
}

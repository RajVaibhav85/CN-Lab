
#include <iostream>
using namespace std;

#define MAX 10
#define INF 999

int cost[MAX][MAX];
int dist[MAX][MAX];
int nextHop[MAX][MAX];

int n;

// Distance Vector Algorithm
void distanceVector()
{
    // Initialize routing tables
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = cost[i][j];

            if (i == j)
                nextHop[i][j] = i;
            else if (cost[i][j] != INF)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }

    // Update distance vectors
    bool changed = true;

    while (changed)
    {
        changed = false;

        int oldDist[MAX][MAX];

        // Save previous distance vectors
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                oldDist[i][j] = dist[i][j];

        // Check all possible neighbors
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (cost[i][k] != INF &&
                        oldDist[k][j] != INF)
                    {
                        int newCost =
                            cost[i][k] + oldDist[k][j];

                        if (newCost < dist[i][j])
                        {
                            dist[i][j] = newCost;
                            nextHop[i][j] = k;
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

// Display routing tables
void display()
{
    for (int i = 0; i < n; i++)
    {
        cout << "\nRouter " << char('A' + i) << endl;

        cout << "Destination\tCost\tNext Hop\n";

        for (int j = 0; j < n; j++)
        {
            cout << char('A' + j) << "\t\t";

            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";

            if (nextHop[i][j] == -1)
                cout << "-";
            else
                cout << char('A' + nextHop[i][j]);

            cout << endl;
        }
    }
}


int main()
{
    // cout << "Enter number of routers: ";
    // cin >> n;

    // cout << "Enter adjacency matrix (0 = no link):\n";


    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         int x;
    //         cin >> x;

    //         if (i == j)
    //             cost[i][j] = 0;
    //         else if (x == 0)
    //             cost[i][j] = INF;
    //         else
    //             cost[i][j] = x;
    //     }
    // }

    n = 4;
    int matrix[4][4] = {{0, 1, 4, INF},
                      {1, 0, 2, 6},
                      {4, 2, 0, 3},
                      {INF, 6, 3, 0}};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = matrix[i][j];


    cout << "\nInitial Routing Tables:\n";

    distanceVector();
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

    distanceVector();
    display();

    return 0;
}

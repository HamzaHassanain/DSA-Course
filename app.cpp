#include <iostream>
#include <algorithm>
#include "MinHeap.h"
#include "LinkedList.h"

using namespace std;

class Graph
{

public:
    int numVertices;
    LinkedList<int> adjList[1000];

    Graph(int numVertices)
    {
        this->numVertices = numVertices;
    }

    void addEdge(int a, int b)
    {
        adjList[a].push_back(b);
    }

    void printGraph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " --> ";
            for (int j = 0; j < adjList[i].getSize(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }

    LinkedList<int> shortestPath(int src, int dir)
    {
        src++, dir++;

        int n = numVertices;

        LinkedList<pair<int, int>> adj[n + 1];
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < adjList[i].getSize(); j++)
            {
                adj[i + 1].push_back({adjList[i][j] + 1, 1});
                adj[adjList[i][j] + 1].push_back({i + 1, 1});
            }
        }

        MinHeap<pair<int, int>> pq;

        int dist[n + 1];
        int parent[n + 1];
        for (int i = 1; i <= n; i++)
            dist[i] = 1e9;
        for (int i = 1; i <= n; i++)
            parent[i] = -1;
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        dist[src] = 0;

        pq.insert({0, src});

        while (!pq.isEmpty())
        {
            auto it = pq.getMin();
            pq.remove();

            int node = it.second;
            int dis = it.first;

            for (int i = 0; i < adj[node].getSize(); i++)
            {
                int adjNode = adj[node][i].first;
                int edW = adj[node][i].second;

                if (dis + edW < dist[adjNode])
                {
                    dist[adjNode] = dis + edW;
                    pq.insert({dis + edW, adjNode});

                    parent[adjNode] = node;
                }
            }
        }

        if (dist[dir] == 1e9)
        {
            cout << "No path exists" << endl;
            return {};
        }

        LinkedList<int> path;
        int node = dir;

        while (parent[node] != node)
        {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(src);

        path.reverse();
        return path;

        return {};
    }
};

class Application
{
    string airbase[1000];
    pair<string, string> flights[1000];
    int airbasesNumber;
    int availableFlightsNumber;
    bool isTwoWay;
    Graph *graph;

public:
    Application() {}
    void run()
    {
        read_input();
    }
    string get_shortest_path(string src, string dest)
    {
        if (!is_valid_airbase_name(src, 1) || !is_valid_airbase_name(dest, 1))
        {
            cout << "Invalid Airbase name" << endl;
            exit(1);
        }
        int srcIndex = get_airbase_index(src);
        int destIndex = get_airbase_index(dest);

        auto path = graph->shortestPath(srcIndex, destIndex);
        if (path.getSize() == 0)
            return "";

        string result = "";
        for (int i = 0; i < path.getSize(); i++)
        {
            result += airbase[path[i] - 1];
            if (i != path.getSize() - 1)
                result += " -> ";
        }
        return result;
    }

private:
    bool is_valid_airbase_name(string name, bool isFlight = false)
    {
        if (name.length() != 3)
        {
            cout << "Invalid name. Name should be of length 3" << endl;
            return false;
        }
        for (int i = 0; i < name.length(); i++)
        {
            if ('A' <= name[i] && name[i] <= 'Z')
                continue;
            else
            {
                cout << "Invalid name. Name should contain only uppercase alphabets" << endl;
                return false;
            }
        }
        int equaltCount = 0;
        if (not isFlight)
            for (int i = 0; i < airbasesNumber; i++)
            {
                if (airbase[i] == name)
                    equaltCount++;
                if (equaltCount > 1)
                {
                    cout << "Invalid name. Name should be unique" << endl;
                    return false;
                }
            }
        return true;
    }

    void read_input()
    {
        read_airbases();
        read_flights();
    }

    void read_airbases()
    {
        cout << "Enter the number of Air bases: ";
        cin >> airbasesNumber;

        graph = new Graph(airbasesNumber);

        for (int i = 0; i < airbasesNumber; i++)
        {
            bool valid = 0;
            while (!valid)
            {

                cout << "Enter the name of Air base " << i + 1 << ": ";
                cin >> airbase[i];

                valid = is_valid_airbase_name(airbase[i]);
            }
        }
    }

    void read_flights()
    {
        cout << "Is the flight two way? (y/n): ";
        char ch;
        cin >> ch;
        isTwoWay = (ch == 'y');

        cout << "Enter the number of available flights: ";
        cin >> availableFlightsNumber;

        for (int i = 0; i < availableFlightsNumber; i++)
        {
            bool valid = 0;
            while (!valid)
            {
                cout << "Enter the source and destination of flight " << i + 1 << ": ";
                cin >> flights[i].first >> flights[i].second;

                valid = is_valid_airbase_name(flights[i].first, 1) && is_valid_airbase_name(flights[i].second, 1);
            }
        }

        inialize_graph();
    }

    int get_airbase_index(string name)
    {
        for (int i = 0; i < airbasesNumber; i++)
        {
            if (airbase[i] == name)
                return i;
        }
        cout << "Invalid Airbase name" << endl;
        exit(1);
        return -1;
    }

    void inialize_graph()
    {
        for (int i = 0; i < availableFlightsNumber; i++)
        {
            int src = get_airbase_index(flights[i].first);
            int dest = get_airbase_index(flights[i].second);

            graph->addEdge(src, dest);

            if (isTwoWay)
                graph->addEdge(dest, src);
        }
    }
};
int main()
{
    cout << "Welcome to Shortest Path Finder System" << endl;
    bool userWantsToContinue = true;
    while (userWantsToContinue)
    {
        Application app;
        app.run();

        string src, dest;
        cout << "Enter the source and destination: ";
        cin >> src >> dest;

        string ans = app.get_shortest_path(src, dest);
        if (ans.size())
        {
            cout << "Shortest path from " << src << " to " << dest << " is: " << ans << endl;
        }
        else
        {
            cout << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        char ch;
        cin >> ch;
        userWantsToContinue = (ch == 'y');
    }

    return 0;
}
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

struct City {
    string Name;
    int Cost;

    City(string n, int c) : Name(n), Cost(c) {}

    bool operator<(const City& OtherCity) const {
        return Cost > OtherCity.Cost;
    }
};

class Graph {
public:
    void AddEdge(string from, string to, int cost) {
        graph[from].emplace_back(to, cost);
        graph[to].emplace_back(from, cost);
    }

    int UniformCostSearch(string Start, string Goal) {
        priority_queue<City> pq;
        unordered_map<string, int> Cost;
        unordered_map<string, string> Parent;

        pq.emplace(Start, 0);
        Cost[Start] = 0;
        Parent[Start] = "";

        while (!pq.empty()) {
            City Current = pq.top();
            pq.pop();

            if (Current.Name == Goal) {
                PrintPath(Start, Goal, Parent);
                return Cost[Goal];
            }

            for (const auto& Neighbor : graph[Current.Name]) {
                int NewCost = Cost[Current.Name] + Neighbor.Cost;
                if (!Cost.count(Neighbor.Name) || NewCost < Cost[Neighbor.Name]) {
                    Cost[Neighbor.Name] = NewCost;
                    Parent[Neighbor.Name] = Current.Name;
                    pq.emplace(Neighbor.Name, NewCost);
                }
            }
        }

        return numeric_limits<int>::max();
    }

private:
    unordered_map<string, vector<City>> graph;

    void PrintPath(const string& Start, const string& Goal, const unordered_map<string, string>& Parent) {
        vector<string> path;
        string current = Goal;

        while (current != Start) {
            path.push_back(current);
            current = Parent.at(current);
        }

        path.push_back(Start);

        cout << "The path from " << Start << " to " << Goal << " is: ";
        for (auto city = path.rbegin(); city != path.rend(); ++city) {
            cout << *city;
            if (city + 1 != path.rend()) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
};

int main() {
    Graph graph;


    graph.AddEdge("Arad", "Zerind", 75);
    graph.AddEdge("Arad", "Timisoara", 118);
    graph.AddEdge("Zerind", "Oradea", 71);
    graph.AddEdge("Oradea", "Sibiu", 151);
    graph.AddEdge("Sibiu", "Fagaras", 99);
    graph.AddEdge("Sibiu", "Rimnicu Vilcea", 80);
    graph.AddEdge("Rimnicu Vilcea", "Pitesti", 97);
    graph.AddEdge("Timisoara", "Lugoj", 111);
    graph.AddEdge("Lugoj", "Mehadia", 70);
    graph.AddEdge("Mehadia", "Drobeta", 75);
    graph.AddEdge("Drobeta", "Craiova", 120);
    graph.AddEdge("Craiova", "Rimnicu Vilcea", 146);
    graph.AddEdge("Pitesti", "Craiova", 138);
    graph.AddEdge("Pitesti", "Bucuresti", 101);
    graph.AddEdge("Fagaras", "Bucuresti", 211);
    graph.AddEdge("Bucuresti", "Giurgiu", 90);

    string StartCity = "Rimnicu Vilcea";
    string GoalCity = "Timisoara";

    int Cost = graph.UniformCostSearch(StartCity, GoalCity);

    if (Cost != numeric_limits<int>::max()) {
        cout << "The minimum Cost from " << StartCity << " to " << GoalCity << " is: " << Cost << endl;
    }
    else {
        cout << "No path found from " << StartCity << " to " << GoalCity << endl;
    }

    return 0;
}
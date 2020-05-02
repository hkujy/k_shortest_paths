#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include<fstream>
#include <ctime>
#include<unordered_map>
#include<queue>
#include<limits>

using namespace std;

/* Node class to store each node
    each class stores:
        - list of nodes this node connects to
        - each cost of the connection
*/

class Node {

    public:
        void findConnections();
        void isConnection();
        void addEdge(string dest, double cost);
        void printConnections();
        double getCost();
        void setCost(double c);
        void setName(const string &name);
        string getName();
        void visit();
        bool getVisited();
        vector<string> getConnections();
        vector<double> getConnectCosts();

        Node(): cost{numeric_limits<double>::infinity()}, visited{false} {}

    private:
        double cost;
        bool visited;
        string name;
        vector<string> connections;
        vector<double> connectCosts;
};

void Node::addEdge(string dest, double cost) {
    connections.push_back(dest);
    connectCosts.push_back(cost);
}

void Node::printConnections() {
    cout << "Node: " << name << " : ";
    for(int i = 0; i < connections.size(); i++) {
        cout << connections[i] << " " << connectCosts[i] << " ";
    }
    cout << endl;
}

double Node::getCost() {
    return cost;
}

void Node::setCost(double c) {
    cost = c;
}

void Node::setName(const string &n) {
    name = n;
}

string Node::getName() {
    return name;
}
void Node::visit() {
    visited = true;
}

bool Node::getVisited() {
    return visited;
}

vector<string> Node::getConnections() {
    return connections;
}

vector<double> Node::getConnectCosts() {
    return connectCosts;
}


int main(int argc, char ** argv) {

    string filename = "input.txt";
    ifstream input;

    clock_t start_t, end_t;
    double cpu_time_used;
    start_t = clock();

    /*
        6 nodes, 9 edges between nodes, directed graph
        find 3 shortest paths from C -> H: last input line Source, Destination, k

    */

    input.open(filename);
    int n, e;
    input >> n >> e;

    //for each node, initalise a node
    unordered_map<string, Node> nodes;
    for(int i = 0; i < e; i++) {
        //input : G D 6
        string s, d; double cost;
        input >> s >> d >> cost;

        //iterator to check if node already exists
        auto iter = nodes.find(s);

        //if node does not exist yet in map, else already exists
        if(iter == nodes.end()) {
            Node n;
            n.addEdge(d, cost);
            n.setName(s);
            nodes[s] = n;
        } else {
            Node n(iter->second);
            n.addEdge(d, cost);
            nodes[s] = n;
        }
    }
    //read in the source, destination and how many paths
    string source, dest; int k;

    input >> source >> dest >> k;

    /*
        add source node to path queue
        check it's connections, find cheapest, add to queue
    */

   //comparator function for sorting priority upon insert 
   struct CostCompare {
       bool operator()(Node & nodeA, Node & nodeB) {
           return nodeA.getCost() > nodeB.getCost();
       }
   };

    priority_queue<Node, vector<Node>, CostCompare> queue;
    nodes[source].setCost(0);
     // queue.push(nodes[source]);


    for(auto &i: nodes) {
        queue.push(i.second);
    }

    //iterate over queue
    while(!queue.empty()) {
        Node n = queue.top();
        queue.pop();
        n.printConnections();
        vector<string> connects = n.getConnections();
        vector<double> connectCs = n.getConnectCosts();

        for(int i = 0; i < connects.size(); i++) {
            //update costs for all connects to node

        }
    }

    //print out list of nodes
    // auto iterator = nodes.begin();
    // while (iterator != nodes.end()) {
    //     cout << iterator->first << ":: ";
    //     iterator->second.printConnections();
    //     iterator++;
    // }
    end_t = clock();
    cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);
    cout << endl; 
    input.close();
    return 0;
}

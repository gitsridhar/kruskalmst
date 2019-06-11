#include <iostream>

using namespace std;

class Edge {
    public:
        int source, destination, weight; 
};

class Graph {
    public:
        int numberofvertices, numberofedges;

        Edge *edge;
};

Graph *createGraph(int vertices, int edges) {
    Graph *graph = new Graph();
    graph->numberofvertices = vertices;
    graph->numberofedges = edges;

    graph->edge = new Edge[edges];

    return graph;
}

class SubGraph {
    public:
        int parent;
        int rank;
};

int find(SubGraph subgraphs[], int i) {
    if(subgraphs[i].parent != i) {
        subgraphs[i].parent = find(subgraphs, subgraphs[i].parent);
    }

    return subgraphs[i].parent;
}

void mix(SubGraph subgraphs[], int x, int y) {
    int xroot = find(subgraphs, x);
    int yroot = find(subgraphs, y);

    if(subgraphs[xroot].rank < subgraphs[yroot].rank) {
        subgraphs[xroot].parent = yroot;
    }
    else if (subgraphs[xroot].rank > subgraphs[yroot].rank) {
        subgraphs[yroot].parent = xroot;
    }
    else {
        subgraphs[yroot].parent = xroot;
        subgraphs[xroot].rank++;
    }
}

int comparisonfunction(const void *a, const void *b) {
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph *graph) {
    int numberofvertices = graph->numberofvertices;

    Edge result[numberofvertices];

    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->numberofedges, sizeof(graph->edge[0]), comparisonfunction);

    SubGraph *subgraphs = new SubGraph[numberofvertices];

    for(int v=0; v<numberofvertices; v++) {
        subgraphs[v].parent = v;
        subgraphs[v].rank = 0;
    }

    while(e < numberofvertices - 1) {
        Edge next_edge = graph->edge[i++];

        int x = find(subgraphs, next_edge.source);
        int y = find(subgraphs, next_edge.destination);

        if (x != y) {
            result[e++] = next_edge;
            mix(subgraphs, x, y);
        }
    }

    for(i=0; i<e; ++i) {
        cout << result[i].source << " -- " << result[i].destination << " -- " << result[i].weight << endl;
    }

    return;
}

int main() {
    int V = 4;
    int E = 5;

    Graph *graph = createGraph(V, E);

    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;
    graph->edge[0].weight = 10;

    graph->edge[1].source = 0;
    graph->edge[1].destination = 2;
    graph->edge[1].weight = 6;

    graph->edge[2].source = 0;
    graph->edge[2].destination = 3;
    graph->edge[2].weight = 5;

    graph->edge[3].source = 1;
    graph->edge[3].destination = 3;
    graph->edge[3].weight = 15;

    graph->edge[4].source = 2;
    graph->edge[4].destination = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return(0);
}

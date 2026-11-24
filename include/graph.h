#ifndef GRAPH_H
#define GRAPH_H

#define MAX_STATIONS 30
#define STATION_NAME_LEN 50
#define INF 999999

/* Adjacency List Node representing a railway connection */
typedef struct AdjListNode {
    int dest;
    int dist;
    int time;
    struct AdjListNode* next;
} AdjListNode;

/* Adjacency List for a station */
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

/* Station metadata */
typedef struct Station {
    int id;
    char name[STATION_NAME_LEN];
} Station;

/* Graph representation using Adjacency List */
typedef struct Graph {
    int numStations;
    Station stations[MAX_STATIONS];
    AdjList array[MAX_STATIONS];
} Graph;

/* Function prototypes */
Graph* createGraph(int numStations);
void freeGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest, int dist, int time);
int addStation(Graph* graph, const char* name);
int findStationIndex(const Graph* graph, const char* name);
void displayStations(const Graph* graph);
int loadGraphFromCSV(Graph* graph, const char* filepath);
void initDefaultGraph(Graph* graph);

#endif /* GRAPH_H */

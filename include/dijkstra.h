#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

/* Structure to store computed shortest/fastest route */
typedef struct RouteResult {
    int path[MAX_STATIONS];
    int pathLen;
    int totalDist;
    int totalTime;
    int isValid;
} RouteResult;

/* Function prototypes */
RouteResult findShortestRoute(const Graph* graph, int src, int dest, int isTime);
void printRoute(const Graph* graph, const RouteResult* result, int isTime);
void printFareEstimate(int distanceKm);
void printStationConnections(const Graph* graph, int stationIdx);

#endif /* DIJKSTRA_H */

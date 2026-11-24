#include <stdio.h>
#include <stdlib.h>
#include "../include/dijkstra.h"
#include "../include/minheap.h"

/* Helper to get edge metrics between two adjacent vertices */
static void getEdgeMetrics(const Graph* graph, int u, int v, int* dist, int* time) {
    *dist = 0;
    *time = 0;
    AdjListNode* crawl = graph->array[u].head;
    while (crawl) {
        if (crawl->dest == v) {
            *dist = crawl->dist;
            *time = crawl->time;
            return;
        }
        crawl = crawl->next;
    }
}

RouteResult findShortestRoute(const Graph* graph, int src, int dest, int isTime) {
    RouteResult result;
    result.pathLen = 0;
    result.totalDist = 0;
    result.totalTime = 0;
    result.isValid = 0;

    int V = graph->numStations;
    if (src < 0 || src >= V || dest < 0 || dest >= V) {
        return result;
    }

    int* dist = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INF;
        parent[v] = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        free(minHeapNode);

        if (dist[u] == INF) break;
        if (u == dest) break; /* Reached target destination */

        AdjListNode* crawl = graph->array[u].head;
        while (crawl != NULL) {
            int v = crawl->dest;
            int weight = isTime ? crawl->time : crawl->dist;

            if (isInMinHeap(minHeap, v) && dist[u] != INF && (dist[u] + weight < dist[v])) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            crawl = crawl->next;
        }
    }

    if (dist[dest] != INF) {
        result.isValid = 1;
        int curr = dest;
        int tempPath[MAX_STATIONS];
        int count = 0;

        while (curr != -1) {
            tempPath[count++] = curr;
            curr = parent[curr];
        }

        /* Reverse to store path from src to dest */
        for (int i = 0; i < count; i++) {
            result.path[i] = tempPath[count - 1 - i];
        }
        result.pathLen = count;

        /* Calculate exact total distance and time along the traversed path */
        for (int i = 0; i < count - 1; i++) {
            int u = result.path[i];
            int v = result.path[i + 1];
            int edgeDist, edgeTime;
            getEdgeMetrics(graph, u, v, &edgeDist, &edgeTime);
            result.totalDist += edgeDist;
            result.totalTime += edgeTime;
        }
    }

    freeMinHeap(minHeap);
    free(dist);
    free(parent);

    return result;
}

void printRoute(const Graph* graph, const RouteResult* result, int isTime) {
    if (!result->isValid || result->pathLen == 0) {
        printf("\n[-] No route found between the specified stations.\n");
        return;
    }

    printf("\n============================================================\n");
    if (isTime) {
        printf("              FASTEST ROUTE (OPTIMIZED FOR TIME)            \n");
    } else {
        printf("            SHORTEST ROUTE (OPTIMIZED FOR DISTANCE)         \n");
    }
    printf("============================================================\n");

    printf("\nPath Itinerary:\n");
    for (int i = 0; i < result->pathLen; i++) {
        int u = result->path[i];
        if (i == 0) {
            printf("  [Start] %s\n", graph->stations[u].name);
        } else {
            int prev = result->path[i - 1];
            int d, t;
            getEdgeMetrics(graph, prev, u, &d, &t);
            printf("     | \n");
            printf("     +---> %s  (Leg: %d km, %d min)\n", graph->stations[u].name, d, t);
        }
    }

    printf("\nSummary:\n");
    printf("  * Total Stops    : %d stations (%d intermediate stops)\n", 
           result->pathLen, result->pathLen > 2 ? result->pathLen - 2 : 0);
    printf("  * Total Distance : %d km\n", result->totalDist);

    int hours = result->totalTime / 60;
    int mins = result->totalTime % 60;
    printf("  * Total Duration : %d hours %d minutes (%d mins)\n", hours, mins, result->totalTime);
    printf("============================================================\n");

    printFareEstimate(result->totalDist);
}

void printFareEstimate(int distanceKm) {
    if (distanceKm <= 0) return;

    /* Base rates and cost per kilometer for Indian Railways style tiers */
    int sleeper = 120 + (int)(distanceKm * 0.45);
    int ac3     = 320 + (int)(distanceKm * 1.15);
    int ac2     = 550 + (int)(distanceKm * 1.70);
    int ac1     = 850 + (int)(distanceKm * 2.60);

    printf("\n--- Estimated Ticket Fares ---\n");
    printf("+----------------------+-------------------+\n");
    printf("| Travel Class         | Approx. Fare (INR)|\n");
    printf("+----------------------+-------------------+\n");
    printf("| Sleeper Class (SL)   | Rs. %-13d |\n", sleeper);
    printf("| AC 3-Tier (3A)       | Rs. %-13d |\n", ac3);
    printf("| AC 2-Tier (2A)       | Rs. %-13d |\n", ac2);
    printf("| AC First Class (1A)  | Rs. %-13d |\n", ac1);
    printf("+----------------------+-------------------+\n\n");
}

void printStationConnections(const Graph* graph, int stationIdx) {
    if (stationIdx < 0 || stationIdx >= graph->numStations) {
        printf("\n[!] Invalid station selected.\n");
        return;
    }

    printf("\nDirect Railway Lines from [%s]:\n", graph->stations[stationIdx].name);
    printf("+------------------------+---------------+-----------------+\n");
    printf("| Destination Station    | Distance (km) | Duration (min)  |\n");
    printf("+------------------------+---------------+-----------------+\n");

    AdjListNode* crawl = graph->array[stationIdx].head;
    int count = 0;
    while (crawl) {
        printf("| %-22s | %-13d | %-15d |\n", 
               graph->stations[crawl->dest].name, crawl->dist, crawl->time);
        crawl = crawl->next;
        count++;
    }

    if (count == 0) {
        printf("| No direct tracks found from this station                 |\n");
    }
    printf("+------------------------+---------------+-----------------+\n\n");
}

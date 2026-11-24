#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/graph.h"

/* Helper to compare strings case-insensitively */
static int caseInsensitiveCompare(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
        }
        s1++;
        s2++;
    }
    return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}

/* Helper to trim leading/trailing whitespace */
static void trimWhitespace(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

Graph* createGraph(int numStations) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numStations = numStations;
    for (int i = 0; i < MAX_STATIONS; i++) {
        graph->array[i].head = NULL;
        graph->stations[i].id = -1;
        graph->stations[i].name[0] = '\0';
    }
    return graph;
}

void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numStations; i++) {
        AdjListNode* current = graph->array[i].head;
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

int addStation(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numStations; i++) {
        if (caseInsensitiveCompare(graph->stations[i].name, name) == 0) {
            return i;
        }
    }
    if (graph->numStations >= MAX_STATIONS) {
        return -1;
    }
    int idx = graph->numStations;
    graph->stations[idx].id = idx;
    strncpy(graph->stations[idx].name, name, STATION_NAME_LEN - 1);
    graph->stations[idx].name[STATION_NAME_LEN - 1] = '\0';
    graph->numStations++;
    return idx;
}

int findStationIndex(const Graph* graph, const char* name) {
    if (!graph || !name) return -1;
    for (int i = 0; i < graph->numStations; i++) {
        if (caseInsensitiveCompare(graph->stations[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addEdge(Graph* graph, int src, int dest, int dist, int time) {
    if (src < 0 || src >= graph->numStations || dest < 0 || dest >= graph->numStations)
        return;

    /* Add edge from src to dest */
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->dist = dist;
    newNode->time = time;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    /* Since railway tracks are bi-directional, add edge from dest to src */
    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = src;
    newNode->dist = dist;
    newNode->time = time;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void displayStations(const Graph* graph) {
    if (!graph || graph->numStations == 0) {
        printf("\n[!] No stations available.\n");
        return;
    }
    printf("\n+-----+------------------------------+\n");
    printf("| No. | Station Name                 |\n");
    printf("+-----+------------------------------+\n");
    for (int i = 0; i < graph->numStations; i++) {
        printf("| %2d  | %-28s |\n", i + 1, graph->stations[i].name);
    }
    printf("+-----+------------------------------+\n\n");
}

int loadGraphFromCSV(Graph* graph, const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        return 0; /* File could not be opened */
    }

    char line[256];
    int edgesLoaded = 0;

    while (fgets(line, sizeof(line), file)) {
        trimWhitespace(line);
        if (line[0] == '#' || line[0] == '\0') {
            continue; /* Skip comments or empty lines */
        }

        char srcName[STATION_NAME_LEN];
        char destName[STATION_NAME_LEN];
        int dist, time;

        char* token = strtok(line, ",");
        if (!token) continue;
        trimWhitespace(token);
        strncpy(srcName, token, STATION_NAME_LEN - 1);
        srcName[STATION_NAME_LEN - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        trimWhitespace(token);
        strncpy(destName, token, STATION_NAME_LEN - 1);
        destName[STATION_NAME_LEN - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        dist = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        time = atoi(token);

        int u = addStation(graph, srcName);
        int v = addStation(graph, destName);

        if (u != -1 && v != -1) {
            addEdge(graph, u, v, dist, time);
            edgesLoaded++;
        }
    }

    fclose(file);
    return edgesLoaded;
}

void initDefaultGraph(Graph* graph) {
    const char* defaultStations[] = {
        "Delhi", "Chandigarh", "Ambala", "Ludhiana",
        "Amritsar", "Pathankot", "Jammu", "Shimla",
        "Dehradun", "Haridwar"
    };

    for (int i = 0; i < 10; i++) {
        addStation(graph, defaultStations[i]);
    }

    /* Distances in km, times in minutes */
    addEdge(graph, 0, 2, 200, 180); // Delhi - Ambala
    addEdge(graph, 0, 8, 250, 300); // Delhi - Dehradun
    addEdge(graph, 0, 9, 210, 240); // Delhi - Haridwar
    addEdge(graph, 0, 1, 260, 240); // Delhi - Chandigarh
    addEdge(graph, 2, 1, 50,  45);  // Ambala - Chandigarh
    addEdge(graph, 2, 3, 110, 90);  // Ambala - Ludhiana
    addEdge(graph, 2, 7, 150, 200); // Ambala - Shimla
    addEdge(graph, 1, 7, 110, 180); // Chandigarh - Shimla
    addEdge(graph, 1, 3, 100, 110); // Chandigarh - Ludhiana
    addEdge(graph, 3, 4, 140, 120); // Ludhiana - Amritsar
    addEdge(graph, 3, 5, 170, 160); // Ludhiana - Pathankot
    addEdge(graph, 4, 5, 110, 100); // Amritsar - Pathankot
    addEdge(graph, 5, 6, 100, 110); // Pathankot - Jammu
    addEdge(graph, 8, 9, 50,  60);  // Dehradun - Haridwar
    addEdge(graph, 8, 7, 220, 360); // Dehradun - Shimla
}

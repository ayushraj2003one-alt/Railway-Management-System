#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"
#include "../include/dijkstra.h"

/* Helper to resolve station input: user can type either station number (1-based) or station name */
static int resolveStationInput(const Graph* graph, const char* prompt) {
    char input[100];
    printf("%s", prompt);
    if (!fgets(input, sizeof(input), stdin)) {
        return -1;
    }

    /* Remove trailing newline */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (strlen(input) == 0) {
        return -1;
    }

    /* Check if input is a numeric ID (1-based index for user friendliness) */
    char* endptr;
    long val = strtol(input, &endptr, 10);
    if (*endptr == '\0') {
        int idx = (int)val - 1;
        if (idx >= 0 && idx < graph->numStations) {
            return idx;
        }
        return -1;
    }

    /* Otherwise, search by name */
    return findStationIndex(graph, input);
}

static void printHeader() {
    printf("\n");
    printf("************************************************************\n");
    printf("*           RAILWAY NETWORK & TRACKING SYSTEM              *\n");
    printf("*        Dijkstra's Shortest Path & Fast Transit           *\n");
    printf("************************************************************\n");
}

static void printMenu() {
    printf("\n--- MAIN MENU ---\n");
    printf("1. View All Railway Stations\n");
    printf("2. Find Shortest Route by Distance (km)\n");
    printf("3. Find Fastest Route by Travel Time (minutes)\n");
    printf("4. Inspect Direct Connections of a Station\n");
    printf("5. Fare Calculator (Custom Distance)\n");
    printf("6. Reload Network Dataset\n");
    printf("7. Exit\n");
    printf("Enter your choice (1-7): ");
}

int main() {
    Graph* graph = createGraph(0);

    /* Try loading network dataset from CSV first; fallback to default graph if missing */
    int loaded = loadGraphFromCSV(graph, "data/network.csv");
    if (!loaded) {
        loaded = loadGraphFromCSV(graph, "../data/network.csv");
    }
    if (!loaded) {
        initDefaultGraph(graph);
        printf("[i] Loaded internal default railway network (10 stations).\n");
    } else {
        printf("[i] Successfully loaded railway network from CSV (%d routes).\n", loaded);
    }

    int choice;
    char buffer[64];

    printHeader();

    do {
        printMenu();
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            break;
        }
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                displayStations(graph);
                break;

            case 2:
            case 3: {
                int isTime = (choice == 3);
                printf("\n--- %s Route Planner ---\n", isTime ? "Fastest (Time)" : "Shortest (Distance)");
                printf("(Tip: You can enter station name e.g., 'Delhi' or station number e.g., '1')\n\n");

                int src = resolveStationInput(graph, "Enter Source Station: ");
                if (src == -1) {
                    printf("[!] Invalid source station. Please try again or check option 1 for valid names/numbers.\n");
                    break;
                }

                int dest = resolveStationInput(graph, "Enter Destination Station: ");
                if (dest == -1) {
                    printf("[!] Invalid destination station.\n");
                    break;
                }

                if (src == dest) {
                    printf("[!] Source and destination stations cannot be identical.\n");
                    break;
                }

                RouteResult result = findShortestRoute(graph, src, dest, isTime);
                printRoute(graph, &result, isTime);
                break;
            }

            case 4: {
                printf("\n--- Direct Connection Inspector ---\n");
                int st = resolveStationInput(graph, "Enter Station Name or Number: ");
                if (st == -1) {
                    printf("[!] Station not recognized.\n");
                } else {
                    printStationConnections(graph, st);
                }
                break;
            }

            case 5: {
                printf("\nEnter travel distance in kilometers (km): ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    int distKm = atoi(buffer);
                    if (distKm <= 0) {
                        printf("[!] Distance must be a positive number.\n");
                    } else {
                        printFareEstimate(distKm);
                    }
                }
                break;
            }

            case 6: {
                freeGraph(graph);
                graph = createGraph(0);
                int reloaded = loadGraphFromCSV(graph, "data/network.csv");
                if (!reloaded) {
                    reloaded = loadGraphFromCSV(graph, "../data/network.csv");
                }
                if (!reloaded) {
                    initDefaultGraph(graph);
                    printf("[i] Reset to internal default network.\n");
                } else {
                    printf("[+] Network successfully reloaded from data/network.csv!\n");
                }
                break;
            }

            case 7:
                printf("\nThank you for using Railway Tracking System. Safe travels!\n\n");
                break;

            default:
                printf("\n[!] Invalid option. Please select between 1 and 7.\n");
                break;
        }
    } while (choice != 7);

    freeGraph(graph);
    return 0;
}

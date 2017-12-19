/*
 * Planner.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Samuel B. Soares
 *      Course: 1160
 *      St. ID: 11271978
 *
 *      This program solves the proposed problem in Assignment 4.
 *
 *  File Format must be:
 *      The first line of file includes name of cities separated by coma.
 *      There is no space in city names. In next lines you have two city
 *      name and a ticket price followed by a dollar sign ($), which are
 *      separated by space.If there is no line about ticket price of two
 *      given cities, it means a direct traveling is not possible.
 *
 */

// Using modified Dijkstra algorithm
// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

#include <limits.h> // INT_MAX
#include <string> // string
#include <sstream> // stringstream
#include <iostream> // cin, cout
#include <fstream> // ifstream
#include <cstring> // s_str()
#include <cstdlib> // exit

using namespace std;

// Maximum number of cities
const int V = 100;
// Actual number of cities (global)
int nCities = 0;

// Function prototypes
int minDistance(int dist[], bool sptSet[]);
string toString(int n);
int toInt(string s);
void printSolution(int dist[], int steps[], int n, string path[], string cities[], int graph[V][V]);
void dijkstra(int graph[V][V], int src, string cities[]);
int getCity(string city, string cities[], int n);
int readValues(int graph[V][V], string cities[V]);
int getCityNumber(string cities[V], int nCities);

// driver program to test above function
int main() {

    /* Let us create the example graph discussed above */
    string cities[V];
    int graph[V][V];
    nCities = readValues(graph, cities); // Function that populates cities and graph arrays,
                // and returns the number of cities.
    int c = getCityNumber(cities, nCities); // Asks user for valid input
    dijkstra(graph, c, cities); // Calculates paths, chooses best, and prints results
    return 0;
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[]) {
   // Initialize min value
   int min = INT_MAX, min_index = -1;
   for (int v = 0; v < nCities; v++)
     if (sptSet[v] == false && dist[v] < min)
         min = dist[v], min_index = v;
   return min_index;
}

// Transforms int to string
string toString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

// Transforms string to int
int toInt(string s) {
    stringstream ss;
    ss.str(s);
    int n;
    ss >> n;
    return n;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int steps[], int n, string path[], string cities[], int graph[V][V]) {
    // Looks for the path with the lowest average ticket price
    int min_avg = INT_MAX, min_idx = -1; // Starting values
    for (int i = 0; i < nCities; i++) {
        int avg = steps[i] ? dist[i] / steps[i] : steps[i];
        // Ignores travels from one city to itself and updates travel
        //with minimum average price
        if (steps[i] > 0 && min_avg > avg) {
            min_avg = avg;
            min_idx = i;
        }
    }
    int pos, i = 0;

    // Starts printing results
    //     String was built with commas between city stops
    cout << "======================================================================\n";
    string separator = ",";
    int *min_path = new int[steps[min_idx]];
    while ((pos = path[min_idx].find(separator)) != string::npos) {
        min_path[i++] = toInt(path[min_idx].substr(0, pos));
        cout << cities[min_path[i-1]] << " -> ";
        path[min_idx].erase(0, pos + separator.length());
    }
    min_path[i] = toInt(path[min_idx]);

    cout << cities[min_path[i]] << endl;
    cout << "======================================================================\n";
    cout << "Detailed Plan #Visiting city: " << steps[min_idx] << " Cost Rate: " << min_avg << endl;
    cout << "----------------------------------------------------------------------\n";
    for (int j = 0; j < steps[min_idx]; j++) {
        cout << cities[min_path[j]] << " to " << cities[min_path[j+1]] << " cots $" << graph[min_path[j]][min_path[j+1]] << endl;
    }
    cout << "----------------------------------------------------------------------\n";
    cout << "Total cost is $" << dist[min_idx] << endl;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src, string cities[]) {
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Array created to keep track of how many cities were visited in the best case
     //for every possible destination
     int steps[V];
     // Generates the sequence of city numbers in the best case for each destination
     string path[V];

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        // Initializes new arrays for base numbers (0 for the int counters
        //and empty for strings)
        steps[i] = 0;
        path[i] = "";
     }

     // Distance of source vertex from itself is always 0
     dist[src] = 0;
     path[src] = toString(src);

     bool srcBefore = false;

     // Find shortest path for all vertices
     for(int count = 0; count < nCities-1; count++) {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);

       if(u == -1) {
           cout << "This city has no connections!";
              exit(0);
       }
       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < nCities; v++) {
         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
           if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u] + graph[u][v] < dist[v]) {
               dist[v] = dist[u] + graph[u][v];
               // Updates steps taken
               steps[v] = steps[u] + 1;
               // Adds the new city visited
               path[v] = path[u] + "," + toString(v);
           }
       }
     }
     // Calls function that finds best path and prints it
     printSolution(dist, steps, V, path, cities, graph);
}

// Helper function to get city index by its name
int getCity(string city, string cities[], int n) {
    for(int i = 0; i < n || (city.compare("") == 0); i++) {
        if(strcmp(city.c_str(), cities[i].c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

// Function that asks the user for a file input, opens the file (no check if file
//is wrong or doesn't open for any other reason) and populates the array of values(graph)
//and the array of cities with their respective names. Indexes of both arrays are related.
// i.e.: array[1][2] is the cost of a trip from cities[1] to cities[2]
int readValues(int graph[V][V], string cities[V]) {
    string f;
    cout << "Enter the file name: ";
    cin >> f;
    //Opens file
    ifstream in (f.c_str()); // for testing "t.txt"); //
    string line;
    getline(in, line);

    // Sets separator for cities in first line
    string separator = ", ";
    unsigned pos = 0, i = 0;

    // Searches the separator and removes the city name out of line
    //inserting it sequentially into the cities array
    while ((pos = line.find(separator)) != string::npos) {
        cities[i++] = line.substr(0, pos);
        line.erase(0, pos + separator.length());
    }
    cities[i++] = line;

    // Populate distances array searching for the format "CITY1 CITY2 $VALUE"
    separator = " ";
    string city1, city2;
    while (!in.eof()) {
        getline(in, line);
        pos = line.find(separator);
        string city1 = line.substr(0, pos);
        int c1 = getCity(city1, cities, i);
        line.erase(0, pos + separator.length());
        pos = line.find(separator);
        string city2 = line.substr(0, pos);
        int c2 = getCity(city2, cities, i);
        line.erase(0, pos + separator.length() + 1); // Ignores "$"
        graph[c1][c2]= toInt(line);
        graph[c2][c1]= toInt(line);
    }
    return i;
}

// Asks the user for a valid number of origin for the printed cities and
//doesn't get out of the loop until a valid input is provided
int getCityNumber(string cities[V], int nCities) {
    for(int i = 0; i < nCities; i++) {
        cout << i << ") " << cities[i] << endl;
    }
    int c;
    do {
        cin.clear();
        cout << "Enter the number of the desired city of origin: ";
        cin >> c;
    } while(c < -1 || c > nCities);
    return c;
}

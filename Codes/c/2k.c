// Ce Cao 
// 9/6/2022

// “Imperial Messengers” Solution: 
// The cities can be abstracted as nodes while travel time can be edges. 
// Since the type of graph (whether it is sparse or dense) is not known, 
// so both Adjacency Matrix and Adjacency List are fine to store the graph.

// At first I thought it is a travelling salesman problem, but then I realized that 
// once the message got to one city it can spread from the new city, at same time.
// So the question is esstianlly a single-source shortest path problem.
// So Dijkistra algorithm (O(V^2)) comes to my mind naturally.

// Since the weight of edge is travel time, which can not be less than 0,
// so it is unnecessary to user bellman-ford algorithm (O(EV)).
// A-star algorithm is not not good either since it won't allow multiple cities as heuristic -
// and we want to get to all cities and find the "maximum of all shortest paths".
// Floyd-Warshall algorithm (O(V^3)) has the highest complexity.

// It took me around 3.5 hours on the solution





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Largest distance
#define INF  999999
// Maximum number of cities
#define MAX  100
// Maximum length of input
#define MAXLENGTH 200

// Adjacency Matrix
int matrix[MAX+5][MAX+5];
int cityNum;


void init(void);
int getCityNumber(void);
char* readString(void);
void buildMatrix(int);
void printMatrix(int);
void calculateTime(void);
int dijkstra(int);

void init() {
    cityNum = getCityNumber();
    buildMatrix(cityNum);
}

// Helper funciton for getting a number
int getCityNumber() {
    int num = 0;
    char *input = readString();
    sscanf(input,"%i",&num);
    free(input);
    if(num > MAX)   num = MAX;
    return num;
}

// Helper function for robust input
char* readString() {
    char buffer[MAXLENGTH];
    fgets(buffer, MAXLENGTH, stdin);
    size_t inputLength = strlen(buffer);
    char *input = calloc(sizeof(char), inputLength);
    strncpy(input, buffer, inputLength-1);
    input[inputLength] = '\0';
    return input;
}

void buildMatrix(int cityNum) {
    for(int i = 1; i < cityNum; i++ ) { 
        int j = 0; 
        char *input = readString();
        char *next_token = NULL;
        // split string with space delimiter
        char *token = strtok_r(input, " ", &next_token);
        // loop through the input to extract all other tokens
        while( token != NULL && j < cityNum ) {
            if (token[0] == 'x') { // if not specified, mark as x as well
				matrix[i][j] = 0;
				matrix[j][i] = matrix[i][j];
				j++;
				token = strtok_r(NULL, " ", &next_token);
				continue;
			}
			matrix[i][j] = atoi(token);
			matrix[j][i] = matrix[i][j];
			j++;
            token = strtok_r(NULL, " ", &next_token);
        }

        free(input);
    }
}

// For testing purposes
void printMatrix(int cityNum) {
    for(int i = 0; i < cityNum; i++) {
        for(int j = 0; j < cityNum ; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculateTime() {

    if (cityNum < 1) {
        printf("The number of city is incorrect!\n");
        return;
    } else if (cityNum == 1) {
        printf("0\n");
        return;
    }

    int time = dijkstra(cityNum);

    if (time == INF) {
        printf("The message cannot be spread!\n");
        return;
    }

    printf("%d\n", time);
}

int dijkstra(int num){
    int* distance;
	distance = calloc(num, sizeof(int));
    
	bool* book; // Record city visited
	book = calloc(num, sizeof(bool));

    // init 
    for(int i = 0 ; i < num ; i++){
        for(int j = 0 ; j < num ; j++)
            if(i!=j && matrix[i][j] == 0)
                matrix[i][j] = INF;
            else
                matrix[i][j] = matrix[i][j];
        distance[i] = matrix[0][i];  // start from index 0 (capital)
        book[i] = false;
    }

    book[0] = true;
    int nextNode, minDistance, count = 1;

    while(count < num-1) {
        minDistance = INF + 1;

        for(int i = 0 ; i < num ; i++) {
            if (distance[i] < minDistance && !book[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        book[nextNode] = true;

        for (int i = 0; i < num; i++)
            if (!book[i])
                if (minDistance + matrix[nextNode][i] < distance[i])
                    distance[i] = minDistance + matrix[nextNode][i];
        
        count++;
    }

    // calculate time
    int time = distance[0];
	for (int i = 0; i < num; i++) {
		time = distance[i] > time ? distance[i] : time;
	}

    free(distance);
    free(book);

    return time;
}

int main() {
    init();
    calculateTime();
    return 0;
}
#ifndef FUNCTII_H
#define FUNCTII_H


typedef struct Node{
char oras[50];;
struct Node* next;
}Node;

typedef struct list{
struct Node *head;
int size;
}list;

typedef struct Graph
{
    int V;
    int E;
    int **a;
    int **b;
}Graph;

list *create_list();
Node *create_node(char oras[]);
Graph *create_graph(int n);
void add(list *list, char oras[]);
void print(list *list);
int id(list *list, char oras[]);
void graph_orientat(Graph *graph, list *list, char oras1[],char oras2[],int c1,int c2);
void graph_neorientat(Graph *graph, list *list, char oras1[],char oras2[],int c1,int c2);
void dist(Graph *graph);
void total_km(Graph *graph);
void print_neorientat(Graph *graph);
void print_orientat(Graph *graph);
void orientat_costuri(Graph *graph);
void neorientat_costuri(Graph *graph);
int minDistance(int dist[], int sps[], int V);
void dijkstra(Graph *graph, int s, int *dist);
#endif
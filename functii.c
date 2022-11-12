#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <limits.h>
#include "functii.h"

list *create_list()
{
    list *list = malloc(sizeof(list));
   
    list->head = NULL;
    list->size = 0;

    return list;
}

Node *create_node(char oras[])
{
    Node *node = malloc(sizeof(Node));

    strcpy(node->oras, oras);
    node->next = NULL;

    return node;
}

Graph *create_graph(int n)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->V=n;
    graph->E=0;
    graph->a=(int**)malloc((graph->V) * sizeof(int*));
    graph->b=(int**)malloc((graph->V) * sizeof(int*));

    for(int i=0;i<n;i++)
    {   graph->a[i]=(int*)calloc(graph->V,sizeof(int));
        graph->b[i]=(int*)calloc(graph->V,sizeof(int));
    }
    if(graph->a==NULL)
    {
        printf("Eroare la crearea matricei");
        exit(1);
    }
    if(graph->b==NULL)
    {
        printf("Eroare la crearea matricei");
        exit(1);
    }
    return graph;
}

void add(list *list, char oras[])
{
    Node *new_node = create_node(oras);

    if(list->head == NULL)
    {
        list->head = new_node;
        list->size = list->size + 1;
    }
    else
    {
        Node *node = list->head;

        while(node->next != NULL)
        {
            if(strcmp(node->oras, new_node->oras) == 0)
            {
                break;
            }

            node = node->next;
        }

        if(node->next == NULL && !(strcmp(node->oras, new_node->oras) == 0))
        {
            node->next = new_node;
            list->size = list->size + 1;
        }
    }
}

void print(list *list)
{   
    Node *node = list->head;
    while(node != NULL)
    {
        printf("%s\n", node->oras);
        node = node->next;
        
    }
}

int id(list *list, char oras[])
{
    Node *node = list->head;
    int i=0;
    while (node != NULL)
    {
        if (strcmp(node->oras,oras)==0)
            return i;
        node = node->next;
        i++;
    }
   
    return -1;
}

void graph_orientat(Graph *graph, list *list, char oras1[],char oras2[],int c1,int c2)
{
    int l,c;
    l=id(list,oras2);
    c=id(list,oras1);

    if(graph->a[l][c]==0)
    {
        graph->a[l][c]=1;
        graph->b[l][c] = c2 - c1;
        graph->E=graph->E+1;
    }
}

void graph_neorientat(Graph *graph, list *list, char oras1[],char oras2[],int c1,int c2)
{
    int l,c;
    l=id(list,oras2);
    c=id(list,oras1);

    //printf("%d %s\n",l,oras2);
    //printf("%d %s\n",c,oras1);
    if(graph->a[l][c]==0)
    {
        graph->a[l][c]=1;
        graph->a[c][l]=1;
        graph->b[l][c] = c2 - c1;
        graph->b[c][l] = c2 - c1;
        graph->E=graph->E+1;
    }
}

void dist(Graph *graph)
{
    FILE *f;

    int max = 0;

    for(int i=0; i<graph->V; i++)
    {
        for(int j=0; j<graph->V; j++)
        {
            if(graph->b[i][j] > max)
            {
                max = graph->b[i][j];
            }
        }
    }

    int min = max;

    for(int i=0; i<graph->V; i++)
    {
        for(int j=0; j<graph->V; j++)
        {
            if(graph->b[i][j] < min && graph->b[i][j] != 0)
            {
                min = graph->b[i][j];
            }
        }
    }

    f = fopen("min.txt","wt");
    fprintf(f,"%d",min);

    f = fopen("max.txt","wt");
    fprintf(f,"%d",max);

    fclose(f);
}

void total_km(Graph *graph)
{
    FILE *f;

    int s = 0;

    for(int i=0; i<graph->V; i++)
    {
        for(int j=i+1; j<graph->V; j++)
        {
            s=s+graph->b[i][j];
        }
    }



    f = fopen("total.txt","wt");
    fprintf(f,"%d KM",s);

    fclose(f);
}

void print_neorientat(Graph *graph)
{
    FILE *f;
    f=fopen("neorientat.txt","wt");
    for (int i=0;i<graph->V;i++)
    {
        for (int j=0;j<graph->V;j++)
        {
            fprintf(f,"%d ",graph->a[i][j]);
        }
        fprintf(f,"\n");
    }
}

void print_orientat(Graph *graph)
{
    FILE *f;
    f=fopen("orientat.txt","wt");
    for (int i=0;i<graph->V;i++)
    {
        for (int j=0;j<graph->V;j++)
        {
            fprintf(f,"%d ",graph->a[i][j]);
        }
        fprintf(f,"\n");
    }
}

void orientat_costuri(Graph *graph)
{
    FILE *f;
    f=fopen("orientat_costuri.txt","wt");
    for (int i=0;i<graph->V;i++)
    {
        for (int j=0;j<graph->V;j++)
        {
            fprintf(f,"%d ",graph->b[i][j]);
        }
        fprintf(f,"\n");
    }
}

void neorientat_costuri(Graph *graph)
{
    FILE *f;
    f=fopen("neorientat_costuri.txt","wt");
    for (int i=0;i<graph->V;i++)
    {
        for (int j=0;j<graph->V;j++)
        {
            fprintf(f,"%d ",graph->b[i][j]);
        }
        fprintf(f,"\n");
    }
}
int minDistance(int dist[], int sps[], int V){
    int v, min = INT_MAX, min_index;
    for ( v = 0; v < V; v++)
        if (sps[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
}
return min_index;
}

void dijkstra(Graph *graph, int s, int *dist)
{
    int i,j,u;
    int sps[graph->V],next;
    for (i=0;i<graph->V;i++)
    {
        dist[i]=INT_MAX;
        sps[i]=0;
    }
    dist[s]=0;

    for(j=0;j<((graph->V)-1);j++)
    {
       u = minDistance(dist, sps, graph->V); 
       sps[u]=1;
    }
    for (i = 0; i < graph->V; i++){
       if (sps[i] == 0 && graph->a[u][i]!=0 &&
            dist[u] != INT_MAX && dist[u]+graph->a[u][i] < dist[i])
            dist[i] = dist[u] + graph->a[u][i];
} 
}



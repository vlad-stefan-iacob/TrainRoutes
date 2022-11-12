#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "functii.h"

int main()
{
    FILE *f,*g;
    char n[30],C;
    char oras_1[30],oras_2[30];
    Graph *gr1,*gr2,cost[30],distance[30];
    int cost1,cost2,index=0;

    list *list = create_list();

    f=fopen("_all_files.txt","rt");

    while(1)
    {
        if(fscanf(f,"%s", n)==EOF)
        {
            break;
        }
        g=fopen(n,"rt");
        
        
         while(1)
        {

            index=0;
            if(fscanf(g,"%c",&C)==EOF)
            {
                break;
            }
            while(1)
            {
                if(C==',')
                {
                    oras_1[index]='\0';
                    break;
                }

                oras_1[index] = C;
                index++;

                fscanf(g,"%c",&C);
            }

            fscanf(g,"%d",&cost1);
            add(list, oras_1);


            fscanf(g,"%c",&C);
        }

        fclose(g);
    }

    print(list);
    gr1=create_graph(list->size);
    gr2=create_graph(list->size);
    
    fseek(f,0,SEEK_SET);
    
    
    while(1)
    {
        if(fscanf(f,"%s", n)==EOF)
        {
            break;
        }
        g = fopen(n,"rt");
        
         index=0;
        if(fscanf(g,"%c",&C)==EOF)
        {
            break;
        }
        while(1)
        {
            if(C==',')
            {
                oras_1[index]='\0';
                break;
            }

            oras_1[index]=C;
            index++;

            fscanf(g,"%c",&C);
        }
        fscanf(g,"%d",&cost1);
        fscanf(g,"%c",&C);

        while(1)
        {
            index=0;
            if(fscanf(g,"%c",&C)==EOF)
            {
                break;
            }
            while(1)
            {
                if(C==',')
                {
                    oras_2[index]='\0';
                    break;
                }

                oras_2[index]=C;
                index++;

                fscanf(g,"%c",&C);
            }
            fscanf(g,"%d",&cost2);
            fscanf(g,"%c",&C);

            graph_orientat(gr1, list, oras_1, oras_2, cost1, cost2);
            graph_neorientat(gr2, list, oras_1, oras_2, cost1, cost2);

            strcpy(oras_1, oras_2);
            cost1 = cost2;
        }

        fclose(g);
    }

    fclose(f);
    print_neorientat(gr2);
    print_orientat(gr1);
    orientat_costuri(gr1);
    neorientat_costuri(gr2);
    dist(gr2);

    total_km(gr2);

   int distance=(int*)malloc((cost->V)*sizeof(int));
   Node *cpy;
   dijkstra(cost,0,distance);
   cpy=id(list,"Constanta");
   f=fopen("ruta.txt","wt");
   fprintf(f,"Distanta Bucuresti-Constanta este de %d km",distance);
return 0;
}
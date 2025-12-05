#include <stdio.h>
#include <limits.h>

#define BN   0   // Bonne Nouvelle
#define INV  1   // Invalides
#define OBK  2   // Oberkampf
#define AUS  3   // Gare d'Austerlitz
#define SSD  4   // Strasbourg-St-Denis
#define SMN  5   // Saint-Michel Notre-Dame
#define REP  6   // République
#define BFM  7   // Bibliothèque F. Mitterrand
#define IVR  8   // Ivry-sur-Seine (arrivée)

#define NODES 9
#define INFINITY INT_MAX
#define FALSE 0
#define TRUE 1

typedef struct {
    int to;
    int weight;
} Edge;

Edge graph[NODES][10] = {
    // BN = 0
    { {INV, 8}, {OBK, 4}, {SSD, 1}, {REP, 3}, {-1, -1} },
    // INV = 1
    { {BFM, 13}, {-1, -1} },
    // OBK = 2
    { {BN, 4}, {AUS, 7}, {-1, -1} },
    // AUS = 3
    { {OBK, 7}, {REP, 9}, {IVR, 5}, {-1, -1} },
    // SSD = 4
    { {BN, 1}, {SMN, 7}, {-1, -1} },
    // SMN = 5
    { {SSD, 7}, {IVR, 11}, {-1, -1} },
    // REP = 6
    { {BN, 3}, {AUS, 9}, {-1, -1} },
    // BFM = 7
    { {INV, 13}, {IVR, 3}, {-1, -1} },
    // IVR = 8
    { {AUS, 5}, {SMN, 11}, {BFM, 3}, {-1, -1} }
};

// Variables globales pour Dijkstra
int distance[NODES];
int visited[NODES];
int prev[NODES];

// Noms des stations pour l'affichage
const char* station_names[NODES] = {
    "Bonne Nouvelle",
    "Invalides",
    "Oberkampf",
    "Gare d'Austerlitz",
    "Strasbourg-St-Denis",
    "Saint-Michel Notre-Dame",
    "République",
    "Bibliothèque F. Mitterrand",
    "Ivry-sur-Seine"
};

int node_with_min_distance()
{
    int min_dist = INFINITY;
    int min_node = -1;
    
    for (int i = 0; i < NODES; i++)
    {
        if (!visited[i] && distance[i] < min_dist)
        {
            min_dist = distance[i];
            min_node = i;
        }
    }
    return min_node;
}

void dijkstra(int source, int destination)
{
    for (int i = 0; i < NODES; i++)
    {
        distance[i] = INFINITY;
        visited[i] = FALSE;
        prev[i] = -1;
    }
    distance[source] = 0;
   
    while (!visited[destination])
    {
        int u = node_with_min_distance();

        if (u == -1)
            break;

        if (u == destination)
        {
            visited[u] = TRUE;
            break;
        }

        visited[u] = TRUE;
    
        for (int i = 0; graph[u][i].to != -1; i++)
        {
            int v = graph[u][i].to;
            int w = graph[u][i].weight;

            if (!visited[v])
            {
                int alt = distance[u] + w;
                if (alt < distance[v])
                {
                    distance[v] = alt;
                    prev[v] = u;
                }
            }
        } 
    }
}

void afficher_chemin(int source, int destination)
{
    if (distance[destination] == INFINITY)
    {
        printf("Aucun chemin trouvé.\n");
        return;
    }

    // Reconstruire le chemin en remontant prev[]
    int chemin[NODES];
    int longueur = 0;
    
    int current = destination;
    while (current != -1)
    {
        chemin[longueur++] = current;
        current = prev[current];
    }

    // Afficher le chemin (inversé car on a remonté depuis la destination)
    printf("Chemin optimal (%d min) :\n", distance[destination]);
    for (int i = longueur - 1; i >= 0; i--)
    {
        printf("  %s", station_names[chemin[i]]);
        if (i > 0)
            printf(" ->\n");
    }
    printf("\n");
}

int main()
{
    int source = BN;
    int destination = IVR;
    
    dijkstra(source, destination);
    afficher_chemin(source, destination);
    
    return 0;
}
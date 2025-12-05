#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAXV 10
#define MAXE 50

typedef struct {
    int src, dest;
    double weight;
} Edge;

typedef struct {
    int V, E;
    Edge edges[MAXE];
} Graph;

// Ajoute une arête au graphe
void addEdge(Graph *g, int u, int v, double rate) {
    g->edges[g->E].src = u;
    g->edges[g->E].dest = v;
    g->edges[g->E].weight = -log(rate); // transformation Bellman-Ford arbitrage
    g->E++;
}

void detectArbitrage(Graph *g) {
    double dist[MAXV];
    int prev[MAXV];

    // 1. INIT
    for(int i = 0; i < g->V; i++) {
        dist[i] = DBL_MAX;
        prev[i] = -1;
    }
    dist[0] = 0;  // On choisit 0 = EUR comme source

    // 2. RELAXATIONS V-1 FOIS
    for(int i = 0; i < g->V - 1; i++) {
        for(int j = 0; j < g->E; j++) {
            int u = g->edges[j].src;
            int v = g->edges[j].dest;
            double w = g->edges[j].weight;

            if(dist[u] != DBL_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }

    // 3. DÉTECTION CYCLE NÉGATIF
    for(int j = 0; j < g->E; j++) {
        int u = g->edges[j].src;
        int v = g->edges[j].dest;
        double w = g->edges[j].weight;

        if(dist[u] + w < dist[v]) {
            printf("\n Arbitrage détecté ! Cycle négatif trouvé.\n");

            // Reconstruction du cycle
            int visited[MAXV] = {0};
            int cycle = v;

            // Trouver un sommet dans le cycle
            for(int i = 0; i < g->V; i++)
                cycle = prev[cycle];

            // Afficher le cycle
            printf("Cycle d'arbitrage potentiel : ");

            int start = cycle;
            while(1) {
                printf("%d → ", cycle);
                cycle = prev[cycle];
                if(cycle == start) break;
            }
            printf("%d\n", start);

            return;
        }
    }

    printf("\nAucun arbitrage détecté.\n");
}

int main() {
    Graph g;
    g.V = 3; // EUR, USD, JPY
    g.E = 0;

    // Exemple de taux (arbitrage réel)
    addEdge(&g, 0, 1, 1.10);    // EUR → USD
    addEdge(&g, 1, 2, 150.0);   // USD → JPY
    addEdge(&g, 2, 0, 0.0068);  // JPY → EUR

    detectArbitrage(&g);

    return 0;
}

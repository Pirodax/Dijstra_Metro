Algorithme  Dijkstra sert à résoudre le problème  du plus court chemin dans un graph à poids non negatifs. 

l’algorime fonctionne comme cela :
Soit un graphe avec une source (point de depart) noté S.

1. **Initialisation**
- `dist[S] = 0`
- Pour tout autre nœud `v`: `dist[v] = +∞`
- `prev[v] = null` (pour reconstruire le chemin)
- Ensemble des nœuds “non traités” dans un tableau non traités
1. **Choisir le prochain nœud**
- Prendre le nœud `u` non traité avec la **plus petite** `dist[u]`. Qui devient le chemin optimal temporaire .
- Si `dist[u] = +∞`, on peut arrêter : le reste est inatteignable.
- Marquer `u` comme **traité** (sa distance est maintenant optimale).
1. **“Relaxer” les arêtes sortantes**
    
    Pour chaque voisin `v` de `u` avec un poids `w(u,v)` :
    
- Calculer `alt = dist[u] + w(u,v)`
- Pour `dist[v]` la valeur la plus courte enregistré jusqu’à là.
- Si `alt < dist[v]` :
    - mettre `dist[v] = alt`
    - mettre `prev[v] = u`
    - mettre à jour `v` dans la file de priorité
1. **Répéter**
- Refaire 2) puis 3) jusqu’à ce que :
    - tous les nœuds soient traités, ou
    - tu aies traité la **destination** (si tu ne veux qu’un seul chemin), ou
    - la file soit vide.
    
    **5 . Reconstruire un chemin (optionnel)**
    
    Pour obtenir le chemin vers un nœud `T` :
    
- partir de `T`, puis suivre `prev[T]`, `prev[prev[T]]`, … jusqu’à `S`, et inverser la liste

Et voila pour l’algo concernant ça complexité:
Deux cas :

Avec une file de priorité (heap) : tas binaire

- `extract-min` : **O(log V)**
- `decrease-key` : **O(log V)** (ou équivalent en pratique)
- tu fais `extract-min` environ **V fois** → `V * log V`
- tu peux faire une mise à jour par arête (au pire) **E fois** → `E * log V`

Total : **O((V + E) log V)**

Sans heap : recherche linéaire du minimum

structure pas optimisé

- Tu mets tous les nœuds **pas encore visités** dans un **tableau**.
- À chaque tour, pour choisir `u`, tu dois **parcourir tout le tableau** et comparer les `dist[...]` pour trouver **le plus petit**.
- Comme tu regardes potentiellement **V nœuds** à chaque tour, ça coûte **O(V)** par tour (un balayage complet).

Et comme V+(V−1)+(V−2)+⋯+1=V(V+1)/2 en notation O donne O(v^2) qui est la complexité sans heap.

Flowshart : DE S A T

![Untitled diagram-2025-12-02-231838.png](attachment:d2f4d1eb-adee-461a-9f21-4044d75bd51e:Untitled_diagram-2025-12-02-231838.png)

Voici ce que j’ai demandé à ChatGPT :

Donne-moi le graphe qui simulera mon trajet jusqu’au nouveau campus de l’ESIEA en passant par les lignes de métro. Voici les chemins possibles pour y arriver avec le format :

**ligne | direction | arrêt de départ | -> temps (en min) -> | arrêt d’arrivée**.

On ne prend en compte que le temps passé dans le métro.

Chemin possible 1 :

8 | Balard | Bonne Nouvelle | -> 7 -> | Invalides | -> C | Massy | Invalides | -> 16 -> | Ivry-sur-Seine |

Chemin possible 2 :

9 | Mairie de Montreuil | Bonne Nouvelle | -> 4 -> | Oberkampf | -> 5 | Place d’Italie | Oberkampf | -> 7 -> | Gare d’Austerlitz | -> C | Place d’Italie | Brétigny | -> 6 -> | Ivry-sur-Seine |

Fais une recherche sur le web pour ajouter d’autres moyens pour aller à la station Ivry-sur-Seine en métro/RER et ajoute-les à la liste.

Réponses 

## Le graphe (prêt à “dijkstra-iser”)

### Nœuds (stations)

Je te propose ces IDs :

- `BN` = Bonne Nouvelle
- `INV` = Invalides
- `IVR` = Ivry-sur-Seine (RER C)
- `OBK` = Oberkampf
- `AUS` = Gare d’Austerlitz
- `SSD` = Strasbourg–Saint-Denis
- `SMN` = Saint-Michel Notre-Dame
- `REP` = République
- `BFM` = Bibliothèque François Mitterrand

### Arêtes (trajets) — format

`FROM --(ligne, direction, minutes)--> TO`

```
BN  --(M8, "Balard", 8)-->      INV
BN  --(M9, "Mairie de Montreuil", 4)--> OBK
BN  --(M9, "Mairie de Montreuil", 1)--> SSD
BN  --(M9, "Mairie de Montreuil", 3)--> REP

OBK --(M5, "Place d'Italie", 7)--> AUS
REP --(M5, "Place d'Italie", 9)--> AUS
SSD --(M4, "Bagneux – Lucie Aubrac", 7)--> SMN

AUS --(RER C, "via Bibliothèque F. Mitterrand", 5)--> IVR
SMN --(RER C, "via Bibliothèque F. Mitterrand", 11)--> IVR

INV --(RER C, "vers Bibliothèque F. Mitterrand", 13)--> BFM
BFM --(RER C, "vers Ivry-sur-Seine", 3)--> IVR

```

Voici le mermaid du graph pour qu’on y voit plus claire 

![image.png](attachment:d7121de4-2baf-47d6-8dc6-3fb5303d245c:image.png)

Représentation graphique du graph sur carte RATP

![repréntation_graph_map_metro.png](attachment:f4a5d336-f85e-4991-ab08-c80248f211d3:reprntation_graph_map_metro.png)

Voici le résultat :

![image.png](attachment:93285c2b-2c5a-4de6-8382-00c86333d2ff:image.png)

C’est donc ce chemin qui est le plus court.

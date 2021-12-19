Note: Here are my solutions that might help other students. I take no responsibility for the completeness of the solutions.

# Solutions for 

| Week                  | Problem                         | Points | Solution Description ([some are adapted from](https://github.com/chaehni/AlgoLab))                                         | Topic            |
| --------------------- | ------------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------- | -----------------|
| intro                 | Basic data types                | 100    | types                                                                                                             | |
| intro                 | BFS                             | 100    | standard BFS                                                                                                      | |
| intro                 | Build the sum                   | 100    | naive                                                                                                             | |
| intro                 | DFS                             | 100    | standard DFS                                                                                                      | |
| intro                 | Hello World                     | 100    | naive                                                                                                             | |
| intro                 | Maps                            | 100    | maps                                                                                                              | |
| intro                 | Sets                            | 100    | sets                                                                                                              | |
| intro                 | Sort                            | 100    | std::sort()                                                                                                       | |
| intro                 | Strings                         | 100    | strings                                                                                                           | |
| intro                 | Vectors                         | 100    | vectors                                                                                                           | |
| 1                     | Build the sum                   | 100    | naive linear                                                                                                      | |
| 1                     | Dominoes                        | 100    | naive linear                                                                                                      | |
| 1                     | Even Pairs                      | 100    | Partial sums, binomial coefficient                                                                                | |
| 1                     | Even Matrices                   | 100    | dimension reduction & partial sums                                                                                | |
| PotW 2                | Deck of Cards                   | 100    | sliding window                                                                                                    | |
| 2                     | Beach Bars                      | 100    | partial sums, sliding window                                                                                      | DP |
| 2                     | Burning Coins                   | 100    | DP, 2 tables                                                                                                      | |
| 2                     | Search Snippets                 | 100    | ordering words by occurences, sliding window                                                                      | |
| 2                     | The Great Game                  | 100    | recursion & memoization, 2 tables                                                                                 | DP |
| PotW 3                | From Russia with Love           | 100    | recursion & memoization                                                                                           | DP |
| 3                     | Hit                             | 100    | intersection                                                                                                      | CGAL |
| 3                     | First hit                       | 100    | intersection, shuffle input and clip ray to avoid costly intersections                                            | CGAL |
| 3                     | Hiking Maps                     | 100    | orientation test & sliding window (similar to search snippets)                                                    | CGAL |
| 3                     | Antenna                         | 100    | Min_circle, with two different kernels                                                                            | CGAL |
| PotW 4                | Defensive Line                  | 100    | sliding window & DP                                                                                               | DP |
| 4                     | Ant Challenge                   | 100    | Kruskal per species, then Dijkstra                                                                                | Boost |
| 4                     | Buddy Selection                 | 100    | perfect matching                                                                                                  | Boost |
| 4                     | First steps with BGL            | 100    | Kruskal & Dijkstra                                                                                                | Boost |
| 4                     | Important Bridges BGL           | 100    | biconnected components, count edges per component                                                                 | Boost |
| PotW 5                | Motorcycles                     | 100    | sorting by increasing slope and then linear pass to test for intersections                                        | CTAL |
| 5                     | Boats                           | 100    | greedy, version of earliest deadline first                                                                        | Greedy |
| 5                     | Attack of the Clones            | 100    | greedy, earliest deadline first in a circle                                                                       | |
| 5                     | San Francisco                   | 100    | binary search over recursive function to find smallest k to achieve x points                                      | |
| 5                     | Asterix and the tour of Gaul    | 100    |                                                                                                  | |
| PotW 6                | Tracking                        | 100    | Shortest Path - make multiple layers to force dijkstra to use a path segment                                      | BGL - Dijkstra |
| 6                     | Shopping Trip                   | 100    | max flow, adding edges between junctions in both directions, and a weight map for cap to sink                     | BGL - Maxflow |
| 6                     | Kingdom Defence                 | 100    | max flow with edge demand (min capacity)                                                                          | BGL - Maxflow |
| 6                     | Tiles                           | 100    | max flow matrix with odd even, edges between even and odd neighbors | BGL - Maxflow |
| 6                     | Knights                         | 100    | Maxflow | BGL - Maxflow |
| PotW 7                | Octopussy                       | 100    | greedy, order by finish time, and use recursive function for childs                                               | Greedy |
| 7                     | What is the Maximum             | 100    | linear programming intro, with changing max. function to minimizeing opposite                                     | LP |
| 7                     | Diet                            | 100    | linear programming                                                                                                | LP |
| 7                     | Radiation                       | 100    | LP, similar to slides                                                                                             | LP |
| 7                     | Inball                          | 100    | LP, calculate norm as further point / radius, take the negative as objective -> maximize                          | LP |
| PotW 8                | Surveillance Photographs        | 100    | max flow on graph with two layers (photo connect to lower layer)                                                  | BGL - Maxflow |
| 8                     | Bistro                          | 100    | voronoi using Delaunay triangulation                                                                              | CGAL - Voronoi |
| 8                     | H1N1                            | 100    | Delaunay/voronoi duality and precomputing largest escape path                                                     | CGAL - Voronoi |
| 8                     | Germs                           | 100    | Delaunay for nearest neighbour graph                                                                              | CGAL - Voronoi |
| 8                     | Clues                           | 100    | computing graph 2-coloring and connected components simultaneously using Delaunay triangulation                   | CGAL - |
| PotW 9                | Legions                         | 100    | LP, maximize time                                                                                                 | LP |
| 9                     | Algocoon                        | 100    | simpel maxflow, iterate over all possible i, i+1 maxflows, take min                                               | BGL - Maxflow |
| 9                     | Real Estate Market              | 100    | max flow (invert cost by maxbid - bid per edge)                                                                   | BGL - Maxflow |
| 9                     | Placing Knigths                 | 100    | max matching of non-conflicting -> Invert to max possible - matching conflicting                                  | BGL - Matching |
| 9                     | Casino Royale                   | 100    | min cost max flow, space-time graph (see Carsharing)                                                              | BGL - Maxflow |
| PotW 10               | Idefix                          | 100    | Delaunay and Union Find                                                                                           | CGAL - Voronoi  & UF|
| 10                    | World Cup                       | 100    | Delaunay to find relevant contour lines & LP to maximize profit under constraints                                 | CGAL - Voronoi & LP|
| 10                    | Asterix in switzerland          | 100    | MaxFlow - check if max flow = possible flow from source                                                           | BGL - Maxflow |
| 10                    | Chariot Race (                  | 100    | recursion and memoization, passing information if current node is covered by parent                               | |
| 10                    | New York                        | 100    | DFS over all trees, for every node discovered update node m hops above                                            | |
| PotW 11               | Fleetrace                       | 100    | minimum cost bipartite matching                                                                                   | |
| 11                    | Return of the Jedi              | 100    | finding 2nd most optimal spanning tree, by manually creating it with uf                                           | |
| 11                    | Lestrase                        | 100    | Delaunay for nearest vertex, than LP                                                        | |
| 11                    | Hand                            | 100    | Delaunay, Creating MST, Creating Clusters, then binary search                                                        | |
| 11                    | Fighting Pits of Meereen        | ---    | ""                                                        | |
| PotW 12               | The Iron Islands                | 100    | Sliding window                                                                                                    | |
| 12                    | India                           | 100    | min cost max flow, binary search on number of suitcases to find maximum that still respects budget (see Marathon) | |
| 12                    | Hong Kong                       | 100    | Delaunay/voronoi duality and precomputing max clearance for every triangle (see H1N1)                             | |
| 12                    | Carsharing                      | 100    | min cost max flow with a space-time graph and clever edge weights                                                 | |
| 12                    | Moving Books                    | 100    | greedy, in every round everyone picks the heaviest box he can                                                     | |
| PotW 13               | Testex Lannister                | 55    |                                                                                                                   | |
| 13                    | Revenge of the Sith             | 100    | Delaunay and union find to find the largest suitable set of connected planets                                     | CGAL - Delaunay |
| 13                    | Evolution                       | 100    | binary search on each interval found by DFS                                                                       | |
| 13                    | Punch                           | 100    | dynamic programming, 2D table with pairs,                                                                         | DP |
| 13                    | Marathon                        | 100    | multiple max flow min cost & binary search to find the optimal flow                                               | |
| PotW 14               | On Her Majesty's Secret Service | 100    | minimum bottleneck matching, minimizing longest edge in bipartite graph                                           | |

# My solutions for 

| Week                  | Problem                         | Points | Solution Description ([adapted from](https://github.com/chaehni/AlgoLab))                                         | Topic            |
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
| 5                     | Attack of the Clones            | ---    | greedy, earliest deadline first in a circle                                                                       | |
| 5                     | San Francisco                   | 100    | binary search over recursive function to find smallest k to achieve x points                                      | |
| 5                     | Asterix and the tour of Gaul    | ---    |                                                                                                  | |
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
| 8                     | H1N1                            | ---    | Delaunay/voronoi duality and precomputing largest escape path                                                     | | |
| 8                     | Germs                           | ---    | Delaunay for nearest neighbour graph                                                                              | |
| 8                     | Clues                           | 100    | computing graph 2-coloring and connected components simultaneously using Delaunay triangulation                   | |
| PotW 9                | Legions                         | ---    |                                                                                                                   | |
| 9                     | Algocoon                        | ---    | max flow / min cut with multiple min cuts                                                                         | |
| 9                     | Real Estate Market              | ---    | min cost matching                                                                                                 | |
| 9                     | Placing Knigths                 | ---    | - | |
| 9                     | Casino Royale                   | ---    | min cost max flow, space-time graph (see Carsharing)                                                              | |
| PotW 10               | Idefix                          | ---    |                                                                                                                   | |
| 10                    | World Cup                       | ---    | Delaunay to find relevant contour lines & LP to maximize profit under constraints                                 | |
| 10                    | Asterix in switzerland          | ---    | "" | |
| 10                    | Chariot Race (                  | 100    | recursion and memoization, passing information if current node is covered by parent                               | |
| 10                    | New York                        | ---    | DFS over all trees, for every node discovered update node m hops above                                            | |
| PotW 11               | Fleetrace                       | ---    | minimum cost bipartite matching                                                                                   | |
| 11                    | Return of the Jedi              | ---    | finding 2nd most optimal spanning tree using Prim & DFS                                                           | |
| 11                    | Lestrase                        | ---    | ""                                                        | |
| 11                    | Hand                            | ---    | ""                                                        | |
| 11                    | Fighting Pits of Meereen        | ---    | ""                                                        | |
| PotW 12               | The Iron Islands                | ---    |                                                                                                                   | |
| 12                    | India                           | ---    | min cost max flow, binary search on number of suitcases to find maximum that still respects budget (see Marathon) | |
| 12                    | Hong Kong                       | ---    | Delaunay/voronoi duality and precomputing max clearance for every triangle (see H1N1)                             | |
| 12                    | Carsharing                      | ---    | min cost max flow with a space-time graph and clever edge weights                                                 | |
| 12                    | Moving Books                    | ---    | greedy, in every round everyone picks the heaviest box he can                                                     | |
| PotW 13               | Testex Lannister                | ---    |                                                                                                                   | |
| 13                    | Revenge of the Sith             | ---    | Delaunay and union find to find the largest suitable set of connected planets                                     | |
| 13                    | Evolution                       | ---    | binary search on each interval found by DFS                                                                       | |
| 13                    | Punch                           | 100    | dynamic programming, 2D table with pairs,                                                                         | DP |
| 13                    | Marathon                        | ---    | multiple max flow min cost & binary search to find the optimal flow                                               | |
| PotW 14               | On Her Majesty's Secret Service | ---    | minimum bottleneck matching, minimizing longest edge in bipartite graph                                           | |

# older solutions

| Week                  | Problem                         | Points | Solution                                                                                                          |
| --------------------- | ------------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------- |
| PotW 3 (2018)         | Magician and the Coin           | 100    | recursion & memoization                                                                                           |
| old 3                     | Almost antenna                  | 100    | Min_circle, support points                                                                                        |
| old 4                     | Building a Graph                | 100    | Kurskal, Dijkstra                                                                                                 |
| old 4                     | Shortest Paths                  | 100    | Dijkstra                                                                                                          |
| old 5                     | Ligth at the Museum             | 100    | split & list, brute force all switch configurations                                                               |
| old 5                     | High School Teams               | 100    | split & list, brute force all combinations with at most k refs, for those brute force all team combinations       |
| old 5 (2019)              | Planks                          | 100    | Split & List with to bits per plank                                                                               |
| PotW 6 (2018 & 2019)  | Planet Express                  | 100    | strong components & Dijkstra                                                                                      |
| old 6                     | Coin Tossing                    | 100    | max flow, making sure claimed scores and flow match number of games                                               |
| old 6                     | Tetris                          | 100    | max flow with splitting nodes into in- and out-nodes (vertex capacity)                                            |
| old 6 (2019)              | London                          | 100    | max flow, edges between front/back letter combinations                                                            |
| 7                     | Portfolios                      | ---    | quadratic programming, minimize over variance matrix                                                              | |
| PotW 8 (2019)         | Cantonal Courier                | 100    | max flow                                                                                                          |
| old 8                     | Graypes                         | 100    | Delaunay triangulation, taking shortest edge                                                                      |
| PotW 9 (2018 & 2019)  | Suez                            | 100    | find constraints/objective and solve with LP                                                                      |
| old 9                     | Satellites                      | 100    | max cardinality matching in bipartite graph & König algorithm                                                     |
| old 9                 | Canteen                         | 100    | min cost max flow, days as nodes and edges between days as fridge                                                 |
| 10                    | New Tiles                       | ---    | Cancer to implement                                                                                               |
| 10                    | Light the Stage                 | 100    | Delaunay for nearest neighbour & trying out all possible collisions                                               |
| 10                    | Poker Chips                     | 100    | recursion with insane 5D memoization table                                                                        |
| 11                    | The Empire Strikes Back         | 100    | Delaunay for finding max radius per shot, then LP for solving for required energy                                 |
| 11                    | Planks                          | 100    | Split & List with to bits per plank                                                                               |
| 11 (2019)             | DHL                             | 100    | DP making use of the nature of the cost function                                                                  |
| 12                    | Ligh Pattern                    | 100    | DP with linear table and two numbers per entry for normal and inverted lights                                     |
| 12 (2019)             | Asterix and the Roman Lines     | 100    | LP                                                                                                                |
| 13                    | Bob's Burden                    | 100    | Dijkstra for finding shortest path between 3 vertices & modelling node weight with in- and out-nodes              |
| 13                    | Corbusier                       | 100    | simple DP with 2D table                                                                                           |
| 13                    | Cantonal Courier                | 100    | max flow                                                                                                          |
| 13 (2019)             | Phantom Menace                  | 100    | max flow for finding maximal vertex-disjoint paths                                                                |

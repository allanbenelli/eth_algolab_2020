//std
#include <iostream>
#include <vector>

// BGL
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, allow_parallel_edge_tag, property<edge_weight_t, int>> Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef boost::graph_traits<Graph>::edge_descriptor            edge_desc;

void testcase(){
    int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
    Graph species_graphs[s];
    Graph F(n);
    WeightMap species_wm[s];
    WeightMap wmf = get(edge_weight, F);

    for (int i = 0; i < e; i++){
        int t1, t2; cin >> t1 >> t2;
        for (int j = 0; j < s; j++){
            species_wm[j] = get(edge_weight, species_graphs[j]);
            int temp; cin >> temp;
            edge_desc e = add_edge(t1, t2, species_graphs[j]).first;
            species_wm[j][e] = temp;
        }
    }

    // waste the the hive locations
    for (int i = 0; i < s; i++){
        int temp; cin >> temp;
    }
    // run kruskal for all species and add all edges to the final graph
    for(int i = 0; i < s; ++i){
        vector<edge_desc> mst;
        kruskal_minimum_spanning_tree(species_graphs[i], back_inserter(mst));
        for (auto k: mst){
            edge_desc e = add_edge(source(k, species_graphs[i]), target(k, species_graphs[i]), F).first;
            wmf[e] = get(edge_weight_t(), species_graphs[i], k);
        }
    }

    vector<int> dist_map(n);
    dijkstra_shortest_paths(F, a, distance_map(make_iterator_property_map(dist_map.begin(), get(vertex_index, F))));

    cout << dist_map[b] << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
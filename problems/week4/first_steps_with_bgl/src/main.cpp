#include <vector>
#include <iostream>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;

using namespace std;

void testcase(){
    int n, m; cin >> n >> m;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    vector<edge_desc> mst;
    for(int i = 0; i < m; ++i){
        int u, v, w; cin >> u >> v >> w;
        edge_desc e = boost::add_edge(u, v, G).first;
        weights[e] = w;
    }

    boost::kruskal_minimum_spanning_tree(G, back_inserter(mst));
    int sum = 0;
    for(vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it){
        sum += weights[*it];
    }

    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

    auto d = max_element(dist_map.begin(), dist_map.end());

    cout << sum << " " << *d << "\n";
}

int main(){
    int t; cin >> t;
    while(t--) testcase();
}
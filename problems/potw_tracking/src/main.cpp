#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void run(){
    int n, m, k, x, y; std::cin >> n >> m >> k >> x >> y;
    weighted_graph G(n*(k+1)); // idea solve with multiple layers of graph
    weight_map weights = boost::get(boost::edge_weight, G);

    edge_desc e;
    for(int i = 0; i < m; ++i){
        int a, b, c, d; std::cin >> a >> b >> c >> d;
        for(int j = 0; j < k; ++j){
            if(d){
                e = boost::add_edge(a+(j*n),b+((j+1)*n), G).first; weights[e] = c;
                e = boost::add_edge(b+(j*n),a+((j+1)*n), G).first; weights[e] = c;
            } else{
                e = boost::add_edge(a+(j*n),b+(j*n), G).first; weights[e] = c;
            }
        }
        e = boost::add_edge(a+(k*n),b+(k*n), G).first; weights[e] = c;
    }
    std::cout << dijkstra_dist(G, x, y+(k*n)) << "\n"; 
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) run();
}
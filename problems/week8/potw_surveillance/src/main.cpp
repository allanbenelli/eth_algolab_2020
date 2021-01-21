#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

using namespace std;

void run(){
    int n, m, k, l; cin >> n >> m >> k >> l;
    map<int,int> stations, locations;
    for(int i = 0; i < k; ++i){
        int s; cin >> s;
        stations[s]++;
    }
    for(int i = 0; i < l; ++i){
        int l; cin >> l;
        locations[l]++;
    }
    vector<map<int, int>> streets(n);
    for(int i = 0; i < m; ++i){
        int x, y; cin >> x >> y;
        streets[x][y]++;
    }

    graph G(n*2);
    edge_adder adder(G);
    const vertex_desc source = boost::add_vertex(G);
    const vertex_desc sink = boost::add_vertex(G);
    for(auto it=stations.begin(); it != stations.end(); ++it){
        adder.add_edge(source, it->first, it->second); //first where do we start
        adder.add_edge(n+it->first, sink, it->second); //secondly, how much photos can be returned here
    }
    for(auto it=locations.begin(); it != locations.end(); ++it){ // photo locations i to i+n
        adder.add_edge(it->first, n + it->first, it->second); 
    }
    int high_c = 1 << 20;
    for(int i = 0; i < n; ++i){
        for(auto it : streets[i]){
            adder.add_edge(i, it.first, high_c);
            adder.add_edge(i+n, n+it.first, it.second);
            //cout << "from " << i+n <<" to: " << n+it.first << " cap:" <<it.second << endl;
        }
    }
    long flow = boost::push_relabel_max_flow(G, source, sink);

    cout << flow << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
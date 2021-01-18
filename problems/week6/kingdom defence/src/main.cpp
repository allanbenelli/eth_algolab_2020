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

void testcase(){
    int l,p; cin >> l >> p;
    graph G(l);
    edge_adder adder(G);
    const vertex_desc source = boost::add_vertex(G);
    const vertex_desc sink = boost::add_vertex(G);
    vector<int> resources(l, 0);
    for(int i = 0; i < l; ++i){
        int stationed, needed; cin >> stationed >> needed;
        resources[i] = stationed-needed;
    }
    int flow_needed = 0;
    for(int i = 0; i < p; ++i){
        int u, v, min_c, max_c; cin >> u >> v >> min_c >> max_c;
        resources[u] -= min_c;
        resources[v] += min_c;
        adder.add_edge(u,v,max_c-min_c);
    }
    for(int i = 0; i < l; ++i){
        if(resources[i] > 0) adder.add_edge(source, i, resources[i]);
        else if(resources[i]<0){
            adder.add_edge(i, sink, -resources[i]);
            flow_needed -= resources[i]; 
        }
    }
    long max = boost::push_relabel_max_flow(G,source, sink);

    if(max >= flow_needed) cout << "yes\n";
    else cout << "no\n";
    


}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
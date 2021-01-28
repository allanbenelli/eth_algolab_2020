#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>


// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef traits::vertex_descriptor                               v_desc;

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
    return e;
  }
};


using namespace std;
void run(){
    int N, M, B, S, F; cin >> N >> M >> B >> S >> F;
    graph G(N);
    edge_adder adder(G);  
    auto c_map = boost::get(boost::edge_capacity, G);
    const v_desc source = boost::add_vertex(G);

    for(int i = 0; i < M; ++i){
        int x, y, d, e; cin >> x >> y >> d >> e;
        adder.add_edge(x,y,e,d);
        //adder.add_edge(b,a,c,d);
    }
    edge_desc e_keep = adder.add_edge(source, S, 1, 0);
    boost::successive_shortest_path_nonnegative_weights(G, source, F);

    long cost = boost::find_flow_cost(G);
    long flow = boost::push_relabel_max_flow(G, S, F);
    if(B<cost){
        cout << "0\n"; return;
    }
    long l = 1;
    long r = flow;
    long mid = flow;
    while(l < r){
        mid = l+(r-l+1)/2;
        c_map[e_keep] = mid;
        boost::successive_shortest_path_nonnegative_weights(G, source, F);
        long costs = boost::find_flow_cost(G);
        if(B < costs){
            r = mid -1;
        } else{
            l = mid;
        }
    }
    cout << r << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
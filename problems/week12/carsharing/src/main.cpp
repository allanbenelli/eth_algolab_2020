#include <iostream>
#include <vector>
#include <set>
#include <map>

#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
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
using namespace std;

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
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
  }
};

struct Booking{
    int s, t, d, a, p;
};

void run(){
    int N, S; cin >> N >> S;
    vector<int> L(S);
    for(int i = 0; i < S; i++){
        cin >> L[i];
    }
    const int MAXL = 100;
    const int MAXT = 100000;
    const int MAXP = 100;
    const int INF = MAXL*S;
    vector<Booking> B;
    vector<set<int>> times(S);
    for(int i = 0; i < S; ++i){
        times[i].insert(0);
        times[i].insert(MAXT);
    }
    for(int i = 0; i < N; ++i){
        int s, t, d, a, p; cin >> s >> t >> d >> a >> p;
        s--; t--; // 1-based indexing
        times[s].insert(d); times[t].insert(a);
        B.push_back({s,t,d,a,p});
    }
    vector<map<int,int>> M(S); // coordinate compression
    vector<int> psum(S+1);
    for(int i = 0; i < S; ++i){
        int j = 0;
        for(auto t: times[i]){
            M[i][t] = j;
            j++;
        }
        psum[i+1] = psum[i] + M[i].size();
    }
    int vertices = psum.back();
    int source = vertices;
    int sink = vertices + 1;
    graph G(vertices+2);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    // graph construction
    for(int i = 0; i < S; ++i){
        adder.add_edge(source, psum[i], L[i], 0);
        adder.add_edge(psum[i+1]-1, sink, INF, 0);
        int it = -1, lastt = 0;
        for(auto &t:times[i]){
            if(it != -1){
                adder.add_edge(psum[i]+it, psum[i]+it+1, INF, MAXP*(t-lastt));
            } 
            it++; lastt = t;
        }
    }
    for(int i = 0; i < N; ++i){
        adder.add_edge(psum[B[i].s] + M[B[i].s][B[i].d], psum[B[i].t] + M[B[i].t][B[i].a], 1, (MAXP*(B[i].a - B[i].d)-B[i].p));
    }
    boost::successive_shortest_path_nonnegative_weights(G, source, sink);
    int profit = boost::find_flow_cost(G);
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {

        s_flow += c_map[*e] - rc_map[*e];     
    }
    cout << MAXT*MAXP*s_flow-profit << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
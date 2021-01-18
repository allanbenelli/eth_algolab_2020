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
    int w,h; cin >> w >> h;
    graph G(w*h);
    edge_adder adder(G);
    const vertex_desc source = boost::add_vertex(G);
    const vertex_desc sink = boost::add_vertex(G);
    vector<vector<int>> even(h, vector<int>(w, -1));
    int out = 0, in = 0;
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            char a; cin >> a;
            if(a == '.'){
                if((i+j) % 2 == 0){
                    in++;
                    adder.add_edge(source, (w*i)+j, 1);
                    even[i][j] = 1;
                } else{
                    out++;
                    adder.add_edge((w*i)+j, sink, 1);
                    even[i][j] = 0;
                }
            }
        }
    } 
    
    //add intra edeges
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            if (i < h-1){
                // TODO: Correct the indexes for adding with w*i+j
                if(even[i][j] == 1 && even[i+1][j] == 0){ adder.add_edge((i)*(w)+j, (i+1)*(w)+j, 1);} // from here to the bottom
                else if(even[i][j] == 0 && even[i+1][j] == 1){ adder.add_edge((i+1)*(w)+j, (i)*(w)+j, 1);} // from the bottom to this one
            }
            if(j < w-1){
                if(even[i][j] == 1 && even[i][j+1] == 0){ adder.add_edge((i)*(w)+(j), (i)*(w)+(j+1), 1);} // from here to the right
                else if(even[i][j] == 0 && even[i][j+1] == 1){  adder.add_edge((i)*(w)+(j+1), (i)*(w)+(j), 1);} // from the right to this one
            }
        }
    }
    if(in!=out){
        cout << "no\n"; return; //fasten up and sanity check
    }
    int tiles = boost::push_relabel_max_flow(G,source, sink);
    //cout << "tiles: " << tiles << endl; 
    if(tiles == out) cout << "yes\n";
    else cout << "no\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
    return 0;
}
#include <iostream>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>


using namespace std;

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
    //cout << "Adding from|to|cap " << from << " | " << to << " | " << capacity << "\n";
  }
};
int myIndex(int m, int x, int y, int plus){
    //y row idx, x col idx
    return 2*(y*m+x)+plus;
}

void testCase(){
    //m = cols, n = rows
    int m, n, k, c;
    cin >> m >> n >> k >> c;
    int nodes = 2*m * n; //double it up in order to use capacities of intersection
    graph G( nodes+2);
    edge_adder adder(G);
    if(m == 0 || n == 0) {
        cout << k << "\n";
        return;
    }
    int src = nodes;
    int sink = src + 1;

    // source to knights positions
    for(int i = 0; i < k; i++){
        int x,y;
        cin >> x >> y;
        int to = myIndex(m,x,y,0);
        //cout << "knight: " << i << " pos: " << to << "\n";
        adder.add_edge(src,to,1);
    }

    // create intra grid
    for(int i = 0; i<m; i++){ // cols
        for(int j = 0; j<n; j++){ // rows
            //add capacity
            int v_idx = myIndex(m,i,j,0);
            adder.add_edge(v_idx, v_idx+1, c);

            //intra connections
            if(i<m-1){ // to the right
                adder.add_edge(v_idx+1, myIndex(m,i+1,j,0), 1);
            }
            if(j<n-1){ // to the bottom
                adder.add_edge(v_idx+1, myIndex(m,i,j+1,0), 1);
            }
            if(i>0){ // to the left
                adder.add_edge(v_idx+1, myIndex(m,i-1,j,0), 1);

            }
            if(j>0){ // to the top
                adder.add_edge(v_idx+1, myIndex(m,i,j-1,0), 1);

            }
        }
    }
    // create exit points to sink
    //cout << "cornes: \n";
    //corners capacity = 2
    adder.add_edge(myIndex(m,0,0,1),sink, 2);
    adder.add_edge(myIndex(m,m-1,0,1),sink, 2);
    adder.add_edge(myIndex(m,0,n-1,1),sink, 2);
    adder.add_edge(myIndex(m,m-1,n-1,1),sink, 2);

    //cout << "left and right \n";
    // left and right
    for(int i = 1; i< n-1; i++){ // trav row
        adder.add_edge(myIndex(m,0,i,1), sink, 1); // to the left
        adder.add_edge(myIndex(m,m-1,i,1), sink, 1); // to the rigth       
    }
    //cout << "top and bottom \n";
    // top and bottom
    for(int j = 1; j< m-1; j++){ // trav cols
        adder.add_edge(myIndex(m,j,0,1), sink, 1); // to the top
        adder.add_edge(myIndex(m,j,n-1,1), sink, 1); // to the bottom
    }


     
  long flow = boost::push_relabel_max_flow(G, src, sink);
  std::cout << flow << "\n";

/*
     // Retrieve the capacity map and reverse capacity map
  const auto c_map = boost::get(boost::edge_capacity, G);
  const auto rc_map = boost::get(boost::edge_residual_capacity, G);

  // Iterate over all the edges to print the flow along them
  auto edge_iters = boost::edges(G);
  for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
    const edge_desc edge = *edge_it;
    const long flow_through_edge = c_map[edge] - rc_map[edge];
    
    std::cout << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
              << " runs " << flow_through_edge
              << " units of flow (negative for reverse direction). cap: " << c_map[edge] << "\n";
    
  }
  */
}


int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; i++)
    {
        testCase();
    }
}
#include <iostream>
#include <vector>
#include <algorithm>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property> Graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

void run(){
    int N, M, A, S, C, D; cin >> N >> M >> A >> S >> C >> D;
    weighted_graph G(N);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    for(int i = 0; i < M; ++i){
        char w; int x, y, z; cin >> w >> x >> y >> z;
        e = boost::add_edge(x, y, G).first; weights[e] = z;
        if(w=='L'){
            e = boost::add_edge(y,x,G).first; weights[e] = z;
        }
    }
    vector<vector<int>> distmap(A, vector<int>(N));
    for(int i = 0; i < A; ++i){
        int a; cin >> a;
        boost::dijkstra_shortest_paths(G, a,
            boost::distance_map(boost::make_iterator_property_map(
            distmap[i].begin(), boost::get(boost::vertex_index, G))));
    }
    vector<vector<int>> distances(A, vector<int>(S));
    for(int i = 0; i < S; ++i){
        int s; cin >> s;
        for(int j = 0; j < A; ++j){
            distances[j][i] = distmap[j][s];
        }
    }
    int low = 0, high = INT_MAX;
    while (low < high){
        int mid = low + (high-low)/2;
        Graph G2(A+C*S);
        for(int i = 0; i < A; ++i){
            for(int j = 0; j < S; j++){
                if(distances[i][j] == INT_MAX) continue;
                for(int c = 0; c < C; ++c){
                    if(distances[i][j] +(c+1)*D <= mid) // we can reach it in time mid
                        boost::add_edge(i, A+c*S + j, G2);
                }
            }
        }
        vector<vertex_desc> mate_map(A+C*S);  // exterior property map

        boost::edmonds_maximum_cardinality_matching(G2,
            boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
        int matching_size = boost::matching_size(G2,
            boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
        if(matching_size == A) high = mid;
        else low = mid+1;
    }
    

    cout << low << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
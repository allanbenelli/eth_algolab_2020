// STL includes
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    std::vector<vertex_desc> mate_map(n);  // exterior property map
    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

    boost::edmonds_maximum_cardinality_matching(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    return matching_size;
}
bool comm_int(const vector<string>& s1, const vector<string>& s2, const int f){
    int i = 0, j = 0, common = 0;
    while(i < s1.size() && j < s2.size()){
        if (s1[i] == s2[j]){
            common++;
            i++;
            j++;
        } else if (s1[i] < s2[j]) {
            i++;
        } else j++;
    }
    return common > f;
}

void run(){
    int n, c, f; cin >> n >> c >> f;
    vector<vector<string>> stud(n, vector<string>(c));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            cin >> stud[i][j];
        } sort(stud[i].begin(), stud[i].end());
    }
    graph G(n);
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; ++j){
            if(comm_int(stud[i], stud[j], f)) boost::add_edge(i,j,G);
        }
    }
    int m = maximum_matching(G);
    if(m*2 == n) cout << "not optimal\n"; else cout << "optimal\n";

}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();

}
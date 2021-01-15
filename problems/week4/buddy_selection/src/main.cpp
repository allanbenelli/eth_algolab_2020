// STL includes
#include <iostream>
#include <vector>
#include <string>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    std::vector<vertex_desc> mate_map(n);  // exterior property map
    boost::edmonds_maximum_cardinality_matching(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    return matching_size;

}
int common_interest(const vector<string> &s1, const vector<string> &s2){
    int i = 0, j = 0, common = 0;
    while (i < s1.size() && j < s2.size())
    {
        if(s1[i]==s2[j]){
            common++;
            i++;
            j++;
        }
        else if(s1[i]<s2[j]){
            i++;
        } else j++;
    }
    return common;
    
}
void testcase(){
    int n,c,f; cin >> n >> c >> f;
    graph G(n);
    vector<vector<string>> students(n, vector<string>(c));
    for(int i = 0; i < n ; ++i){
        for(int j = 0; j < c; ++j) cin >> students[i][j];
        sort(students[i].begin(), students[i].end());
    }

    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            int c = common_interest(students[i], students[j]);
            if( c > f) boost::add_edge(i,j, G);
        }
    }
    /*
    Read in the characteristics, make a mapping, create graph
    */
    int max = maximum_matching(G);
    bool perfect = max*2 == n;
    cout << (perfect ? "not optimal" : "optimal") << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
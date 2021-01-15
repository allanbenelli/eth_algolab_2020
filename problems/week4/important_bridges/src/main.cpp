#include <boost/config.hpp>
#include <vector>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>

namespace boost{
    struct edge_component_t{
        enum{
            num = 555
        };
        typedef edge_property_tag kind;
    } edge_component;
}

using namespace std;
using namespace boost;
typedef adjacency_list< vecS, vecS, undirectedS, no_property,
    property< edge_component_t, std::size_t > >
    graph_t;
typedef graph_traits< graph_t >::vertex_descriptor vertex_t;

void testcase(){
    int n, m; cin >> n >> m;
    graph_t g(n);
    for(int i = 0; i < m; ++i){
        int x,y; cin >> x >> y;
        add_edge(x, y, g);
    } 

    property_map< graph_t, edge_component_t >::type component = get(edge_component, g);
    size_t num_comps = biconnected_components(g, component);
    vector<int> component_edges(num_comps, 0);
    graph_traits< graph_t >::edge_iterator ei, ei_end;

    for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
        component_edges[component[*ei]]++;
    }
    vector<pair<int,int>> results;
    for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
        if(component_edges[component[*ei]] == 1){
            int x = source(*ei, g);
            int y = target(*ei, g);
            results.push_back(make_pair(min(x,y), max(x,y)));
        }
    }
    sort(results.begin(), results.end());
    cout << results.size() << "\n";
    if(results.size()){
        for(int i = 0; i < results.size(); ++i){
            cout << results[i].first << " " << results[i].second << "\n";
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
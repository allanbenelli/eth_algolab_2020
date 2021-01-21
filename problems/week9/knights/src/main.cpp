#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void run(){
    int n; std::cin >> n;
    VVI board(n, VI(n, 0));
    int possible_positions = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; j++){
            int placeable; std::cin >> placeable;
            board[i][j] = placeable;
            possible_positions+=placeable;
        }
    }
    graph G(n*n);

    /* Idea: we only add edges for possible knights locations
        Add only if possible, and add only the lower for edges from this:
         _ _
       |__|__|
       | _|_ |

    */
    // left down
    for(int i = 0; i < n-1; ++i){
        for(int j = 2; j < n; ++j){
            if(board[i][j]&&board[i+1][j-2]){
                boost::add_edge(i*n+j, (i+1)*n+j-2, G);
            } 
        }
    }
    // down left
    for(int i = 0; i < n-2; ++i){
        for(int j = 1; j < n; ++j){
            if(board[i][j]&&board[i+2][j-1]){
                boost::add_edge(i*n+j, (i+2)*n+j-1, G);
            } 
        }
    }
    // down right
    for(int i = 0; i < n-2; ++i){
        for(int j = 0; j < n-1; ++j){
            if(board[i][j]&&board[i+2][j+1]){
                boost::add_edge(i*n+j, (i+2)*n+j+1, G);
            } 
        }
    }
    // to right down
    for(int i = 0; i < n-1; ++i){
        for(int j = 0; j < n-2; ++j){
            if(board[i][j]&&board[i+1][j+2]){
                boost::add_edge(i*n+j, (i+1)*n+j+2, G);
            } 
        }
    }

    std::vector<vertex_desc> mate_map(n*n);  // exterior property map
    boost::edmonds_maximum_cardinality_matching(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
        boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    std::cout << possible_positions-matching_size << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) run();
}

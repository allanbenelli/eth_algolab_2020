#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<vector<int>> VVI;

void run(){
    int n, m, k; cin >> n >> m >> k;
    VI temp(n);
    VVI sails(n);
    for(int i = 0; i < n; ++i){
        cin >> temp[i];
    }
    for(int i = 0; i < n -1; ++i){
        int u, v; cin >> u >> v;
        sails[u].push_back(v);
    }
    stack<int> s; s.push(0);
    vector<int> leg;
    multiset<int> temp_set;
    vector<bool> visited(n,false);
    vector<bool> starting_point(n, false);
    int last_index = -1;
    while (!s.empty()){ // DFS and keep track of legs, visited, a temperature set and possible starting points
        int current = s.top();
        if(visited[current]){
            s.pop(); // we were already here
            temp_set.erase(temp_set.find(temp[current]));
            if( last_index - m >= 0){
                temp_set.insert(temp[leg[last_index-m]]); // reinsert removed index (because temp_set was bigger than m)
            }
            leg.pop_back();
            last_index--;
            continue;
        }
        visited[current] = true;
        leg.push_back(current);
        last_index++;
        temp_set.insert(temp[current]);
        if(temp_set.size() > m){ // too long 
            temp_set.erase(temp_set.find(temp[leg[last_index-m]])); // index at front from leg
        }
        if(temp_set.size() >= m && abs(*temp_set.rbegin() - *temp_set.begin()) <= k){ // we found a starting point
            starting_point[leg[last_index-m + 1]] = true;
        }
        //dfs push children
        for(auto c: sails[current])
            s.push(c);
    }
    bool any = false;
    for(int i = 0; i < n; ++i){
        if(starting_point[i]){
            any = true; 
            cout << i << " ";
        }
    }
    if(!any) cout << "Abort mission";
    cout << "\n";
    



}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
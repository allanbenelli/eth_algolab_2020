#include <vector>
#include <iostream>
#include <climits>
#include <set>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PI;


void testcase(){
    int n; cin >> n;
    VI m(n, 0);
    for(int i = 0; i < n; i++){
        cin >> m[i];
    }
    VVI p(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m[i]; j++){
            int c; cin >> c;
            p[i].push_back(c);
        }
    }
    sort(p.begin(), p.end());
    set<PI> positions;
    for(int i = 0; i<n; i++) positions.insert({p[i][0], i}); // insert first occurence
    int size = INT_MAX;
    while(true){
        PI first = *positions.begin();
        PI last = *positions.rbegin();
        int s = last.first - first.first + 1;
        if(s < size) size = s;

        int index = first.first;
        int word_i = first.second;
        auto it = upper_bound(p[word_i].begin(), p[word_i].end(), index);
        if(it==p[word_i].end()) break; // end reached
        positions.erase(positions.begin());
        positions.insert({*it, word_i});
         
    }
    cout << size << "\n";



}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for( int i = 0 ; i < t; i++){
        testcase();
    }    
}
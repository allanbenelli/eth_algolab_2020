#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

void testcase(){
    int n, q;
    cin >> n >> q; 
    unordered_map<string, int> names; names.reserve(n);
    vector<string> inames(n);
    vector<int> ages(n);
    vector<int> parents(n, -1);
    vector<int> ppar(n, -1);
    vector<int> p2(n, -1);

    for(int i = 0; i<n; ++i){
        string s; int a;
        cin >> s >> a;
        names.insert(make_pair(s, i));
        inames[i] = s;
        ages[i] = a;
    }

    for(int i = 0; i < n-1; ++i){
        string s, p;
        cin >> s >> p;
        int s_i = names.find(s)->second;
        int p1_i = names.find(p)->second;
        parents[s_i] = p1_i;
    }
    vector<vector<pair<int, int>>> vvi(n);
    vector<string> sol(n);

    for(int i = 0; i < q; ++i){
        string s; int b;
        cin >> s >> b;
        int g_i =names.find(s)->second;
        vvi[g_i].push_back(make_pair(b, i));
        
    }

    for (int i = n-1; i >= 0 ; i--)
    {
        int qu_i = vvi[i].size();
        if(qu_i){
            sort(vvi[i].begin(), vvi[i].end());
            int s_i = i;
            int g_i = s_i;
            int j = 0;
            while(j<qu_i){
                int b = vvi[i][j].first;
                while(parents[s_i] != -1 && ages[parents[s_i]] <= b){
                    if(p2[s_i] != -1 &&p2[s_i] != s_i &&ages[p2[s_i]] <= b) s_i = p2[s_i];
                    else s_i = parents[s_i];
                }
                if(p2[g_i] == -1) {p2[g_i] = s_i;}
                else if(ages[p2[g_i]] < ages[s_i]) {p2[g_i] = s_i;}; // overwrite it with older anchestor
                sol[vvi[i][j].second] = inames[s_i];
                j++;
            }
        }
    }
    
    cout << sol[0];
    for(int i = 1; i<q; ++i) cout <<  " " << sol[i] ;

    cout << "\n";
   

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
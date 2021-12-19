#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

int recursive(VVI &trans, VI &max_s, VI &min_s, bool minimize, int start, int end){
    if (start == end) return 0;
    if(minimize){
        if(min_s[start] != -1) return min_s[start];
        int minV = INT32_MAX;
        for(auto t : trans[start]){
            minV = min(minV, recursive(trans, max_s, min_s, !minimize, t, end)+1);
        }
        return min_s[start] = minV;
    } else {
        if(max_s[start] != -1) return max_s[start];
        int maxV = 0;
        for(auto t : trans[start]){
            maxV = max(maxV, recursive(trans, max_s, min_s, !minimize, t, end)+1);
        }
        return max_s[start] = maxV;
    }
}

void testCase(){
    int n, m, r, b; cin >> n >> m >> r >> b;
    n--; r--; b--;
    VVI trans(n);
    for (size_t i = 0; i < m; i++){
        int u, v; cin >> u >> v; u--; v--;
        trans[u].push_back(v);
    }
    VI min_steps (n, -1), max_steps(n,-1);
    int stepsH = recursive(trans, max_steps, min_steps, true, r, n);
    int stepsM = recursive(trans, max_steps, min_steps, true, b, n);
    int out = 0;
    if(stepsH > stepsM || (stepsH==stepsM && stepsH % 2 == 0)) out = 1;
    cout << out << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) testCase();
}
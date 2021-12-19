#include <iostream>
#include <vector>

using namespace std;

void run(){
    int n, m, k; cin >> n >> m >> k;
    vector<int> def; def.reserve(n);
    for(int i = 0; i < n; i++){
        int v; cin >> v;
        def.push_back(v);
    }
    int l = 0, r = 0, sum = def[0];
    vector<int> brk(n, 0);
    while(r<n){
        if(sum == k) brk[r] = r-l+1;
        if(sum < k){
            sum += def[++r];
        } else {
            sum -= def[l++];
            if(l>r){
                r = l;
                if(l < n) sum = def[l];
            }
        }
    }
    vector<vector<int>> dp(m+1, vector<int>(n, -1));
    for(int i = 0; i < n; i++) dp[0][i] = 0;
    for(int i = 1; i <= m; i++) dp[i][0] = brk[0];

    for(int i = 1; i <= m; i++){
        for(int j = 1; j < n; j++){
            int max_j = max(0, j-brk[j]);
            dp[i][j] = max(dp[i][j-1], dp[i-1][max_j]+brk[j]);
        }
    }
    if(dp[m-1][n-1] != dp[m][n-1]) cout << dp[m][n-1] << "\n";
    else cout << "fail\n";

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        run();
    }
}
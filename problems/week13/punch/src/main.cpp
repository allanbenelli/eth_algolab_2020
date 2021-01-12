#include <iostream>
#include <vector>

using namespace std;

typedef pair<int,int> mp;

void testcase(){
    int n, k;
    cin >> n >> k; // k = people, each wants one liter, n = # distinct beverages
    vector<int> vol(n+1, 0), cost(n+1, 0);
    for(int i = 1; i <= n; ++i) cin >> cost[i] >> vol[i];
    int max_i = 1 << 22;

    vector<vector<pair<int,int>>> dp(n+1, vector<pair<int,int>>(k+1, {0,0}));

    for(int i = 0; i <= n; ++i) dp[i][0] = make_pair(0,0);
    for(int i = 1; i <= k; ++i) dp[0][i] = make_pair(max_i, -max_i);
    
    for(int i = 1; i<=n; ++i){
        for(int j = 1; j<=k; ++j){
            dp[i][j] = dp[i-1][j]; // no improvement
            
            int left_index = max(0,j-vol[i]); // take leftes element or this one with lesser volume
            mp upp = dp[i-1][left_index];
            mp left = dp[i][left_index]; 
            int cost_upp = upp.first + cost[i];
            int cost_left = left.first + cost[i];

            if(cost_left < dp[i][j].first){
                dp[i][j] = make_pair(cost_left, left.second);
            } else if (cost_left == dp[i][j].first) dp[i][j].second = max(dp[i][j].second, left.second);
            if(cost_upp < dp[i][j].first){
                dp[i][j] = make_pair(cost_upp, upp.second+1);
            } else if (cost_upp == dp[i][j].first) dp[i][j].second = max(dp[i][j].second, upp.second+1);

        }
    }
    cout << dp[n][k].first << " " << dp[n][k].second << "\n";

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
#include <iostream>
#include <vector>

using namespace std;

void run(){
    int n, k; cin >> n >> k;
    vector<pair<int,int>> bev(n+1);
    bev[0] = {0,0};
    for(int i = 1; i <= n; ++i){
        int c,v; cin >> c >> v;
        bev[i] = {c,v};
    }
    int maxi = 1 << 25;
    vector<vector<pair<int,int>>> dp(n+1, vector<pair<int,int>>(k+1, {0,0}));
    for(int i = 1; i <= k; ++i) dp[0][i] = {maxi, -maxi};

    for(int i = 1; i<= n; ++i){
        for(int j = 1; j <= k; ++j){
            dp[i][j] = dp[i-1][j];
            int cost_b = bev[i].first;
            int lit_b = bev[i].second;
            int left_j = max(0, j-lit_b);

            pair<int,int> upper_l = dp[i-1][left_j];
            pair<int,int> this_l = dp[i][left_j];
            int cost_upper = upper_l.first + cost_b;
            int cost_this = this_l.first + cost_b;
            if(cost_upper < dp[i][j].first){
                dp[i][j] = {cost_upper, upper_l.second+1};
            } else if(cost_upper == dp[i][j].first){
                dp[i][j].second = max(upper_l.second+1, dp[i][j].second);
            }

            if(cost_this < dp[i][j].first){
                dp[i][j] = {cost_this, this_l.second};
            } else if (cost_this == dp[i][j].first){
                dp[i][j].second = max(this_l.second, dp[i][j].second);
            }
        }
    }
    cout << dp[n][k].first << " " << dp[n][k].second << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
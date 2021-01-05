#include <iostream>
#include <vector>
#include <climits>

using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

int max_pos_win( int i, int j, int n, int m, const VI& coins, VVI& dp){
    if ( j < i) return 0;
    if (j-i <1) return dp[i][j] = 0;
    if (dp[i][j] != -1) return dp[i][j];

    int win_left = INT_MAX, win_right = INT_MAX;
    for (int l = 0; l < m; l++){
        win_left = min(win_left, max_pos_win(i + l + 1, j - (m - l - 1), n, m, coins, dp));
        win_right = min(win_right, max_pos_win(i + l, j - (m - l), n, m, coins, dp));
    }
    dp[i][j] = max(coins[i] + win_left, coins[j-1] + win_right);
    return dp[i][j];
    
}

void testcase(){
    int n, m, k;
    cin >> n >> m >> k;
    VI coins;

    for(int i = 0; i< n; i++){
        int c; cin >> c;
        coins.push_back(c);
    }
    VVI dp(n+1, VI(n+1, -1));

    int max_win = INT_MAX;
    for(int i = 0; i<= k; i++){ // try out all possibilites, take worst case
        max_win = min(max_win, max_pos_win(i, n - (k -i), n, m, coins, dp));
    }
    cout << max_win << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}

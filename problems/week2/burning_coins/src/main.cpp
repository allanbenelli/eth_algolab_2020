#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> VVI;

void testcase(){
    int n; cin >> n;
    vector<int> coins(n);
    for(int i = 0; i < n; ++i){
        cin >> coins[i];        
    }
    VVI opt(n, vector<int>(n));
    VVI neg(n, vector<int>(n));
    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n-k; ++i){
            int j = k+i;
            if(i == j){
                opt[i][i] = coins[i];
                neg[i][i] = 0;
            } else {
                opt[i][j] = max(coins[i]+neg[i+1][j], coins[j]+neg[i][j-1]);
                neg[i][j] = min(opt[i][j-1], opt[i+1][j]);
            }
        }
    }
    cout << opt[0][n-1] << "\n";


}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}
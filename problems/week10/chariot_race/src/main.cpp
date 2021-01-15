#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;


int memo(VVI& dp, const VVI& stages, const VI& costs, int pos, bool parent){
    if(parent){
        if(dp[0][pos] != -1) return dp[0][pos];
    }
    else if(!parent){
        if(dp[1][pos] != -1) return dp[1][pos];
    }

    int sum_take_this = costs[pos], sum_not_take_this = 0;
    for (int child: stages[pos]){
        sum_take_this += memo(dp, stages, costs, child, true);  //we take parent
        sum_not_take_this += memo(dp, stages, costs, child, false); //we don't
    }
    int res = 1 << 14;
    if(parent) res = min(sum_not_take_this, sum_take_this);
    else { // calculate, if we should take this
        int child_min = INT_MAX;
        for(int child : stages[pos]){
            int c = costs[child];
            for(int grand_child: stages[child]){
                c += memo(dp, stages, costs, grand_child, true);  // we take the child, so grand_child must not be taken
            }
            c+= sum_not_take_this - memo(dp, stages, costs, child, false); //we can take this away
            child_min = min(c, child_min);
        }
        res = min(sum_take_this, child_min);
    }

    if(parent){
        dp[0][pos] = res;
    }
    else if(!parent){
        dp[1][pos] = res;
    }
    return res;
}

void testcase(){
    int n; cin >> n;
    VVI stages(n);
    for(int i = 0; i<n-1; ++i){
        int x,y; cin >> x >> y;
        stages[x].push_back(y);
    }
    VI costs(n);
    for(int i = 0; i<n; ++i){
        cin >> costs[i];
    }
    VVI dp (2,VI(n, -1));
    
    int max_cost = memo(dp, stages, costs, 0, false);

    cout << max_cost << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
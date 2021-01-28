#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void run(){
    int n, k, w; cin >> n >> k >> w;
    vector<int> c(n);
    for(int i = 0; i < n; ++i) cin >> c[i];
    vector<int> length(n);
    vector<vector<int>> ways(w);
    for(int i = 0; i < w; ++i){
        cin >> length[i];
        ways[i].resize(length[i]);
        for(int j = 0; j < length[i]; ++j){
            cin >> ways[i][j];
        }
    }

    int best = 0;

    for(int i = 0; i < w; ++i){ // single waterway
        int a = 0, b = 0;
        int sum = c[0];
        while (a < length[i] && b < length[i]){
            if( sum == k) best = max(best, b - a + 1);
            if( sum >= k || b == length[i] - 1) sum -= c[ways[i][a++]];
            else sum += c[ways[i][++b]];
        }
    }
    map<int,int> sumToDistance;
    for(int i = 0; i < w; ++i){
        vector<int> sums;
        sums.push_back(0);
        for(int j = 1; j < length[i]; ++j){
            int sum = sums[j-1] + c[ways[i][j]];
            if (sum + c[0] >= k) break;
            sums.push_back(sum);

            int diff = k -(sum+c[0]);
            auto other = sumToDistance.find(diff);
            if(other != sumToDistance.end()) best = max(best, j + other->second + 1);
        }
        for(int j = 1; j < sums.size(); ++j){
            sumToDistance[sums[j]] = max(j, sumToDistance[sums[j]]);
        }
    }
    cout << best << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
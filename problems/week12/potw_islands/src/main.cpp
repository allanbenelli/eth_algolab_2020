#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void run(){
    int n, k, w; cin >> n >> k >> w;
    vector<vector<int>> ways(w);
    vector<int> str; str.reserve(n);
    for(int i = 0; i < n; ++i){
        int c; cin >> c;
        str.push_back(c);
    }
    vector<int> length(w);
    for(int i = 0; i < w; ++i){
        int l; cin >> l;
        length[i] = l;
        ways[i].reserve(l);
        for(int j = 0; j < l; ++j){
            cin >> ways[i][j];
        }
    }
    int best = 0;
    for(int i = 0; i < w; ++i){
        int l = 0, r = 0;
        int sum = str[0];
        while(r < length[i]){
            if(sum == k) best = max(best, r-l+1);
            if(sum >= k) {
                sum -= str[ways[i][l++]];
                if(l>r){
                    r = l;
                    if( r < length[i]) sum = str[ways[i][r]];
                }
            } else {
                if(++r < length[i]){
                    sum+= str[ways[i][r]];
                } else break;
            }
        }
    }

    map<int,int> sumMap;
    for(int i = 0; i < w; ++i){
        vector<int> sums;
        sums.push_back(0);
        for(int j = 1; j < length[i]; ++j){
            int sum = sums[j-1] + str[ways[i][j]];
            if(sum+str[0]>= k) break;
            sums.push_back(sum);

            int diff = k-(sum+str[0]);
            auto t = sumMap.find(diff);
            if(t!=sumMap.end()) best = max(best, j+t->second+1);
        }
        for(int j = 0; j < sums.size(); ++j){
            sumMap[sums[j]] = max(j, sumMap[sums[j]]);
        }
    }
    cout << best << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
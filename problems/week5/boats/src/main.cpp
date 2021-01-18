#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool int_second(const pair<int, int> &i, const pair<int,int> &j){
    return (i.second < j.second);
}

void testcase(){
    int n; cin >> n;
    vector<pair<int,int>> intervals;
    intervals.reserve(n);
    for(int i = 0; i < n; ++i){
        int l, p; cin >> l >> p;
        intervals.push_back({l,p});
    }
    sort(intervals.begin(), intervals.end(), int_second);

    int maxi = 1;
    int re = intervals[0].second;
    int re_old = 0;
    for(int i = 1; i < n; ++i){
        if (intervals[i].second < re){ // previous boat is overlapping the ring of i, could finish earlier or we don't count it
            re = min(re, max(re_old+intervals[i].first,intervals[i].second)); // same check as below
        } else {
            re_old = re;
            re = max(re + intervals[i].first, intervals[i].second); // ring has to be on boats length
            maxi++;
        }
    }
    cout << maxi << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
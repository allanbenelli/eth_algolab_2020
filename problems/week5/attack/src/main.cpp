#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

bool mySort(pair<int,int> &p1, pair<int,int> &p2){
    return p1.second < p2.second;
}

void run(){
    int n, m; cin >> n >> m;
    vector<pair<int,int>> segs; segs.reserve(n);
    map<int,int> counter;

    for(int i = 0; i < n; ++i){
        int a, b; cin >> a >> b;
        a--; b--;
        segs.push_back({a,b});
        counter[a]++;
        counter[b]--;
        if(a>b) counter[0]++;
    }
    //where to start:
    int min_disk = 0;
    int min_overlaps = 11;
    int overlaps = 0;
    for(auto c: counter){
        overlaps += c.second;
        if( overlaps < min_overlaps){
            min_disk = c.first;
            min_overlaps = overlaps;
        }
    }
    min_disk++;
    for(int i = 0; i < n; ++i){
        segs[i].first = (segs[i].first - min_disk + m) %m;
        segs[i].second = (segs[i].second - min_disk + m) %m;
        if(segs[i].first>segs[i].second) segs[i].second += m;
    }
    sort(segs.begin(), segs.end(), mySort);
    int cnt = 0;
    int curr_pos = -1;
    for(auto seg: segs){
        if(((seg.first <= curr_pos) && (curr_pos <= seg.second)) || (seg.second >= m)&&(seg.second % m >= segs[0].first))
            curr_pos = min(curr_pos, seg.second);
        else{
            curr_pos = seg.second;
            cnt++;
        }
    }
    cout << cnt << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool mySort(int & a, int & b){
    return a > b;
}
void run(){
    int N, M; cin >> N >> M;
    vector<int> friends(N);
    vector<int> weights(M);
    multiset<int, greater<int>> ws;
    int max_f = -1, max_w = -1;
    for(int i = 0; i < N; ++i){
        int s; cin >> s;
        friends[i] = s;
        max_f = max(max_f, s);
    }
    for(int i = 0; i < M; ++i){
        int wi; cin >> wi;
        weights[i] = wi;
        max_w = max(max_w, wi);
        ws.insert(wi);
    }
    if(max_f < max_w){
        cout << "impossible\n"; return;
    }
    sort(friends.begin(), friends.end(), greater<int>());

    int round = 0;
    while(!ws.empty()){
        ++round;
        for(int i = 0; i < N; ++i){
            auto w = ws.lower_bound(friends[i]);
            if(w!=ws.end()){
                ws.erase(w);
            } else break;
        }
    }
    cout << 3*round -1 << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
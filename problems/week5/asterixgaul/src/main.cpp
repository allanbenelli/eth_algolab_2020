#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<pair<long,long>> VPLL;
typedef vector<long> VL;

bool mySort(pair<long,long> &p1, pair<long,long> &p2){
    return p1.second < p2.second;
}

void recursive(const int move, const int moves_used, const long remaining_d, const long remaining_t, const VPLL &moves, VL & best_wo_potions){
    if(move >= moves.size() || remaining_t <= moves[move].second){
        best_wo_potions[moves_used] = min(best_wo_potions[moves_used], remaining_d);
        return;
    }
    recursive(move+1, moves_used, remaining_d, remaining_t, moves, best_wo_potions);
    recursive(move+1, moves_used+1, remaining_d - moves[move].first , remaining_t-moves[move].second, moves, best_wo_potions);
}

void run(){
    int n, m; long D, T; cin >> n >> m >> D >> T;
    VPLL moves; moves.reserve(n);
    vector<long> gulps; gulps.reserve(m);

    for(int i = 0; i < n ; ++i){
        long d,t; cin >> d >> t;
        moves.push_back({d,t});
    }
    for(int i = 0; i < m; ++i){
        long s; cin >> s;
        gulps.push_back(s);
    }

    sort(moves.begin(), moves.end(), mySort);
    if(moves[0].second > T) cout << "Panoramix captured\n";
    else{
        const long long_max = numeric_limits<long>::max();
        VL best_wo_potions(31, long_max);
        recursive(0,0, D, T, moves, best_wo_potions);
        long best = long_max;
        for(int i = 1; i <= n; ++i){
            if(best_wo_potions[i] <= 0){
                cout << "0\n";
                return;
            }
            if(best_wo_potions[i] != long_max){
                long needed = (best_wo_potions[i]-1)/(i)+1;
                const auto it = lower_bound(gulps.begin(), gulps.end(), needed);
                if(it != gulps.end()){
                    best = min(best, it-gulps.begin()+1);
                }
            }
        }
        if (best == long_max){
            cout << "Panoramix captured\n"; 
        } else cout << best << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
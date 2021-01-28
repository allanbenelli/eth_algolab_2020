#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

constexpr int difference_offset = 12;

int calculate_bonus(const int a, const int b, const int c){
    return ((a && a!= b && a != c) + (b && b != c) + 1)* 1000;
}

void run(){
    int n, k, m; cin >> n >> k >> m;
    vector<int> fighters(n);
    for(int i = 0; i < n; ++i){
        int type; cin >> type;
        fighters[i] = type + 1;
    } 
    const int mask = m == 3 ? 255 : 15;

    unordered_map<uint32_t, int> current, next;
    next.emplace(difference_offset<<16, 0);

    const auto try_insert = [&next](const uint32_t key, const int round_score, const int current_best){
        if (round_score < 0) return;
        
        if (const auto it = next.find(key); it != std::end(next)) {
            it->second = std::max(it->second, current_best + round_score);
        } else {
            next.emplace_hint(it, key, current_best + round_score);
        }
    };
    for(const auto fighter : fighters) {
        std::swap(current, next);
        next.clear();

        for(const auto pair : current) {
            const uint32_t key = pair.first;
            const int value = pair.second;
            const int difference = (key>>16)-difference_offset;
            const int south_history = key & 255;
            const int north_history = (key>>8) & 255;
            
            const int new_south = ((south_history << 4) + fighter) & mask;
            const int new_north = ((north_history << 4) + fighter) & mask;

            const int south_score = calculate_bonus(south_history & 15, (south_history>>4) & 15, fighter) - (1<<std::abs(difference-1));
            const int north_score = calculate_bonus(north_history & 15, (north_history>>4) & 15, fighter) - (1<<std::abs(difference+1));
            
            const uint32_t south_key = ((difference+difference_offset-1) << 16) + (north_history<<8) + new_south;
            const uint32_t north_key = ((difference+difference_offset+1) << 16) + (new_north<<8) + south_history;
            
            try_insert(south_key, south_score, value);
            try_insert(north_key, north_score, value);
        }
    }
    int best = 0;
    for(const auto pair: next) {
        best = max(best, pair.second);
    }
    cout << best <<"\n";    
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
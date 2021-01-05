#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void testcase(){
    int n;
    cin >> n;
    vector<int> para(n);
    for (int i = 0; i<n; i++){
        cin >> para[i];
    }
    sort(para.begin(), para.end());
    int i, j, max, min, best_max, best_min;
    i = 0;
    j = 1;
    max = 1;
    min = 0;
    best_max = 1;
    best_min = 0;
    vector<int> positions;
    while (j < n) {
        int dist = para[j] - para[i];
        if(dist <= 200){
            max++;
            if(best_max <= max){
                int min = ceil(dist/2.0);
                if(best_max<max){
                    positions.clear();
                    best_min = min;
                }
                if(min<best_min){
                    positions.clear();
                }
                if(min<=best_min){
                    best_min = std::min(min, best_min);
                    int pos = para[i]+min;
                    if(dist%2==1){
                        positions.push_back(pos-1);
                    }
                    positions.push_back(pos);
                    best_max = max;
                }


            }
            j++;
        } else {
            max--;
            i++;
        }
        
    }
    
    cout << best_max << " " << best_min << "\n";
    for(auto e:positions){
        cout << e << " ";
    }
    cout << "\n";

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}
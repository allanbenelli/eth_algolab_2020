#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void testcase(){
    int n, k; cin >> n >> k;
    vector<int> cards(n);
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        cards[i] = x;
    }
    int i = 0;
    int b_i = 0;
    int j = 0;
    int b_j = 0;
    int val = cards[0];
    int b_val =  0;
    while (j < n-1)
    {
        if(val == k) {
            b_i = i;
            b_j = j;
            break;
        }
        if(val < k ){
            j++;
            val += cards[j];
        }
        else{
            val -= cards[i];
            i++;
            if(i>j){
                j=i;
                val = cards[j];
            }
        }
        if(abs(val-k) < abs(b_val-k)){
            b_i = i;
            b_j = j;
            b_val = val;
        }
    }
    cout << b_i << " " << b_j << "\n";
    

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i<t; i++){
        testcase();
    }    
}
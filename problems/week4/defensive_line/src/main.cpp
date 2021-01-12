#include <iostream>
#include <vector>

using namespace std;

void testcase(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> def;
    def.reserve(n);
    for(int i = 0; i < n; ++i){
        int v; cin >> v;
        def.push_back(v);
    }
    int cnt = def[0];
    int i = 0, j = 0;
    vector<int> interval(n, 0);
    while (j<n){
        if(cnt==k){
            interval[j] = j - i + 1;
            
            // save possible breakthrough;
        }
        if(cnt < k){
            j++;
            if(j < n){
                cnt += def[j];
            }
        } else{
            cnt -= def[i];
            i++;
            if(i > j){
                j = i;
                if( i < n)
                    cnt = def[i];
            }
        }
    }

    vector<vector<int>> memo(m+1);
    for(int i = 0; i<= m; ++i) memo[i]= vector<int>(n, -1);
    for(int j = 0; j<n; ++j) memo[0][j] = 0;
    for(int i = 1; i<=m; ++i) memo[i][0] = interval[0];
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j < n; ++j){
            int idx = max(j-interval[j], 0);
            memo[i][j]= max(memo[i-1][idx]+interval[j], memo[i][j-1]);
        }
    }

    if(memo[m][n-1] != memo[m-1][n-1]) cout << memo[m][n-1] << "\n";
    else cout << "fail\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i<t; ++i){
        testcase();
    }
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase(){
  int n, m, v;
  cin >> n >> m >> v;
  VVI graph(n);
  for (size_t i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  //sort it
  for (size_t i = 0; i < n; i++){
    std::sort(graph[i].begin(), graph[i].end());
  }
  
  VI distance(n, -1);
  std::queue<int> sta;
  sta.push(v);
  distance[v] = 0;
  while (!sta.empty())
  {
    int top = sta.front();
    sta.pop();
    for (auto it = graph[top].begin(); it != graph[top].end(); it++){
      if(distance[*it] == -1){
          distance[*it] = distance[top] + 1;
          sta.push(*it);
      }
    }
  }
  
  for(auto e: distance){
    cout << e << " ";
  }
  cout << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;  cin >> t;
  for (size_t i = 0; i < t; i++){
    testcase();
  }
}
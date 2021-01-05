#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void dfs(VI& visited, VI& timestamp, VVI& graph, std::stack<int>& sta, int& counter){
  int top = sta.top();
  sta.pop();
  if(visited[top] == -1){
    visited[top] = counter++;
  }
  for (size_t i = 0; i < graph[top].size(); i++)
  {
    int next = graph[top][i];
    if(visited[next] == -1){
        visited[next] = counter++;
        sta.push(next);
        dfs(visited,timestamp, graph, sta, counter);
    }
  }
  timestamp[top] = counter++;
}


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
  for (size_t i = 0; i < n; i++)
  {
    std::sort(graph[i].begin(), graph[i].end());
  }
  
  VI visited(n, -1);
  VI timestamp(n, -1);

  std::stack<int> sta;
  sta.push(v);
  int counter = 0;
  while (!sta.empty())
  {
    dfs(visited,timestamp, graph, sta, counter);
  }
  
  for(auto e: visited){
    cout << e << " ";
  }
  cout << "\n";

  for(auto e: timestamp){
    cout << e << " ";
  }
  cout << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (size_t i = 0; i < t; i++)
  {
    testcase();
    /* code */
  }
  


}
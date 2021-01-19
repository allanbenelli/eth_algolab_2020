#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int counter;

bool sort_greater(const pair<int,int> &a, const pair<int,int> &b){
    return a.first > b.first;
}

bool recursive(vector<int> &deactivated, pair<int,int> todo, vector<vector<int>> &child, const vector<int> &time){
    int this_time = todo.first;
    int this_index = todo.second;
    if(!deactivated[this_index]){ // we need to deactivate it
        if(counter >= this_time) return false; // early exit possible
        bool possible = true;
        if(child[this_index].size()>0){
            int ind_c0 = child[this_index][0];
            int ind_c1 = child[this_index][1];
            int time_c0 = time[ind_c0];
            int time_c1 = time[ind_c1];

            if(time_c0 > time_c1){ //other execution order
                possible = possible && recursive(deactivated, {time_c1, ind_c1}, child, time) && recursive(deactivated, {time_c0, ind_c0}, child, time); 
            } else {
                possible = possible && recursive(deactivated, {time_c0, ind_c0}, child, time) && recursive(deactivated, {time_c1, ind_c1}, child, time);
            }
        }
        if(possible && counter < this_time){ //recheck as counter may have increased
            deactivated[this_index] = 1;
            counter++;
        } else return false;
        return possible;
    } 
    return true;
}

void run(){
    int n; cin >> n;
    vector<int> time; time.reserve(n);
    vector<vector<int>> child(n);
    vector<pair<int,int>> time_index; time_index.reserve(n);
    vector<int> deactivated(n, 0);
    for(int i = 0; i < n; ++i){
        int t; cin >> t;
        time.push_back(t);
        time_index.push_back({t, i});
    }
    sort(time_index.begin(), time_index.end(), sort_greater);
    for(int i = 0; i<= (n-3)/2; ++i){
        child[i].push_back(2*i+1);
        child[i].push_back(2*i+2);
    }
    counter = 0;
    while (time_index.size()>0){
        pair<int,int> todo = time_index[time_index.size()-1];
        int this_time = todo.first;
        int this_index = todo.second;
        if(deactivated[this_index]){ // clean up
            time_index.pop_back();
        } else{
            if(recursive(deactivated, todo, child, time)){ //check if it's possible
                time_index.pop_back();
            } else break; // break, as it's not possible
        }
    }
    
    if(time_index.size()>0){
        cout << "no\n";
    } else{
        cout << "yes\n";
    }   
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}
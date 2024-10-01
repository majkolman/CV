#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <random>
#include <queue>
using namespace std;

int main(){
    int n;
    cin >> n;

    priority_queue <int, vector<int>, greater<int>> max;
    priority_queue <int, vector<int>> min;
    vector<int> rezultati;


    for(int i = 0; i < n; i++){

        int x;
        cin >> x;

        if(min.size() == 0 && max.size() == 0){
            min.push(x);
        }else if(x <= min.top()){
            min.push(x);
        }else{
            max.push(x);
        }

        if(min.size() == max.size() + 2){
            int a = min.top();
            min.pop();
            max.push(a);
        }

        if(max.size() == min.size() + 2){
            int a = max.top();
            max.pop();
            min.push(a);
        }

        if(min.size() == max.size()){
            rezultati.push_back(min.top());
        }else if(min.size() > max.size()){
            rezultati.push_back(min.top());
        }else{
            rezultati.push_back(max.top());
        }

    }
    
    for(int i: rezultati) cout << i << endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> PII;
typedef vector<pair<int,int>> VII;

template<typename T>
void print(vector<T> sez) {
    for (T x : sez) cout << x << " ";
    cout << endl;
}

void DijsktraPQ(vector<vector<PII>> &sosedi, int start, vector<int> &dist, vector<int> &prev) {
    int n=sosedi.size();
    dist=vector<int>(n,-1); prev=vector<int>(n,-1);
    priority_queue<PII, vector<PII>, greater<PII>> pq;  // min heap (dist, x)
    dist[start]=0; pq.push({0,start});
    while (!pq.empty()) {
        // najmanjsi v okolici
        auto [d,x]=pq.top(); pq.pop();
        if (d!=dist[x]) continue;  // ignoriram stare vrednosti
        // popravim potencialne razdalje
        for (auto [y,w] : sosedi[x]) {
            int d=dist[x]+w;
            if (dist[y]==-1 || d<dist[y]) {
                dist[y]=d; prev[y]=x;
                pq.push({d,y});
            }
        }
    }
}

int main() {
    
    int n,m;
    cin >> n >> m;
    vector<vector<PII>> sosedi(n);
    for (int i=0;i<m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        sosedi[a].push_back({b,c});
        sosedi[b].push_back({a,c});
    }
    vector<int> dist, prev;

    DijsktraPQ(sosedi, 0, dist, prev);
    /*
    print(dist);
    print(prev);
    */

    
    vector<int> pot;
    if(prev[n - 1] == -1){
        int g = -1;
        pot.push_back(g);
    }else{
        int x = n-1;
        while(x != 0){
            pot.push_back(x);
            x = prev[x];
        }
        pot.push_back(0);
    }
    //print(pot);


    priority_queue<int, vector<int>, greater<int>> distances;
    for(int i = 0; i < pot.size() - 1; i++){
        vector<int> dist1, prev1;

        //save povezava
        int a = pot[i];
        int b = pot[i + 1];
        int c;
        for(auto [y,w] : sosedi[a]){
            if(y == b){
                c = w;
            }
        }
        //cout << a << " " << b << " " << c << endl;
        //remove povezava

        for (auto it = sosedi[b].begin(); it != sosedi[b].end(); ++it) {
        if (it->first == a) {
            sosedi[b].erase(it);
            break;
            }
        } 
        for (auto it = sosedi[a].begin(); it != sosedi[a].end(); ++it) {
        if (it->first == b) {
            sosedi[a].erase(it);
            break;
            }
        }  

        //run djisktra
        DijsktraPQ(sosedi, 0, dist1, prev1);

        
        /*
        cout << "Dijkstra's Algorithm after removing connection (" << a << ", " << b << "):\n";
        print(dist1);
        print(prev1);
        */


        //add povezava
        sosedi[a].push_back({b, c});
        sosedi[b].push_back({a, c});


        /*
        vector<int> pot1;
        if(prev1[n - 1] == -1){
            int g = -1;
            pot1.push_back(g);
        }else{
            int x = n-1;
            while(x != 0){
                pot1.push_back(x);
                x = prev1[x];
            }
            pot1.push_back(0);
        }
        print(pot1);
        */


        int cost = dist1[n-1];
        if(cost != -1){
            distances.push(cost);
        }


    }
    if(distances.empty()){
        cout << -1 << endl;
    }else{
        cout << distances.top() << endl;
    }
    

    return 0;
}
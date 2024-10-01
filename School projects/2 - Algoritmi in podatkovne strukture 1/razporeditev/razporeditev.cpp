#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> PII;
typedef vector<pair<int,int>> VII;
void delaj(vector<vector<int>> &sosedi, int x, vector<int> &skup, vector<bool> &obdelano);

template<typename T>
void print(vector<T> sez) {
    for(T x: sez){
        if(x == 0){
            continue;
        }
        cout << x << '\n';
    }
    /*
    for (T x : sez) cout << x << " ";
    cout << endl;
    */
}

void BFS(int n, vector<vector<int>> &sosedi, vector<int> &seq) {
    vector<int> vis(n);
    queue<int> q;
    q.push(0); vis[0]=1;
    while (!q.empty()) {
        int x=q.front(); q.pop();
        seq.push_back(x);
        for (int y : sosedi[x]) {
            if (!vis[y]) {
                q.push(y); vis[y]=1;
            }
        }
    }
}

void DFS(int x, vector<vector<int>> &sosedi, vector<int> &seq, vector<int> &vis) {
    seq.push_back(x);
    vis[x]=1;
    for (int y : sosedi[x]) if (!vis[y]) {
        DFS(y,sosedi,seq,vis);
    }
}

vector<int> skupine(vector<vector<int>> &sosedi, int &n){
    vector<int> skup(n + 1); 
    vector<bool> obdelano(n + 1);
    int x = 1;

    delaj(sosedi,x,skup,obdelano);
    
    for(int i = 1; i <= n; i++){
        if(!obdelano[i]){
            delaj(sosedi,i,skup,obdelano);
        }
    }

    return skup;
}
bool check = false;
void delaj(vector<vector<int>> &sosedi, int x, vector<int> &skup, vector<bool> &obdelano){
    if(obdelano[x] || check){
        return;
    }
    int skupina_x;
    if(skup[x] == 0){
        skup[x] = 1;
        skupina_x = 1;
    }else if(skup[x] == 1){
        skupina_x = 1;
    }else if(skup[x] == 2){
        skupina_x =2;
    }


    //za vse sosede nastavimo skupino
    for(int i: sosedi[x]){
        if(skupina_x == 1){
            if(skup[i] == 1){
                check = true;
            }
            skup[i] = 2;
        }
        if(skupina_x == 2){
            if(skup[i] == 2){
                check = true;
            }
            skup[i] = 1;
        }
    }
    obdelano[x] = true;
    //nastavimo sosede sosedov
    for(int i: sosedi[x]){
        delaj(sosedi,i,skup,obdelano);
    }
    return;
}


int main() {
    /*
    ifstream fin("graph.txt");
    int n,m;
    fin >> n >> m;
    */

   int n,m;
   cin >> n >> m;
   
    vector<vector<int>> sosedi(100000);
    for (int i=1;i<=m;i++) {
        int a,b;
        cin >> a >> b;
        sosedi[a].push_back(b);
        sosedi[b].push_back(a);
    }
    /*
    for (int x=1;x<=n;x++) {
        cout << x << ": ";
        print(sosedi[x]);
    }
    */

    vector<int> skup = skupine(sosedi, n);
    if(!check){
        print(skup);
    }else{
        cout << -1 << endl;
    }
    


    
    /*
    vector<int> seqB;
    BFS(n,sosedi,seqB);
    print(seqB);

    vector<int> seqD, visD(n);
    DFS(0,sosedi,seqD,visD);
    print(seqD);
    */

    return 0;
}
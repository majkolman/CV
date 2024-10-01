#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;


int v,s;
void izracunaj(vector<vector<pair<int,bool>>> &tab, int visina, int x, int y);

template<typename T>
void print_vek(vector<T> sez) {
    for (T x : sez) cout << x << " ";
    cout << endl;
}

int izracunaj_otoke(vector<vector<pair<int,bool>>> tab, int visina){
    //poisci prvi neobiskan element ki ni pod vodo, ce ga najdes dodaj counterju
    //obisci cel otok
    int count = 0;
    for(int x = 0; x < tab.size(); x++){
        for(int y = 0; y < tab[0].size(); y++){
            if(!tab[x][y].second && tab[x][y].first - visina != 0){
                izracunaj(tab, visina, x, y);
                if(tab[x][y].first - visina > 0) count++;
            }
        }
    }
    return count;
}
void izracunaj(vector<vector<pair<int,bool>>> &tab, int visina, int x, int y){
    //cout << "here" << x << " - " << y << " --- " << tab[x][y].second << endl;
    if(tab[x][y].second || tab[x][y].first - visina <= 0){
        //cout << "tu" << endl;
        return;
    }
    tab[x][y].second = 1;
    //cout << x-1 << " - " << y << endl;
    if(x - 1 >= 0) izracunaj(tab, visina, x - 1, y);
    //cout << x+1 << " - " << y << endl;
    if(x + 1 < v) izracunaj(tab, visina, x + 1, y);
    //cout << x << " - " << y - 1 << endl;
    if(y - 1 >= 0) izracunaj(tab, visina, x, y - 1);
    //cout << x << " - " << y+1 << endl;
    if(y + 1 < s) izracunaj(tab, visina, x, y + 1);
    return;
}

int main() {
    
    cin >> v >> s;
    
    vector<vector<pair<int,bool>>> tab;

    tab.resize(v);


    int max = 0;
    for(int i = 0; i < v; i++){
        for(int j = 0; j < s; j++){
            pair<int,bool> a = {0,0};
            cin >> a.first;
            if(a.first > max) max = a.first;
            tab[i].push_back(a);
        }
    }
    for(int visina = 0; visina <= max; visina++){
        int count = izracunaj_otoke(tab, visina);
        cout << count << endl;
    }
    

    return 0;
}
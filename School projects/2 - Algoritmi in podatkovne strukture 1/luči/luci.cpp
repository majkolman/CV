#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
int main(){
    int M = 0;
    int N = 0;
    
    cin >> M >> N;

    vector<pair<int,int>> luci;

    for(int i = 0; i < N; i++){
        pair<int,int> element;
        cin >> element.first >> element.second;
        luci.push_back(element);
    }
    



    vector<pair<int,int>> zacetki;
    //int pokritje = 0;
    for(auto xy: luci){
        pair<int,int> element;
        

        
        if(xy.second == 0){
            continue;
        }
        else if(xy.first - xy.second < 0){
            element.first = 0;
            if(xy.first + xy.second > M){
                element.second = M;
            }
            else{
                element.second = xy.first + xy.second;
            }
        }
        else if(xy.first + xy.second > M){
            element.second = M;
            if(xy.first - xy.second < 0){
                element.first = 0;
            }
            else{
                element.first = xy.first - xy.second;
            }
        }
        else{
            element.first = xy.first - xy.second;
            element.second = xy.first + xy.second;
        }
    /*
        if(xy.first - xy.second < 0){
            pokritje = xy.first + xy.second;
        }
        else if(xy.first + xy.second > M){
            pokritje = M - xy.first + xy.second;
        }
        else{
            pokritje = xy.second * 2;
        }
        element.second = element.first + pokritje;
        */
        zacetki.push_back(element);
            
    }
    sort(zacetki.begin(),zacetki.end());
    int nepokrito = M;
    int temp_x = 0;
    int temp_y = 0;
    for(auto xy: zacetki){
        if(temp_x == 0 && temp_y == 0){
            temp_x = xy.first;
            temp_y = xy.second;
        }

        if(xy.first <= temp_y && xy.second > temp_y){
            temp_y = xy.second;
        }
        else if(xy.first > temp_y){
            nepokrito -= (temp_y - temp_x);

            temp_x = xy.first;
            temp_y = xy.second;
        } 
    }

    nepokrito -= (temp_y - temp_x);

    cout << nepokrito << endl;

    return 0;
}
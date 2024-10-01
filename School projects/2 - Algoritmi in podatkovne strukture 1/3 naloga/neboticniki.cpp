#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> visine;
    for(int i= 0; i < n; i++){
        int a;
        cin >> a;
        visine.push_back(a);
    }
    //ustvarimo sklad, s katerim bomo zapisovali najblizje vecje clene in njihove indekse
    stack<pair<int,int>> my_stack;

    int vsota = 0;
    //nastavimo prvi clen na zacetek
    auto curr = visine.begin();

    //cez seznam gremo od zacetka do konca
    for(int i = 0; i < visine.size(); i++){
        //ce je zadnji element na skladu manjsi od trenutnega ga odstranimo
        while(my_stack.size() !=0 && my_stack.top().second <= *curr){
            my_stack.pop();
        }

        //preverimo ali je sklad prazen in vsoti pristejem razdaljo od zacetka do elementa
        if(my_stack.size() == 0){
            vsota += i;
            pair<int,int> nov = {i, *curr};
            my_stack.push(nov);
            curr++;
        }
        //ce sklad ni prazen pristejemo vsoti razdaljo od prejsnega vecjega elementa do trenutnega elementa
        else{
            vsota += (i - my_stack.top().first - 1);
            pair<int,int> nov = {i, *curr};
            my_stack.push(nov);
            curr++;
        }
    }
    
    //spraznemo sklad
    while(!my_stack.empty()){
        my_stack.pop();
    }

    //postavimo trenutni element na konec
    curr = visine.end() - 1;

    //ponovimo zgornjo logiko samo da gremo od konca proti zacetku
    for(int i = visine.size() - 1; i >= 0; i--){
        while(my_stack.size() !=0 && my_stack.top().second <= *curr){
            my_stack.pop();
        }
        if(my_stack.size() == 0){
            vsota += visine.end() - 1 - curr;
            pair<int,int> nov = {i, *curr};
            my_stack.push(nov);
            curr--;
        }
        else{
            vsota += my_stack.top().first - i -1;
            pair<int,int> nov = {i, *curr};
            my_stack.push(nov);
            curr--;
        }
    }

    cout << vsota << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;


class Interval{
    public:
    Interval* desno;
    Interval* levo;
    int LMeja;
    int RMeja;
    int stEl;
    Interval(int l, int d,Interval* le, Interval* de): LMeja(l), RMeja(d), levo(le), desno(de), stEl(0){};
};

class Tree{
    public:
    int capacity;
    Interval* root;
    Tree(){
        capacity = pow(2,20) - 1;

        root = new Interval(0,capacity,NULL,NULL);
        build();
    }

    void build(){
        build(root);
    }
    void build(Interval* trenutno){
        if(trenutno == NULL || trenutno->LMeja == trenutno->RMeja){
            return;
        }

        int lev = trenutno->LMeja;
        int des = trenutno->RMeja;
        int sredinal = (des - lev)/2 + lev;
        int sredinar = sredinal + 1;

        Interval *l = new Interval(lev, sredinal,NULL,NULL);
        trenutno->levo = l;
        build(l);

        Interval *d = new Interval(sredinar, des,NULL,NULL);
        trenutno->desno = d;
        build(d); 
    }
    
    void insert(int x){
        insert(x,root);
    }
    void insert(int x, Interval* ok){
        if(ok == NULL){
            return;
        }
        if(x > ok->RMeja || x < ok->LMeja){
            return;
        }
        ok->stEl++;
        insert(x, ok->desno);
        insert(x, ok->levo);
    }

    void remove(int x){
        remove(x,root);
    }
    bool remove(int x, Interval* trenutno){
        if(trenutno == NULL ){
            return false;
        }
        if(trenutno->stEl == 0){
            return false;
        }
        if(x > trenutno->RMeja || x < trenutno->LMeja){
            return false;
        }else{
            if(remove(x, trenutno->desno)){
                trenutno->stEl--;
                return true;
            }
            if(remove(x, trenutno->levo)){
                trenutno->stEl--;
                return true;
            }
        }
        if(trenutno->LMeja == trenutno->RMeja){
            trenutno->stEl--;
            return true;
        }
        return false;
    }



    int poizvedba(Interval* interval){
        return poizvedba(interval, root);
    }
    int poizvedba(Interval* interval, Interval* trenutno){
        int a = 0;
        if(trenutno == NULL){
            return 0;
        }
        if(trenutno->RMeja < interval->LMeja || trenutno->LMeja > interval->RMeja){
            return 0;
        }

        if(trenutno->LMeja >= interval->LMeja && trenutno->RMeja <= interval->RMeja){
            return trenutno->stEl;
        }

        a += poizvedba(interval, trenutno->levo);
        a += poizvedba(interval, trenutno->desno);

        //cout << a << "--[" << trenutno->LMeja << "," << trenutno->RMeja <<"]" << '\n';
        return a;
    }






    void izpis(){
        izpis(root);
    }

    void izpis(Interval* a){
        if(a == NULL){
            return;
        }
        izpis(a->levo);
        izpis(a->desno);
        cout<< "["<< a->LMeja <<"," << a->RMeja << "] ->"  << a->stEl << '\n';
    }
};

int main(){
    Tree krneki;
    
    /*
    int a = 4;
    krneki.insert(a);
    a = 6;
    krneki.insert(a);
    int c = 0;
    krneki.insert(c);
    int d = 7;
    krneki.insert(d);
    Interval* b = new Interval(c,d,NULL,NULL);
    */
    
    //krneki.izpis();
    //cout << krneki.poizvedba(b) << '\n';
    

   
   int n;
   cin >> n;


    long count = 0;
    
    for(int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;

        if(a < 0){
            //insert(vreca, b);
            krneki.insert(b);
        }
        else if(a == 0){
            //remove(vreca, b);
            krneki.remove(b);
        }
        else{
            int l = min(a,b);
            int d = max(a,b);
            Interval* lol = new Interval(l,d,NULL,NULL);
            count += krneki.poizvedba(lol);
        }

    }
    
    cout << count << endl;
    

    return 0;
}
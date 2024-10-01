#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;





int main(){
    int k, n, a;

    cin >> n >> k >> a;
    int prejsna = -1;
    vector<vector<int>> nov;
    vector<int> trenutno;
    int stevec = 0;
    int korak = 0;
    for(int i = 0; i < n; i++){
        //preberemo vhod
        int st;
        cin >> st;
      
        //ce se zacne nova ceta vstopimo v if stavek
        if(st < prejsna){
            //dodamo stevcu in ko je stevec enak k pomeni da moramo zapisane elemente skupaj zliti
            stevec++;
            if(stevec == k){
                //elemente skupaj zlijemo z funkcijo sort in jih dodamo v vektor ki shrani vse urejene cete tega koraka
                sort(trenutno.begin(), trenutno.end());
                nov.push_back(trenutno);
                //resetriamo stevec in vektor
                trenutno.clear();
                stevec = 0;
            }
        }
        //element dodamo vektorju in ga shranimo v int 'prejsna'
        trenutno.push_back(st);
        prejsna = st;

        //ko smo na zadnjem koraku zlijemo skupaj preostale elemente
        if(i == n - 1){
            sort(trenutno.begin(), trenutno.end());
            nov.push_back(trenutno);
            trenutno.clear();
        }
    }
    korak++;

    //zanka se izvaja dokler ne naredimo vseh korakov
    while(korak < a){
        prejsna = -1;
        stevec = 0;
        int count = 0;
        //ustvarimo nov vektor, ki shranjuje iteracijo
        vector<vector<int>> vektor = nov;
        vector<int> temp;
        nov.clear();

        //enaka logika kot pri zgornjem delu, ampak tu beremo elemente iz vektorja namesto iz vhoda
        for(vector<int> trenutno: vektor){
            for(int i: trenutno){     
                if(i < prejsna){
                    stevec++;
                    if(stevec == k){
                        sort(temp.begin(), temp.end());
                        nov.push_back(temp);
                        temp.clear();
                        stevec = 0;
                    }
                }
                temp.push_back(i);
                prejsna = i;
                if(count == n - 1){
                    sort(temp.begin(), temp.end());
                    nov.push_back(temp);
                    temp.clear();
                }
                count++;
            }
        }
        korak++;
    } 

    //izpisemo rezultat
    for(vector<int> trenutno: nov){
        for(int x: trenutno){
            cout << x << endl;
        }
    } 
    return 0;
}
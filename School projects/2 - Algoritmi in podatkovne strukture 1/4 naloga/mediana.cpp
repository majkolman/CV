#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <algorithm>
#include <random>
using namespace std;

class SkipNode {
public:
    int value, height;
    vector<SkipNode*> next;
    SkipNode(int _value, int _height) : value(_value), height(_height) {
        next.resize(height);
    }
};

class SkipList {
    int max_height;
    SkipNode *head;
    default_random_engine rnd;
public:
    SkipList() : max_height(20) {
        head = new SkipNode(-1, max_height);
        rnd = default_random_engine(123);
    }
    ~SkipList() { delete head; }

    bool contains(int x) {
        SkipNode *node = head;
        for (int h=max_height-1; h>=0; h--) {
            while (node->next[h]!=NULL && node->next[h]->value < x) node = node->next[h];
        }
        return node->next[0]!=NULL && node->next[0]->value == x;
    }

    void insert(int x) {
        int height=1;
        while (height<max_height && rnd()%2==0) height++;
        SkipNode *new_node = new SkipNode(x, height);
        SkipNode *node = head;
        for (int h=max_height-1; h>=0; h--) {
            while (node->next[h]!=NULL && node->next[h]->value < x) node = node->next[h];
            if (h<height) {
                new_node->next[h] = node->next[h];
                node->next[h] = new_node;
            }
        }
    }

    int element_on_indeks(int i){
        SkipNode *node = head;
        int count = 0;
        node = node->next[0];
        cout << head - node->next[0] << " <- " << endl;

            /*
            for (int h=max_height-1; h>=0; h--) {
                
                
                if(node->next[h] != NULL && node->next[h] - node < i){
                    node = node->next[h];
                    i -= (node->next[h] - node);
                }else if(node->next[h] != NULL && node->next[h] - node == i){
                    return node->next[h]->value;
                }
                
            }
            */
            return 1;
        }
        
};



int main(){
    int n;
    cin >> n;

    SkipList sl;
    vector<int> rezultati;

    for(int i = 0; i < n; i++){

        int x;
        cin >> x;

        sl.insert(x);
        rezultati.push_back(sl.element_on_indeks(i / 2));


    }
    for(int i: rezultati)cout << i << endl;
 
    return 0;
}
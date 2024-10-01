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

class RMQ {
private:
    int n;
    vector<int> array;
    struct Node { int st, begin, end; };
    vector<Node> tree;
    int INF=1e9;
public:
    RMQ(vector<int> &a) {
        n = pow(2, ceil(log2((double)a.size())));  // potenca 2
        array = a;
        array.resize(n, INF);
        tree.resize(2*n);
        build();
    }



    void build(int id=1) {
        if (id>=n) { tree[id] = {array[id-n], id-n, id-n+1}; return; }  // list
        int left=2*id, right=2*id+1;
        build(left); build(right);
        tree[id] = {tree[left].st + tree[right].st, tree[left].begin, tree[right].end};
    }

    int query(int l, int r, int id=1) {
        if (l<=tree[id].begin && tree[id].end<=r) return tree[id].st;  // znotraj
        if (r<=tree[id].begin || tree[id].end<=l) return INF;           // zunaj
        return query(l,r,2*id) + query(l,r,2*id+1);
    }
};

int main(){
    //int n;
    //cin >> n;
        int n=100'000;
        default_random_engine rnd(123);
        vector<int> v;
        for (int i=0;i<n;i++) v.push_back(rnd()%1'000'000'000);
        RMQ rmq(v);
        for (int it=0;it<100;it++) {
            int l=rnd()%n, r=rnd()%(n+1);
            if (l>=r) continue;
            if (rmq.query(l, r) != *min_element(v.begin()+l, v.begin()+r)) cout << "ups" << endl;
        }
        cout << "done" << endl;
    return 0;
}
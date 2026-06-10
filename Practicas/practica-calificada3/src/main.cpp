#include <iostream>
#include "IntervalTreap.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        ods::IntervalTreap<long long> treap;
        
        for (int i = 0; i < n; ++i) {
            int type;
            long long l, r;
            cin >> type >> l >> r;
            
            if (type == 1) {
                treap.addInterval(l, r);
            } else if (type == 2) {
                treap.removeInterval(l, r);
            } else if (type == 3) {
                treap.invertInterval(l, r);
            }
            
            cout << treap.getMEX() << "\n";
        }
    }
    return 0;
}
#include <iostream>
#include "IntervalTreap.h"

using namespace std;

int main() {
    // Optimizacion obligatoria para problemas de Codeforces con muchos datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        ods::IntervalTreap<long long> treap;
        
        // TODO (Dia 4): Leer tipo de operacion (1, 2 o 3), L y R.
        // Ejecutar treap.addInterval, treap.removeInterval, etc.
        // Imprimir treap.getMEX()
    }

    return 0;
}
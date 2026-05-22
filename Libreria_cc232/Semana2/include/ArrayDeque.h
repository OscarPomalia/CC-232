/*
 * ArrayDeque.h
 * Adaptado pedagogicamente para CC232 a partir del codigo de Morin.
 */

#ifndef ARRAYDEQUE_H_
#define ARRAYDEQUE_H_

#include <cassert>
#include "array.h"
#include "utils.h"

namespace ods {

template<class T>
class ArrayDeque {
protected:
    array<T> a;
    int j;
    int n;
    void resize();
public:
    ArrayDeque();
    virtual ~ArrayDeque() = default;
    int size();
    int capacity() const;
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual T remove(int i);
    virtual void clear();
};

template<class T> inline
T ArrayDeque<T>::get(int i) {
    assert(0 <= i && i < n);
    return a[(j + i) % a.length];
}

template<class T> inline
T ArrayDeque<T>::set(int i, T x) {
    assert(0 <= i && i < n);
    T y = a[(j + i) % a.length];
    a[(j + i) % a.length] = x;
    return y;
}

template<class T>
void ArrayDeque<T>::clear() {
    n = 0;
    j = 0;
    array<T> b(1);
    a = b;
}

template<class T>
ArrayDeque<T>::ArrayDeque() : a(1), j(0), n(0) {
}

template<class T>
void ArrayDeque<T>::resize() {
    array<T> b(max(1, 2*n));
    for (int k = 0; k < n; k++) {
        b[k] = a[(j+k)%a.length];
    }
    a = b;
    j = 0;
}

template<class T>
int ArrayDeque<T>::size() {
    return n;
}

template<class T>
int ArrayDeque<T>::capacity() const {
    return a.length;
}

template<class T>
void ArrayDeque<T>::add(int i, T x) {
    assert(0 <= i && i <= n);
    if (n + 1 > a.length) resize();
    if (i < n/2) {
        j = (j == 0) ? a.length - 1 : j - 1;
        for (int k = 0; k <= i-1; k++) {
            a[(j+k)%a.length] = a[(j+k+1)%a.length];
        }
    } else {
        for (int k = n; k > i; k--) {
            a[(j+k)%a.length] = a[(j+k-1)%a.length];
        }
    }
    a[(j+i)%a.length] = x;
    n++;
}

template<class T>
T ArrayDeque<T>::remove(int i) {
    assert(0 <= i && i < n);
    T x = a[(j+i)%a.length];
    if (i < n/2) {
        for (int k = i; k > 0; k--) {
            a[(j+k)%a.length] = a[(j+k-1)%a.length];
        }
        j = (j + 1) % a.length;
    } else {
        for (int k = i; k < n-1; k++) {
            a[(j+k)%a.length] = a[(j+k+1)%a.length];
        }
    }
    n--;
    if (3*n < a.length) resize();
    return x;
}

} /* namespace ods */

#endif /* ARRAYDEQUE_H_ */

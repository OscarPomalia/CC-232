/*
 * ArrayQueue.h
 * Adaptado pedagogicamente para CC232 a partir del codigo de Morin.
 */

#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

#include <cassert>
#include "array.h"
#include "utils.h"

namespace ods {

template<class T>
class ArrayQueue {
protected:
    array<T> a;
    int j;
    int n;
    void resize();
public:
    ArrayQueue();
    virtual ~ArrayQueue() = default;
    virtual bool add(T x);
    virtual T remove();
    T peek();
    int size();
    int capacity() const;
    void clear();
};

template<class T>
ArrayQueue<T>::ArrayQueue() : a(1), j(0), n(0) {
}

template<class T>
void ArrayQueue<T>::resize() {
    array<T> b(max(1, 2*n));
    for (int k = 0; k < n; k++) {
        b[k] = a[(j+k)%a.length];
    }
    a = b;
    j = 0;
}

template<class T>
bool ArrayQueue<T>::add(T x) {
    if (n + 1 > a.length) resize();
    a[(j+n) % a.length] = x;
    n++;
    return true;
}

template<class T>
T ArrayQueue<T>::remove() {
    assert(n > 0);
    T x = a[j];
    j = (j + 1) % a.length;
    n--;
    if (a.length >= 3*n) resize();
    return x;
}

template<class T>
T ArrayQueue<T>::peek() {
    assert(n > 0);
    return a[j];
}

template<class T>
int ArrayQueue<T>::size() {
    return n;
}

template<class T>
int ArrayQueue<T>::capacity() const {
    return a.length;
}

template<class T>
void ArrayQueue<T>::clear() {
    n = 0;
    j = 0;
    array<T> b(1);
    a = b;
}

} /* namespace ods */

#endif /* ARRAYQUEUE_H_ */

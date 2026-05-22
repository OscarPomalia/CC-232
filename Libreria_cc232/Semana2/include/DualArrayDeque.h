/*
 * DualArrayDeque.h
 * Adaptado pedagogicamente para CC232 a partir del codigo de Morin.
 */

#ifndef DUALARRAYDEQUE_H_
#define DUALARRAYDEQUE_H_

#include <cassert>
#include "ArrayStack.h"

namespace ods {

template<class T>
class DualArrayDeque {
protected:
    ArrayStack<T> front;
    ArrayStack<T> back;
    void balance();
public:
    DualArrayDeque() = default;
    virtual ~DualArrayDeque() = default;
    int size();
    int frontSize() { return front.size(); }
    int backSize() { return back.size(); }
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual T remove(int i);
    virtual void clear();
};

template<class T> inline
T DualArrayDeque<T>::get(int i) {
    assert(0 <= i && i < size());
    if (i < front.size()) {
        return front.get(front.size() - i - 1);
    }
    return back.get(i - front.size());
}

template<class T> inline
T DualArrayDeque<T>::set(int i, T x) {
    assert(0 <= i && i < size());
    if (i < front.size()) {
        return front.set(front.size() - i - 1, x);
    }
    return back.set(i - front.size(), x);
}

template<class T>
int DualArrayDeque<T>::size() {
    return front.size() + back.size();
}

template<class T>
void DualArrayDeque<T>::add(int i, T x) {
    assert(0 <= i && i <= size());
    if (i < front.size()) {
        front.add(front.size() - i, x);
    } else {
        back.add(i - front.size(), x);
    }
    balance();
}

template<class T>
T DualArrayDeque<T>::remove(int i) {
    assert(0 <= i && i < size());
    T x;
    if (i < front.size()) {
        x = front.remove(front.size() - i - 1);
    } else {
        x = back.remove(i - front.size());
    }
    balance();
    return x;
}

template<class T>
void DualArrayDeque<T>::balance() {
    if (3*front.size() < back.size() || 3*back.size() < front.size()) {
        int n = front.size() + back.size();
        int nf = n/2;
        array<T> af(max(2*nf, 1));
        for (int i = 0; i < nf; i++) {
            af[nf-i-1] = get(i);
        }
        int nb = n - nf;
        array<T> ab(max(2*nb, 1));
        for (int i = 0; i < nb; i++) {
            ab[i] = get(nf+i);
        }
        front.a = af;
        front.n = nf;
        back.a = ab;
        back.n = nb;
    }
}

template<class T>
void DualArrayDeque<T>::clear() {
    front.clear();
    back.clear();
}

} /* namespace ods */

#endif /* DUALARRAYDEQUE_H_ */

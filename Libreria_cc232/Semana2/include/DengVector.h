// Adaptado pedagogicamente para CC232 a partir del codigo de Deng.

#pragma once

#include <cassert>

namespace ods {

template<class T>
class DengVector {
protected:
    inline static constexpr int DEFAULT_CAPACITY = 3;

    int _size;
    int _capacity;
    T* _elem;

    void copyFrom(const T* A, int lo, int hi) {
        const int n = hi - lo;
        _capacity = (n * 2 > DEFAULT_CAPACITY) ? (n * 2) : DEFAULT_CAPACITY;
        _elem = new T[_capacity];
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];
        }
    }

    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    void shrink() {
        if (_capacity <= DEFAULT_CAPACITY * 2) return;
        if (_size * 4 > _capacity) return;
        T* oldElem = _elem;
        _capacity >>= 1;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

public:
    explicit DengVector(int c = DEFAULT_CAPACITY, int s = 0, const T& v = T())
        : _size(s), _capacity(c) {
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        if (_capacity < _size) _capacity = _size;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = v;
        }
    }

    DengVector(const T* A, int n) {
        copyFrom(A, 0, n);
    }

    DengVector(const T* A, int lo, int hi) {
        copyFrom(A, lo, hi);
    }

    DengVector(const DengVector<T>& V) {
        copyFrom(V._elem, 0, V._size);
    }

    ~DengVector() {
        delete[] _elem;
    }

    DengVector<T>& operator=(const DengVector<T>& V) {
        if (this != &V) {
            delete[] _elem;
            copyFrom(V._elem, 0, V._size);
        }
        return *this;
    }

    int size() const {
        return _size;
    }

    int capacity() const {
        return _capacity;
    }

    bool empty() const {
        return _size == 0;
    }

    T& operator[](int r) {
        assert(0 <= r && r < _size);
        return _elem[r];
    }

    const T& operator[](int r) const {
        assert(0 <= r && r < _size);
        return _elem[r];
    }

    int find(const T& e, int lo, int hi) const {
        assert(0 <= lo && lo <= hi && hi <= _size);
        while ((lo < hi--) && !(e == _elem[hi])) {
        }
        return hi;
    }

    int find(const T& e) const {
        return find(e, 0, _size);
    }

    int insert(int r, const T& e) {
        assert(0 <= r && r <= _size);
        expand();
        for (int i = _size; i > r; --i) {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        ++_size;
        return r;
    }

    int remove(int lo, int hi) {
        assert(0 <= lo && lo <= hi && hi <= _size);
        if (lo == hi) return 0;
        const int n = hi - lo;
        while (hi < _size) {
            _elem[lo++] = _elem[hi++];
        }
        _size -= n;
        shrink();
        return n;
    }

    T remove(int r) {
        assert(0 <= r && r < _size);
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    void clear() {
        delete[] _elem;
        _capacity = DEFAULT_CAPACITY;
        _size = 0;
        _elem = new T[_capacity];
    }

    void traverse(void (*visit)(T&)) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }

    template<class VST>
    void traverse(VST& visit) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }
};

} // namespace ods


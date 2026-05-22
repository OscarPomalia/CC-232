#pragma once

namespace ods {

template<class T>
class Simple {
    int *a;
    int n;
public:
    void snippet();
};

template<class T>
void Simple<T>::snippet() {
    for (int i = 0; i < n; i++) a[i] = i;
}

} /* namespace ods */

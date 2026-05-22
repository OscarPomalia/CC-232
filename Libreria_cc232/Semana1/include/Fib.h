#pragma once

using Rank = unsigned int;

class Fib {
private:
    Rank f_;
    Rank g_;
public:
    explicit Fib(Rank n) : f_(1), g_(0) {
        while (g_ < n) next();
    }
    Rank get() const { return g_; }
    Rank next() {
        g_ += f_;
        f_ = g_ - f_;
        return g_;
    }
    Rank prev() {
        f_ = g_ - f_;
        g_ -= f_;
        return g_;
    }
};

long long fibI(int n);
long long fib(int n);
long long fib(int n, long long& prev);

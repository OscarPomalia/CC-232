#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace ods {

template <typename T>
class Stack {
private:
    std::vector<T> data_;

public:
    Stack() = default;

    int size() const {
        return static_cast<int>(data_.size());
    }

    bool empty() const {
        return data_.empty();
    }

    void clear() {
        data_.clear();
    }

    void push(const T& value) {
        data_.push_back(value);
    }

    void push(T&& value) {
        data_.push_back(std::move(value));
    }

    T pop() {
        assert(!empty());
        T value = std::move(data_.back());
        data_.pop_back();
        return value;
    }

    T& top() {
        assert(!empty());
        return data_.back();
    }

    const T& top() const {
        assert(!empty());
        return data_.back();
    }

    const std::vector<T>& data() const {
        return data_;
    }

    std::vector<T> toVector() const {
        return data_;
    }
};

} // namespace ods

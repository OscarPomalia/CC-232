#pragma once

#include <cassert>
#include <deque>
#include <utility>

namespace ods {

template <typename T>
class Queue {
private:
    std::deque<T> data_;

public:
    Queue() = default;

    int size() const {
        return static_cast<int>(data_.size());
    }

    bool empty() const {
        return data_.empty();
    }

    void clear() {
        data_.clear();
    }

    void enqueue(const T& value) {
        data_.push_back(value);
    }

    void enqueue(T&& value) {
        data_.push_back(std::move(value));
    }

    T dequeue() {
        assert(!empty());
        T value = std::move(data_.front());
        data_.pop_front();
        return value;
    }

    T& front() {
        assert(!empty());
        return data_.front();
    }

    const T& front() const {
        assert(!empty());
        return data_.front();
    }

    const std::deque<T>& data() const {
        return data_;
    }
};

} // namespace ods

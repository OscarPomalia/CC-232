#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IntSequence {
public:
    virtual ~IntSequence() = default;
    virtual int size() const = 0;
    virtual int get(int i) const = 0;
    virtual void set(int i, int x) = 0;
    virtual void add(int i, int x) = 0;
    virtual int remove(int i) = 0;
    virtual std::string name() const = 0;
    virtual void debug_print() const = 0;
};

class FixedArraySequence final : public IntSequence {
private:
    static constexpr int kCapacity = 16;
    int data_[kCapacity]{};
    int n_ = 0;

public:
    int size() const override { return n_; }

    int get(int i) const override {
        assert(0 <= i && i < n_);
        return data_[i];
    }

    void set(int i, int x) override {
        assert(0 <= i && i < n_);
        data_[i] = x;
    }

    void add(int i, int x) override {
        assert(0 <= i && i <= n_);
        assert(n_ < kCapacity);
        for (int j = n_; j > i; --j) {
            data_[j] = data_[j - 1];
        }
        data_[i] = x;
        ++n_;
    }

    int remove(int i) override {
        assert(0 <= i && i < n_);
        const int x = data_[i];
        for (int j = i; j + 1 < n_; ++j) {
            data_[j] = data_[j + 1];
        }
        --n_;
        return x;
    }

    std::string name() const override { return "FixedArraySequence"; }

    void debug_print() const override {
        std::cout << "  rep = arreglo fijo, n=" << n_ << ", contenido = [";
        for (int i = 0; i < n_; ++i) {
            std::cout << data_[i] << (i + 1 < n_ ? ", " : "]\n");
        }
        std::cout << "  invariante: 0 <= n <= " << kCapacity << " y los datos validos estan en [0, n)\n";
    }
};

class VectorSequence final : public IntSequence {
private:
    std::vector<int> data_;

public:
    int size() const override { return static_cast<int>(data_.size()); }

    int get(int i) const override {
        assert(0 <= i && i < size());
        return data_[i];
    }

    void set(int i, int x) override {
        assert(0 <= i && i < size());
        data_[i] = x;
    }

    void add(int i, int x) override {
        assert(0 <= i && i <= size());
        data_.insert(data_.begin() + i, x);
    }

    int remove(int i) override {
        assert(0 <= i && i < size());
        const int x = data_[i];
        data_.erase(data_.begin() + i);
        return x;
    }

    std::string name() const override { return "VectorSequence"; }

    void debug_print() const override {
        std::cout << "  rep = std::vector<int>, size=" << data_.size()
                  << ", capacity=" << data_.capacity() << ", contenido = [";
        for (int i = 0; i < size(); ++i) {
            std::cout << data_[i] << (i + 1 < size() ? ", " : "]\n");
        }
        std::cout << "  invariante: el ADT es el mismo, cambia la representacion interna\n";
    }
};

void run_scenario(IntSequence& seq) {
    std::cout << "\n=Escenario sobre " << seq.name() << " ==\n";
    seq.add(0, 10);
    seq.add(1, 20);
    seq.add(1, 15);
    seq.debug_print();

    std::cout << "  get(1) = " << seq.get(1) << "\n";
    seq.set(1, 99);
    std::cout << "  despues de set(1, 99):\n";
    seq.debug_print();

    std::cout << "  remove(0) = " << seq.remove(0) << "\n";
    seq.debug_print();
}

int main() {
    std::cout << "ADT de secuencia: size, get, set, add, remove\n";
    std::cout << "Idea clave: el cliente usa la interfaz, no la representacion.\n";

    FixedArraySequence fixed;
    VectorSequence vec;

    run_scenario(fixed);
    run_scenario(vec);

    std::cout << "\nConclusion: misma interfaz, diferente implementacion.\n";
    return 0;
}

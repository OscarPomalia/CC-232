#pragma once

#include <cstdint>
#include <random>
#include <utility>

namespace ods {

template <class T>
class IntervalTreap {
public:
    // Un nodo representa un intervalo contiguo [l, r] de números que están "presentes" (valor 1)
    struct Node {
        T l;
        T r;
        std::uint64_t priority;
        Node* parent{nullptr};
        Node* left{nullptr};
        Node* right{nullptr};

        Node(T leftBound, T rightBound, std::uint64_t p)
            : l(leftBound), r(rightBound), priority(p) {}

        bool isLeftChild() const { return parent != nullptr && parent->left == this; }
        bool isRightChild() const { return parent != nullptr && parent->right == this; }
    };

    IntervalTreap() : rng_(232) {} // Semilla fija para pruebas reproducibles

    ~IntervalTreap() {
        clear(root_);
    }

    // --- Declaración de Operaciones Centrales (CF 817F) ---
    // A implementar en los próximos días
    void addInterval(T l, T r);     // Operación 1: Poner rango a 1
    void removeInterval(T l, T r);  // Operación 2: Poner rango a 0
    void invertInterval(T l, T r);  // Operación 3: Invertir rango
    T getMEX() const;               // Consulta: Menor entero positivo ausente

    bool empty() const { return root_ == nullptr; }

private:
    Node* root_{nullptr};
    std::mt19937_64 rng_;

    std::uint64_t nextPriority() {
        return rng_();
    }

    void clear(Node* u) {
        if (!u) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

    // --- Mecánica Base del Treap (Semana 6) ---
    void rotateLeft(Node* u) {
        if (!u || !u->right) return;
        Node* w = u->right;
        w->parent = u->parent;
        if (!u->parent) {
            root_ = w;
        } else if (u->isLeftChild()) {
            u->parent->left = w;
        } else {
            u->parent->right = w;
        }
        u->right = w->left;
        if (u->right) u->right->parent = u;
        w->left = u;
        u->parent = w;
    }

    void rotateRight(Node* u) {
        if (!u || !u->left) return;
        Node* w = u->left;
        w->parent = u->parent;
        if (!u->parent) {
            root_ = w;
        } else if (u->isLeftChild()) {
            u->parent->left = w;
        } else {
            u->parent->right = w;
        }
        u->left = w->right;
        if (u->left) u->left->parent = u;
        w->right = u;
        u->parent = w;
    }
};

} // namespace ods
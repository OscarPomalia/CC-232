#pragma once

#include <algorithm>
#include <cstdint>
#include <random>

namespace ods {

template <class T>
class IntervalTreap {
public:
    struct Node {
        T l, r;
        std::uint64_t priority;
        Node* parent{nullptr};
        Node* left{nullptr};
        Node* right{nullptr};

        Node(T leftBound, T rightBound, std::uint64_t p)
            : l(leftBound), r(rightBound), priority(p) {}

        bool isLeftChild() const { return parent != nullptr && parent->left == this; }
        bool isRightChild() const { return parent != nullptr && parent->right == this; }
    };

    IntervalTreap() : rng_(232) {}

    ~IntervalTreap() { clear(root_); }

    // --- Operación 1: Añadir un intervalo (Fusionando solapamientos) ---
    void addInterval(T L, T R) {
        T newL = L;
        T newR = R;

        // 1. Encontrar y eliminar todos los intervalos que se solapan o tocan con [L, R]
        // Dos intervalos [a,b] y [c,d] se tocan/solapan si: max(a,c) <= min(b,d) + 1
        Node* u = lowerBound(newL - 1);
        while (u != nullptr && u->l <= newR + 1) {
            // Expandimos nuestros límites para absorber al nodo existente
            newL = std::min(newL, u->l);
            newR = std::max(newR, u->r);
            
            // Eliminamos el nodo viejo
            Node* next = successor(u);
            removeNode(u);
            u = next;
        }

        // 2. Insertamos el nuevo gran intervalo fusionado
        insertNode(new Node(newL, newR, nextPriority()));
    }

    void removeInterval(T L, T R) {} // TODO: Día 4
    void invertInterval(T L, T R) {} // TODO: Día 4
    T getMEX() const { return 1; }   // TODO: Día 4

    bool empty() const { return root_ == nullptr; }

private:
    Node* root_{nullptr};
    std::mt19937_64 rng_;
    std::uint64_t nextPriority() { return rng_(); }

    void clear(Node* u) {
        if (!u) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

    // --- Búsquedas (Semanas 5 y 6) ---
    Node* lowerBound(T v) const {
        Node* w = root_;
        Node* candidate = nullptr;
        while (w != nullptr) {
            if (w->r >= v) {
                candidate = w;
                w = w->left; // Buscamos uno más a la izquierda que también cumpla
            } else {
                w = w->right;
            }
        }
        return candidate;
    }

    Node* successor(Node* u) const {
        if (u->right) {
            u = u->right;
            while (u->left) u = u->left;
            return u;
        }
        while (u->isRightChild()) u = u->parent;
        return u->parent;
    }

    // --- Inserción y Borrado base de Treap ---
    void insertNode(Node* u) {
        if (!root_) {
            root_ = root_ = u;
            return;
        }
        Node* w = root_;
        Node* p = nullptr;
        while (w != nullptr) {
            p = w;
            if (u->l < w->l) w = w->left;
            else w = w->right;
        }
        u->parent = p;
        if (u->l < p->l) p->left = u;
        else p->right = u;
        
        bubbleUp(u);
    }

    void removeNode(Node* u) {
        trickleDown(u);
        Node* p = u->parent;
        if (p) {
            if (u->isLeftChild()) p->left = nullptr;
            else p->right = nullptr;
        } else {
            root_ = nullptr;
        }
        delete u;
    }

    // --- Rotaciones y Mantenimiento del Heap ---
    void rotateLeft(Node* u) {
        if (!u || !u->right) return;
        Node* w = u->right;
        w->parent = u->parent;
        if (!u->parent) root_ = w;
        else if (u->isLeftChild()) u->parent->left = w;
        else u->parent->right = w;
        u->right = w->left;
        if (u->right) u->right->parent = u;
        w->left = u;
        u->parent = w;
    }

    void rotateRight(Node* u) {
        if (!u || !u->left) return;
        Node* w = u->left;
        w->parent = u->parent;
        if (!u->parent) root_ = w;
        else if (u->isLeftChild()) u->parent->left = w;
        else u->parent->right = w;
        u->left = w->right;
        if (u->left) u->left->parent = u;
        w->right = u;
        u->parent = w;
    }

    void bubbleUp(Node* u) {
        while (u->parent && u->priority < u->parent->priority) {
            if (u->isRightChild()) rotateLeft(u->parent);
            else rotateRight(u->parent);
        }
        if (!u->parent) root_ = u;
    }

    void trickleDown(Node* u) {
        while (u->left || u->right) {
            if (!u->left) rotateLeft(u);
            else if (!u->right) rotateRight(u);
            else if (u->left->priority < u->right->priority) rotateRight(u);
            else rotateLeft(u);
            if (root_ == u) root_ = u->parent;
        }
    }
};

} // namespace ods
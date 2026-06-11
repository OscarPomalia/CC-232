#pragma once

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>
#include <utility>

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

    // --- Operación 1: Añadir (Poner a 1) ---
    void addInterval(T L, T R) {
        T newL = L, newR = R;
        Node* u = lowerBound(newL - 1);
        std::vector<Node*> toRemove;

        // Recolectamos solapamientos o adyacencias
        while (u != nullptr && u->l <= newR + 1) {
            newL = std::min(newL, u->l);
            newR = std::max(newR, u->r);
            toRemove.push_back(u);
            u = successor(u);
        }

        for (Node* n : toRemove) removeNode(n);
        insertNode(new Node(newL, newR, nextPriority()));
    }

    // --- Operación 2: Remover (Poner a 0) ---
    void removeInterval(T L, T R) {
        Node* u = lowerBound(L);
        std::vector<Node*> toRemove;
        std::vector<std::pair<T, T>> toAdd;

        // Recolectamos nodos afectados y calculamos los recortes (splits)
        while (u != nullptr && u->l <= R) {
            toRemove.push_back(u);
            if (u->l < L) toAdd.push_back({u->l, L - 1}); // Parte izquierda que sobrevive
            if (u->r > R) toAdd.push_back({R + 1, u->r}); // Parte derecha que sobrevive
            u = successor(u);
        }

        for (Node* n : toRemove) removeNode(n);
        for (auto& p : toAdd) insertNode(new Node(p.first, p.second, nextPriority()));
    }

    // --- Operación 3: Invertir (0s a 1s y 1s a 0s) ---
    void invertInterval(T L, T R) {
        Node* u = lowerBound(L);
        std::vector<std::pair<T, T>> newOnes;
        T currentL = L;

        // Detectamos los "huecos" (ceros) que ahora serán unos
        while (u != nullptr && u->l <= R) {
            if (currentL < u->l) {
                newOnes.push_back({currentL, u->l - 1});
            }
            currentL = std::max(currentL, u->r + 1);
            u = successor(u);
        }
        if (currentL <= R) {
            newOnes.push_back({currentL, R});
        }

        // Primero borramos todos los 1s en el rango, luego insertamos los nuevos 1s
        removeInterval(L, R);
        for (auto& p : newOnes) addInterval(p.first, p.second);
    }

    // --- Consulta: Menor entero positivo ausente (MEX) ---
    T getMEX() const {
        if (!root_) return 1;
        Node* u = root_;
        while (u->left) u = u->left; // Nodo con el valor mínimo
        
        // Si el primer bloque contiene al 1, el MEX es el primer número libre a su derecha
        if (u->l <= 1) return u->r + 1;
        return 1;
    }

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

    Node* lowerBound(T v) const {
        Node* w = root_;
        Node* candidate = nullptr;
        while (w != nullptr) {
            if (w->r >= v) {
                candidate = w;
                w = w->left;
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

    void insertNode(Node* u) {
        if (!root_) {
            root_ = u;
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
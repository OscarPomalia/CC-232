#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace ods {

template <typename T, typename Compare = std::less<T>>
class AVLTreeCompact {
 public:
  struct Node {
    T data{};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};
    int height{0};

    Node() = default;

    explicit Node(const T& value, Node* p = nullptr)
        : data(value), parent(p) {}
  };

  AVLTreeCompact() = default;

  AVLTreeCompact(std::initializer_list<T> init) {
    for (const auto& v : init) insert(v);
  }

  AVLTreeCompact(const AVLTreeCompact&) = delete;

  AVLTreeCompact& operator=(const AVLTreeCompact&) = delete;

  ~AVLTreeCompact() {
    clear();
  }

  Node* root() const {
    return root_;
  }

  std::size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  int height() const {
    return stature(root_);
  }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  Node* search(const T& value) const {
    return findNode(value);
  }

  bool contains(const T& value) const {
    return findNode(value) != nullptr;
  }

  Node* insert(const T& value) {
    if (!root_) {
      root_ = new Node(value);
      size_ = 1;
      return root_;
    }

    Node* parent = nullptr;
    Node* cur = root_;

    while (cur) {
      parent = cur;

      if (comp_(value, cur->data)) {
        cur = cur->left;
      } else if (comp_(cur->data, value)) {
        cur = cur->right;
      } else {
        return cur;
      }
    }

    Node* x = new Node(value, parent);

    if (comp_(value, parent->data)) {
      parent->left = x;
    } else {
      parent->right = x;
    }

    ++size_;

    for (Node* g = parent; g; g = g->parent) {
      updateHeight(g);

      if (!avlBalanced(g)) {
        rotateAt(tallerChild(tallerChild(g)));
        break;
      }
    }

    return x;
  }

  bool remove(const T& value) {
    Node* x = findNode(value);

    if (!x) return false;

    Node* hot = removeAt(x);
    --size_;

    for (Node* g = hot; g;) {
      updateHeight(g);

      if (!avlBalanced(g)) {
        Node* r = rotateAt(tallerChild(tallerChild(g)));
        g = r ? r->parent : nullptr;
      } else {
        g = g->parent;
      }
    }

    return true;
  }

  std::vector<T> inorder() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  std::vector<T> levelOrder() const {
    std::vector<T> out;

    if (!root_) return out;

    std::queue<Node*> q;
    q.push(root_);

    while (!q.empty()) {
      Node* u = q.front();
      q.pop();

      out.push_back(u->data);

      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }

    return out;
  }

  bool isBST() const {
    return isBST(root_, nullptr, nullptr);
  }

  bool isAVL() const {
    bool ok = true;
    validateAVL(root_, ok);
    return ok && isBST();
  }

  std::string summary() const {
    std::ostringstream oss;
    oss << "AVLTreeCompact(size=" << size()
        << ", height=" << height() << ")";
    return oss.str();
  }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};

  static int stature(Node* x) {
    return x ? x->height : -1;
  }

  static bool isLeftChild(const Node* x) {
    return x && x->parent && x->parent->left == x;
  }

  static void destroy(Node* x) {
    if (!x) return;

    destroy(x->left);
    destroy(x->right);
    delete x;
  }

  Node* findNode(const T& value) const {
    Node* cur = root_;

    while (cur) {
      if (comp_(value, cur->data)) {
        cur = cur->left;
      } else if (comp_(cur->data, value)) {
        cur = cur->right;
      } else {
        return cur;
      }
    }

    return nullptr;
  }

  static void inorder(Node* x, std::vector<T>& out) {
    if (!x) return;

    inorder(x->left, out);
    out.push_back(x->data);
    inorder(x->right, out);
  }

  bool isBST(Node* x, const T* lo, const T* hi) const {
    if (!x) return true;
    if (lo && !comp_(*lo, x->data)) return false;
    if (hi && !comp_(x->data, *hi)) return false;

    return isBST(x->left, lo, &x->data) &&
           isBST(x->right, &x->data, hi);
  }

  int validateAVL(Node* x, bool& ok) const {
    if (!x) return -1;

    int hl = validateAVL(x->left, ok);
    int hr = validateAVL(x->right, ok);

    if (std::abs(hl - hr) > 1) ok = false;
    if (x->height != 1 + std::max(hl, hr)) ok = false;

    return 1 + std::max(hl, hr);
  }

  static void updateHeight(Node* x) {
    if (x) {
      x->height = 1 + std::max(stature(x->left), stature(x->right));
    }
  }

  static int balanceFactor(Node* x) {
    return stature(x->left) - stature(x->right);
  }

  static bool avlBalanced(Node* x) {
    return x && std::abs(balanceFactor(x)) < 2;
  }

  Node* tallerChild(Node* x) const {
    if (!x) return nullptr;

    int hl = stature(x->left);
    int hr = stature(x->right);

    if (hl > hr) return x->left;
    if (hl < hr) return x->right;

    if (!x->parent) return x->left ? x->left : x->right;
    if (isLeftChild(x)) return x->left ? x->left : x->right;

    return x->right ? x->right : x->left;
  }

  Node* connect34(
      Node* a,
      Node* b,
      Node* c,
      Node* T0,
      Node* T1,
      Node* T2,
      Node* T3) {
    a->left = T0;
    if (T0) T0->parent = a;

    a->right = T1;
    if (T1) T1->parent = a;

    updateHeight(a);

    c->left = T2;
    if (T2) T2->parent = c;

    c->right = T3;
    if (T3) T3->parent = c;

    updateHeight(c);

    b->left = a;
    a->parent = b;

    b->right = c;
    c->parent = b;

    updateHeight(b);

    return b;
  }

  Node* rotateAt(Node* v) {
    if (!v || !v->parent || !v->parent->parent) return v;

    Node* p = v->parent;
    Node* g = p->parent;
    Node* gg = g->parent;
    bool gleft = (gg && gg->left == g);
    Node* r = nullptr;

    if (p == g->left) {
      if (v == p->left) {
        r = connect34(v, p, g, v->left, v->right, p->right, g->right);
      } else {
        r = connect34(p, v, g, p->left, v->left, v->right, g->right);
      }
    } else {
      if (v == p->right) {
        r = connect34(g, p, v, g->left, p->left, v->left, v->right);
      } else {
        r = connect34(g, v, p, g->left, v->left, v->right, p->right);
      }
    }

    r->parent = gg;

    if (!gg) {
      root_ = r;
    } else if (gleft) {
      gg->left = r;
    } else {
      gg->right = r;
    }

    return r;
  }

  static Node* minimum(Node* x) {
    while (x && x->left) x = x->left;

    return x;
  }

  void transplant(Node* u, Node* v) {
    if (!u->parent) {
      root_ = v;
    } else if (u->parent->left == u) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }

    if (v) v->parent = u->parent;
  }

  Node* removeAt(Node* x) {
    if (!x->left) {
      Node* hot = x->parent;
      transplant(x, x->right);
      delete x;
      return hot;
    }

    if (!x->right) {
      Node* hot = x->parent;
      transplant(x, x->left);
      delete x;
      return hot;
    }

    Node* y = minimum(x->right);
    x->data = y->data;

    Node* hot = y->parent;
    Node* replacement = y->right;

    transplant(y, y->right);
    delete y;

    if (hot == x && replacement) hot = replacement;

    return hot;
  }
};

}  // namespace ods
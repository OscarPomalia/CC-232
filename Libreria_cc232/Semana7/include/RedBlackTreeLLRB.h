#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <vector>

namespace ods {

template <typename T, typename Compare = std::less<T>>
class RedBlackTreeLLRB {
 public:
  struct Node {
    T key{};
    Node* left{nullptr};
    Node* right{nullptr};
    bool red{true};

    Node() = default;

    explicit Node(const T& value, bool is_red = true)
        : key(value), red(is_red) {}
  };

  RedBlackTreeLLRB() = default;

  RedBlackTreeLLRB(std::initializer_list<T> init) {
    for (const auto& v : init) add(v);
  }

  RedBlackTreeLLRB(const RedBlackTreeLLRB&) = delete;

  RedBlackTreeLLRB& operator=(const RedBlackTreeLLRB&) = delete;

  ~RedBlackTreeLLRB() {
    clear();
  }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  int height() const {
    return height(root_);
  }

  bool contains(const T& key) const {
    Node* x = root_;

    while (x) {
      if (comp_(key, x->key)) {
        x = x->left;
      } else if (comp_(x->key, key)) {
        x = x->right;
      } else {
        return true;
      }
    }

    return false;
  }

  bool add(const T& key) {
    bool added = false;
    root_ = insert(root_, key, added);

    if (root_) root_->red = false;

    return added;
  }

  bool remove(const T& key) {
    if (!contains(key)) return false;

    if (root_ && !isRed(root_->left) && !isRed(root_->right)) {
      root_->red = true;
    }

    bool removed = false;
    root_ = erase(root_, key, removed);

    if (root_) root_->red = false;

    return removed;
  }

  std::vector<T> inorder() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  bool isRedBlackTree() const {
    if (root_ && root_->red) return false;

    int bh = -1;
    return validate(root_, nullptr, nullptr, 0, bh);
  }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};

  bool equals(const T& a, const T& b) const {
    return !comp_(a, b) && !comp_(b, a);
  }

  static bool isRed(Node* x) {
    return x && x->red;
  }

  static int height(Node* x) {
    return x ? 1 + std::max(height(x->left), height(x->right)) : -1;
  }

  static void destroy(Node* x) {
    if (!x) return;

    destroy(x->left);
    destroy(x->right);
    delete x;
  }

  static Node* rotateLeft(Node* h) {
    Node* x = h->right;

    h->right = x->left;
    x->left = h;
    x->red = h->red;
    h->red = true;

    return x;
  }

  static Node* rotateRight(Node* h) {
    Node* x = h->left;

    h->left = x->right;
    x->right = h;
    x->red = h->red;
    h->red = true;

    return x;
  }

  static void flipColors(Node* h) {
    h->red = !h->red;

    if (h->left) h->left->red = !h->left->red;
    if (h->right) h->right->red = !h->right->red;
  }

  static Node* fixUp(Node* h) {
    if (isRed(h->right) && !isRed(h->left)) {
      h = rotateLeft(h);
    }

    if (isRed(h->left) && isRed(h->left->left)) {
      h = rotateRight(h);
    }

    if (isRed(h->left) && isRed(h->right)) {
      flipColors(h);
    }

    return h;
  }

  static Node* moveRedLeft(Node* h) {
    flipColors(h);

    if (h->right && isRed(h->right->left)) {
      h->right = rotateRight(h->right);
      h = rotateLeft(h);
      flipColors(h);
    }

    return h;
  }

  static Node* moveRedRight(Node* h) {
    flipColors(h);

    if (h->left && isRed(h->left->left)) {
      h = rotateRight(h);
      flipColors(h);
    }

    return h;
  }

  Node* insert(Node* h, const T& key, bool& added) {
    if (!h) {
      added = true;
      ++size_;
      return new Node(key, true);
    }

    if (comp_(key, h->key)) {
      h->left = insert(h->left, key, added);
    } else if (comp_(h->key, key)) {
      h->right = insert(h->right, key, added);
    } else {
      return h;
    }

    return fixUp(h);
  }

  static Node* minNode(Node* h) {
    while (h && h->left) h = h->left;

    return h;
  }

  Node* eraseMin(Node* h) {
    if (!h->left) {
      delete h;
      --size_;
      return nullptr;
    }

    if (!isRed(h->left) && !isRed(h->left->left)) {
      h = moveRedLeft(h);
    }

    h->left = eraseMin(h->left);

    return fixUp(h);
  }

  Node* erase(Node* h, const T& key, bool& removed) {
    if (comp_(key, h->key)) {
      if (h->left) {
        if (!isRed(h->left) && !isRed(h->left->left)) {
          h = moveRedLeft(h);
        }

        h->left = erase(h->left, key, removed);
      }
    } else {
      if (isRed(h->left)) {
        h = rotateRight(h);
      }

      if (equals(key, h->key) && h->right == nullptr) {
        delete h;
        --size_;
        removed = true;
        return nullptr;
      }

      if (h->right) {
        if (!isRed(h->right) && !isRed(h->right->left)) {
          h = moveRedRight(h);
        }

        if (equals(key, h->key)) {
          Node* x = minNode(h->right);
          h->key = x->key;
          h->right = eraseMin(h->right);
          removed = true;
        } else {
          h->right = erase(h->right, key, removed);
        }
      }
    }

    return fixUp(h);
  }

  static void inorder(Node* x, std::vector<T>& out) {
    if (!x) return;

    inorder(x->left, out);
    out.push_back(x->key);
    inorder(x->right, out);
  }

  bool validate(Node* x, const T* lo, const T* hi, int blacks, int& expected_bh) const {
    if (!x) {
      if (expected_bh == -1) expected_bh = blacks;

      return expected_bh == blacks;
    }

    if (lo && !comp_(*lo, x->key)) return false;
    if (hi && !comp_(x->key, *hi)) return false;
    if (isRed(x->right)) return false;
    if (isRed(x) && (isRed(x->left) || isRed(x->right))) return false;

    int next = blacks + (x->red ? 0 : 1);

    return validate(x->left, lo, &x->key, next, expected_bh) &&
           validate(x->right, &x->key, hi, next, expected_bh);
  }
};

}  // namespace ods
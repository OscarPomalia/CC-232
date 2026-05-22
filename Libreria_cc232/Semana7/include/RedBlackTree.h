#pragma once

#include <cassert>
#include <vector>

#include "BinarySearchTree.h"

namespace ods {

template <class Node, class T>
class RedBlackNode : public BSTNode<Node, T> {
 protected:
  template <class N, class U, class C>
  friend class RedBlackTree;
  int colour{0};
};

template <class Node, class T, class Compare = std::less<T>>
class RedBlackTree : public BinarySearchTree<Node, T, Compare> {
 protected:
  using BinaryTree<Node>::r;
  using BinaryTree<Node>::nil;
  using BinarySearchTree<Node, T, Compare>::n;
  using BinarySearchTree<Node, T, Compare>::findLast;
  using BinarySearchTree<Node, T, Compare>::splice;
  using BinarySearchTree<Node, T, Compare>::add;
  using BinarySearchTree<Node, T, Compare>::rotateLeft;
  using BinarySearchTree<Node, T, Compare>::rotateRight;
  using BinarySearchTree<Node, T, Compare>::eq;

  static constexpr int red = 0;
  static constexpr int black = 1;

  void pushBlack(Node* u) {
    --u->colour;
    ++u->left->colour;
    ++u->right->colour;
  }

  void pullBlack(Node* u) {
    ++u->colour;
    --u->left->colour;
    --u->right->colour;
  }

  void swapColours(Node* u, Node* w) {
    int tmp = u->colour;
    u->colour = w->colour;
    w->colour = tmp;
  }

  void flipLeft(Node* u) {
    swapColours(u, u->right);
    rotateLeft(u);
  }

  void flipRight(Node* u) {
    swapColours(u, u->left);
    rotateRight(u);
  }

  void addFixup(Node* u) {
    while (u->colour == red) {
      if (u == r) {
        u->colour = black;
        return;
      }
      Node* w = u->parent;
      if (w->left->colour == black) {
        flipLeft(w);
        u = w;
        w = u->parent;
      }
      if (w->colour == black) return;
      Node* g = w->parent;
      if (g->right->colour == black) {
        flipRight(g);
        return;
      }
      pushBlack(g);
      u = g;
    }
  }

  Node* removeFixupCase1(Node* u) {
    flipRight(u->parent);
    return u;
  }

  Node* removeFixupCase2(Node* u) {
    Node* w = u->parent;
    Node* v = w->right;
    pullBlack(w);
    flipLeft(w);
    Node* q = w->right;
    if (q->colour == red) {
      rotateLeft(w);
      flipRight(v);
      pushBlack(q);
      if (v->right->colour == red) flipLeft(v);
      return q;
    }
    return v;
  }

  Node* removeFixupCase3(Node* u) {
    Node* w = u->parent;
    Node* v = w->left;
    pullBlack(w);
    flipRight(w);
    Node* q = w->left;
    if (q->colour == red) {
      rotateRight(w);
      flipLeft(v);
      pushBlack(q);
      return q;
    }
    if (v->left->colour == red) {
      pushBlack(v);
      return v;
    }
    flipLeft(v);
    return w;
  }

  void removeFixup(Node* u) {
    while (u->colour > black) {
      if (u == r) {
        u->colour = black;
      } else if (u->parent->left->colour == red) {
        u = removeFixupCase1(u);
      } else if (u == u->parent->left) {
        u = removeFixupCase2(u);
      } else {
        u = removeFixupCase3(u);
      }
    }
    if (u != r) {
      Node* w = u->parent;
      if (w->right->colour == red && w->left->colour == black) flipLeft(w);
    }
  }

  int verify(Node* u) const {
    if (u == nil) return u->colour;
    assert(u->colour == red || u->colour == black);
    if (u->colour == red) {
      assert(u->left->colour == black && u->right->colour == black);
    }
    assert(u->right->colour == black || u->left->colour == red);
    int dl = verify(u->left);
    int dr = verify(u->right);
    assert(dl == dr);
    return dl + u->colour;
  }

  void inorder(Node* u, std::vector<T>& out) const {
    if (u == nil) return;
    inorder(u->left, out);
    out.push_back(u->x);
    inorder(u->right, out);
  }

 public:
  RedBlackTree() {
    nil->left = nil->right = nil->parent = nil;
    nil->colour = black;
    r = nil;
  }

  virtual ~RedBlackTree() = default;

  bool add(const T& x) override {
    Node* u = new Node();
    u->left = u->right = u->parent = nil;
    u->x = x;
    u->colour = red;
    bool added = BinarySearchTree<Node, T, Compare>::add(u);
    if (!added) {
      delete u;
      return false;
    }
    addFixup(u);
    return true;
  }

  bool remove(const T& x) override {
    Node* u = findLast(x);
    if (u == nil || !eq(u->x, x)) return false;

    Node* w = u->right;
    if (w == nil) {
      w = u;
      u = w->left;
    } else {
      while (w->left != nil) w = w->left;
      u->x = w->x;
      u = w->right;
    }

    splice(w);
    u->colour += w->colour;
    u->parent = w->parent;
    delete w;
    removeFixup(u);
    return true;
  }

  bool verifyRB() const {
    if (r == nil) return true;
    if (r->colour != black) return false;
    verify(r);
    return true;
  }

  int size() const { return n; }

  std::vector<T> inorder() const {
    std::vector<T> out;
    inorder(r, out);
    return out;
  }
};

template <class T>
class RedBlackNode1 : public RedBlackNode<RedBlackNode1<T>, T> {};

template <class T, class Compare = std::less<T>>
class RedBlackTree1 : public RedBlackTree<RedBlackNode1<T>, T, Compare> {};

}  // namespace ods

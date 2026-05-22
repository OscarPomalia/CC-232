#pragma once

#include <cstddef>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

namespace ods {

enum class InorderStrategy {
  Recursive,
  Iterative1,
  Iterative2,
  Iterative3,
};

template <typename T>
struct BinNode {
  using Node = BinNode<T>;

  T data{};
  Node* parent{nullptr};
  Node* left{nullptr};
  Node* right{nullptr};
  int height{0};

  BinNode() = default;

  explicit BinNode(const T& value, Node* p = nullptr)
      : data(value), parent(p) {}

  bool hasLeft() const { return left != nullptr; }
  bool hasRight() const { return right != nullptr; }
  bool isRoot() const { return parent == nullptr; }
  bool isLeaf() const { return left == nullptr && right == nullptr; }
  bool isLeftChild() const { return parent != nullptr && parent->left == this; }
  bool isRightChild() const { return parent != nullptr && parent->right == this; }

  Node* insertAsLC(const T& value) {
    if (left != nullptr) {
      throw std::logic_error("El hijo izquierdo ya existe");
    }
    left = new Node(value, this);
    return left;
  }

  Node* insertAsRC(const T& value) {
    if (right != nullptr) {
      throw std::logic_error("El hijo derecho ya existe");
    }
    right = new Node(value, this);
    return right;
  }

  std::size_t size() const {
    const std::size_t ls = (left == nullptr) ? 0U : left->size();
    const std::size_t rs = (right == nullptr) ? 0U : right->size();
    return 1U + ls + rs;
  }

  Node* leftmost() {
    Node* u = this;
    while (u->left != nullptr) {
      u = u->left;
    }
    return u;
  }

  const Node* leftmost() const {
    const Node* u = this;
    while (u->left != nullptr) {
      u = u->left;
    }
    return u;
  }

  Node* rightmost() {
    Node* u = this;
    while (u->right != nullptr) {
      u = u->right;
    }
    return u;
  }

  const Node* rightmost() const {
    const Node* u = this;
    while (u->right != nullptr) {
      u = u->right;
    }
    return u;
  }

  Node* succ() {
    Node* s = this;
    if (right != nullptr) {
      s = right;
      while (s->left != nullptr) {
        s = s->left;
      }
      return s;
    }
    while (s->isRightChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  const Node* succ() const {
    const Node* s = this;
    if (right != nullptr) {
      s = right;
      while (s->left != nullptr) {
        s = s->left;
      }
      return s;
    }
    while (s->isRightChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  Node* pred() {
    Node* s = this;
    if (left != nullptr) {
      s = left;
      while (s->right != nullptr) {
        s = s->right;
      }
      return s;
    }
    while (s->isLeftChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  const Node* pred() const {
    const Node* s = this;
    if (left != nullptr) {
      s = left;
      while (s->right != nullptr) {
        s = s->right;
      }
      return s;
    }
    while (s->isLeftChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  template <typename Visit>
  void travPre(Visit visit) {
    visit(*this);
    if (left != nullptr) {
      left->travPre(visit);
    }
    if (right != nullptr) {
      right->travPre(visit);
    }
  }

  template <typename Visit>
  void travPreIterative2(Visit visit) {
    std::stack<Node*> st;
    st.push(this);
    while (!st.empty()) {
      Node* u = st.top();
      st.pop();
      visit(*u);
      if (u->right != nullptr) {
        st.push(u->right);
      }
      if (u->left != nullptr) {
        st.push(u->left);
      }
    }
  }

  template <typename Visit>
  void travInRecursive(Visit visit) {
    if (left != nullptr) {
      left->travInRecursive(visit);
    }
    visit(*this);
    if (right != nullptr) {
      right->travInRecursive(visit);
    }
  }

  template <typename Visit>
  void travInIterative1(Visit visit) {
    std::stack<Node*> st;
    Node* u = this;
    while (u != nullptr || !st.empty()) {
      while (u != nullptr) {
        st.push(u);
        u = u->left;
      }
      u = st.top();
      st.pop();
      visit(*u);
      u = u->right;
    }
  }

  template <typename Visit>
  void travInIterative2(Visit visit) {
    Node* prev = nullptr;
    Node* curr = this;
    while (curr != nullptr) {
      Node* next = nullptr;
      if (prev == curr->parent) {
        if (curr->left != nullptr) {
          next = curr->left;
        } else {
          visit(*curr);
          next = (curr->right != nullptr) ? curr->right : curr->parent;
        }
      } else if (prev == curr->left) {
        visit(*curr);
        next = (curr->right != nullptr) ? curr->right : curr->parent;
      } else {
        next = curr->parent;
      }
      prev = curr;
      curr = next;
    }
  }

  template <typename Visit>
  void travInIterative3(Visit visit) {
    Node* end = rightmost()->succ();
    for (Node* u = leftmost(); u != end; u = u->succ()) {
      visit(*u);
    }
  }

  template <typename Visit>
  void travIn(Visit visit, InorderStrategy strategy = InorderStrategy::Recursive) {
    switch (strategy) {
      case InorderStrategy::Recursive:
        travInRecursive(visit);
        break;
      case InorderStrategy::Iterative1:
        travInIterative1(visit);
        break;
      case InorderStrategy::Iterative2:
        travInIterative2(visit);
        break;
      case InorderStrategy::Iterative3:
        travInIterative3(visit);
        break;
    }
  }

  template <typename Visit>
  void travPost(Visit visit) {
    if (left != nullptr) {
      left->travPost(visit);
    }
    if (right != nullptr) {
      right->travPost(visit);
    }
    visit(*this);
  }

  template <typename Visit>
  void travPostIterative(Visit visit) {
    std::stack<Node*> s1;
    std::stack<Node*> s2;
    s1.push(this);
    while (!s1.empty()) {
      Node* u = s1.top();
      s1.pop();
      s2.push(u);
      if (u->left != nullptr) {
        s1.push(u->left);
      }
      if (u->right != nullptr) {
        s1.push(u->right);
      }
    }
    while (!s2.empty()) {
      visit(*s2.top());
      s2.pop();
    }
  }

  template <typename Visit>
  void travLevel(Visit visit) {
    std::queue<Node*> q;
    q.push(this);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      visit(*u);
      if (u->left != nullptr) {
        q.push(u->left);
      }
      if (u->right != nullptr) {
        q.push(u->right);
      }
    }
  }
};

template <typename T>
inline int stature(const BinNode<T>* node) {
  return node == nullptr ? -1 : node->height;
}

template <typename T>
inline std::vector<T> preorderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPre([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> preorderValuesIterative(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPreIterative2([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> inorderValues(BinNode<T>* root,
                                    InorderStrategy strategy = InorderStrategy::Recursive) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travIn([&out](const BinNode<T>& node) { out.push_back(node.data); }, strategy);
  }
  return out;
}

template <typename T>
inline std::vector<T> postorderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPost([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> postorderValuesIterative(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPostIterative([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> levelOrderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travLevel([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

}  // namespace ods

/**
 * @file   BalanceTree.h
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sat Nov 13 23:50:33
 * 
 * @brief  Inplementation of AVLTree class and SplayTree class.
 */
#ifndef _lcrBT_
#define _lcrBT_

#include <iostream>
#include <new>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Comparable>
class AVLTree
{
 public:
  AVLTree()
  {
    root = nullptr;
  }
  
  AVLTree(const AVLTree & rhs): root{nullptr}
  {
    root = clone(rhs.root);
  }
  
  ~AVLTree()
  {
    makeEmpty();
  }

  void printTree(vector<Comparable> & _d) 
  {
    printTree(root, _d);
  }
  
  void makeEmpty()
  {
    makeEmpty(root);
  }
  
  void insert(const Comparable & x)
  {
    insert(x, root);
  }

 private:
  struct AvlNode
  {
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;

  AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
    :element{ele}, left{lt}, right{rt}, height{h} {}
  };

  AvlNode *root;

  // Print the AVLTree using inorder travesal.
  void printTree(AvlNode *t, vector<Comparable> & _d) 
  {
    if (t == nullptr)
      return;
    printTree(t->left, _d);
    _d.push_back(t->element);
    printTree(t->right, _d);
  }
  
  void makeEmpty(AvlNode * &t)
  {
    if (t != nullptr)
    {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  int height(AvlNode *t) const
  {
    return t == nullptr ? -1: t->height;
  }

  static const int ALLOWED_IMBALANCE = 1;
  
  void insert(const Comparable & x, AvlNode * &t)
  {
    if (t == nullptr)
      t = new AvlNode{x, nullptr, nullptr};
    else if (x < t->element)
      insert(x, t->left);
    else if (x > t->element)
      insert(x, t->right);

    balance(t);
  }

  void balance(AvlNode * &t)
  {
    if (t == nullptr)
      return;
    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
      if (height(t->left->left) >= height(t->left->right))
	rotateWithLeftChild(t);
      else
	doubleWithLeftChild(t);
    else
    if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
      if (height(t->right->right) >= height(t->right->left))
	rotateWithRightChild(t);
      else
	doubleWithRightChild(t);

    t->height = max(height(t->left), height(t->right)) + 1;
  }

  void rotateWithLeftChild(AvlNode * & k2)
  {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }

  void rotateWithRightChild(AvlNode * & k2)
  {
    AvlNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
  }

  void doubleWithLeftChild(AvlNode * & k3)
  {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void doubleWithRightChild(AvlNode * & k1)
  {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }

  // Clones data.
  AvlNode *clone(AvlNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
  }
};


template <typename Comparable>
class SplayTree
{
 public:
  SplayTree()
  {
    root = nullptr;
  }
  
  SplayTree(const SplayTree & rhs): root{nullptr}
  {
    root = clone(rhs.root);
  }
  
  ~SplayTree()
  {
    makeEmpty();
  }

  void printTree(vector<Comparable> & _d) 
  {
    printTree(root, _d);
  }
  
  void makeEmpty()
  {
    makeEmpty(root);
  }
  
  void insert(const Comparable & x)
  {
    insert(x, root);
  }

 private:
  struct SplayNode
  {
    Comparable element;
    SplayNode *left;
    SplayNode *right; // Height of SplayTree is not neccessary.

  SplayNode(const Comparable & ele, SplayNode *lt, SplayNode *rt)
    :element{ele}, left{lt}, right{rt} {}
  };

  SplayNode *root;

  // Print the SplayTree using inorder travesal.
  void printTree(SplayNode *t, vector<Comparable> & _d) 
  {
    if (t == nullptr)
      return;
    printTree(t->left, _d);
    _d.push_back(t->element);
    printTree(t->right, _d);
  }
  
  void makeEmpty(SplayNode * &t)
  {
    if (t != nullptr)
    {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  
  void insert(const Comparable & x, SplayNode * &t)
  {
    if (t == nullptr)
      t = new SplayNode{x, nullptr, nullptr};
    else if (x < t->element)
      insert(x, t->left);
    else if (x > t->element)
      insert(x, t->right);

    splay(x,t);
  }

  // Bottom-up splay.
  void splay(const Comparable & x, SplayNode * &t)
  {
    if (t == nullptr)
      return;
    if (t == root)
    {
      if (t->right != nullptr && t->right->element == x)
      	rotateWithRightChild(t);
      else if (t->left != nullptr && t->left->element == x)
	rotateWithLeftChild(t);
    }
    else if (t->left != nullptr && t->left->left != nullptr
	     && t->left->left->element == x) // Zig-zig case.
      {
	rotateWithLeftChild(t->left);
	rotateWithLeftChild(t);
	rotateWithLeftChild(t->right);
      }
    else if (t->left != nullptr && t->left->right != nullptr
	     && t->left->right->element == x) // Zig-zag case.
        doubleWithLeftChild(t);
    else if (t->right != nullptr && t->right->right != nullptr
	     && t->right->right->element == x) // Zig-zig case.
      {
	rotateWithRightChild(t->right);
	rotateWithRightChild(t);
	rotateWithRightChild(t->left);
      }
    else if (t->right != nullptr && t->right->left != nullptr
	     && t->right->left->element == x) // Zig-zag case.
        doubleWithRightChild(t);
  }

  void rotateWithLeftChild(SplayNode * & k2)
  {
    SplayNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
  }

  void rotateWithRightChild(SplayNode * & k2)
  {
    SplayNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2 = k1;
  }

  void doubleWithLeftChild(SplayNode * & k3)
  {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void doubleWithRightChild(SplayNode * & k1)
  {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }

  // Clones data.
  SplayNode *clone(SplayNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new SplayNode{t->element, clone(t->left), clone(t->right)};
  }
};


#else
/// DO NOTHING.
#endif

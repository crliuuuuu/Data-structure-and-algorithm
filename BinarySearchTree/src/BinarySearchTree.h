/**
 * @file   BinarySearchTree.h
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Fri Oct 29 16:06:20
 * 
 * @brief  Inplementation of BinarySearchTree class.
 */
#ifndef _lcrBST_
#define _lcrBST_

#include <iostream>
#include <new>
#include <vector>

using namespace std;

template <typename Comparable>
class BinarySearchTree
{
 public:
  BinarySearchTree()
  {
    root = nullptr;
  }
  
  BinarySearchTree(const BinarySearchTree & rhs): root{nullptr}
  {
    root = clone(rhs.root);
  }
  
  ~BinarySearchTree()
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
  struct BinaryNode
  {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
    :element{theElement}, left{lt}, right{rt} {}
  };

  BinaryNode *root;

  // Print the Binary Search Tree using inorder travesal.
  void printTree(BinaryNode *t, vector<Comparable> & _d) 
  {
    if (t == nullptr)
      return;
    printTree(t->left, _d);
    _d.push_back(t->element);
    printTree(t->right, _d);
  }
  
  void makeEmpty(BinaryNode * &t)
  {
    if (t != nullptr)
    {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }
  
  void insert(const Comparable & x, BinaryNode * &t)
  {
    if (t == nullptr)
      t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
      insert(x, t->left);
    else if (x > t->element)
      insert(x, t->right);
    else
      ;
  }
  
  BinaryNode *clone(BinaryNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new BinaryNode{t->element, clone(t->left), clone(t->right)};
  }
};

#else
/// DO NOTHING.
#endif

#ifndef BINARYTREE
#define BINARYTREE
#include"leaf.h"
template <class A>class Leaf;
template <class A>
class BinaryTree
{
  private :
    Leaf<A>* root;
    int count;
    void addAux(Leaf<A>** root,Leaf<A> * node);
    void traverseTreeAux(Leaf<A> * root,void(*function)(A node));
    void removeTreeAux(Leaf<A> *root);
    Leaf<A> *searchAux(Leaf<A>* root,int value);
  public :
  BinaryTree();
  void add(A value,int v);
  void traverseTree(void(*function)(A node));
  int getSize();
  Leaf<A> * getRoot();
  void removeTree();
  Leaf<A> *search(int value);

};
template<class A>
void BinaryTree<A>::addAux(Leaf<A>** root,Leaf<A> * node)
    {
        if(!*root)
        {
            *root=node;
        }
        else if(node->v<(*root)->v)
           addAux(&(*root)->left,node);
        else
           addAux(&(*root)->right,node);
    }

template<class A>
void BinaryTree<A>::traverseTreeAux(Leaf<A> * root,void(*function)(A node))
  {
      if(root)
      {
          traverseTreeAux(root->left,function);
          function(root->value);
          traverseTreeAux(root->right,function);
      }
  }
template<class A>
BinaryTree<A>::BinaryTree()
  :count(0)
  {
 root=NULL;
  }

template<class A>
void BinaryTree<A>::add(A value,int v)
  {
   Leaf<A> * node = new Leaf<A> (NULL,NULL,value,v);
   addAux(&root,node);
   count++;
  }
template<class A>
void BinaryTree<A>::traverseTree(void(*function)(A node))
  {
 traverseTreeAux(root,function);
  }
template<class A>
int BinaryTree<A>::getSize()
  {
      return count;
  }
template<class A>
Leaf<A> * BinaryTree<A>::getRoot()
  {
      return root;
  }
template<class A>
void BinaryTree<A>::removeTreeAux(Leaf<A> * root)
{
    if(root)
    {
        removeTreeAux(root->left);
        removeTreeAux(root->left);
        delete root;
    }

}
template<class A>
void BinaryTree<A>::removeTree()
{
    removeTreeAux(root);
}
template <class A>
Leaf<A> *BinaryTree<A>::search(int value)
  {
    return searchAux(root,value);
  }
template<class A>
Leaf<A> *BinaryTree<A>::searchAux(Leaf<A>* root,int value)
{
    if(!root)
    {
        return NULL;
    }

    if(root->v==value)
    {
        return  root;
    }
    if(value<root->v)
    {
         searchAux(root->left,value);
    }
    else
    {
          searchAux(root->right,value);
    }







}












#endif // BINARYTREE


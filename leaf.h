#ifndef LEAF
#define LEAF
#include<QMessageBox>
template <class A>class BinaryTree;
template <class A >
class Leaf
{
      friend class BinaryTree<A>;
  private :
   Leaf<A>* left;
   Leaf<A>* right;
   A value;
   int v;
  public :
   Leaf( Leaf<A>* l, Leaf<A>* r,A val,int vl);
   Leaf<A>* getLeft();
   Leaf<A>* getRight();
   A getValue();
   void setValue(A val);
};

template <class A>
   Leaf<A>::Leaf( Leaf<A>* l, Leaf<A>* r,A val,int vl)
  :value(val),left(l),right(r),v(vl)
  {
  }
  template <class A>
  Leaf<A>* Leaf<A>::getLeft()
  {
      return left;
  }
 template <class A>
  Leaf<A>* Leaf<A>::getRight()
  {
      return right;
  }
template <class A>
  A Leaf<A>::getValue()
  {
      return value;
  }
template<class A>
void Leaf<A>::setValue(A val)
{
  value=val;
}

#endif // LEAF


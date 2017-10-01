#include"mymapnode.h"
template <class A,class B > MYMapNode<A,B>::MYMapNode(A k , B v)
  {
      key=k;
      value=v;
      next=NULL;
      prev=NULL;

  }
 template <class A,class B > MYMapNode<A,B>::MYMapNode(A k , B v,int w)
 {
      key=k;
      value=v;
      next=NULL;
      prev=NULL;
     setWeight(w);

 }
 template <class A,class B > A MYMapNode<A,B>::getKey()
  {

      return key;

  }
  template <class A,class B > B  MYMapNode<A,B>::getValue()
  {

      return value;
  }

template <class A,class B > int MYMapNode<A,B>:: getWeight()
{
    return weight;

}
template <class A,class B > void  MYMapNode<A,B>::setWeight(int w)
{

    weight=w;
}

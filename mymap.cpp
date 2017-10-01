#include"mymap.h"
template <class A,class B >  MYMap<A,B>::MYMap()
 {
     count=0;
     first=NULL;
     last=NULL;
 }

template <class A,class B > void MYMap<A,B>::add(A k,B v)
 {
     MYMapNode<A,B> *node= new MYMapNode<A,B>(k,v);

    if(count==0)
    {

         node->next=last;
         node->prev=first;
         first=node;
         last=node;

    }
    else
    {
        node->prev=last;
        last->next=node;
        last=node;
        node->next=first;
        first->prev=last;

    }
 count++;

 }

 template <class A,class B > void MYMap<A,B>::add(A k,B v,int weight)
 {
     MYMapNode<A,B> *node= new MYMapNode<A,B>(k,v,weight);

    if(count==0)
    {

         node->next=last;
         node->prev=first;
         first=node;
         last=node;

    }
    else
    {
        node->prev=last;
        last->next=node;
        last=node;
        node->next=first;
        first->prev=last;

    }
 count++;

 }
 template <class A,class B >  MYMapNode<A,B> * MYMap<A,B>::contains(A key)
 {

     if (count==0)
     return NULL;

     MYMapNode<A,B> *holder=first;

     for(int i=0;i<count;i++)
     {
     if(holder->key==key)
     return holder;

     holder=holder->next;



     }
     return NULL;


 }


template <class A,class B >bool MYMap<A,B>::update(A key ,B value)
{

     if (count==0)
     return false;

     MYMapNode<A,B> *holder=first;

     for(int i=0;i<count;i++)
     {
     if(holder->key==key){
      holder->value=value;
       return true;
     }
     holder=holder->next;



     }
     return false;



}

template <class A,class B >MYMapNode<A,B> *  MYMap<A,B>::getMin()
  {


       if (count==0)
     return NULL;

     MYMapNode<A,B> *holder=first;
     MYMapNode<A,B> *minNode=first;
      B min ;
      min=holder->value;

      holder=holder->next;
     for(int i=1;i<count;i++)
     {
     if(holder->value<min){
      min=holder->value;
      minNode=holder;
     }
     holder=holder->next;



     }

     return minNode;





  }
  template <class A,class B > int MYMap<A,B>::getSize()
  {
      return count;
  }
  template <class A,class B >MYMapNode<A,B> * MYMap<A,B>::getFirst()
  {

      return first;
  }
  template <class A,class B >MYMapNode<A,B> * MYMap<A,B>::getLast()
  {

      return last;
  }
  template <class A,class B > MYMapNode<A,B> * MYMap<A,B>::at(int i)
  {
      if (count==0)
     return NULL;

     MYMapNode<A,B> *holder=first;

     for(int j=0;j<count;j++)
     {
     if(j==i){
      return holder;
         }
     holder=holder->next;



     }
  return NULL;


  }
 template <class A,class B >bool MYMap<A,B>::isEmpty()
  {
      return !count;
  }
template <class A,class B >bool MYMap<A,B>::remove(A k)
{



     if (count==0)
     return false;


     MYMapNode<A,B> *holder=first;

     for(int i=0;i<count;i++)
     {
     if(holder->key==k)
     {
      if(count==1)
      {

          first=NULL;
          last=NULL;

          delete holder;

      }
      else{
      if(holder==first)
      {
          first=first->next;

          holder->next->prev=holder->prev;

          holder->prev->next=holder->next;
          last->next=first;
      }
      else if(holder==last)
      {
          last=last->prev;
          holder->next->prev=holder->prev;
          holder->prev->next=holder->next;
          first->prev=last;

      }

     holder->prev->next=holder->next;
     holder->next->prev=holder->prev;


     delete holder;

      }
      count--;
       return true;
     }
     holder=holder->next;



     }
     return false;



}
  template <class A,class B >MYMapNode<A,B>* MYMap<A,B>::getMinWeight()
  {

         if (count==0)
     return NULL;

     MYMapNode<A,B> *holder=first;
     MYMapNode<A,B> *minNode=first;
      int min ;
      min=holder->weight;

      holder=holder->next;
     for(int i=1;i<count;i++)
     {
     if(holder->weight<min){
      min=holder->weight;
      minNode=holder;
     }
     holder=holder->next;



     }

     return minNode;
  }
   template <class A,class B >MYMap<A,B> *  MYMap<A,B>::createMapfromKey(A key)
  {


    MYMap<A,B> *newMap =new MYMap ;
     if (count==0)
     return NULL;



     for(int i=0;i<count;i++)
     {
     if(at(i)->getKey()==key){
      newMap->add(at(i)->getKey(),at(i)->getValue(),at(i)->getWeight());

     }

     }

     return newMap;



  }

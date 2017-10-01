#ifndef NEWER_H
#define NEWER_H

#include <QObject>
#include<time.h>
#include<QMessageBox>
#include<QMouseEvent>
#include<QPushButton>
#include<QGraphicsScene>
#include"node.h"
#include"edge.h"
#include"mymap.h"
#include"mymapnode.h"
#include"graphwidget.h"
#include<math.h>

class newer:public GraphWidget
{
Q_OBJECT
private :
QGraphicsScene *scene;
int edgeCount;
static QPushButton * addNode;
static QPushButton * findShortest;
static QPushButton * resetsh;
static QPushButton * resetG;
static QPushButton * resetALLBtn;
MYMap<Node * , Node *> *shortest;
void  drawShortest(bool c);
public:
   newer(const char * title);
   void createNode(int x,int y);
   static QPushButton * getAddBtn();
   static QPushButton * getShortestBtn();
   static QPushButton * getResetShBtn();
   static QPushButton * getResetGBtn();
   static QPushButton * getResetALLBtn();
public slots:
   void addAction();
   void findAction();
   void resetShortest();
   void resetGraph();
   void resetAll();

};
template <class A , class B>
MYMap<A,A> * getShortestPath(MYMap<A,B> *nodes,MYMap<A,A> *edges,A source,A dest,A init);


#endif // NEWER_H

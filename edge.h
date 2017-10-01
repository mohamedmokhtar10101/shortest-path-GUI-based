#ifndef EDGE_H
#define EDGE_H
#include <QGraphicsItem>
#include<QLineEdit>
#include<QKeyEvent>
#include"node.h"
#include"mymap.h"
#include"binarytree.h"
class Edge;
class TextBox :public  QLineEdit{
public:
    TextBox(QWidget * parent=0);
    ~TextBox();
    void keyPressEvent(QKeyEvent * event);
    bool IsEntered();
    static bool IsEntered2();
    static void setEnter2(bool a);
    void setEnter(bool a);
    void setEdge(Edge *e);
    Edge* getEdge();
private:
    bool enter;
    Edge * ed;
    static bool enter2;
};
class Node;
class Edge : public QGraphicsItem
{
public:


    double getWeight();
    void setWeight(double w,QString s);
    QString getsWeight();
    QPointF getSourcePoint();
    QPointF getDestPoint();
    static int getCount();
    static MYMap<Node * ,Node *> * getEdges();
    static MYMap<Node * ,int > * getNodes();
    static void resetAll();
    void resetSource();
    void resetDest();
   static BinaryTree<Node *> * getTree();
    void setShortest(bool c);
    Edge(Node *sourceNode, Node *destNode);
    Node *sourceNode() const;
    Node *destNode() const;
    void adjust();

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w) Q_DECL_OVERRIDE;
private:
    Node *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    static TextBox *box;
    static  int count;
    double weight;
    QString sweight;
    static  MYMap<Node * , Node *> * edges ;
    static  MYMap<Node * , int > * nodes ;
    static  BinaryTree<Node *>  *connectedTree;
    bool shortest;
};
#endif // EDGE_H

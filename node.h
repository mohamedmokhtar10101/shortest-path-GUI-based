

#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include<QMessageBox>
#include <QList>
#include "mymapnode.h"
#include"mymap.h"
class Node;

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE
class Node : public QGraphicsItem
{
public:

    Node(GraphWidget *graphWidget);
    ~Node();
    void addEdge(Edge *edge);
    QList<Edge *> &edges() ;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) Q_DECL_OVERRIDE;
    void setScene(QGraphicsScene *sc);
    void setPressed(bool a);
    int getValue();
    void setValue(int val);
    static Node * getSource();
    static Node * getDest();
    static void resetSource();
    static void resetDest();
    static int getSize();
    static MYMap<Node *, int> *getAllNodes();
    static void resetALL();
    QImage &getImg();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    QList<Edge *> edgeList;
    bool pressed;
    static int clickedCount;
    static int nodeCount;
    static Node * a;
    static Node * b;
    static Node * source;
    static Node * dest;
    static MYMap<Node * , int > * allNodes;
    int value;
    QGraphicsScene *sce;
    QImage img;
    GraphWidget *graph;

};


#endif // NODE_H

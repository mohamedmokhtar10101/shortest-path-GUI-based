
#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
// the initialization of static members
int Node::clickedCount=0;
int Node::nodeCount=0;
Node * Node::a=NULL;
Node * Node::b=NULL;
Node * Node::source;
Node * Node::dest;
MYMap<Node * , int > * Node::allNodes=NULL;
Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget),pressed(0),img(43,43,QImage::Format_ARGB6666_Premultiplied),value(nodeCount)
{
    if(nodeCount==0)
    {
       allNodes=new MYMap<Node * , int > ;
       allNodes->add(this,value,0);
    }
    else
       allNodes->add(this,value,0);

   setFlag(ItemIsMovable);
   setFlag(ItemSendsGeometryChanges);
   setCacheMode(DeviceCoordinateCache);
   setZValue(-1);
   img.load("0","png");
   nodeCount++;
}
Node::~Node()
{

   nodeCount --;
}
void Node::resetALL()
{

    a=NULL;
    b=NULL;
    for(int i=0,s=allNodes->getSize();i<s;i++)
    {
        if(allNodes->at(i)->getWeight()!=-1)
            delete allNodes->at(i)->getKey();
    }
    delete allNodes;
    allNodes=NULL;
    clickedCount=0;
    nodeCount=0;
    source=NULL;
    dest=NULL;
}
MYMap<Node *, int> *Node::getAllNodes()
{
    return allNodes;
}

int Node::getSize()
{
    return nodeCount;
}
 int Node::getValue()
 {
     return value;
 }

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *>& Node::edges()
{
    return edgeList;
}
QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    /*
   // painter->setPen(Qt::NoPen);
   // painter->setBrush(Qt::darkGray);
    //painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
   // painter->setBrush(gradient);
  //  painter->setPen(QPen(Qt::black, 0));
  //  painter->drawEllipse(-10, -10, 20, 20);
    */

    // change  the node shape
      painter->setViewport(0,0,25,25);
      painter->drawImage(QRect(-10,-10,20,20), img);
}
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}
 void Node::setValue(int val)
 {
     value=val;

 }

 Node * Node::getSource()
{
    return source;
}
 Node * Node::getDest()
{
    return dest;
}
QImage &Node::getImg()
{
    return img;
}
 void Node::setScene(QGraphicsScene *sc)
 {
     sce=sc;
 }
  void Node::resetSource()
  {
      source=NULL;
  }
  void  Node::resetDest()
  {
      dest=NULL;
  }
  void Node::setPressed(bool a)
  {
      pressed=a;
  }

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   // if(this->)
    pressed?pressed=0:pressed=1;
    if(this==source)
    {
        if(pressed){
        this->getImg().load("0","png");
        this->update();
        source=NULL;}
    }
    else if(this==dest)
    {
        if(pressed){
        this->getImg().load("0","png");
        this->update();
        dest=NULL;
        }
    }
    else{
    if(this ==a || this ==b)
    {
     return ;
    }
    clickedCount++;
    if(source && dest &&this!=source&&this!=dest)
    {
        source->getImg().load("0","png");
        source->update();
        dest->getImg().load("0","png");
        dest->update();
        source=NULL;
        dest=NULL;
    }
    if(a)
        b=this;
    else
        a=this;
 }
    if(clickedCount==2)
    {

        if(Edge::getCount()>0){


        bool flag=false;
        for(int i=0,s=a->edges().size();i<s;i++)
        {

            if((a->edges()[i]->sourceNode()==a&&a->edges()[i]->destNode()==b)||(a->edges()[i]->sourceNode()==b&&a->edges()[i]->destNode()==a))
            {
                flag=true;
                break;
            }
        }

        if(flag||event->button()==Qt::RightButton)
        {
            source=a;
            dest=b;
            a->getImg().load("00","png");
            a->update();
            b->getImg().load("00","png");
            b->update();
            b=NULL;
            a=NULL;
            clickedCount=0;
        }
        else
        {

            Edge *ed=new Edge(a,b);
             sce->addItem(ed);
             clickedCount=0;
             a=NULL;
             b=NULL;
        }
  }
        else
        {
            Edge *ed=new Edge(a,b);
             sce->addItem(ed);
             clickedCount=0;
             a=NULL;
             b=NULL;
        }
}
}

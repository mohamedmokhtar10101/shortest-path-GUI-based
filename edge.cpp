#include "edge.h"
#include "node.h"
#include <math.h>
#include<QIntValidator>
#include <QPainter>
#include<stdlib.h>
#include"newer.h"
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
MYMap<Node * , Node *> * Edge::edges=NULL ;
MYMap<Node * , int > * Edge::nodes=NULL ;
BinaryTree<Node *>  *Edge::connectedTree=NULL;
int Edge::count=0;
TextBox * Edge::box=NULL;
bool TextBox::enter2=true;
Edge::Edge(Node *sourceNode, Node *destNode)
    : arrowSize(10)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
    shortest=false;

    if(count==0)
    {
        box=new TextBox(newer::getAddBtn()->parentWidget());
        QFont f("Arial",9,-1,false);
        f.setBold(false);
        f.setLetterSpacing(QFont::AbsoluteSpacing,0);
        box->setFont(f);
        box->setFocus();
        box->setVisible(true);
        box->setEnter(false);
        box->setFixedWidth(50);
        box->setFixedHeight(13);
        edges = new MYMap<Node *, Node *>;
        nodes= new MYMap<Node * , int > ;
        nodes->add(sourceNode,0);
        nodes->add(destNode,0);
        connectedTree=new BinaryTree<Node *>;
        connectedTree->add(sourceNode, sourceNode->getValue());
        connectedTree->add(destNode, destNode->getValue());

    }
    else
    {
        if(!nodes->contains(sourceNode))
            nodes->add(sourceNode,0);
        if(!nodes->contains(destNode))
            nodes->add(dest,0);

        if(!connectedTree->search(sourceNode->getValue()))
        {
            connectedTree->add(sourceNode, sourceNode->getValue());

        }
        if(!connectedTree->search(destNode->getValue()))
        {
              connectedTree->add(destNode, destNode->getValue());

        }
    }
    box->setEdge(this);
    box->setVisible(true);
    count++;
    box->setEnter2(false);
}
TextBox::~TextBox()
{

    ed=NULL;
    enter2=true;
}

void Edge::resetSource()
{
    source=NULL;
}
void Edge::resetDest()
{
    dest=NULL;
}
void Edge::resetAll()
    {

      if(count>0){
         if(nodes){
         for(int i=0,s=nodes->getSize();i<s;i++) // size of nodes
         {

             for(int j=0,size=nodes->at(i)->getKey()->edges().size();j<size;j++)//size of node ->edges
             {
                 if(nodes->at(i)->getKey()->edges()[j]->sourceNode()==nodes->at(i)->getKey())//if  node -> edge ->source =node
                 {
                     if(!nodes->at(i)->getKey()->edges()[j]->destNode())   //if ! node ->edge -> dest
                         delete nodes->at(i)->getKey()->edges()[j];        //delete node -> edge
                     else
                     nodes->at(i)->getKey()->edges()[j]->resetSource(); //else node -> edge ->  source=NULL;
                 }
                 else if(nodes->at(i)->getKey()->edges()[j]->destNode()==nodes->at(i)->getKey())//if node -> edge ->dest =node
                 {
                     if(!nodes->at(i)->getKey()->edges()[j]->sourceNode())//if ! node ->edge -> source
                     {
                         delete nodes->at(i)->getKey()->edges()[j];    //delete node -> edge
                     }
                     else
                     nodes->at(i)->getKey()->edges()[j]->resetDest(); //else node -> edge ->  dest=NULL;
                 }
             }
                  Node::getAllNodes()->contains(nodes->at(i)->getKey())->setWeight(-1);
                  delete nodes->at(i)->getKey();  //delete node

      }
         }
          nodes->removeAll();
         }
         if(edges)
            edges->removeAll();


         if(connectedTree){
           delete connectedTree;
           connectedTree=NULL;
              }
        count=0;
        edges=NULL;
        nodes=NULL;
        delete box;
        box=NULL;
    }

BinaryTree<Node *> * Edge::getTree()
{
    return connectedTree;
}
double Edge::getWeight()
{
    return weight;
}
void Edge::setWeight(double w,QString s)
{
    weight=w;
    sweight=s;
}
QString Edge::getsWeight()
{
    return sweight;
}
QPointF Edge::getSourcePoint()
{
    return sourcePoint;
}
QPointF Edge::getDestPoint()
{
    return destPoint;
}
 int Edge::getCount()
{
    return count;
}
 MYMap<Node * ,Node *> * Edge::getEdges()
{
    return edges;
}
 MYMap<Node * ,int > *Edge::getNodes()
{
    return nodes;
}
void Edge::setShortest(bool c)
{
    shortest=c;
}
Node *Edge::sourceNode() const
{
    return source;
}
Node *Edge::destNode() const
{
    return dest;
}
void Edge::adjust()
{
    if (!source || !dest)
        return;
    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();
    prepareGeometryChange();
    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
                           }
    else {
        sourcePoint = destPoint = line.p1();
         }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;
    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
}
TextBox::TextBox(QWidget * parent)
    : QLineEdit(parent)
{
}
void TextBox::setEnter(bool a)
{
    enter=a;
}
void TextBox::setEdge(Edge *e)
{
    ed=e;
}
Edge* TextBox::getEdge()
{
    return ed;
}
bool TextBox::IsEntered2()
{
    return enter2;
}
void TextBox::keyPressEvent(QKeyEvent * event)
{
    enter2=false;
    if(event->key()==Qt::Key_Enter)
    {
        if(text().size()!=0){
          setVisible(false);
          enter=true;
          enter2=true;
          ed->setWeight(text().toDouble(),text());
          ed->update();
          clear();
          ed->getEdges()->add(ed->sourceNode(),ed->destNode(),ed->getWeight());
          ed->getEdges()->add(ed->destNode(),ed->sourceNode(),ed->getWeight());
         }
    }
    else
    {
        if(event->key()>=48 &&event->key()<=57)
            setText(text()+event->text());
        if(event->key()==Qt::Key_Backspace){
            QString s;
            for(int i=0;i<text().size()-1;i++)
              s+=text().at(i);

            setText(s);
               }
    }

}
bool TextBox::IsEntered()
{
    return enter;
}
 void TextBox::setEnter2(bool a)
 {
     enter2=a;
 }

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * w)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    // Draw the line itself
    if(shortest)
          painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,cos(angle + Pi / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,cos(angle + Pi - Pi / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,cos(angle - Pi + Pi / 3) * arrowSize);
    if(shortest)
         painter->setBrush(Qt::red);
    else
         painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    box->setParent(w);
    if(count==1 && !box->IsEntered())
       box->setVisible(true);

    if(!box->IsEntered2()&&box->text().size()==0)
       box->setEnter2(false);


    box->setFixedWidth(50);
    box->setFixedHeight(13);
    box->move((destPoint.x()+sourcePoint.x())/2,(destPoint.y()+sourcePoint.y())/2);
    box->setFocus();
    QFont font = painter->font();
    font.setBold(false);
    font.setPointSize(13);
    painter->setFont(font);
    painter->setPen(Qt::blue);
    painter->drawText((destPoint.x()+sourcePoint.x())/2,(destPoint.y()+sourcePoint.y())/2,sweight);

}


#include "newer.h"
#include<QMessageBox>
#include<stdio.h>
QPushButton * newer::addNode=NULL;
QPushButton * newer::findShortest=NULL;
QPushButton * newer::resetsh=NULL;
QPushButton * newer::resetG=NULL;
QPushButton * newer::resetALLBtn=NULL;
void reset(Node * node)
{
    node->getImg().load("0","png");
    node->update();
    for(int i=0,s=node->edges().size();i<s;i++)
    {
          node->edges()[i]->setShortest(false);
          node->edges()[i]->update();
    }
}

void newer::resetAll()
{
    if(Node::getSize()>0){
    Edge::resetAll();

    Node::resetALL();
}
}
void newer::resetGraph()
{
 if(Edge::getTree())
if(Edge::getTree()->getSize()>0)
{
 resetShortest();
 Edge::getTree()->traverseTree(reset);
 Node * node;
 for(int i=0,s=Node::getAllNodes()->getSize();i<s;i++)
 {
     node=Node::getAllNodes()->at(i)->getKey();
     node->getImg().load("0","png");
     node->update();
 }
 Node::resetSource();
 Node::resetDest();
}
}


void newer::addAction()
{
    if(TextBox::IsEntered2()){
      std::srand(time(0));
      createNode(100+30*std::rand()%900,100+30*std::rand()%720);
}

}
void newer::resetShortest()
{
    if(Edge::getCount()>0&&shortest){
      drawShortest(false);
    delete shortest;
    shortest=NULL;

    }
}
 void newer::findAction()
 {
    if(Edge::getCount()>0&& Node::getSource()&&Node::getDest()&&TextBox::IsEntered2()){
        Node::getDest()->getImg().load("00","png");
        Node::getDest()->update();
        Node::getSource()->getImg().load("00","png");
        Node::getSource()->update();
        MYMap<Node *,int> * nodes= new MYMap<Node *,int>(Edge::getNodes());
        MYMap<Node *,Node *> * edges= new MYMap<Node *,Node *>(Edge::getEdges());

        shortest= getShortestPath(nodes,edges,Node::getSource(),Node::getDest(),Node::getDest());
        delete nodes;
        delete edges;
        drawShortest(true);
        Node::getSource()->setPressed(true);
        Node::getDest()->setPressed(true);
        Node::resetSource();
        Node::resetDest();
     }
 }

void  newer::drawShortest(bool c)
{
    MYMapNode<Node * , Node *> *node;
    int edges;
    for(int i=0,size=shortest->getSize();i<size-1;i++)
    {
        node=shortest->at(i);
        edges= node->getKey()->edges().size();
        for(int j=0;j<edges;j++)
          {
               if( ( node->getKey()->edges()[j]->sourceNode()==node->getKey() && node->getKey()->edges()[j]->destNode()==shortest->at(i+1)->getKey())||( node->getKey()->edges()[j]->destNode()==node->getKey() && node->getKey()->edges()[j]->sourceNode()==shortest->at(i+1)->getKey()))
            {
                 node->getKey()->edges()[j]->setShortest(c);
                 node->getKey()->edges()[j]->update();
                 if(c)
                 {
                     node->getKey()->edges()[j]->sourceNode()->getImg().load("00","png");
                     node->getKey()->edges()[j]->sourceNode()->update();
                     node->getKey()->edges()[j]->destNode()->getImg().load("00","png");
                     node->getKey()->edges()[j]->destNode()->update();
                 }
                 else
                 {
                     node->getKey()->edges()[j]->sourceNode()->getImg().load("0","png");
                     node->getKey()->edges()[j]->sourceNode()->update();
                     node->getKey()->edges()[j]->destNode()->getImg().load("0","png");
                     node->getKey()->edges()[j]->destNode()->update();
                 }
            }
           }
        }
}


newer::newer(const char *  title)
    :GraphWidget(0,1),scene( new QGraphicsScene(this))
{
  edgeCount=0;
  addNode=new QPushButton("Add_a_Node",this);
  QPalette p ;
  p.setColor(QPalette::ButtonText,QColor(20,206,160));
  addNode->move(this->width()/2 +155 ,this->height()+this->height()/2);
  addNode->setToolTip("To_add_a_node");
  addNode->setToolTipDuration(5000);
  addNode->setPalette(p);
  connect(addNode, SIGNAL(clicked()),this, SLOT(addAction()));
  resetsh =new QPushButton("Reset_shortest",this);
  resetsh->move(this->width()/2 +280 ,this->height()+this->height()/2);
  resetsh->setToolTip("To_reset_the_last_shortest_path");
  resetsh->setToolTipDuration(5000);
  resetsh->setPalette(p);
  connect(resetsh, SIGNAL(clicked()),this, SLOT(resetShortest()));
  resetG =new QPushButton("Reset_Graph",this);
  resetG->move(this->width()/2 +435 ,this->height()+this->height()/2);
  resetG->setToolTip("To_reset_the_the_graph");
  resetG->setToolTipDuration(5000);
  resetG->setPalette(p);
  connect(resetG, SIGNAL(clicked()),this, SLOT(resetGraph()));
  resetALLBtn =new QPushButton("Delete ALL",this);
  resetALLBtn->move(this->width()/2 -150 ,this->height()+this->height()/2);
  resetALLBtn->setToolTip("To_delete_the_graph");
  resetALLBtn->setToolTipDuration(5000);
  resetALLBtn->setPalette(p);
  connect(resetALLBtn, SIGNAL(clicked()),this, SLOT(resetAll()));
  findShortest =new QPushButton("The_Shortest_Path",this);
  findShortest->move(this->width()/2 -30 ,this->height()+this->height()/2);
  findShortest->setToolTip("To_get_the_shortest_path");
  findShortest->setToolTipDuration(5000);
  findShortest->setPalette(p);
  connect(findShortest, SIGNAL(clicked()),this, SLOT(findAction()));
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(0, 0, 1275, 1230);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
  setMinimumSize(1000, 1000);
  setWindowTitle(tr(title));
}
void newer::createNode(int x, int y)
{
     Node * node = new Node(this);
     node->setScene(scene);
     node->setPos(x,y);
     scene->addItem(node);
}
 QPushButton * newer::getAddBtn()
{
    return addNode;
}
 QPushButton * newer::getShortestBtn()
{
    return findShortest;
}
 QPushButton * newer::getResetGBtn()
{
    return resetG;
}
 QPushButton * newer::getResetShBtn()
{
    return resetsh;
}
 QPushButton * newer::getResetALLBtn()
{
    return resetALLBtn;
}
template <class A , class B>
MYMap<A,A> * getShortestPath(MYMap<A,B> *nodes,MYMap<A,A> *edges,A source,A dest,A init)
{
 //intialization
 MYMap<A,int> sdistances;
 MYMap<A,A> parents;
 MYMap<A,A> * currentEdges;
 MYMapNode<A,A> *node;
 MYMapNode<A,int> *minNode;
A current=source;
A currentEdge;
nodes->update(source,0);
sdistances.add(source,0);
parents.add(source,init);
nodes->remove(source);
for(int i=0, size=nodes->getSize();i<size;i++)
    nodes->update(nodes->at(i)->getKey(),2147483646 );
while(!nodes->isEmpty())
{
currentEdges=edges->createMapfromKey(current);
for(int i=0,sumw=0,size=currentEdges->getSize();i<size;i++)
{
    node= currentEdges->at(i);
    currentEdge= node->getValue();
    if(!nodes->contains(node->getValue()))
    continue;
    sumw=node->getWeight()+sdistances.getLast()->getValue();
     if(sumw< nodes->contains(currentEdge)->getValue())
     {
         nodes->update(currentEdge,sumw);
         if(parents.contains(currentEdge))
             parents.update(currentEdge,sdistances.getLast()->getKey());
         else
             parents.add(currentEdge,sdistances.getLast()->getKey());
     }
     else
     {
        if(!parents.contains(currentEdge))
             parents.add(currentEdge,sdistances.getLast()->getKey());
     }
}

 delete currentEdges;
 minNode=nodes->getMin();
 sdistances.add(minNode->getKey(),minNode->getValue());
 current =minNode->getKey();
 nodes->remove(minNode->getKey());
}

MYMap<A,A> *shortestPath = new MYMap<A,A>;
MYMapNode<A,A> * temp;
for(int i=0;true;i++)
{
    temp=parents.contains(dest);
    if(!temp)
     break;
    shortestPath->add(temp->getKey(),temp->getKey());
    dest=temp->getValue();
     if(temp->getValue()==init)
    break;
}
return shortestPath;
}

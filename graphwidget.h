#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include<iostream>
#include<QPushButton>
#include "node.h"
#include "edge.h"
using namespace std;
#include <QGraphicsView>
class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = 0);
    GraphWidget::GraphWidget(QWidget *parent , int);
    void itemMoved();
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
private:
    int timerId;
    Node *centerNode;
};
#endif // GRAPHWIDGET_H

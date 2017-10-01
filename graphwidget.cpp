#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <math.h>
#include <QKeyEvent>
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
}
GraphWidget::GraphWidget(QWidget *parent,int )
    : QGraphicsView(parent), timerId(0)
{
}
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
    QRectF textRect(sceneRect.left() + 20, sceneRect.top() + 10,sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("#Mohamed_Mokhtar                                                                                                                                                                                                محمد_مختار#"));//
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(QColor(118,194,175));
    painter->drawText(textRect.translated(2, 920), "@Mohamed_m10101\n@mohamedmokhtar10101"); // اى حاجه معمللها كومنت  دى ملهاش لازمه عايز تشلها شلها
    painter->setPen(QColor(118,194,175));
    painter->drawText(textRect, message);
}

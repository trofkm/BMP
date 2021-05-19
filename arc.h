#ifndef ARC_H
#define ARC_H
#include <QGraphicsItem>
#include "qmath.h"
class arc : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    arc(int, QPointF, QPointF, QPointF);
    arc(int, QLineF, QLineF);


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    enum { Type = UserType + 6 };
    int type() const;
    int id;

    QPointF startP, midP, endP, p1, p2, p3,center;
    QLineF lineBC;
    QLineF lineAC;
    QLineF lineBA;
    QLineF lineOA;
    QLineF lineOC;
    QLineF bisectorBC;
    QLineF bisectorBA;
    QGraphicsEllipseItem *ellipse;
    qreal rad;

private:
    QVector<QPointF> stuff;

};

#endif // ARC_H

#include "arc.h"

arc::arc(int i, QPointF point1, QPointF point2, QPointF point3)
{
    // assigns id
    id = i;
    p1 = point1;
    p2 = point2;
    p3 = point3;

    lineBC(point2, point3);
    lineAC(point1, point3);
    lineBA(point2, point1);

    rad = qAbs(lineBC.length()/(2*qSin(qDegreesToRadians(lineAC.angleTo(lineBA)))));

    bisectorBC(lineBC.pointAt(0.5), lineBC.p2());
    bisectorBC.setAngle(lineBC.normalVector().angle());

    bisectorBA(lineBA.pointAt(0.5), lineBA.p2());
    bisectorBA.setAngle(lineBA.normalVector().angle());


    bisectorBA.intersect(bisectorBC, &center);

    ellipse = new QGraphicsEllipseItem(center.x() - rad, center.y() - rad, rad*2, rad*2);

    lineOA(center, point1);
    lineOC(center, point3);
}

arc::arc(int i, QLineF start, QLineF end)
{
    // assigns id
    id = i;

    lineOA.angle() = start;
    lineOC.angle() - lineOA.angle() = end;
}

int arc::type() const
{
    // Enable the use of qgraphicsitem_cast with arc item.
    return Type;
}

void arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    QPen paintpen;
    painter->setRenderHint(QPainter::Antialiasing);
    paintpen.setWidth(1);

    if (isSelected())
    {
        // sets brush for end points
        painter->setBrush(Qt::SolidPattern);
        paintpen.setColor(Qt::red);
        painter->setPen(paintpen);

        paintpen.setStyle(Qt::DashLine);
        paintpen.setColor(Qt::black);
        painter->setPen(paintpen);
        painter->drawArc(ellipse->boundingRect(),lineOA.angle(),lineOC.angle() - lineOA.angle());
    }
    else
    {
        painter->setBrush(Qt::SolidPattern);
        paintpen.setColor(Qt::black);
        painter->setPen(paintpen);
        painter->drawArc(ellipse->boundingRect(),lineOA.angle(),lineOC.angle() - lineOA.angle());

    }
}

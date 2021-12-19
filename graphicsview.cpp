#include "graphicsview.h"
#include <QGraphicsScene>
#include <QDebug>
#include <limits>
#include <QGraphicsPixmapItem>
#include "datamanager.h"

const int INF_MIN = std::numeric_limits<int>::min();
const int INF_MAX = std::numeric_limits<int>::max();

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView (parent), scene(new QGraphicsScene(this))
{
    scene->setSceneRect(QRectF(INF_MIN, INF_MIN, INF_MAX, INF_MAX));
    this->setScene(scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    image_item = new QGraphicsPixmapItem();
    image_item->setFlag(QGraphicsItem::ItemIsMovable);


    scene->addItem(image_item);
    this->setMouseTracking(true);
}

void GraphicsView::DisplayImage(const QImage &img)
{
    if(img.isNull())
        return ;
    image_item->setPixmap(QPixmap::fromImage(img));
    CalcViewPort(img.width(), img.height());
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    is_mouse_press = true;
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(is_mouse_press)
    {
        QGraphicsView::mouseMoveEvent(event);
    }


    if(image_item != nullptr && image_item->mapFromScene(this->mapToScene(event->pos())).x() >= 0.0 && image_item->mapFromScene(this->mapToScene(event->pos())).y() >= 0.0)
    {
        int image_pos_x = int(image_item->mapFromScene(this->mapToScene(event->pos())).x());
        int image_pos_y = int(image_item->mapFromScene(this->mapToScene(event->pos())).y());

        auto rgb_tuple = DataManager::instance().AccessCurrentImagePixelValue(image_pos_y, image_pos_x);

        emit SendPosition(image_pos_x, image_pos_y);
        emit SendRGB(std::get<0>(rgb_tuple), std::get<1>(rgb_tuple), std::get<2>(rgb_tuple));
    }
    else {
        emit SendPosition(-1, -1);
        emit SendRGB(0.0, 0.0, 0.0);
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        this->scale(m_scale-0.1, m_scale-0.1);
    }
    else {
        this->scale(m_scale+0.1, m_scale+0.1);
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    is_mouse_press = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::CalcViewPort(int image_width, int image_height)
{
    //respect with image height
    //center with width



    int window_width = this->width();
    int window_height = this->height();


    QPoint view_right_down_corner(window_width, window_height);

    QPointF scene_left_up_corner(-100, 0);
    QPointF scene_right_down_corner(2200, image_height);

    this->setSceneRect(QRectF(scene_left_up_corner, scene_right_down_corner));
}

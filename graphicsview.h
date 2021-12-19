#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
class QGraphicsScene;
class QGraphicsPixmapItem;

class GraphicsView : public QGraphicsView
{
Q_OBJECT

public:
    GraphicsView(QWidget *parent = nullptr);

    void DisplayImage(const QImage &img);



protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


signals:
    void SendPosition(int row, int col);
    void SendRGB(double r, double g, double b);

private:
    void CalcViewPort(int image_width, int image_height);

private:
    QGraphicsScene *scene{nullptr};
    QGraphicsPixmapItem *image_item{nullptr};
    double m_scale{1.0};
    bool is_mouse_press{false};
};

#endif // GRAPHICSVIEW_H

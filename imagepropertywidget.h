#ifndef IMAGEPROPERTYWIDGET_H
#define IMAGEPROPERTYWIDGET_H

#include <QWidget>

namespace Ui {
class ImagePropertyWidget;
}

class ImagePropertyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImagePropertyWidget(QWidget *parent = nullptr);
    void SetImageWidth(int width);
    void SetImageHeight(int height);
    void SetImageChannle(int c);
    int SetImageBitDepth(int bit);


    ~ImagePropertyWidget();

private:
    Ui::ImagePropertyWidget *ui;
};

#endif // IMAGEPROPERTYWIDGET_H

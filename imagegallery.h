#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H

#include <QWidget>


class ImageGallery : public QWidget
{
public:
    ImageGallery(QWidget *parent = nullptr);

    void ChangeDisplayStatus();


private:
    bool status_display{false}; //default hide
};

#endif // IMAGEGALLERY_H

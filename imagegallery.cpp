#include "imagegallery.h"
#include <QDebug>
ImageGallery::ImageGallery(QWidget *parent) : QWidget (parent)
{
    ChangeDisplayStatus();
}

void ImageGallery::ChangeDisplayStatus()
{
    if(status_display)
    {
        this->show();
        status_display = false;
    }
    else {
        this->hide();
        status_display = true;
    }
}

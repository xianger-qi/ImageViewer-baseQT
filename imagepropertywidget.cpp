#include "imagepropertywidget.h"
#include "ui_imagepropertywidget.h"

ImagePropertyWidget::ImagePropertyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImagePropertyWidget)
{
    ui->setupUi(this);
}

void ImagePropertyWidget::SetImageWidth(int width)
{
    ui->label_width->setText(QString::number(width));
}

void ImagePropertyWidget::SetImageHeight(int height)
{
    ui->label_height->setText(QString::number(height));
}

void ImagePropertyWidget::SetImageChannle(int c)
{
    ui->label_channel->setText(QString::number(c));
}

int ImagePropertyWidget::SetImageBitDepth(int bit)
{
    ui->label_bit_depth->setText(QString::number(bit));
}

ImagePropertyWidget::~ImagePropertyWidget()
{
    delete ui;
}

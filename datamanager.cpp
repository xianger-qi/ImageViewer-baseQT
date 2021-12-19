#include "datamanager.h"

#include <QDir>
#include <QFile>
#include <QRgb>
DataManager::DataManager()
{

}

void DataManager::LoadImageFileFromDirectory(std::vector<QString> files_path)
{
    ClearAllImage();
    for(auto &ele: files_path)
        LoadImageFile(ele);

    current_display_image = map_data_pointer[*image_order.begin()];
}

void DataManager::LoadImageFile(QString filename)
{
    QImage *img = new QImage(filename);

    map_data_pointer[filename] = img;
    image_order.push_back(filename);
    current_display_image = img;
}

void DataManager::ClearAllImage()
{
    std::map<QString, QImage *> ().swap(map_data_pointer);
    current_display_image = nullptr;
}

std::tuple<double, double, double> DataManager::AccessCurrentImagePixelValue(int row, int col)
{
    if(current_display_image != nullptr)
    {
        QRgb v = current_display_image->pixel(col, row);
        return std::make_tuple(qRed(v), qGreen(v), qBlue(v));
    }
    return std::make_tuple(0, 0, 0);
}

QImage &DataManager::GetFirstImage()
{
    return *(current_display_image);
}

QImage &DataManager::GetSpecifiedImage(QString filename)
{
    return *(map_data_pointer[filename]);
}

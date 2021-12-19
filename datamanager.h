#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <map>
#include <vector>
#include <QString>
#include <array>
#include <tuple>
#include <QImage>
#include "singleton.h"

class DataManager : public singleton<DataManager>
{
public:
    DataManager();

    void LoadImageFileFromDirectory(std::vector<QString> files_path);
    void LoadImageFile(QString filename);

    void ClearAllImage();

    std::tuple<double, double, double> AccessCurrentImagePixelValue(int row, int col);

    QImage &GetFirstImage();
    QImage &GetSpecifiedImage(QString filename);



private:

    std::map<QString, QImage *> map_data_pointer;
//    std::map<QImage *, > map_raw_data;

    std::vector<QString> image_order;
    QImage *current_display_image{nullptr};
};



#endif // DATAMANAGER_H

#include "fileio.h"
#include <QFileDialog>
#include <QDebug>
QString FileIO::OpenImageFile(QWidget *parent)
{
    return QFileDialog::getOpenFileName(parent, ("Choose ImageFile"), "/home", ("Images (*.bmp *.jpg *.png *.tif *.tiff *jpeg)"));
}

std::vector<QString> FileIO::OpenImageDirectory(QWidget *parent)
{
    QString dir_path = QFileDialog::getExistingDirectory(parent, "Open Directory", "/home", QFileDialog::ShowDirsOnly);
    QDir dir(dir_path);
    QStringList file_filter;
    file_filter << "*.bmp" << "*.jpg" << "*.png" << "*.tif" << "*.tiff" << "*.jpeg";
    QFileInfoList file_list = dir.entryInfoList(file_filter, QDir::Files | QDir::NoDotAndDotDot);

    std::vector<QString> file_path;
    for(int i = 0; i < file_list.size(); ++i)
        file_path.push_back(file_list.at(i).filePath());

    return file_path;
}

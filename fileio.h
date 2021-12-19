#ifndef FILEIO_H
#define FILEIO_H


#include <QWidget>
#include <QStringList>
#include <vector>

namespace FileIO
{
    QString OpenImageFile(QWidget *parent);
    std::vector<QString> OpenImageDirectory(QWidget *parent);

};

#endif // FILEIO_H

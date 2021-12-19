#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ImageGallery;
class GraphicsView;
class QLabel;
class ImagePropertyWidget;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitUI();
    void EngageSingalConnection();
    void DisplayRGBInfo(double r, double g, double b);
    void DisplayPositionInfo(double row, double col);
    void DisplayImage();

private:
    Ui::MainWindow *ui;
    ImageGallery  *m_gallery{nullptr};
    GraphicsView *view{nullptr};
    QLabel *rgb_label{nullptr};
    QLabel *position_label{nullptr};
    ImagePropertyWidget *property_widget{nullptr};
};

#endif // MAINWINDOW_H

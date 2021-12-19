#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QFileDialog>
#include <QSpacerItem>
#include <QHBoxLayout>
#include "datamanager.h"
#include "graphicsview.h"
#include "aboutdialog.h"
#include "imagegallery.h"
#include "fileio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUI();
    EngageSingalConnection();
}

void MainWindow::InitUI()
{

    //status setup
    this->statusBar()->hide();
    this->setWindowTitle("Image Viewer Supported for Multiple Image Formats: PNG, BMP, JPG, JPEG, TIF, etc... ");

    QWidget *central_widget = new QWidget(this);
    //gallery
    m_gallery = new ImageGallery(central_widget);


    //splitor
    QSplitter *splitor = nullptr;
    splitor = new QSplitter(central_widget);
    splitor->setStretchFactor(0, 2);
    splitor->setStretchFactor(1, 1);
    splitor->setOrientation(Qt::Horizontal);
    QWidget *property_widget = new QWidget(splitor);
    view = new GraphicsView(splitor);
    splitor->addWidget(view);
    splitor->addWidget(property_widget);

    //info bar
    QWidget *info_bar = new QWidget(this);
    QHBoxLayout *info_bar_layout = new QHBoxLayout(info_bar);
    rgb_label = new QLabel(info_bar);
    position_label = new QLabel(info_bar);

    info_bar_layout->addWidget(position_label);
    info_bar_layout->addWidget(rgb_label);
    info_bar->setLayout(info_bar_layout);




    //central widget
    QVBoxLayout *central_layout = new QVBoxLayout(central_widget);
    central_layout->setContentsMargins(0, 0, 0, 0);
    central_layout->addWidget(splitor);
    central_layout->addWidget(m_gallery);
    central_layout->addWidget(info_bar);
    central_layout->setStretch(0, 20);
    central_layout->setStretch(1, 2);
    central_layout->setStretch(2, 1);



    this->setCentralWidget(central_widget);
}

void MainWindow::EngageSingalConnection()
{
    connect(this->ui->actionGallery, &QAction::triggered, [this]{this->m_gallery->ChangeDisplayStatus();});
    connect(this->ui->action_Open_Image, &QAction::triggered, [this]{DataManager::instance().LoadImageFile(FileIO::OpenImageFile(this));\
    this->view->DisplayImage(DataManager::instance().GetFirstImage());});
    connect(this->ui->action_Open_Diretory, &QAction::triggered, [this]{DataManager::instance().LoadImageFileFromDirectory(FileIO::OpenImageDirectory(this));\
        this->view->DisplayImage(DataManager::instance().GetFirstImage());});

    connect(this->view, &GraphicsView::SendRGB, this, &MainWindow::DisplayRGBInfo);
    connect(this->view, &GraphicsView::SendPosition, this, &MainWindow::DisplayPositionInfo);

    connect(this->ui->action_open_About, &QAction::triggered, this, [this]{AboutDialog dlg(this); dlg.exec();});
}

void MainWindow::DisplayRGBInfo(double r, double g, double b)
{
    QString rgb_res = QString("R, G, B (%1, %2, %3)").arg(QString::number(int(r))).arg(QString::number(int(g))).arg(QString::number(int(b)));
    rgb_label->setText(rgb_res);
}

void MainWindow::DisplayPositionInfo(double row, double col)
{
    QString rgb_res = QString("X, Y (%1, %2)").arg(QString::number(int(col))).arg(QString::number(int(row)));
    position_label->setText(rgb_res);
}

MainWindow::~MainWindow()
{
    delete ui;
}

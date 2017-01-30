#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "opencv2/opencv.hpp"
#include "controller.h"
#include <QStandardPaths>
#include <QStringList>
#include <QFileDialog>

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    cv::Mat img(400,400,CV_8UC3);
    img = cv::Scalar(0,0,255);
    ui->videoWidget->showImage(img);
    ui->videoLoadedLabel->setText("No video loaded!");

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::on_prevButton_clicked()
{
    pController->prevFrame();
}

void MyMainWindow::on_playButton_clicked()
{
    pController->togglePlayPause();
}

void MyMainWindow::on_nextButton_clicked()
{
    pController->nextFrame();
}

void MyMainWindow::on_exportButton_clicked()
{
    QString filepath, tmp;
    filepath = videoFilename + "_" + tmp.setNum(pController->getCurrentFrameNumber()) + ".tif";
    pController->saveCurrentFrame(filepath.toStdString());
}

void MyMainWindow::on_loadButton_clicked()
{
    QStringList fileNames;
    fileNames.empty();

    QString videoLocation = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::MoviesLocation);

    QFileDialog dlg(this);
    dlg.setViewMode(QFileDialog::Detail);
    fileNames = QFileDialog::getOpenFileNames(this, tr("Select Video File"), videoLocation, tr("FFMpeg (*.*)"));

    if (fileNames.isEmpty())
        return;

    videoFilename = fileNames.first();

    bool ok = pController->loadVideo(videoFilename.toStdString());

    if (ok) {
        initSlider();
        ui->videoLoadedLabel->setText("");
    }

}

void MyMainWindow::on_videoSlider_sliderReleased()
{
    emit requestUpdate();
}

void MyMainWindow::initWindow(Controller *pCtrl)
{
    pController = pCtrl;
    connect(ui->videoSlider, SIGNAL(valueChanged(int)), pController, SLOT(setVideoFrame(int)));
    connect(this, SIGNAL(requestUpdate()), pController, SLOT(updateRequested()));
}

void MyMainWindow::setCurrentTime(std::string str)
{
    ui->labelTime->setText(QString::fromStdString(str));
}

void MyMainWindow::initSlider()
{
    int sliderlength = pController->getVideoLength();
    ui->videoSlider->setRange(1, sliderlength);
}

void MyMainWindow::updateView(cv::Mat img)
{
    ui->videoWidget->showImage(img);
}

void MyMainWindow::updateSlider(int frameNo)
{
    ui->videoSlider->setValue(frameNo);
}


void MyMainWindow::updateButtons(bool playing)
{
    if (playing) {
        ui->playButton->setText("Pause");
        ui->fastplayButton->setText("Pause");
    }
    else {
        ui->playButton->setText("Play");
        ui->fastplayButton->setText("Fast play");
    }
}


void MyMainWindow::on_fastplayButton_clicked()
{
    pController->toggleFastPlay();
}

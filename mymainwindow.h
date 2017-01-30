#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
class Controller;

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();

    void initWindow(Controller *pCtrl);
signals:
    void requestUpdate();

private slots:
    //my slots
    void updateView(cv::Mat img);
    void updateSlider(int frameNo);
    void updateButtons(bool playing);
    void setCurrentTime(std::string);
    // dlg slots
    void on_prevButton_clicked();
    void on_playButton_clicked();
    void on_nextButton_clicked();
    void on_exportButton_clicked();
    void on_loadButton_clicked();
    void on_videoSlider_sliderReleased();

    void on_fastplayButton_clicked();

private:
    Ui::MyMainWindow *ui;
    Controller *pController;
    void initSlider();
    QString videoFilename;
};

#endif // MYMAINWINDOW_H

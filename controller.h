#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include "mymainwindow.h"
#include "videodata.h"
#include <QBasicTimer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    MyMainWindow mainWnd;

    void togglePlayPause();
    void nextFrame();
    void prevFrame();
    void saveCurrentFrame(std::string filename);
    int  getVideoLength();
    bool loadVideo(std::string filename);
    int  getCurrentFrameNumber();
    void toggleFastPlay();

private slots:
    void setVideoFrame(int no);
    void updateRequested();

signals:
    void updateView(cv::Mat img);
    void updateSlider(int no);
    void updateButtons(bool playing);
    void updateCurrentTime(std::string);

protected:
    void timerEvent(QTimerEvent *event);
    void updateGUI();

private:
    VideoData       data;
    bool			stillPlay;
    QBasicTimer		timer;

};

#endif // CONTROLLER_H

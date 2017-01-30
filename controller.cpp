#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mainWnd.initWindow(this);
    mainWnd.show();

    connect(this, SIGNAL(updateView(cv::Mat)), &mainWnd, SLOT(updateView(cv::Mat)));
    connect(this, SIGNAL(updateSlider(int)), &mainWnd, SLOT(updateSlider(int)));
    connect(this, SIGNAL(updateButtons(bool)), &mainWnd, SLOT(updateButtons(bool)));
    connect(this, SIGNAL(updateCurrentTime(std::string)), &mainWnd, SLOT(setCurrentTime(std::string)));

    stillPlay = false;

}

void Controller::updateGUI()
{
    emit updateView(data.getCurrentFrame());
    emit updateSlider(data.getCurrentFrameNumber());
    emit updateCurrentTime(data.getCurrentTime());
    emit updateButtons(stillPlay);
}

void Controller::nextFrame()
{
    data.nextFrame();
    updateGUI();
}

void Controller::prevFrame()
{
    data.prevFrame();
    updateGUI();
}

void Controller::timerEvent(QTimerEvent *event)
{
    if(stillPlay)
    {
        data.nextFrame();
    }
    updateGUI();
}


void Controller::togglePlayPause()
{
    stillPlay = !stillPlay;
    if (stillPlay)
        timer.start(int(1000/data.getFrameRate()), this);
     else
        timer.stop();

    emit updateButtons(stillPlay);
}

void Controller::toggleFastPlay()
{
    stillPlay = !stillPlay;
    if (stillPlay)
        timer.start(0, this);
    else
        timer.stop();

    emit updateButtons(stillPlay);
}

void Controller::saveCurrentFrame(std::string filename)
{
    data.saveCurrentFrame(filename);
}

int Controller::getVideoLength()
{
    return data.getVideolength();
}

bool Controller::loadVideo(std::string filename)
{
    bool result = data.loadVideo(filename);
    updateGUI();

    return result;
}

void Controller::setVideoFrame(int no)
{
    data.setCurrentFrameNumber(no);
    updateGUI();
}

void Controller::updateRequested()
{
    updateGUI();
}

int Controller::getCurrentFrameNumber()
{
    return data.getCurrentFrameNumber();
}

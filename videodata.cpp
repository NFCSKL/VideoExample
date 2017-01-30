#include "videodata.h"
#include "VideoData.h"


VideoData::VideoData()
{
}


VideoData::~VideoData()
{
}

bool VideoData::loadVideo(std::string name)
{
    filepath = name;
    bool result = video.open(name);
    nextFrame();
    return result;
}

void VideoData::nextFrame()
{
    video >> currentFrame;
}

void VideoData::prevFrame()
{
    int no = int(video.get(CV_CAP_PROP_POS_FRAMES))-1;
    if (no < 1) no = 1;
    video.set(CV_CAP_PROP_POS_FRAMES, no);
    video.retrieve(currentFrame);
}

void VideoData::jumpFrames(int amount)
{
    int no = getCurrentFrameNumber();
    no += amount;
    setCurrentFrameNumber(no);

}


void VideoData::saveCurrentFrame(std::string str)
{
    cv::imwrite(str,currentFrame);
}

int VideoData::getVideolength()
{
    double d = video.get(CV_CAP_PROP_FRAME_COUNT);
    return int(d);
}

int VideoData::getCurrentFrameNumber()
{
    double d = video.get(CV_CAP_PROP_POS_FRAMES);
    return int(d);
}

void VideoData::setCurrentFrameNumber(int no)
{
    int min = 1;
    int max = int(video.get(CV_CAP_PROP_FRAME_COUNT));

    if (no < min) no = min;
    if (no > max) no = max;

    video.set(CV_CAP_PROP_POS_FRAMES, no);
    video.retrieve(currentFrame);
}

std::string VideoData::getCurrentTime()
{
    int t = int(video.get(CV_CAP_PROP_POS_MSEC));
    int h, m, s;
    char hh[2], mm[2], ss[2];

    h = int(t / 3600000);	t = t % 3600000;
    m = int(t / 60000);		t = t % 60000;
    s = int(t / 1000);

    (h < 10) ? sprintf(hh, "0%d", h) : sprintf(hh, "%d", h);
    (m < 10) ? sprintf(mm, "0%d", m) : sprintf(mm, "%d", m);
    (s < 10) ? sprintf(ss, "0%d", s) : sprintf(ss, "%d", s);

    char tt[9];
    sprintf(tt,"%s:%s:%s",hh,mm,ss);

    std::string time(tt);
    return time;
}


cv::Mat VideoData::getCurrentFrame()
{
    return currentFrame;
}


int VideoData::getFrameRate()
{
    return int(video.get(cv::CAP_PROP_FPS));
}

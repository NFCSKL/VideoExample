#ifndef VIDEODATA_H
#define VIDEODATA_H
#include "opencv2/opencv.hpp"

class VideoData
{
public:
    VideoData();
    ~VideoData();

    bool loadVideo(std::string name);
    void nextFrame();
    void prevFrame();
    void jumpFrames(int amount);

    void saveCurrentFrame(std::string str);
    int  getVideolength();
    int  getCurrentFrameNumber();
    void setCurrentFrameNumber(int no);
    int  getFrameRate();

    std::string getCurrentTime();
    cv::Mat		getCurrentFrame();

private:
    cv::VideoCapture	video;
    std::string			filepath;
    cv::Mat				currentFrame;


};


#endif // VIDEODATA_H

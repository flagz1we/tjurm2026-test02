#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    std::vector<std::vector<cv::Point>> all;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray,gray,150,255,cv::THRESH_BINARY);
    //cv::imshow("gray",gray);
    cv::findContours(gray , all , hierarchy , cv::RETR_CCOMP ,cv::CHAIN_APPROX_NONE);
    for(int i  = 0 ; i < all.size() ; i ++)
    {
        if(hierarchy[i][3] != -1)
        {
            
            res.first = boundingRect(all[i]);
            res.second = minAreaRect(all[i]);
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return res;
}
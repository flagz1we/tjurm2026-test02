#include<iostream>
#include "impls.h"
int cal_q(const cv::Mat input,int x1,int y1, float dx,float dy , int c_bx,int c_by,int k)
{
    float Q = input.at<cv::Vec3b>(y1,x1)[k] * (1 - dx) * (1 - dy)   
            + input.at<cv::Vec3b>(y1,x1 + c_bx)[k] * dx * (1 - dy)
            + input.at<cv::Vec3b>(y1 + c_by,x1)[k] * (1 - dx) * dy
            + input.at<cv::Vec3b>(y1 + c_by,x1 + c_bx)[k]* dx * dy;
    return int(Q);
}

cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    //std::cout<<"2"<<" ";
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat mat(new_rows, new_cols,input.type());
    //std::cout<<new_rows<<" "<<new_cols<<std::endl;
    int tim = 0;
    for(int i = 0 ; i < new_rows ; i++)
    {
        for(int j = 0 ; j < new_cols ; j++)
        {
            float src_x = float(j) * (1.0f / scale) + 0.5f * ((1.0f / scale) -1.0f);
            float src_y = float(i) * (1.0f / scale) + 0.5f * ((1.0f / scale) -1.0f);
            int x1 = static_cast<int>(src_x);
            int y1 = static_cast<int>(src_y);
            float dx = src_x - x1;
            float dy = src_y - y1;
            int call_backx = 0,call_backy = 0;
            if(x1 + 1> input.rows) call_backx = -1;
            if(y1 + 1> input.cols) call_backy = -1;
            for(int k = 1 ;k <= 3;k ++)
            {
                mat.at<cv::Vec3b>(i,j)[k-1] = cal_q(input,x1,y1 ,dx, dy,  call_backx, call_backy ,k-1);
                //std::cout<<tim++<<" ";
                //std::cout<<mat.at<cv::Vec3b>(i,j)[k-1]<<" ";
            }
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return mat;
}
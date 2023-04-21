#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    //cout <<"argc=" << argc << endl << argv[1] << endl << *(argv+1) << endl;;
    std::string fn;
    cout << "Input image name for classify:";
    cin >> fn;
    cout << fn << endl;
    cv::Mat img = cv::imread(fn, cv::IMREAD_COLOR);
    if(img.empty())
       return -1;
    cv::namedWindow("arnold_schwarzenegger", cv::WINDOW_AUTOSIZE );
    cv::imshow("arnold_schwarzenegger", img);
    cv::waitKey(0);
    return 0;
}

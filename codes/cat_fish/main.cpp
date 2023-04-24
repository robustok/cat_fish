#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/dnn.hpp>
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
    cv::namedWindow("picture", cv::WINDOW_AUTOSIZE );
    cv::imshow("picture", img);
    cv::waitKey(0);
    cv::destroyWindow("picture");

    //load onnx
    cv::dnn::Net net = cv::dnn::readNetFromONNX("./onnx/transfer_model.onnx");
	if(net.empty())
	{
		cout << "model loading error!" << endl;
		system("pause");
		return -1;
	}
	else
	{
		cout << "model loading successed!" << endl;
	}

	cv::Mat inputBlob = cv::dnn::blobFromImage(
			img,
			1.0f,
			cv::Size(64, 64),
			cv::Scalar(104, 117, 128),
			true,
			false);
	cv::Mat prob;
	net.setInput(inputBlob);
	prob = net.forward();
	cout << "prob mat is " << prob << endl;
	cv::Mat probMat = prob.reshape(1, 1);  //Mat Mat::reshape(cn, rows=0); if cn==0 channel unchange, if rows == 0 rows unchange.
	cv::Point classNumber;
	double classProb;
	cv::minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int label_id = classNumber.x;
	if(label_id == 0)
		cout << "cat" << endl;
	else
		cout << "fish" << endl;

    return 0;
}

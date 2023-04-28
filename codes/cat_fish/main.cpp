#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/dnn.hpp>

//using namespace cv;
using namespace std;

//read image for classifing from user inputing.
cv::Mat readImage();
//picture classify
void classifyPicture();

int main(int argc, char *argv[])
{
    char c;
    while(c != 'n')
    {
        classifyPicture();
        cout << "Press 'n' for escaping, 'y' for continue." << endl;
        cin >> c ;
        cout << endl;
    }

    return 0;
}


cv::Mat readImage()
{
    std::string fn;
    cout << "Input image file name for classifying: ";
    cin >> fn;
    cv::Mat img = cv::imread(fn, cv::IMREAD_COLOR);
    return img;
}

void classifyPicture()
{
     //read image for classification
    cv::Mat img = readImage();

    //if could not open the image successfully, then exit.
    if(img.empty())
    {
        cout << "Could not read the image file." << endl;
        return;
    }

    //show the source image for user
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
		return;
	}

    //prepaire data for prediction
	cv::Mat inputBlob = cv::dnn::blobFromImage(
			img,
			1.0f,
			cv::Size(64, 64),
			cv::Scalar(104, 117, 128),
			true,
			false);

	//loading data on net
	net.setInput(inputBlob);

	//predicting
	cv::Mat prob;
	prob = net.forward();

	//cout << "prob mat is " << prob << endl;
	cv::Mat probMat = prob.reshape(1, 1);  //Mat Mat::reshape(cn, rows=0); if cn==0 channel unchange, if rows == 0 rows unchange.
	cv::Point classNumber;
	double classProb;
	cv::minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int label_id = classNumber.x;
	if(label_id == 0)
		cout << "prediction result: cat." << endl << endl;
	else
		cout << "prediction result: fish." << endl << endl;

}

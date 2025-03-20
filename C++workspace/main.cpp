#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>

using namespace cv;
using namespace std;

// 파일 존재 여부 확인 함수
bool fileExists(const string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int main()
{
    string imgPath = "/Users/parkjaehong/C++workspace/data_src/cutedog.jpg";

    cout << "파일 경로: " << imgPath << endl;

    if (!fileExists(imgPath))
    {
        cerr << "Error: 파일이 존재하지 않습니다!" << endl;
        return -1;
    }

    Mat src = imread(imgPath, IMREAD_UNCHANGED);

    if (src.empty())
    {
        cerr << "Error: OpenCV가 이미지를 로드할 수 없습니다!" << endl;
        return -1;
    }

    cout << "이미지 로드 성공!" << endl;
    cout << "채널 수: " << src.channels() << endl;

    // 채널에 따라 그레이스케일 변환 적용
    Mat src_gray;
    if (src.channels() == 3)
    {
        cvtColor(src, src_gray, COLOR_BGR2GRAY);
    }
    else if (src.channels() == 4)
    {
        cvtColor(src, src_gray, COLOR_BGRA2GRAY);
    }
    else
    {
        cout << "이미 그레이스케일 이미지입니다." << endl;
        src_gray = src.clone();
    }

    // 변환된 그레이스케일 이미지 확인
    namedWindow("Grayscale", WINDOW_AUTOSIZE);
    imshow("Grayscale", src_gray);

    // 가우시안 블러 적용
    Mat blurred;
    GaussianBlur(src_gray, blurred, Size(5, 5), 0);

    // 블러 처리된 이미지 확인
    namedWindow("Blurred", WINDOW_AUTOSIZE);
    imshow("Blurred", blurred);

    // Canny 엣지 검출 적용
    Mat edge;
    Canny(blurred, edge, 50, 150);

    // 최종 엣지 검출 이미지 확인
    namedWindow("Edge Detection", WINDOW_AUTOSIZE);
    imshow("Edge Detection", edge);

    waitKey(0);
    return 0;
}

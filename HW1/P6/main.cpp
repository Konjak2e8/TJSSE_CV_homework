#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 读取图像
    Mat img_1 = imread("C:/Users/73497/Documents/courses/CV/homework/HW1/img/img1.jpg", IMREAD_COLOR);
    Mat img_2 = imread("C:/Users/73497/Documents/courses/CV/homework/HW1/img/img2.jpg", IMREAD_COLOR);

    // 初始化
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // 检测 Oriented FAST 角点位置
    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    // 根据角点位置计算 BRIEF 描述子
    descriptor->compute(img_1, keypoints_1, descriptors_1);
    descriptor->compute(img_2, keypoints_2, descriptors_2);

    Mat outimg1;
    drawKeypoints(img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    //imshow("ORB keypoints", outimg1);

    // 使用 Hamming 距离对两幅图像中的BRIEF描述子进行匹配
    vector<DMatch> matches;
    matcher->match(descriptors_1, descriptors_2, matches);

    // 匹配点对筛选
    double min_dist = 10000, max_dist = 0;

    // 找出所有匹配之间最相似的和最不相似的两组点之间的距离
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    min_dist = min_element(matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance < m2.distance; })->distance;
    max_dist = max_element(matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance < m2.distance; })->distance;

    cout << "-- Max dist : " << max_dist << endl << "-- Min dist : " << min_dist << endl;

    // 当描述子之间的距离大于两倍的最小距离时，即认为匹配有误。设置一个经验值30作为下限
    std::vector< DMatch > good_matches;
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 30.0))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // 绘制匹配结果
    Mat img_match;
    Mat img_goodmatch;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
    imwrite("matches.jpg", img_match);
    imwrite("good_matches.jpg", img_goodmatch);
    waitKey(0);

    return 0;
}
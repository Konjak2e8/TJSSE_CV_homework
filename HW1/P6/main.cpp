#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    // ��ȡͼ��
    Mat img_1 = imread("C:/Users/73497/Documents/courses/CV/homework/HW1/img/img1.jpg", IMREAD_COLOR);
    Mat img_2 = imread("C:/Users/73497/Documents/courses/CV/homework/HW1/img/img2.jpg", IMREAD_COLOR);

    // ��ʼ��
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // ��� Oriented FAST �ǵ�λ��
    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    // ���ݽǵ�λ�ü��� BRIEF ������
    descriptor->compute(img_1, keypoints_1, descriptors_1);
    descriptor->compute(img_2, keypoints_2, descriptors_2);

    Mat outimg1;
    drawKeypoints(img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    //imshow("ORB keypoints", outimg1);

    // ʹ�� Hamming ���������ͼ���е�BRIEF�����ӽ���ƥ��
    vector<DMatch> matches;
    matcher->match(descriptors_1, descriptors_2, matches);

    // ƥ����ɸѡ
    double min_dist = 10000, max_dist = 0;

    // �ҳ�����ƥ��֮�������Ƶĺ�����Ƶ������֮��ľ���
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    min_dist = min_element(matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance < m2.distance; })->distance;
    max_dist = max_element(matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance < m2.distance; })->distance;

    cout << "-- Max dist : " << max_dist << endl << "-- Min dist : " << min_dist << endl;

    // ��������֮��ľ��������������С����ʱ������Ϊƥ����������һ������ֵ30��Ϊ����
    std::vector< DMatch > good_matches;
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 30.0))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // ����ƥ����
    Mat img_match;
    Mat img_goodmatch;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
    imwrite("matches.jpg", img_match);
    imwrite("good_matches.jpg", img_goodmatch);
    waitKey(0);

    return 0;
}
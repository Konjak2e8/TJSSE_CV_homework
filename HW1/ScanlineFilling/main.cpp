//#include <opencv2/opencv.hpp>
//#include <vector>
//#include <algorithm>
//
//using namespace cv;
//using namespace std;
//
//class Edge {
//public:
//    int ymin, ymax;
//    float x, inverse_slope;
//};
//
//bool compareEdges(const Edge& a, const Edge& b) {
//    return a.x < b.x;
//}
//
//pair<int, int> buildEdgeTable(const vector<Point>& vertices, vector<vector<Edge>>& edgeTable) {
//    int max_y = max_element(vertices.begin(), vertices.end(), [](const Point& a, const Point& b) {
//            return a.y < b.y;
//            })->y,
//        min_y = min_element(vertices.begin(), vertices.end(), [](const Point& a, const Point& b) {
//            return a.y < b.y;
//            })->y;
//
//    edgeTable.resize(max_y + 1);
//
//    for (size_t i = 0; i < vertices.size(); i++) {
//        Point p1 = vertices[i];
//        Point p2 = vertices[(i + 1) % vertices.size()];
//
//        if (p1.y > p2.y) {
//            swap(p1, p2);
//        }
//
//        if (p1.y != p2.y) {
//            Edge edge;
//            edge.ymin = p1.y;
//            edge.ymax = p2.y;
//            edge.x = p1.x;
//            edge.inverse_slope = static_cast<float>(p2.x - p1.x) / (p2.y - p1.y);
//            edgeTable[p1.y].push_back(edge);
//        }
//    }
//
//    for (int i = 0; i < max_y + 1; i++) {
//        sort(edgeTable[i].begin(), edgeTable[i].end(), compareEdges);
//    }
//
//    return make_pair(min_y, max_y);
//}
//
//void scanlineFill(const vector<Point>& vertices, Mat& image) {
//    vector<vector<Edge>> edgeTable;
//    pair<int, int> range_y = buildEdgeTable(vertices, edgeTable);
//
//    int width = image.cols;
//    int height = image.rows;
//
//    int x_axis = height / 2;
//    int y_axis = width / 2;
//
//    for (int x = 0; x < width; x += 20) {
//        line(image, Point(x, 0), Point(x, height), Scalar(0, 0, 0), 1);
//        putText(image, to_string(x - y_axis), Point(x, height - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
//    }
//
//    for (int y = 0; y < height; y += 20) {
//        line(image, Point(0, y), Point(width, y), Scalar(0, 0, 0), 1);
//        putText(image, to_string(y_axis - y), Point(10, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
//    }
//
//    for (int i = 0; i < min(height, int(edgeTable.size())); i++) {
//        vector<Edge>& active_edges = edgeTable[i];
//
//        if (active_edges.empty())
//            continue;
//
//        for (size_t j = 0; j < active_edges.size(); j += 2) {
//            int x1 = static_cast<int>(active_edges[j].x);
//            int x2 = static_cast<int>(active_edges[j + 1].x);
//
//            for (int x = x1; x < x2; x++) {
//                image.at<Vec3b>(i, x) = Vec3b(0, 0, 0);
//            }
//        }
//
//        for (size_t j = 0; j < active_edges.size(); j++) {
//            active_edges[j].x += active_edges[j].inverse_slope;
//        }
//    }
//}
//
//int main() {
//    int width = 800;
//    int height = 800;
//
//    Mat image(height, width, CV_8UC3, Scalar(255, 255, 255));
//
//    vector<Point> vertices = { Point(50 + width / 2, 50 + height / 2),
//                             Point(150 + width / 2, 100 + height / 2),
//                             Point(100 + width / 2, 200 + height / 2),
//                             Point(20 + width / 2, 100 + height / 2) };
//
//    scanlineFill(vertices, image);
//
//    imshow("Scanline Fill", image);
//    waitKey(0);
//
//    return 0;
//}
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

struct Edge {
    int ymin, ymax;
    float x, inv_slope;
};

bool compareEdge(const Edge& a, const Edge& b) {
    return a.x < b.x;
}

int main() {
    // 创建一个空白图像
    Mat image(500, 500, CV_8UC3, Scalar(255, 255, 255));

    // 定义多边形的顶点
    vector<Point> vertices = { Point(100, 100), Point(300, 100), Point(200, 300) };
    Scalar polygon_color(0, 0, 255);  // 蓝色

    // 画多边形
    fillConvexPoly(image, vertices, polygon_color, LINE_AA);

    // 创建有序边表
    vector<Edge> edge_table;
    for (int i = 0; i < vertices.size(); i++) {
        Point p1 = vertices[i];
        Point p2 = vertices[(i + 1) % vertices.size()];

        if (p1.y > p2.y)
            swap(p1, p2);

        Edge edge;
        edge.ymin = p1.y;
        edge.ymax = p2.y;
        edge.x = p1.x;
        edge.inv_slope = static_cast<float>(p2.x - p1.x) / (p2.y - p1.y);
        edge_table.push_back(edge);
    }

    // 按照ymin对边表进行排序
    sort(edge_table.begin(), edge_table.end(), compareEdge);

    // 扫描线填充
    vector<int> active_edges;
    for (int y = 0; y < image.rows; y++) {
        for (int i = 0; i < active_edges.size() - 1; i += 2) {
            int edge1_idx = active_edges[i];
            int edge2_idx = active_edges[i + 1];
            int ymax1 = edge_table[edge1_idx].ymax;
            int ymax2 = edge_table[edge2_idx].ymax;

            if (ymax1 <= y && ymax2 <= y) {
                active_edges.erase(active_edges.begin() + i, active_edges.begin() + i + 2);
                i -= 2;
            }
        }

        for (int i = 0; i < edge_table.size(); i++) {
            if (edge_table[i].ymin == y) {
                active_edges.push_back(i);
            }
        }

        sort(active_edges.begin(), active_edges.end(), [&](int a, int b) {
            return edge_table[a].x < edge_table[b].x;
            });

        for (int i = 0; i < active_edges.size(); i += 2) {
            int x1 = static_cast<int>(edge_table[active_edges[i]].x);
            int x2 = static_cast<int>(edge_table[active_edges[i + 1]].x);
            line(image, Point(x1, y), Point(x2, y), polygon_color, LINE_AA);
        }
    }


    // 绘制坐标轴
    line(image, Point(0, image.rows / 2), Point(image.cols, image.rows / 2), Scalar(0, 0, 0));
    line(image, Point(image.cols / 2, 0), Point(image.cols / 2, image.rows), Scalar(0, 0, 0));

    // 显示图像
    imshow("Ordered Edge Table", image);
    waitKey(0);

    return 0;
}

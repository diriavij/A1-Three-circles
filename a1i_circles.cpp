#include <iostream>
#include <random>
#include <vector>

double distance(std::pair<double, double> p1, std::pair<double, double> p2) {
    return std::sqrt((p1.first - p2.first) * (p1.first - p2.first) +
        (p1.second - p2.second) * (p1.second - p2.second));
}

int main() {
    std::vector<std::pair<std::pair<double, double>, double>> circles(3);
    double x;
    double y;
    double r;
    for (int i = 0; i < 3; i++) {
        std::cin >> x >> y >> r;
        circles[i].first.first = x;
        circles[i].first.second = y;
        circles[i].second = r;
    }
    double left = circles[0].first.first - circles[0].second;
    double right = circles[0].first.first + circles[0].second;
    double bottom = circles[0].first.second - circles[0].second;
    double top = circles[0].first.second + circles[0].second;
    for (int i = 0; i < 3; i++) {
        left = std::min(left, circles[i].first.first - circles[i].second);
        right = std::max(right, circles[i].first.first + circles[i].second);
        bottom = std::min(bottom, circles[i].first.second - circles[i].second);
        top = std::max(top, circles[i].first.second + circles[i].second);
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist_horizontal(left, right);
    std::uniform_real_distribution<> dist_vertical(bottom, top);
    int points_quantity = 1000000;
    int points_inside_intersection = 0;
    std::vector<std::pair<double, double>> points;
    for (int i = 0; i < points_quantity; i++) {
        double x_point = dist_horizontal(rng);
        double y_point = dist_vertical(rng);
        points.emplace_back(x_point, y_point);
        if (distance(std::pair<double, double>(x_point, y_point),
            circles[0].first) <= circles[0].second &&
            distance(std::pair<double, double>(x_point, y_point),
            circles[1].first) <= circles[1].second &&
                distance(std::pair<double, double>(x_point, y_point),
            circles[2].first) <= circles[2].second) {
            points_inside_intersection++;
        }
    }
    double square_area = (right - left) * (top - bottom);
    std::cout << (static_cast<double>(points_inside_intersection) / points_quantity) * square_area << std::endl;
    return 0;
}
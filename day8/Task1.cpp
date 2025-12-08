#include "../helpers.hpp"
#include <math.h>
#include <set>

class Point3D
{
    uint64_t x;
    uint64_t y;
    uint64_t z;
public:
    double distance(const Point3D& other) const noexcept {
        return std::sqrt(static_cast<double>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z)));
    }
    Point3D(uint64_t x_, uint64_t y_, uint64_t z_) : x{x_}, y{y_}, z{z_} { }
};

struct PointRelation
{
    double distance;
    int id1;
    int id2;
};


int main() {
    auto file = getFile();
    auto points = file | std::views::transform([](const auto& s) {
        auto p = split(s, ',');
        return Point3D{std::stoull(p[0]), std::stoull(p[1]), std::stoull(p[2])};
        }) | std::ranges::to<std::vector>();

    std::vector<PointRelation> shortestConnections;
    shortestConnections.reserve(1000);

    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(points.size()); ++j) {
            auto d = points[i].distance(points[j]);
            if (shortestConnections.size() < 1000ull) {
                shortestConnections.push_back(PointRelation{d, i, j});
            }
            else {
                std::vector<PointRelation>::iterator it = std::ranges::max_element(shortestConnections, { }, &PointRelation::distance);
                if (it->distance > d) {
                    *it = PointRelation{d, i, j};
                }
            }
        }
    }

    std::vector<std::set<int>> circuts;

    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        circuts.push_back(std::set<int>{i});
    }

    for (const auto& r : shortestConnections) {
        std::vector<std::set<int>>::iterator it1 = std::ranges::find_if(circuts, [&r](const auto& s) {return s.contains(r.id1); });
        std::vector<std::set<int>>::iterator it2 = std::ranges::find_if(circuts, [&r](const auto& s) {return s.contains(r.id2); });
        if (it1 != it2) {
            it1->insert_range(*it2);
            circuts.erase(it2);
        }
    }
    std::sort(circuts.begin(), circuts.end(), [](const auto& s1, const auto& s2) {return s1.size() > s2.size(); });
    auto result = circuts[0].size() * circuts[1].size() * circuts[2].size();

    std::println("{}", result);
}
#include "../helpers.hpp"
#include <math.h>
#include <set>

struct Point3D
{
    uint64_t x;
    uint64_t y;
    uint64_t z;
    double distance(const Point3D& other) const noexcept {
        return std::sqrt(static_cast<double>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z)));
    }
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

    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(points.size()); ++j) {
            auto d = points[i].distance(points[j]);
            shortestConnections.push_back(PointRelation{d, i, j});
        }
    }

    std::sort(shortestConnections.begin(), shortestConnections.end(), [](const auto& c1, const auto& c2) {return c1.distance < c2.distance; });

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
        if (circuts.size() == 1ull) {
            std::println("{}", points[r.id1].x * points[r.id2].x);
            break;
        }
    }
}
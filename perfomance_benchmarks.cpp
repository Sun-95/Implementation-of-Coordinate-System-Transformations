#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

const double PI = 3.14159265358979323846;

struct Cartesian {
    double x, y, z;
};

struct Polar {
    double r, theta;
};

struct Spherical {
    double r, theta, phi;
};

enum class CoordinateSystem {
    Cartesian,
    Polar,
    Spherical
};

vector<void*> generateCoordinates(int n, CoordinateSystem system) {
    random_device rd;
    mt19937 gen(rd());
    vector<void*> coords;

    if (system == CoordinateSystem::Cartesian) {
        coords.resize(n);
        for (int i = 0; i < n; ++i) {
            coords[i] = new Cartesian{
                uniform_real_distribution<>(-1000.0, 1000.0)(gen),
                uniform_real_distribution<>(-1000.0, 1000.0)(gen),
                uniform_real_distribution<>(-1000.0, 1000.0)(gen)
            };
        }
    }
    else if (system == CoordinateSystem::Polar) {
        coords.resize(n);
        for (int i = 0; i < n; ++i) {
            coords[i] = new Polar{
                uniform_real_distribution<>(0.0, 1000.0)(gen),
                uniform_real_distribution<>(0.0, 2 * PI)(gen)
            };
        }
    }
    else if (system == CoordinateSystem::Spherical) {
        coords.resize(n);
        for (int i = 0; i < n; ++i) {
            coords[i] = new Spherical{
                uniform_real_distribution<>(0.0, 1000.0)(gen),
                uniform_real_distribution<>(0.0, 2 * PI)(gen),
                uniform_real_distribution<>(0.0, PI)(gen)
            };
        }
    }

    return coords;
}

double distanceCartesian(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

double distancePolar(double r1, double theta1, double r2, double theta2)
{
    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * cos(theta2 - theta1));
}


double distanceSpherical(double r1, double theta1, double phi1, double r2, double theta2, double phi2)
{
    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * (sin(theta1) * sin(theta2) * cos(phi1 - phi2) + cos(theta1) * cos(theta2)));
}

int main() {
    int n = 100000;

    vector<void*> cartesian_coords = generateCoordinates(n, CoordinateSystem::Cartesian);
    auto start = high_resolution_clock::now();
    double cartesian_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        Cartesian* point1 = static_cast<Cartesian*>(cartesian_coords[i]);
        Cartesian* point2 = static_cast<Cartesian*>(cartesian_coords[i + 1]);
        cartesian_distance_sum += distanceCartesian(point1->x, point1->y, point1->z, point2->x, point2->y, point2->z);
    }
    auto end = high_resolution_clock::now();
    duration<double> elapsed = duration_cast<duration<double>>(end - start);
    cout << "Time for Cartesian distance computation: " << elapsed.count() << " seconds\n";

    vector<void*> polar_coords = generateCoordinates(n, CoordinateSystem::Polar);
    start = high_resolution_clock::now();
    double polar_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        Polar* point1 = static_cast<Polar*>(polar_coords[i]);
        Polar* point2 = static_cast<Polar*>(polar_coords[i + 1]);
        polar_distance_sum += distancePolar(point1->r, point1->theta, point2->r, point2->theta);
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    cout << "Time for Polar distance computation: " << elapsed.count() << " seconds\n";

    vector<void*> spherical_coords = generateCoordinates(n, CoordinateSystem::Spherical);
    start = high_resolution_clock::now();
    double spherical_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        Spherical* point1 = static_cast<Spherical*>(spherical_coords[i]);
        Spherical* point2 = static_cast<Spherical*>(spherical_coords[i + 1]);
        spherical_distance_sum += distanceSpherical(point1->r, point1->theta, point1->phi, point2->r, point2->theta, point2->phi);
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    cout << "Time for Spherical distance computation: " << elapsed.count() << " seconds\n";

    for (auto coord : cartesian_coords) delete static_cast<Cartesian*>(coord);
    for (auto coord : polar_coords) delete static_cast<Polar*>(coord);
    for (auto coord : spherical_coords) delete static_cast<Spherical*>(coord);

    return 0;
}
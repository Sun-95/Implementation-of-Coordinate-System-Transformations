#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const double PI = 3.14159265358979323846;

struct Cartesian2D 
{
    double x, y;
};

struct Cartesian3D 
{
    double x, y, z;
};

struct Polar 
{
    double r, theta;
};

struct Spherical 
{
    double r, theta, phi;
};

enum class CoordinateSystem 
{
    Cartesian2D,
    Cartesian3D,
    Polar,
    Spherical
};

// Generate coordinates
vector<void*> generateCoordinates(int n, CoordinateSystem system) 
{
    random_device rd;
    mt19937 gen(rd());
    vector<void*> coords;

    if (system == CoordinateSystem::Cartesian2D) 
    {
        coords.resize(n);
        for (int i = 0; i < n; ++i) 
        {
            coords[i] = new Cartesian2D
            {
                uniform_real_distribution<>(-1000.0, 1000.0)(gen),
                uniform_real_distribution<>(-1000.0, 1000.0)(gen)
            };
        }
    }
    else if (system == CoordinateSystem::Cartesian3D) 
    {
        coords.resize(n);
        for (int i = 0; i < n; ++i) 
        {
            coords[i] = new Cartesian3D
            {
                uniform_real_distribution<>(-1000.0, 1000.0)(gen),
                uniform_real_distribution<>(-1000.0, 1000.0)(gen),
                uniform_real_distribution<>(-1000.0, 1000.0)(gen)
            };
        }
    }
    else if (system == CoordinateSystem::Polar)
    {
        coords.resize(n);
        for (int i = 0; i < n; ++i) 
        {
            coords[i] = new Polar
            {
                uniform_real_distribution<>(0.0, 1000.0)(gen),
                uniform_real_distribution<>(0.0, 2 * PI)(gen)
            };
        }
    }
    else if (system == CoordinateSystem::Spherical)
    {
        coords.resize(n);
        for (int i = 0; i < n; ++i) 
        {
            coords[i] = new Spherical
            {
                uniform_real_distribution<>(0.0, 1000.0)(gen),
                uniform_real_distribution<>(0.0, 2 * PI)(gen),
                uniform_real_distribution<>(0.0, PI)(gen)
            };
        }
    }

    return coords;
}

// Distance Cartesian 2D
double distanceCartesian2D(const Cartesian2D* p1, const Cartesian2D* p2)
{
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
}

// Distance Cartesian 3D
double distanceCartesian3D(const Cartesian3D* p1, const Cartesian3D* p2) 
{
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
}

// Distance Polar
double distancePolar(const Polar* p1, const Polar* p2) 
{
    return sqrt(pow(p1->r, 2) + pow(p2->r, 2) - 2 * p1->r * p2->r * cos(p2->theta - p1->theta));
}

// Distance Spherical Straight-line
double distanceSphericalStraight(const Spherical* p1, const Spherical* p2)
{
    return sqrt(pow(p1->r, 2) + pow(p2->r, 2) - 2 * p1->r * p2->r *(sin(p1->theta) * sin(p2->theta) * cos(p1->phi - p2->phi) + cos(p1->theta) * cos(p2->theta)));
}

// Distance Spherical Arc
double distanceSphericalArc(const Spherical* p1, const Spherical* p2)
{
    return p1->r * acos(sin(p1->theta) * sin(p2->theta) + cos(p1->theta) * cos(p2->theta) * cos(p1->phi - p2->phi));
}

// Function for output result
void printResults(const string& systemName, double time, double totalDistance)
{
    cout << left << setw(20) << systemName << " | " << setw(10) << setprecision(6) << time << " | " << fixed << setprecision(2) << totalDistance << endl;
}

int main() 
{
    int n = 10000;

    cout << "Benchmarking Results:" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Coordinate System"
        << " | " << setw(10) << "Time (s)"
        << " | Total Distance" << endl;
    cout << "---------------------------------------------------------------" << endl;

    //  Distance Cartesian 2D
    vector<void*> cartesian2D_coords = generateCoordinates(n, CoordinateSystem::Cartesian2D);
    auto start = high_resolution_clock::now();
    double cartesian2D_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        cartesian2D_distance_sum += distanceCartesian2D(static_cast<Cartesian2D*>(cartesian2D_coords[i]), static_cast<Cartesian2D*>(cartesian2D_coords[i + 1]));
    }
    auto end = high_resolution_clock::now();
    duration<double> elapsed = duration_cast<duration<double>>(end - start);
    printResults("Cartesian 2D", elapsed.count(), cartesian2D_distance_sum);

    // Distance Cartesian 3D
    vector<void*> cartesian3D_coords = generateCoordinates(n, CoordinateSystem::Cartesian3D);
    start = high_resolution_clock::now();
    double cartesian3D_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        cartesian3D_distance_sum += distanceCartesian3D(static_cast<Cartesian3D*>(cartesian3D_coords[i]), static_cast<Cartesian3D*>(cartesian3D_coords[i + 1]));
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    printResults("Cartesian 3D", elapsed.count(), cartesian3D_distance_sum);

    //Distance Polar
    vector<void*> polar_coords = generateCoordinates(n, CoordinateSystem::Polar);
    start = high_resolution_clock::now();
    double polar_distance_sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        polar_distance_sum += distancePolar(static_cast<Polar*>(polar_coords[i]), static_cast<Polar*>(polar_coords[i + 1]));
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    printResults("Polar", elapsed.count(), polar_distance_sum);

    // Distance Spherical Straight-line
    vector<void*> spherical_coords = generateCoordinates(n, CoordinateSystem::Spherical);
    start = high_resolution_clock::now();
    double spherical_distance_sum_direct = 0;
    for (int i = 0; i < n - 1; ++i) {
        spherical_distance_sum_direct += distanceSphericalStraight(static_cast<Spherical*>(spherical_coords[i]), static_cast<Spherical*>(spherical_coords[i + 1]));
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    printResults("Spherical Straight", elapsed.count(), spherical_distance_sum_direct);

    // Distance Spherical Arc
    start = high_resolution_clock::now();
    double spherical_distance_sum_arc = 0;
    for (int i = 0; i < n - 1; ++i) {
        spherical_distance_sum_arc += distanceSphericalArc(static_cast<Spherical*>(spherical_coords[i]), static_cast<Spherical*>(spherical_coords[i + 1]));
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double>>(end - start);
    printResults("Spherical Arc", elapsed.count(), spherical_distance_sum_arc);

    //Freeing memory
    for (auto coord : cartesian2D_coords) delete static_cast<Cartesian2D*>(coord);
    for (auto coord : cartesian3D_coords) delete static_cast<Cartesian3D*>(coord);
    for (auto coord : polar_coords) delete static_cast<Polar*>(coord);
    for (auto coord : spherical_coords) delete static_cast<Spherical*>(coord);

    return 0;
}

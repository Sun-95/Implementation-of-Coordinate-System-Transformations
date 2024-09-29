#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846;

// Function for converting degrees to radians
double degreesToRadians(double degrees) 
{
    return degrees * (PI / 180.0);
}

// Distance in the Cartesian coordinate system
double distanceCartesian(double x1, double y1, double z1, double x2, double y2, double z2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

// Distance in the polar coordinate system
double distancePolar(double r1, double theta1, double r2, double theta2) 
{
    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * cos(theta2 - theta1));
}

// Distance between two points in the spherical coordinate system (through the volume of the sphere)
double distanceSpherical(double r1, double theta1, double phi1, double r2, double theta2, double phi2)
{
    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * (sin(theta1) * sin(theta2) * cos(phi1 - phi2) + cos(theta1) * cos(theta2)));
}

// Distance between two points on the surface of a sphere (great-circle distance):
double greatCircleDistance(double r, double theta1, double phi1, double theta2, double phi2) 
{
    theta1 = degreesToRadians(theta1);
    phi1 = degreesToRadians(phi1);
    theta2 = degreesToRadians(theta2);
    phi2 = degreesToRadians(phi2);

    double cosine_angle = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(theta1 - theta2);

    double distance = r * acos(cosine_angle);

    return distance;
}

int main() 
{
    double r1, theta1, phi1;
    double r2, theta2, phi2;

    cout << "Enter the coordinates of the first point (r1, theta1 in degrees, phi1 in degrees): ";
    cin >> r1 >> theta1 >> phi1;

    cout << "Enter the coordinates of the second point (r2, theta2 in degrees, phi2 in degrees): ";
    cin >> r2 >> theta2 >> phi2;

    // Calculating the Cartesian coordinates
    double x1 = r1 * sin(degreesToRadians(phi1)) * cos(degreesToRadians(theta1));
    double y1 = r1 * sin(degreesToRadians(phi1)) * sin(degreesToRadians(theta1));
    double z1 = r1 * cos(degreesToRadians(phi1));

    double x2 = r2 * sin(degreesToRadians(phi2)) * cos(degreesToRadians(theta2));
    double y2 = r2 * sin(degreesToRadians(phi2)) * sin(degreesToRadians(theta2));
    double z2 = r2 * cos(degreesToRadians(phi2));

    // Calculate all distances
    double distanceCart = distanceCartesian(x1, y1, z1, x2, y2, z2);
    double distancePol = distancePolar(r1, degreesToRadians(theta1), r2, degreesToRadians(theta2));
    double distanceSphere = distanceSpherical(r1, degreesToRadians(theta1), degreesToRadians(phi1), r2, degreesToRadians(theta2), degreesToRadians(phi2));
    double distanceCircle = greatCircleDistance(r1, theta1, phi1, theta2, phi2);

    // Output the results
    cout << "Distance in Cartesian coordinates: " << distanceCart << endl;
    cout << "Distance in Polar coordinates: " << distancePol << endl;
    cout << "Distance through the volume of the sphere: " << distanceSphere << endl;
    cout << "Distance along the surface of the sphere: " << distanceCircle << endl;

    return 0;
}

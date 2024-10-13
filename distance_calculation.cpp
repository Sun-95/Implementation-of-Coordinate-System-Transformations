#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846;

// Conversion of degrees to radians
double degreesToRadians(double degrees) 
{
    return degrees * (PI / 180.0);
}

// Distance in the Cartesian coordinate system (2D)
double distanceCartesian2D(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Distance in the Cartesian coordinate system (3D)
double distanceCartesian3D(double x1, double y1, double z1, double x2, double y2, double z2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

// Distance in the polar coordinate system (2D)
double distancePolar(double r1, double theta1, double r2, double theta2) 
{
    theta1 = degreesToRadians(theta1);
    theta2 = degreesToRadians(theta2);

    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * cos(theta2 - theta1));
}

// Direct distance in the spherical coordinate system (due to the volume of the sphere)
double distanceSphericalVolume(double r1, double theta1, double phi1, double r2, double theta2, double phi2) 
{
    theta1 = degreesToRadians(theta1);
    theta2 = degreesToRadians(theta2);
    phi1 = degreesToRadians(phi1);
    phi2 = degreesToRadians(phi2);

    return sqrt(pow(r1, 2) + pow(r2, 2) - 2 * r1 * r2 * (sin(theta1) * sin(theta2) * cos(phi1 - phi2) + cos(theta1) * cos(theta2)));
}

// Great circle distance (on the surface of the sphere)
double greatCircleDistance(double r, double theta1, double phi1, double theta2, double phi2) 
{
    theta1 = degreesToRadians(theta1);
    theta2 = degreesToRadians(theta2);
    phi1 = degreesToRadians(phi1);
    phi2 = degreesToRadians(phi2);

    double cosine_angle = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(theta1 - theta2);

    return r * acos(cosine_angle);
}

int main() {
    // Entering Cartesian coordinates for two points (for 2D and 3D)
    double x1, y1, z1, x2, y2, z2;
    cout << "Enter the coordinates of the first point (x1, y1, z1): ";
    cin >> x1 >> y1 >> z1;
    cout << "Enter the coordinates of the second point (x2, y2, z2): ";
    cin >> x2 >> y2 >> z2;

    // Input of spherical coordinates for two points
    double r1, theta1, phi1;
    double r2, theta2, phi2;
    cout << "Enter the coordinates of the first point in the spherical system (r1, theta1 in degrees, phi1 in degrees): ";
    cin >> r1 >> theta1 >> phi1;
    cout << "Enter the coordinates of the second point in the spherical system (r2, theta2 in degrees, phi2 in degrees): ";
    cin >> r2 >> theta2 >> phi2;

    // Calculation of all distances
    double distCart2D = distanceCartesian2D(x1, y1, x2, y2);
    double distCart3D = distanceCartesian3D(x1, y1, z1, x2, y2, z2);
    double distPolar = distancePolar(r1, theta1, r2, theta2);
    double distSpherical = distanceSphericalVolume(r1, theta1, phi1, r2, theta2, phi2);
    double distGreatCircle = greatCircleDistance(r1, theta1, phi1, theta2, phi2);

    // Output of results
    cout << "Distance in Cartesian coordinates (2D): " << distCart2D << endl;
    cout << "Distance in Cartesian coordinates (3D): " << distCart3D << endl;
    cout << "Distance in Polar coordinates (2D): " << distPolar << endl;
    cout << "Straight distance through the volume of the sphere: " << distSpherical << endl;
    cout << "Great circle distance: " << distGreatCircle << endl;

    return 0;
}

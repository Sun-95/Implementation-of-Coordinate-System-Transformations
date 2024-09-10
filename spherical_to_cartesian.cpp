#include <iostream>
#include <cmath>

using namespace std;

// Spherical coordinates to Cartesian coordinates
void sphericalToCartesian(double r, double theta, double phi, double& x, double& y, double& z) {
    x = r * sin(phi) * cos(theta);
    y = r * sin(phi) * sin(theta);
    z = r * cos(phi);
}

// Cartesian coordinates to Spherical coordinates
void cartesianToSpherical(double x, double y, double z, double& r, double& theta, double& phi) {
    r = sqrt(x * x + y * y + z * z);
    theta = atan2(y , x);
    phi = acos(z / r);
}

// Function to normalize angle to the range
double normalizeAngle(double theta) {
    const double PI = 3.14159265358979323846;
    const double TWO_PI = 2 * PI;
    while (theta < 0) theta += TWO_PI;
    while (theta >= TWO_PI) theta -= TWO_PI;
    return theta;
}

int main() {
    double r, theta, phi;
    double x, y, z;
    double r_converted, theta_converted, phi_converted;

    cout << "Enter spherical coordinates:" << endl;
    cout << "r: ";
    cin >> r;
    cout << "theta: ";
    cin >> theta;
    cout << "phi: ";
    cin >> phi;

    // Convert spherical to Cartesian
    sphericalToCartesian(r, theta, phi, x, y, z);
    cout << "Cartesian coordinates:" << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    // Convert Cartesian back to spherical
    cartesianToSpherical(x, y, z, r_converted, theta_converted, phi_converted);
    // Normalize the angle
    theta_converted = normalizeAngle(theta_converted);

    cout << "Converted polar coordinates:" << endl;
    cout << "r: " << r_converted << endl;
    cout << "theta: " << theta_converted << endl;
    cout << "phi: " << phi_converted << endl;

    // Check if the initial and converted coordinates match
    cout << "Verification:" << endl;
    cout << "Initial r: " << r << ", Converted r: " << r_converted << endl;
    cout << "Initial theta: " << theta << ", Converted theta: " << theta_converted << endl;
    cout << "Initial phi: " << phi << ", Converted phi: " << phi_converted << endl;

    return 0;
}

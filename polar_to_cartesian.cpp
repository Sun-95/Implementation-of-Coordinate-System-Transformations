#include <iostream>
#include <cmath>

using namespace std;

// Polar coordinates to Cartesian coordinates
void polarToCartesian(double r, double theta, double& x, double& y) {
    x = r * cos(theta);
    y = r * sin(theta);
}

// Cartesian coordinates to Polar coordinates
void cartesianToPolar(double x, double y, double& r, double& theta) {
    r = sqrt(x * x + y * y);
    theta = atan(y / x);
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
    double r, theta;
    double x, y;
    double r_converted, theta_converted;

    cout << "Enter polar coordinates (r and theta in radians):" << endl;
    cout << "r: ";
    cin >> r;
    cout << "theta: ";
    cin >> theta;

    // Convert polar to Cartesian
    polarToCartesian(r, theta, x, y);
    cout << "Cartesian coordinates:" << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    // Convert Cartesian back to polar
    cartesianToPolar(x, y, r_converted, theta_converted);
    // Normalize the angle
    theta_converted = normalizeAngle(theta_converted);

    cout << "Converted polar coordinates:" << endl;
    cout << "r: " << r_converted << endl;
    cout << "theta: " << theta_converted << endl;

    // Check if the initial and converted coordinates match
    cout << "Verification:" << endl;
    cout << "Initial r: " << r << ", Converted r: " << r_converted << endl;
    cout << "Initial theta: " << theta << ", Converted theta: " << theta_converted << endl;

    return 0;
}
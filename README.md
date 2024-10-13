# Tasks

## 1) Transition Between Coordinate Systems:

### Two-Dimensional Space: Cartesian and Polar Coordinate Systems
- Define the coordinates of several points in the polar coordinate system.
- Convert these coordinates to the Cartesian coordinate system.
- Perform the reverse conversion from the Cartesian coordinate system to the polar coordinate system.
- Verify the correctness of the calculations by ensuring that the initial coordinates match the ones obtained after the reverse conversion.

[Code listening](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/polar_to_cartesian.cpp)  
![Output code](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/screenshotes/polar_to_cartesian.png)

### Three-Dimensional Space: Cartesian and Spherical Coordinate Systems
- Define the coordinates of several points in the spherical coordinate system.
- Convert these coordinates to the Cartesian coordinate system.
- Perform the reverse conversion from the Cartesian coordinate system to the spherical coordinate system.
- Verify the correctness of the calculations by ensuring that the initial coordinates match the ones obtained after the reverse conversion.

[Code listening](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/spherical_to_cartesian.cpp)  
![Output code](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/screenshotes/spherical_to_cartesian.png)

## 2) Distance Calculation in the Spherical Coordinate System:
Compute the distance between points in the spherical coordinate system using two methods:
- **Cartesian Coordinate System:** Use the standard formula for calculating straight-line distance in two-dimensional and three-dimensional spaces.
- **Polar Coordinate System:** Use the formula for calculating the distance between points in a two-dimensional space.
- **Spherical Coordinate System:** Compute the distance between points using two methods:
  1. Through the volume of the sphere: Use the formula for straight-line distance in three-dimensional space.
  2. Along the surface of the sphere: Use the formula for great-circle distance.

[Code listening](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/distance_calculation.cpp)  
![Output code](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/screenshotes/distance_calculation.png)

## 3) Performance Benchmarks:
- Generate an array of coordinate pairs in each coordinate system (Cartesian, polar, spherical).
- Compute the distances between these points for each coordinate system.
- Measure the computation time for each coordinate system.
- Choose an array size that results in minimal variability in benchmarking results between runs (a recommended array size is 10,000 to 100,000 points).

[Code listening](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/perfomance_benchmarks.cpp)  
![Output code](https://github.com/Sun-95/Implementation-of-Coordinate-System-Transformations/blob/main/screenshotes/perfomance_benchmarks.png)

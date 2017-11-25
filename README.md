# Twiddle

C++ version of the twiddle function as shown in the Udacity Self-Driving Car and AI for Robotics courses.

You can build and run with CMake as such:

```
mkdir build
cd build
cmake ..
make
./twiddle
```

Or if you (like me) want to use Xcode or the like, you can do:

```
cmake -G Xcode
```

Upon running this you should get output like this:

```
voas@nerv[5.0]:build : ./twiddle 
Iteration 0, best error = 8315.96
Iteration 1, best error = 0.0434971
Iteration 2, best error = 0.0306544
Iteration 3, best error = 0.00767732
Iteration 4, best error = 0.00322017
Iteration 5, best error = 0.00166459
Iteration 6, best error = 0.000976108
Iteration 7, best error = 0.000616343
Iteration 8, best error = 0.000411028
Iteration 9, best error = 0.000198774
Iteration 10, best error = 1.17692e-06
...
Iteration 50, best error = 6.48625e-16
Values: 2.93312 10.3266 0.49316
```

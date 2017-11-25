//
//  Twiddle.h
//  PID
//
//  Created by Ed Voas on 11/24/2017.
//  C++ version of Twiddle function as shown in Udacity robotics/self-driving car courses.
//

#ifndef Twiddle_h
#define Twiddle_h

#include <functional>
#include <vector>
#include <numeric>
#include <iostream>

//
// Twiddle
//
// Tries different parameters until the combined deltas are below a certain specified threshold.
//
// Parameters:
//    numValues - number of parameters we are testing
//    startValue - starting value for each of the parameters being tested
//    deltaValue - delta value to change each parameter
//    tolerance - when the total delta values are below this value, we terminate
//    errorFunc - the function to call to determine the error based on the current set of values
//    verbose - prints info on each iteration
//
static std::vector<double>
Twiddle(int numValues, double startValue, double deltaValue, double tolerance, bool verbose, std::function<double (std::vector<double>)> errorFunc) {
  std::vector<double> values(numValues, startValue);
  std::vector<double> deltas(numValues, deltaValue);

  double error = errorFunc(values);
  double best_error = error;

  int it = 0;
  while (std::accumulate(deltas.begin(), deltas.end(), 0.0) > tolerance) {
    if (verbose) {
      std::cout << "Iteration " << it << ", best error = " << best_error << std::endl;
    }
    for (int i = 0; i < values.size(); ++i) {
      values[i] += deltas[i];
      error = errorFunc(values);
      if (error < best_error) {
        best_error = error;
        deltas[i] *= 1.1;
      } else {
        values[i] -= 2 * deltas[i];
        error = errorFunc(values);

        if (error < best_error) {
          best_error = error;
          deltas[i] *= 1.1;
        } else {
          values[i] += deltas[i];
          deltas[i] *= 0.9;
        }
      }
    }

    it += 1;
  }

  return values;
}

#endif /* Twiddle_h */

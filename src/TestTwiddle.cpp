//
//  TestTwiddle.cpp
//  pid
//
//  Created by Ed Voas on 11/23/2017.
//  Code to test Twiddle function based on Python code in Udacity robotics/self-driving car courses.
//

#include "TestTwiddle.h"

#include "Robot.h"
#include "Twiddle.h"

#include <math.h>

struct TwiddleResult {
  std::vector<double> x_trajectory;
  std::vector<double> y_trajectory;
  double err;
};

// Make a robot object with some drift.
static Robot MakeRobot() {
  Robot robot;
  robot.SetPosition(0, 1, 0);
  robot.SetSteeringDrift(10.0 / 180.0 * M_PI);
  return robot;
}

// Take the twiddle parameters and run a number of steps forward
// gathering the path and the error
static TwiddleResult RunTwiddlePass(Robot &robot, std::vector<double> params, int n=100, double speed=1.0) {
  TwiddleResult result;

  double err = 0;
  double prev_cte = robot.y_;
  double int_cte = 0;

  for (int i = 0; i < 2 * n; ++i) {
    double cte = robot.y_;
    double diff_cte = cte - prev_cte;
    int_cte += cte;
    prev_cte = cte;
    double steer = -params[0] * cte - params[1] * diff_cte - params[2] * int_cte;
    robot.Move(steer, speed);
    result.x_trajectory.push_back(robot.x_);
    result.y_trajectory.push_back(robot.y_);
    if (i >= n) {
      err += cte * cte;
    }
  }

  result.err = err/n;
  return result;
}

// Main test function. Call twiddle, passing a closure to run
// a pass and get the error.
void TestTwiddle() {
  auto result = Twiddle(3, 0, 1, 0.2, true, [&](std::vector<double> values) {
    Robot r = MakeRobot();
    return RunTwiddlePass(r, values).err;
  });

  std::cout << "Values:";
  for (auto v: result) {
    std::cout << " " << v;
  }
  std::cout << std::endl;
}


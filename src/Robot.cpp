//
//  Robot.cpp
//  Twiddle
//
//  Created by Ed Voas on 11/23/2017.
//  C++ version of Robot class as shown in Udacity robotics/self-driving car courses.
//

#include "Robot.h"

#include <math.h>
#include <random>

Robot::Robot(double length) {
  length_ = length;
}

void Robot::SetPosition(double x, double y, double orientation) {
  x_ = x;
  y_ = y;
  orientation_ = fmod(orientation, (2.0 * M_PI));
}

void Robot::SetNoise(double steering_noise, double distance_noise) {
// Sets the noise parameters.
// makes it possible to change the noise parameters
// this is often useful in particle filters
  steering_noise_ = steering_noise;
  distance_noise_ = distance_noise;
}

void Robot::SetSteeringDrift(double drift) {
// Sets the systematical steering drift parameter
  steering_drift_ = drift;
}

void Robot::Move(double steering, double distance, double tolerance, double max_steering_angle) {
// steering = front wheel steering angle, limited by max_steering_angle
// distance = total distance driven, most be non-negative

  if (steering > max_steering_angle) {
    steering = max_steering_angle;
  }
  if (steering < -max_steering_angle) {
    steering = -max_steering_angle;
  }
  if (distance < 0.0) {
    distance = 0.0;
  }

  std::default_random_engine generator;
  std::normal_distribution<double> steering_dist(steering, steering_noise_);
  std::normal_distribution<double> distance_dist(distance, distance_noise_);

  // apply noise
  double steering2 = steering_dist(generator);
  double distance2 = distance_dist(generator);

  // apply steering drift
  steering2 += steering_drift_;

  // Execute motion
  double turn = tan(steering2) * distance2 / length_;

  if (abs(turn) < tolerance) {
    // approximate by straight line motion
    x_ += distance2 * cos(orientation_);
    y_ += distance2 * sin(orientation_);
    orientation_ = fmod((orientation_+ turn), (2.0 * M_PI));
  } else {
    // approximate bicycle model for motion
    double radius = distance2 / turn;
    double cx = x_ - (sin(orientation_) * radius);
    double cy = y_ + (cos(orientation_) * radius);
    orientation_ = fmod((orientation_ + turn), (2.0 * M_PI));
    x_ = cx + (sin(orientation_) * radius);
    y_ = cy - (cos(orientation_) * radius);
  }
}

std::string Robot::Description() const {
  char buffer[1024];
  snprintf(buffer, sizeof(buffer), "Robot {x=%.5f, y=%.5f, orient=%.5f}", x_, y_, orientation_);
  return buffer;
}

std::ostream& operator<< (std::ostream& stream, const Robot& robot) {
  return stream << robot.Description() << std::endl;
}

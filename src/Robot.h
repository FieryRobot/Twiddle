//
//  Robot.h
//  Twiddle
//
//  Created by Ed Voas on 11/23/2017.
//  C++ version of Robot class as shown in Udacity robotics/self-driving car courses.
//

#ifndef Robot_h
#define Robot_h

#include <math.h>
#include <string>

// While this class is mutable, it might be better depending on the usage to use an
// immutable (const) version of this class.
class Robot {
public:
  Robot(double length = 20.0);

  void SetPosition(double x, double y, double orientation);
  void SetNoise(double steering_noise, double distance_noise);
  void SetSteeringDrift(double drift);
  void Move(double steering, double distance, double tolerance=0.001, double max_steering_angle=M_PI_4);

  std::string Description() const;

  friend std::ostream& operator<< (std::ostream& stream, const Robot& matrix);

public:
  double x_;
  double y_;
  double orientation_;
  double length_;
  double steering_noise_;
  double distance_noise_;
  double steering_drift_;
};

#endif /* Robot_h */

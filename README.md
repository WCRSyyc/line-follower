# omni4-follower
4 wheeled Omni-wheel line follower

Code for an [Omni Wheel](https://en.wikipedia.org/wiki/Omni_wheel) (also called Poly Wheel) based line follower robot.

A regular car has 4 wheels, as 2 sets of wheels, front and back, where the axles for the 2 sets are parallel.  Using the omni wheels, the where pairs have axles that are perpendicular instead.  There is actually no axle.  The wheels (and driving servos) are mounted equidistant (90 degrees apart) around the outside of the approximately circular robot.  With all motors rotating the same direction (clockwise, viewed from outside toward the center), the robot will turn in place (counter-clockwise, viewed from the top).  Driving (only) any 2 opposite wheels,

For a reasonably complete description of the movement and control for this physical layout, see
[Fuzzy](http://www.societyofrobots.com/robot_omni_wheel.shtml) at the [Society of Robots](http://www.societyofrobots.com/) web site.

### Issues with this design

The typical physical structure used for small robot has absolutely no suspension.  At the normal loads, there is no give or flex in the body.  Although the edges of the omni wheels contain rollers, in the vertical (load) direction they are solid.  There is no air pressure or other `sponginess` to provide any give.  The wheels are mounted to solid shafts in the motors (in this case, continuous rotation servos), and the motors in turn are fixed solidly to the body.  The generally circular layout for robot would normally be expected to distribute the weight evenly over all 4 wheels.  However, that rigid structure means that, very minor differences in the wheel mounts results in one of the opposite pairs of being slightly higher than the other pair.  Most of the weight for the robot rests on just one pair of wheels, the robot tilts slightly, with one wheel off of the ground, and very little weight on the final wheel.  Two wheels get good contact and traction, one wheel gets contact, but minimal traction, and the final wheel has no contact with the floor.  That all results in poor driving and directional control.  Deliberately adding some flex and softness (sponginess) to the structure can help, but that still only improves operation on a flat surface.  One of the local line following tracks includes a 'hill' where the robot needs to shift from flat to inclined and back.  Unless the robot meets the edge of the incline nearly simultaneously with 2 wheels, when the leading wheel starts up the incline (sideways), the driving wheels are lifted up, and loose traction.

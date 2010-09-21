# Anything that starts with a # is a comment!
# Use lots of comments in your code to explain what you're doing.

# Use the PIC-specific Python libraries
import pic24_dspic33 as pic

# Monitor RAM usage
import sys
print "\n\nRAM usage: (free, total): ", sys.heap()



###############################################################
# Set up line sensors, distance sensor, motors 
###############################################################

# Line sensors are digital inputs. Create one.
print "Testing line sensors.",
# For port and pin, a label of RA1 is port = 0 (A), pin = 1;
#                   a label of RB9 is port = 1 (B), pin = 9.
#                             port pin isInput
line_sensor_left =   pic.digital_io(1,   7,  True)
line_sensor_middle = pic.digital_io(1,   8,  True)
line_sensor_right =  pic.digital_io(1,   9,  True)
print "Line sensor 4: Is a black line present?",
print line_sensor_middle.get()

# The distance sensor is an analog input. Create one.
print "Distance sensor: voltage is",
# The only argument to analog_input is the ANx number of
# the analog pin to use. Below, the distance sensor is
# connected to AN4.
dist_sensor = pic.analog_input(4)
print dist_sensor.getVoltage(), "V"

# The servos are controlled by pulse-width modulation.
print "Driving left..."
#                    Frequency  isTimer2  OC module  RPx pin number
left_wheel  = pic.pwm(50,        True,     1,         6)
right_wheel = pic.pwm(50,        True,     2,         5)
# The motor speed is controlled by the parameter to the setCounts method.
# In this case, 1 count = 1.6 us.
# Values to use:
#   Max forward: 1300 us = 1300/1.6 counts = 813 counts
#   Stopped    : 1500 us = 1500/1.6 counts = 938 counts
#   Max reverse: 1700 us = 1700/1.6 counts = 1063 counts
# Values between these maxima control the forward/reverse speed.
#
# NOTES:
# - The actual counts to make each wheel stop vary slightly
#   from wheel to wheel. So, tune these until the wheels actually do stop.
# - Because the wheels are physically installed in opposite directions,
#   "forward" for one wheel makes it spin in reverse.
# To keep track of this, use variables to record forward/stop/reverse
# for each wheel.
left_wheel_forward  = 1063
left_wheel_stopped  = 942
left_wheel_backward = 813

right_wheel_forward  = 813
right_wheel_stopped  = 938
right_wheel_backward = 1063

#def drive_forward():
#    left_wheel.setCounts(left_wheel_forward)
#    right_wheel.setCounts(right_wheel_forward)
    
#def stop_driving():
#    left_wheel.setCounts(left_wheel_stopped)
#    right_wheel.setCounts(right_wheel_stopped)

#left_wheel.setCounts(813)
#right_wheel.setCounts(1063)



###############################################################
# Main loop
###############################################################

while True:
    # Stop if object is close
    if dist_sensor.getVoltage() > 2.5:
        left_wheel.setCounts(left_wheel_stopped)
        right_wheel.setCounts(right_wheel_stopped)
    # Stop if line is detected
    elif line_sensor_middle.get():
        left_wheel.setCounts(left_wheel_stopped)
        right_wheel.setCounts(right_wheel_stopped)
    # Keep running
    else:
        left_wheel.setCounts(left_wheel_forward)
        right_wheel.setCounts(right_wheel_forward)

    # Print out line following diags
    if line_sensor_left.get():
        print "X",
    else:
        print ".",
    if line_sensor_middle.get():
        print "X",
    else:
        print ".",
    if line_sensor_right.get():
        print "X"
    else:
        print "."

    # Delay some
    time = sys.time()
    while time + 10 > sys.time():
        pass
    








# Anything that starts with a # is a comment!
# Use lots of comments in your code to explain what you're doing.

# Use the PIC-specific Python libraries
import t114 as pic

line_sensor_right =  pic.digital_io(1,   8,  True)
right_wheel_stopped  = 938

print "Running..."
i = 0;
while i < 10:
    i = i + 1
    # Print out line following diags
    if line_sensor_right.get():
        pass

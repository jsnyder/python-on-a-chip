#
# Feature Test for Issue #22
#
# Implement classes
#
# This test investigates how instances of objects are created
#


# Create an instance using a module
e = Instantiate(object)


# Create an instance using a function
def Shape(n):
    inst = Instantiate(Shape)
    inst.n = n
    return inst
Shape.__p = object

hexagon = Shape(6)
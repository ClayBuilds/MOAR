# MOAR
Mother Of All Roombas - basic autonomous vacuum robot

This is the code used in the following video:
https://youtu.be/BIobB7fyads?feature=shared

It runs two brushed DC motors with differential "tank style" steering. 

A mechanical limit switch is triggered when the robot runs into an object. It then turns around to some random angle and continues driving.

Written for an arduino uno and a DFR0601 motor driver but will work on just about anything.

Also includes some code for reading a PS2 controller, mostly taken from an example in the library it uses.

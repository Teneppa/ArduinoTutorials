"""Control your Arduino's LED with a slider!

Yea it looks like bASS because it uses tkinter,
but it's quite easy to use and you can find a ton of
tutorials about it because it's old af.

This code is made by Teukkaniikka
YouTube: https://www.youtube.com/c/Teukkaniikka

Video about this project: https://youtu.be/RYxyElk0QRE
"""

import sys


# Change this to <True> if u want to install tkinter and pyserial automatically
enableAutoInstall = False

# This thing will install tkinter and serial to your
# pc if you have pip installed
if enableAutoInstall:
    import pip
    pip.main(['install', 'tk'])
    pip.main(['install', 'pyserial'])

# Lol no PEP8 4U (ಠ_ಠ)
# BTW don't hit <format document> ¯\_(ツ)_/¯
import serial
from tkinter import *

# Try to open up the serial port
# Change these if needed
serialPort = "COM3"
baudrate = 115200

# Spare your eyes from this, but this will check if the port exists
# and tells you if it doesn't
try:
    s = serial.Serial(serialPort, baudrate)
except Exception as e:
    print("\n", e)
    print(f">No device found on {serialPort} probably")

    sys.exit(69)


def sup(val):
    """Send the new slider value to the Arduino and add a semicolon to the message

    Args:
        val ([str]): The new slider position
    """
    # Add semicolon after the value
    msg = val+";"

    # Encode the message
    encodedMessage = msg.encode()

    # Send the encoded message
    s.write(encodedMessage)


# Create the tkinter window
root = Tk()

# Create the slider that is 40x1800, horizontal (the vertical looks pretty weird),
# goes from 0 to 255 and runs the function called "sup" every time it's moved
scale = Scale(root,
              variable=DoubleVar(),
              width=40,
              length=1800,
              orient=HORIZONTAL,
              from_=0,
              to=255,
              command=sup)

# Now we need to put the slider to the window using pack()
scale.pack()

# This will start the tkinter window to run
# This is a blocking function, so the code is basically
# stuck at row 76 unless there's some event's that have been set like
# our "sup" function that runs when the slider is moved.
#
# Only when we close the app the code will execute all of the stuff below.
root.mainloop()

# Close the serial port after the window is closed
print("Closing down")
s.close()

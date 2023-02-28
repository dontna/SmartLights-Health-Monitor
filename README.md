# SmartLights Health Monitor
This code allows you to monitor the health of a game character in real time and update the color of your TPLink SmartLight Strip based on their health.

# Note
1. This game was made and tested on Saints Row 3, however I've tried to make the code extremely easy to modiy so you can monitor the health from another game you want to!

Although bare in mind, you will have to get these addresses yourself with Cheat Engine.

2. I created this and the code for Linux. The Python script should work regardless, however the main CPP code won't, you may have to update the code yourself.

# How to use
To use this code, follow these steps:

1. Clone the repository and navigate to the directory:
`git clone https://github.com/your_username/game-health-monitor.git`
`cd SmartLight-Health-Monitor`

2. Install Python dependencies:
`pip install python-kasa`
Modify the configuration file located at config.h. You need to set the process name of the game, the path to the keyboard event, and the key to exit the script.

3. Compile the code:
`make`

4. Open the game, if you're just trying this out then open SaintsRow3 with DX10/11 when prompted.

5. Run the program:
`sudo ./monitor_health`

Note that the program requires root access to open the keyboard event device. Also, this script only works on the following TPLink SmartLightStrips:


1. KL400
2. KL420
3. KL430

# Taking my code
Please feel free to take this code and use it in your projects. There are so many things you could do with this such as:

1. Make the lights flash red and blue when you're being chased by police in GTA V
2. Make the lights flash each time you shoot, simulating muzzle flash
3. Turn the lights into a score meter for Clone Hero, make it almost like the Rock Meter in Guitar Hero games.

These are just a few ideas I've thought of, I'm sure you have some cool ones too! Go wild!

# Problems
If you encounter any errors in the code, that completely stop it from working; you 

# License
This code is licensed under the MIT license. See the LICENSE file for details
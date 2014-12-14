Pull Repository from Github
===========
1. Create and navigate to ~/catkin_ws/aicrobotics/
2. Run 'git init'
3. Set remote repository by running 'git remote add origin https://github.com/github_username_here/aicrobotics.git'
4. Pull files from repository with 'git pull https://github.com/github_username_here/aicrobotics.git'
5. For questions check out http://www.newthinktank.com/2014/04/git-video-tutorial/ and http://www.newthinktank.com/2014/04/git-video-tutorial-2/

Arduino Setup
===========
1. Install arduino by running 'sudo apt-get update && sudo apt-get install arduino arduino core'
2. Make sure java is installed by running 'sudo apt-get install openjdk-7-jre'
3. Set permissions to use USB port by running 'sudo chmod a+rw /dev/ttyACM0'

Run Application
===========
1. Build workspace by navigating to ~/catkin_ws and run 'catkin_make'
2. Upload aruduino_node sketch to aruino board
3. Open terminal tab (tab1) and run 'roscore'
4. Open terminal tab (tab2) and run 'rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0'
5. Open terminal tab (tab3) and run 'rosrun aicrobotics arduino_relay.py'
6. Open terminal tab (tab4) and run 'rosrun aicrobotics instruction_algorithm.py'

Resouces
===========
1. ROS tutorials - http://wiki.ros.org/ROS/Tutorials
2. ROS-Arduino tutorials - http://wiki.ros.org/rosserial/Tutorials
3. Message types - http://wiki.ros.org/std_msgs



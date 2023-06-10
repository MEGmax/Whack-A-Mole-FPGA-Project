# Whack-A-Mole-FPGA-Project
The game whack a mole! Written for DE1 SoC FPGA to display on a VGA monitor for ECE243
<h2>General Overview</h2>
<li>Title screen, press any key to continue</li>
<li>Screen to choose modes (2 modes, chosen by keys)</li>
<li>Then screen to select a specific setting to each mode (#lives, or #time)</li>
<li>Speed (duration of moles above ground) increased every 30 seconds automatically</li>
<li>Transition animations between each screen</li>
<li>End screen saying press any key to start again (taking you to mode selection)</li>
<h2>Overview of screens</h2>
<ol>
    <li> Title </li>
    <img width="622" alt="Title Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/2189b9fb10fc59c9073af1b4da6bcbaeccddd076/gameplay%20Images/startScreenGC.png">
    <li> Mode selection </li>
    <img width="622" alt="Mode Selection Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/modeSelScreen.png">
    <li> Lives Selection Menu</li>
    <img width="622" alt="Options Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/livesSelModeImg.png">
    <li> Time Selection Menu</li>
    <img width="622" alt="Options Screen 2" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/timeSelScreen.png">
    <li> Gameplay till loss</li>
    <img width="622" alt="Gameplay Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/gameplay.png">
    <li> Game Over Screen</li>
    <img width="622" alt="Game Over Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/endScreen.png">
    <li> (Bonus) Credits Screen</li>
    <img width="622" alt="Credits" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/creditsStatic.png">
</ol>
<h2>Modes</h2>
<h4>Mode 1: Survival</h4>
<li>In survival you have n lives</li> 
<li>After that game is reset number of switches turned on corresponds to number of lives you have</li>
<li>Live countdown of lives is avalibale on screen</li>
<h4>Mode 2: Timed</h4> 
<li>You have a countdown to get as high a score as possible</li>
<li>n Number of switches turned on corresponds to n x 30sec for time</li>
<li>Live time countdown is on screen</li>

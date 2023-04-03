# Whack-A-Mole-FPGA-Project
The game whack a mole! Written for DE1 SoC FPGA to display on a VGA monitor for ECE243
<img width="622" alt="Screenshot_2023-03-08_at_7 29 06_PM" src="https://user-images.githubusercontent.com/96932850/229607133-af9201d4-a7fd-4f2e-b598-d5f256251e33.png">
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
    <li> Mode selection </li>
    <li> Lives/time selection for chosen mode</li>
    <li> Gameplay till loss</li>
    <li> End screen, press any key to adv (to #2)</li>
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

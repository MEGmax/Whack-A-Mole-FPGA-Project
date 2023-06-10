# Whack-A-Mole-FPGA-Project
This is a virtual Whack-A-Mole game played with a keyboard and peripherals such as switches and buttons on a physical DE1-SoC Board.
<h2>General Overview</h2>
<li>Title screen, press any key to continue</li>
<li>Screen to choose modes (2 modes, chosen by keys)</li>
<li>Then screen to select a specific setting to each mode (#lives, or #time)</li>
<li>Speed (duration of moles above ground) increased every 30 seconds automatically</li>
<li>Transition animations between each screen</li>
<li>End screen saying press any key to start again (taking you to mode selection)</li>

<h2>Equitment + Environment</h2>
<li>Testing was completed using CPUlator, an online computer simulator simulating ARMv7 architecture for DE1SoC System</li>
<ul>
    <li>Virutal Environment Link: https://cpulator.01xz.net/?sys=arm-de1soc</li>
</ul>
<li>Built for DE1SoC board which is equipped with an FPGA and ARM Cortex-A9 processor, offering a versatile platform for developing C -based games and exploring software-hardware co-design possibilities</li>
<ul>
    <li>Board Details: https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&No=836</li>
    <li>Documentation Consulted: https://www.terasic.com.tw/cgi-bin/page/archive_download.pl?Language=English&No=836&FID=3a3708b0790bb9c721f94909c5ac96d6</li>
</ul>
<li>Workflow managed between creators Matthew Grech and Mitchell Palermo using GIT</li>
<li>Compiled, built onto board and run using Intel FPGA Monitor Program
<ul>
    <li>Program Documentation: https://fpgacademy.org/Downloads/DE1-SoC_Computer_ARM.pdf</li>
    <li>Tutorial: http://www-ug.eecg.toronto.edu/desl/docs/Monitor_tutorial.pdf</li>
</ul>
<h2>Preview of Gameplay Screens</h2>
<ol>
    <li> <strong>Title </strong></li>
    <img width="622" alt="Title Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/2189b9fb10fc59c9073af1b4da6bcbaeccddd076/gameplay%20Images/startScreenGC.png">
    <li> <strong>Mode selection </strong></li>
    <img width="622" alt="Mode Selection Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/modeSelScreen.png">
    <li> <strong>Lives Selection Menu </strong></li>
    <img width="622" alt="Options Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/livesSelModeImg.png">
    <li> <strong>Time Selection Menu </strong></li>
    <img width="622" alt="Options Screen 2" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/timeSelScreen.png">
    <li> <strong>Gameplay till loss (static) </strong></li>
    <img width="622" alt="Gameplay Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/gameplay.png">
    <li><strong> Game Over Screen </strong></li>
    <img width="622" alt="Game Over Screen" src="https://github.com/MEGmax/Whack-A-Mole-FPGA-Project/blob/b33ad4df3c8d127ce62a0707b48eb54526c5bdae/gameplay%20Images/endScreen.png">
    <li><strong> (Bonus) Credits Screen </strong></li>
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

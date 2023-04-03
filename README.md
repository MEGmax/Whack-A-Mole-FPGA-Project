# Whack-A-Mole-FPGA-Project
The game whack a mole! Written for DE1 SoC FPGA to display on a VGA monitor for ECE243
<img width="622" alt="Screenshot_2023-03-08_at_7 29 06_PM" src="https://user-images.githubusercontent.com/96932850/229607133-af9201d4-a7fd-4f2e-b598-d5f256251e33.png">
<h1>Plan sent to Ta</h1?
Below is our idea for the project, let us know if you think we should add any further complexities
Whack a mole:
- 4 holes, each key corresponds to one, press to whack
- Title screen, press any key to continue
- screen to choose modes (2 modes, chosen by keys)
- Then screen to select a specific setting to each mode (#lives, or #time)
- Speed (duration of moles above ground) increased every 30 seconds automatically
- Transition animations between each screen
- End screen saying press any key to start again (taking you to mode selection)
Overview of screens
1. Title
2. Mode selection
3. Lives/time selection for chosen mode
4. Gameplay till loss
5. End screen, press any key to adv (to #2)
Mode descriptions:
- Mode 1: survival, In survival you have n lives, after that game is reset
- number of switches turned on corresponds to number of lives you have
- Live countdown of lives is on screen
- Mode 2: timed, you have a countdown to get as high a score as possible
n Number of switches turned on corresponds to n x 30sec for time,
- Live time countdown is on screen

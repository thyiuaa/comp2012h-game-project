# COMP2012H - Shooting Game
*** Moved from https://bitbucket.org/thyiuaa/project to https://github.com/thyiuaa/comp2012h-game-project
## Descrption
This is a 2D vertical shooting game. C++ assignments will appear on the top of the screen and gradually move to the bottom. Control Desmond to shoot them down and get points. Get enough points to win the game!<br/>

## Control:
Space - shoot<br/>
Up - move up<br/>
Down - move down<br/>
Left - move left<br/>
Right - move right<br/>

## Environment
Qt Creator 4.13.2/ Qt 5.15.1<br/>

## Steps
Open project.pro<br/>
Press "Ctrl + R"<br/>

## Specifications
### General
Background is always displayed<br/>
Click on the top left "Close window button", a exit confirm window pops up<br/>
The title of the windows is "COMP2012H (Group H19) - Shooting Game"<br/>
### Main menu
Consists of 2 buttons, "Game Start" and "Leave Game"<br/>
Click "Leave Game", a exit confirm window pops up<br/>
Click "Game Start", the game starts and 2 buttons are hidden<br/>
### Game window
Score, hp bar are shown on top left<br/>
enemy appear from the top, player spawn at the bottom middle<br/>
different enemies should have different spawnning location, path, and shooting rate<br/>
Pressing arrows key can control player's movement<br/>
Pressing space bar can shoot<br/>
Player can move slightly out of bound (size of 1 character)<br/>
Cannot move to left and right, or up and down at the same time<br/>
Player takes 1 damage if collide with enemy<br/>
Player takes 1 damage if hit by enemy's bullet<br/>
The hp bar will update if the player takes damage<br/>
If the enemy dies, it disappear from the scene but its bullets remain<br/>
If the player kills a enemy, the score will update<br/>
If score reached a certain number or the player dies, the game is over<br/>
### Game over window
Consist of score bar, 2 button<br/>
If the game ends because the player dies, a message show to indicate the player loses<br/>
If the game ends because the player get enough score, a message show to indicate the player wins<br/>
Click on the "Leave Game" button will open exit confirm window<br/>
Click on the "Play again" button will restart the game<br/>
### Exit confirm window
The title of the window should be "Exit Confirm"<br/>
Cannot click on main window if the exit confirm window is opened<br/>
Consists of a message and 2 buttons<br/>
Click "OK" then the game closes<br/>
Click "Cancel" then the Exit confirm window closes but the main window remains<br/>
If the game is started (after clicking "Game Start" in the main menu), open this window will pause the game<br/>
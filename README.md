# TOP DOWN GAME
#### Video Demo:  <https://youtu.be/PaYKpvcbH64>
#### Description:
The game is built with c++ language using raylib library. All characters is taken from website itch.io. the game is to destroy all the enemy to win. Since the enemy and hero have some common functionality, such as animate the character, idle stage, running stage and render the character to the window. so, the code is design using class inheritance. Which have Player class as a base class and Hero class and Enemy class are inheritance form.

The Hero class inheritance form Player class and add some function such as render the weapon, control the movement and keep track of the health status.

The Enemy class inheritance form Player class also and add some function such as animate attack, animate death and the most importance detect the Hero as target so the enemy can chase the Hero.
The functionality is put together in main.cpp file but the game logic is so long thus the helper file is create to keep main file simple. The main helper function is consisting of three functions as following. gameIntro, gameLogic, and gameOver function 

gameIntro funciton will execute once when the game is lunch by loading the map and knight character the animate while prompt the game control direction until user hit spacebar then the gamIntro function will unload all the picture before return.

gamLogic function will load the picture that need to render the game such as map, knight character and enemy character then initialize the Hero and Enemy and pass the picture address to that object this allow to create same character as much as required by load the character picture once. For example if the enemy is require to create two goblin, the picture or goblin will be lode to the memory just one picture and share together with two goblin Enemy object. Then the game start by keep tract the Hero position, health and the survive enemy. If the health of Hero is decrees to zero the game is over but if all enemy is death the user will win the game in both condition the loaded picture will be unload from the memory and the function will return.

gameOver function will execute when the Hero health in gameLogic function decrees to zero. It begin with loading background picture to render and keep render until user press spacebar to play the game again. Then gamOver function will unload background from memory and return.

All three function are inside while loop so it will loop until user close the window.   

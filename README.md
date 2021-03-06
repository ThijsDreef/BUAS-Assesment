# BUAS-Assesment

## Game
A simple endless runner game with collectables and enemies.

controls:
- WASD to move
- Space to jump
- Esc to pause (in-game only)
- A-D to change color grade (title-screen only)

## Options
On quit the engine will drop an options.txt file in which you will find all persistent data, such as highscores and engine settings for width/height, fullscreen, etc. After changing those options reboot the program to make it take effect.

## Color-grade
I added the option to add color-grade the game based on a look up texture.

The game enginge checks the folder /shaders/postproccesing/luts to find any luts that end with the extension .png and adds them to available luts in game. Any data found in the options.txt regarding luts will be overwritten at runtime

creating your own lut is as easy as taking a screenshot of the game, overlaying it with the default lut use any color filter in your preffered image editor and saving it as "lutname.png" and saving it into the previous mentioned folder

## Engine
I continued this project from my own c++ game engine i have been working on for a longer time. this project can be found [here](https://github.com/ThijsDreef/pointOfNoReturn). While making this project i ran into a few issues with the design/implementation of the engine. This gave me insights on how to change the engine to make it easier to create games with. All changes will be merged back in to PointOfNoReturn after this project

## Build
This project can be build either with visual studio "visual studio solution is in repo". or be build by using mingw with make "makefile can be found in the repo". some quick use bat scripts are included for building/cleaning/running from the git directory

## Credits
- game made by [Thijs Dreef](https://thijsdreef.com)
- sdf-font atlas generated by hiero [link here](https://github.com/libgdx/libgdx/wiki/Hiero)
- water texture by Shirley van Steenis [link here](http://www.shirleyvansteenis.com/)
- pinguin lend from the modellers resource [link here](https://www.models-resource.com/wii/marioparty9/model/4232/)
- shark lend from the modellers resource [link here](https://www.models-resource.com/wii/marioparty9/model/4240/)
- ice texture [link here](https://www.pinterest.com/pin/777363585653620180/?lp=true)
- water plane and ice model made by Thijs Dreef
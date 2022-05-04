# Wolf3D

Inspired by the famous eponymous game of the 90s and the first First Person Shooter, Wolfenstein 3D. This project got me acquainted with ray-casting.
The goal was to represent a dynamic view in a labyrinth which you can move inside.

# How to use it?

04/05/2022: I took the time to add a standalone version of MinilibX for MacOSX so all you gotta do is jump into testing it :) No installing MinilibX anymore

***REALLY IMPORTANT: You MUST have the graphical library used in all my graphical projects at 42 Schools called MinilibX and a MacOS in order to use the keys!***

***If you would like to know how to install MinilibX, check this https://github.com/gcamerli/minilibx for clear instructions and system requirements***
 
***PS: You should always ignore the quotation marks, they are just comments of what you should input***

> git clone "my repo URL" "your folder path"

You can compile it through a Makefile in the root of my Repo
> make

This will compile my library with useful C functions, the graphical library MiniLibX and my Wolf3D files,
creating an executable called **wolf3d**

In order to run the executable, type:
> ./wolf3d "your test map"

# Creating a map

This is the smallest square possible that you can create. It's mandatory to have walls on map limits and at least one floor spot to place the character.

> 1 1 1

> 1 0 1

> 1 1 1

1 2 3 4 5 6 7 8 9 = Walls with a specific sprite each

0 = Floor

You need spaces between the numbers and of course only digits from 0 to 9. I did my best to make sure all mistakes were handled so if something is wrong, my program
will stop and tell you what's wrong on your map.

The player's start position will ALWAYS be the first zero found by the program from the most top-left corner on your map.

**In case you have any doubt of how the map should be made, check map folder with valid and invalid examples.**

# Buttons
- Arrow Keys or WASD -------->"Move around"
- 1 (Numeral) ----------------->"Turn ON/OFF Sprites"
- Left Shift or Right Shift ------>"Hold it to sprint while moving forward"
- ESC Key -------------------->"Close Program"

# Future implementations
Many implementations such as an objective, objects to collect, enemies, health system and everything an actual game would have will be covered at the next project
**Doom Nukem** since it's a continuation of this project according to 42's project schedule. Doom Nukem will be a cross-over between Dukem Nukem and Doom, bringing the best from both games on top of this project. I am very excited to be working on it and I hope you enjoyed Wolf3D.

# Images

![Image of Subject](https://github.com/MuSuareZ/Wolf3D/blob/master/img/textureoff.png)
![Image of Subject](https://github.com/MuSuareZ/Wolf3D/blob/master/img/textureon.png)

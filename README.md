# Wolf3D

Inspired by the famous eponymous game of the 90s and the first First Person Shooter, this project got me acquainted with ray-casting.
The goal is to represent a dynamic view in a labyrinth which you can move inside.

# How to use it?

***REALLY IMPORTANT: You MUST have the graphical library used in the whole project called MinilibX installed and a MacOS in order to
use the keys to interact with the shapes!***

> git clone "my repo URL" "your folder path"

You can compile it through a Makefile in the root of my Repo
> make

This will compile my library with useful C functions, the graphical library MiniLibX and my Wolf3D files,
creating an executable called **wolf3d**

In order to run the executable, type:
> ./wolf3d "test map"

# Creating a map

This is the smallest square possible you can create. It's mandatory to have walls on map limits and at least one floor spot to place the character.

> 1 1 1

> 1 0 1

> 1 1 1

1 2 3 4 5 6 7 8 9 = Walls with a specific sprite each

0 = floor

You need spaces between the numbers and of course only digits. I did my best to make sure all mistakes were handled so if something is wrong, my program
will stop and tell you what's wrong on your map.

**In case you have any doubt of how the map should be made, check map folder with valid and invalid examples.**

**Buttons**
- Arrow Keys or WASD -------->"Move around"
- 1 (Numeral) ----------->"Turn ON/OFF Sprites"
- Left Shift or Right Shift ------>"Hold it to sprint"
- ESC Key ----------->"Close Program"

![Image of Subject](https://github.com/MuSuareZ/Wolf3D/blob/master/img/textureoff.png)
![Image of Subject](https://github.com/MuSuareZ/Wolf3D/blob/master/img/textureon.png)

***PS: You should always ignore the quotation marks, they are just comments of what you should input***

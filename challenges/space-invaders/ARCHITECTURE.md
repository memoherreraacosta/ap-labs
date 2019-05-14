# Advanced Programming 
## Space Invadors Project Arquitecture
### Programming language: Golang
#### -Team Members:
###### Victor Najar
###### Katya Chumakova
###### Guillermo Herrera
###### Floreth Gonzalez




Space Invaders has a component based architecture. It consists of ten .go files that will be described bellow.

**player_control.go**
Set player layout limits
Set bullet trajectory and activation according to players position

**player.go**
Create new player
Render sprite of player

**sprite_renderer.go**
Uses sdl Go library to render players and enemies

**vulnerable_to_bullets.go**
Collision checker

**element.go**
Array of elements that can be {bullets, enemies, players}
Array of components that are actions {shoot, move}

**collisions.go**
Collision logic of bullet and enemy 

**bullet.go**
Initialize pool of bullets

**bullet_mover.go**
Calculates position of bullet 
Collision of bullet

**basic_enemy.go**
Create a new enemy

**main.go**
Player score
Enemies behaviours are implemented on separate threads 

### Libraries
<em>**go-sdl2-sdl**</em>
It enables interoperability between Go and the SDL2 library which is written in C. SDL2 is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.

<em>**go-sdl2-img**</em>
Enables the use of png images as sprites.

<em>**go-sdl2-ttf**</em>
Package ttf is a TrueType font rendering library that is used with the SDL library, and almost as portable. It depends on freetype2 to handle the TrueType font data. It allows a programmer to use multiple TrueType fonts without having to code a font rendering routine themselves.

### Space Invadors prerequisites:
- Have Golang installed.
- Run on a bash terminal.

### Space Invadors game rules:
- The player should choose a minimum of 16 enemies to play against.
- The player can move from left to right using the keyboard left and right arrows.
- The player can shoot the enemies using the space keyboard.
- The player will loose if it gets shoot 10 times.
- The player wins the game if it destroys all of the space invadors.

### To Compile Space Invaders:
```go
make
```

// dot move with joystick
if joystick moves left  
    put dot to left of last dot.
if joystick moves right
    put dot right of last dot.
if joystick moves up   
    put dot over of last dot.
if joystick moves down
    put dot under of last dot.

//Make last dot dissapere
when the dot moved
    turn of the previous dot 

//Plot food atleast one space away from dot
    calculate where dot
        light a randomly atleast one space away. 
    if dot reaches food
        turn of led 
        plot new food 

//make snake grow when eating. 
    if dot reaches food 
        add additional dot to snake. 

//make snake move countoisly 
    for loop?
    snake moves countinusly in last direktion
    when moving forward, last dot dissaperse 

//make game end if snake collides with itself or wall
    if snake crosses itself
        end game
    if snake runs in to wall
        end game

//Random starting position
    randomize a dot to start the game on. 

//Print on ledmatrix
    print GAME on led matrix
        when button is clicked
            start game 
    
    when snake crosses itself or runs int to wall
        print END on ledmatrix
    
    if not able to plot new food 
        print WIN on ledmatrix

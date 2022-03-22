# 2D Game Engine

A standalone application

## Features

### Support needed

The software requirements to run the application :

- Linux OS 
- C++ 11 or above
- SFML library installed

## Controls

The controlls can be edited from the config/key_binds.ini

Key Binds | Actions 
------------ | ------------- 
Toggle menu | Escape  
MOVE_LEFT   | A
MOVE_RIGHT  | D
MOVE_UP     | W
MOVE_DOWN   | S
DASH        | Space
SLOW        | LShift
NEXT_ANIM   | E
PREV_ANIM   | Q
RESET_ANIM  | R
NEW_ROOM    | T


## Install SFML

SFML can be installed dirrectly from the website by following the instructions or cloned from the [repository](https://github.com/SeptimiuPop/2D-Game-Engine/tree/main/External/SFML).

If the latter is chosen, all directories except `include` and `lib` in the SFML folder can be removed. In order to compile the code properly the `Makefile` file should include the following changes :

```
$(CC) -c $(SRC) $(INCLUDES) <SFML/include Path>
$(CC) *.o -o $(EXE_PATH) $(LIBS) -L <SFML/lib Path> 
```

Where `<SFML/include Path>` and `<SFML/lib Path>` are replaced by the path of the include and lib directories in the cloned SFML folder


## Prepare the commands

In order to successfully build and run the application you must create a folder named bin where the build files will go. To do this use the following command from the terminal :

```properties
mkdir bin
```

Other names can also be used for the directory but the 'BIN_PATH' in the Makefile should be changed accordingly

- ### Launch the Application

From the terminal use the following command to build and launch the application :

` make run `  

- ### Build the application
From the terminal use the following command to compile the code in the bin folder created previously, and run it :

`make build`

- ### Clear the previous build for the application

From the terminal use the following command to clear the build :

` make clear `

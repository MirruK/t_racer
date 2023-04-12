# t_racer - typeracer-like CLI-game in C

## Win condition

<ins>Type out the given text correctly to win</ins>

## How to run

Disclaimer: This game has only been ran and tested on
a linux machine, it is unlikely that it will work in
the intended way on a non-linux system.

Firstly, make sure you have the ncurses package installed.
On archlinux ncurses can be installed via the
following command:
```
sudo pacman -S ncurses
```
On ubuntu:
```
sudo apt-get install libncurses5-dev
```

To create the binary simply run these commands:
```
git clone https://github.com/MirruK/t_racer.git
cd t_racer
make
./game
``` 


The text you will be tasked with typing out is found
under the "texts" directory.

You can provide your own text files as a command-line
argument, eg. `./game "texts/my_own_text.txt"`

# This is a simple TODO cli

### what this is not :
- a calendar
- an app with a gui
- complex

### what this is :
- a simple cli
- open source
- cpp code you can run friking anywhere
- customizable as heck if you know cpp
- actually a tool i use everyday now
- coded in like 3 hours (most of it on the bus/metro)

## how to use :
- clone repo
- compile
- create todo.txt in the same folder as executable
- for ease of use
  - add yourself an alias in your .bashrc ; something like this : alias todo="~/todo/executable"

## commands :
- todo add :
  - adds an item to your todo list
  - the flag -i marks it as important
  - the flag -x marks it as crossed out (idk why you would do that though)
  - NOTE : flags can be placed anywhere as argument, even in the middle of your todo sentence and it will still work correctly.
  - alias to add is a
  - examples :
    - todo add -i eat
    - todo add eat
    - todo a eat -i
    - todo a going to -i eat
- todo cross :
  - crosses an item using its index (can be multiple)
  - alias to cross is x or c
  - examples :
    - todo cross 0
    - todo x 0 1 2
    - todo c 3 8
- todo important :
  - marks an item as important using its index (can be multiple)
  - alias to important is i
  - examples :
    - todo important 2
    - todo i 4 5 9
- todo remove :
  - removes an item using its index (can be multiple)
  - alias to remove is r or rm
  - examples :
    - todo remove 0
    - todo r 3 2 7
    - todo rm 1 3
- todo show :
  - simply prints out your todo list
  - alias to show is s or _no arguments_
- todo _other_
  - acts as todo add
  - be careful your item doesnt begin with words like _remove_ or _add_ else it wont work
  - examples :
    - todo going for a walk
    - todo -i going for a walk
    - todo going for a walk -i
    - todo going -i for a walk

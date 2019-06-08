#!/usr/bin/env python3

# Python 3.7.3

### Abstract ###

### Text adventure game ###

### Mars ###

import sys, time, random, io, json, string, os
from player import player 
from script import locations, insults
import readline
import pprint as pp

typing_speed = 100

def slow_type(t):
    
    for l in t:
        sys.stdout.write(l)
        sys.stdout.flush()
        time.sleep(random.random()*10.0/typing_speed)

    print("")

def state():
    pass
    

def initialize():
    os.system('clear')
    slow_type(locations["room"])
    

def loop():
    inp = input("> ")
    while inp:
        if inp == 'clear':
            os.system('clear')

        elif inp == 'quit':
            break

        elif inp.split(" ")[0] == 'walk' and len(inp.split(" ")) == 2:
            if inp.split(" ")[1] in locations.keys():
                adventurer.place = inp.split(" ")[1]
                slow_type(locations[adventurer.place])
            else:
                print('Place doesn\'t exist.')

        elif inp == 'look' or inp == 'l':
            slow_type(locations[adventurer.place])
            

        elif inp == 'inventory':
            print('-Inventory-')
            for i in p.get_inventory():
                print(i)

        else:
            print(random.choice(insults))
    
        inp = input("> ")

adventurer = player()
initialize()
loop()


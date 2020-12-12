#!/usr/bin/env python3

### Abstract ###

### Text adventure game ###

### Mars ###

import sys, time, random, io, json, string, os
import readline
import pprint as pp

typing_speed = 100


class player:

    inventory = ['flashlight', 'knife']
    hunger = 0
    place = 'room'

    def __init__(self):
        pass

    def move(self, place):
        self.place = place

    def add(self, item):
        self.inventory.append(item)

    def get_inventory(self):
        items = []
        for i in self.inventory:
            items.append(i)

        return items

locations = {

    "room": "You are in a small dimly lit empty room",
    "corridor": "You are in a brightly yet haunting long corridor with checkboard ceiling and walls"

}

insults = [
    'What are you talking about?',
    'Are you insane?',
    'Play the game not the fool.',
    'Επικοινωνείς;',
]


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
    

def loop(adventurer):
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
            

        elif inp == 'inventory' or inp == 'inv':
            print('-Inventory-')
            for i in adventurer.get_inventory():
                print(i)

        else:
            print(random.choice(insults))
    
        inp = input("> ")

p = player()
initialize()
loop(p)

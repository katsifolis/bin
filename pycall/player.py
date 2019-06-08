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

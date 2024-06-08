//  Created by Richard Skarbez on 5/7/23.
// Edited by Astrid on June 2024



#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cout << "Welcome to Lost Echoes. Type Start to begin.\n";
    std::getline(std::cin, input);

    if (input == "Start" || input == "start") {
        std::cout << "\nYou are a loving father who wakes up one night to find your child, Emily, missing from her bed.\nIn a panic, you search around but find no trace of her.\nAs you call out her name, you hear a faint echo from the basement,\na place you rarely visit. Determined to find your daughter,\nYou will now descends into the unknown, beginning your journey through a series of mysterious and eerie rooms.\n";

        std::shared_ptr<Room> start = std::make_shared<Room>("bedroom",
                               "\nYou are standing in your bedroom.\nIt's dark and quiet, the only sound is the ticking of the old clock on the wall.\nThere is a torch light on the bedside table.\nThere is a door in front of you");

        std::shared_ptr<Item> torch = std::make_shared<Item>("torch", "A torch light on the bedside table.");
        start->addItem(torch);

        std::shared_ptr<Room> hallway = std::make_shared<Room>("hallway" ,
                                 "\n");
        std::shared_ptr<Room> attic = std::make_shared<Room>("attic", "You are in the attic. It's dusty and full of cobwebs, and you can hear the sound of the wind outside.\n");
        std::shared_ptr<Room> kitchen = std::make_shared<Room>("kitchen",
                           "You are in the kitchen.\nThere is a key on the table.\nYou see a closed door in front of you");

        std::shared_ptr<Item> key = std::make_shared<Item>("key", "A key on the kitchen table.");
        kitchen->addItem(key);
        

        std::shared_ptr<Room> basement = std::make_shared<Room>("basement",
                                        "\n");
        std::shared_ptr<Room> outside = std::make_shared<Room>("outside",
                               "\nYou are outside your house.\nIt's dark and quiet, there is a note on the ground in front of you.\n");
        std::shared_ptr<Item> note = std::make_shared<Item>("note", "A note on the ground");
        kitchen->addItem(note);

        //passage from the bedroom to the hallway
        Passage::createBasicPassage(start.get(), hallway.get(), "front", true);
        //passage from the hallway to bedroom
        Passage::createBasicPassage(hallway.get(), start.get(), "back", true);
         //passage from the hallway to attic
        Passage::createBasicPassage(hallway.get(), attic.get(), "up", true);
         //passage from the hallway to kitchen
        Passage::createBasicPassage(hallway.get(), kitchen.get(), "down", true);
        // passage from the kitchen to the basement
        Passage::createBasicPassage(kitchen.get(), basement.get(), "front", true);
        // passage from basement to kitchen
        Passage::createBasicPassage(basement.get(), kitchen.get(), "back", true);
        // passage from the basement to outside the house
        Passage::createBasicPassage(basement.get(), outside.get(), "front", true);
        // passage from outside the house to the basement
        Passage::createBasicPassage(outside.get(), attic.get(), "back", true);
        // passage from kitchen to hallway
        Passage::createBasicPassage(kitchen.get(), hallway.get(), "up", true);
        // passage from attic to bedroom
        Passage::createBasicPassage(attic.get(), start.get(), "down", true);
        //passage from the attic to hallway
        Passage::createBasicPassage(attic.get(), hallway.get(), "back", true);


        ZOOrkEngine zoork(start);

        zoork.run();
    }
    return 0; 
}
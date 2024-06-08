//  Created by Richard Skarbez on 5/7/23.
// Edited by Astrid on June 2024

#include "ZOOrkEngine.h"

#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {

        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "comfort") {
            handleComfortCommand(arguments);
        } else if (command == "use") { 
            handleUseCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
            if (gameOver) {
                return;
            }
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "l" || arguments[0] == "left") {
        direction = "left";
    } else if (arguments[0] == "r" || arguments[0] == "right") {
        direction = "right";
    } else if (arguments[0] == "f" || arguments[0] == "front") {
        direction = "front";
    } else if (arguments[0] == "b" || arguments[0] == "back") {
        direction = "back";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    if ((currentRoom->getName() == "bedroom" && direction == "back") || 
        (currentRoom->getName() == "hallway" && direction == "front")) {
        std::cout << "You can't go that way.\n";
    } else {
        try {
            auto passage = currentRoom->getPassage(direction);
            if (direction == "front" && currentRoom->getName() == "kitchen" && !player->hasUsedKey()) {
                std::cout << "The door is locked. You need to use a key to open it.\n";
                return;
            }

            player->setCurrentRoom(passage->getTo());
            passage->enter();

            // Check if the player is in the attic and has a note in their inventory
            if (player->getCurrentRoom()->getName() == "attic" && player->hasItem("note")) {
                std::cout << "Emily is in the corner and she is crying.\nComfort Emily";
            }
            // Check if the player has the torch when they enter the hallway
            if (player->getCurrentRoom()->getName() == "hallway") {
                if (player->hasItem("torch")) {
                    std::cout << "It is dark. You should try using your torch.\n";
                } else {
                    std::cout << "It is dark here. You must have a torch to continue.\n";
                }
            }
            // Check if the player has the torch when they enter the basement
            if (player->getCurrentRoom()->getName() == "basement") {
                if (player->hasItem("torch")) {
                    std::cout << "It is dark. You should try using your torch.\n";
                } else {
                    std::cout << "It is dark here. You must have a torch to continue.\n";
                }
            }
            if (player->getCurrentRoom()->getName() == "outside") {
                // Create a new note item
                std::shared_ptr<Item> note = std::make_shared<Item>("note", "A note that reads 'Dad, Save me'");

                // Add the note to the outside room
                player->getCurrentRoom()->addItem(note);
            }
        } catch (std::out_of_range&) {
            std::cout << "You can't go that way.\n";
        }
    }
}

void ZOOrkEngine::displayRoomDescription() {
    Room* currentRoom = player->getCurrentRoom();
    if (currentRoom->getName() == "hallway") {
        if (player->hasItem("torch")) {
            std::cout << "It is dark here. You might have to use the torch.\n";
        } else {
            std::cout << "It is dark here. You should have brought a torch with you.\n";
        }
    } else {
        std::cout << currentRoom->getDescription() << "\n";
    }
     if (currentRoom->getName() == "basement") {
        if (player->hasItem("torch")) {
            std::cout << "It is dark here. You might have to use the torch.\n";
        } else {
            std::cout << "It is dark here. You should have brought a torch with you.\n";
        }
    } else {
        std::cout << currentRoom->getDescription() << "\n";
    }
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();
    if (currentRoom->getName() == "hallway" && !player->hasItem("torch")) {
        std::cout << "It's too dark to see anything. You might need to use a torch.\n";
        return;
    }

    std::cout << currentRoom->getDescription() << "\n";

    // Display the items in the current room
    std::cout << "Items in the room: ";
    for (const auto& item : currentRoom->getItems()) {
        std::cout << item.second->getName() << " ";
    }
    std::cout << "\n";

    // Display the passages leading from the current room
    std::cout << "Passages: ";
    for (const auto& passage : currentRoom->getPassages()) {
        std::cout << passage.first << " ";
    }
    std::cout << "\n";
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> command) {
    if (command.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string itemName = command[0];
    Room* currentRoom = player->getCurrentRoom();

    // Check if the item exists in the room's inventory
    if (currentRoom->hasItem(itemName)) {
        std::shared_ptr<Item> item = currentRoom->removeItem(itemName);
        // Add the item to the player's inventory
        player->addItem(item); // Change this
        std::cout << "You took the " << item->getName() << ".\n";
    } else {
        std::cout << "There is no " << itemName << " here.\n";
    }
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Use what?\n";
        return;
    }

    std::string itemName = arguments[0];

    // Check if the player has the item in their inventory
    if (player->hasItem(itemName)) {
        // Implement the logic for using the item here
        std::cout << "You used the " << itemName << ".\n";
        if (itemName == "torch" && player->getCurrentRoom()->getName() == "hallway") {
            std::cout << "You are in the hallway.\nThe Attic is upstairs.\nThe Kitchen is downstairs.\nYour bedroom is behind you.\n";
        }
        if (itemName == "torch" && player->getCurrentRoom()->getName() == "basement") {
            std::cout << "You are in the basement.\nIt's cold and damp, and you can hear the sound of dripping water.\nThe door that goes outside is in front of you.\n";
        }
        if (itemName == "note") {
            std::cout << "Help me Dad. I am in the Attic\nGo back to the Attic.\n";
        }
        if (itemName == "key") {
            player->setUsedKey(true);
        }
        
    } else {
        std::cout << "You don't have a " << itemName << ".\n";
    }
}
    void ZOOrkEngine::handleComfortCommand(std::vector<std::string> arguments) {
    // Check if the player is in the attic and has a note
    if (player->getCurrentRoom()->getName() == "attic" && player->hasItem("note")) {
        std::cout << "Emily had a nightmare.\nShe saw her mom, who died 5 years go, in her dreams.\nShe was in the attic but there is no one here.\nEmily has to go back to sleep now.\nShe has school tomorrow.\nYou take Emily down to her room.\n";

            // Print the message
            std::cout << "You put Emily to sleep\nYou sit there and wonder who left the note outside.\nEmily didn't do that, did she?\nMaybe there is infact someone else in the house.\nPerhaps a monster.\nYou do not have time to think about it now.\nYou have to go to sleep.\nYou have work tomorrow.\nTHE END";

            gameOver = true;
            return;
    } else {
        std::cout << "You can't do that here.\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input); 
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

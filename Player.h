#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <memory> // Include this for std::shared_ptr

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

    void addItem(std::shared_ptr<Item> item); // Change this

    bool hasItem(const std::string& itemName);

    bool hasUsedKey() const {
        return usedKey;
    }

    void setUsedKey(bool usedKey) {
        Player::usedKey = usedKey;
    }

private:
    bool usedKey = false;

    std::vector<std::shared_ptr<Item>> inventory; // Change this
    static Player *playerInstance;
    Room* currentRoom;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}

};

#endif //ZOORK_PLAYER_H
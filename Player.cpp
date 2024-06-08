//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) { 
    inventory.push_back(item);
}

bool Player::hasItem(const std::string& itemName) {
    for (const auto& item : inventory) {
        if (item->getName() == itemName) {
            return true;
        }
    }
    return false;
}
//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items[item->getName()] = item;
}

bool Room::hasItem(const std::string& itemName) {
    return items.find(itemName) != items.end();
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

std::shared_ptr<Item> Room::removeItem(std::string itemName) {
    auto it = items.find(itemName);
    if (it != items.end()) {
        std::shared_ptr<Item> item = it->second;
        items.erase(it);
        return item;
    }
    return nullptr;  // Return nullptr if no item with the given name is found
}

std::map<std::string, std::shared_ptr<Passage>> Room::getPassages() const {
    std::map<std::string, std::shared_ptr<Passage>> passages;
    for (const auto& pair : passageMap) {
        if (pair.second->getFrom() == this) {
            passages.insert(pair);
        }
    }
    return passages;
}
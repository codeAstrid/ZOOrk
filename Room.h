#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    std::shared_ptr<Item> removeItem(std::string itemName);

    void addItem(std::shared_ptr<Item> item);

    bool hasItem(const std::string& itemName);

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    // get Item Method
    std::map<std::string, std::shared_ptr<Item>> getItems() const {
        return items;
    }
    // get Passage Method
    std::map<std::string, std::shared_ptr<Passage>> getPassages() const;

protected:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;

    std::map<std::string, std::shared_ptr<Item>> items;
};

#endif //ZOORK_ROOM_H
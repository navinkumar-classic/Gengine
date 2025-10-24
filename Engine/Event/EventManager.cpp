//
// Created by navin on 10/22/25.
//
#include "EventManager.h"

#include <iostream>
#include <ostream>

void EventManager::define(const std::string& name, const Condition& condition) {
    conditions[name] = condition;
}

void EventManager::on(const std::string& name, const Action& action) {
    auto it = conditions.find(name);
    if (it != conditions.end()) {
        actions[name].push_back(action);
    }
    else {
        std::cerr << "Event not found: " << name << std::endl;
    }
}

void EventManager::defineOn(const std::string& name, const Condition& condition, const Action& action) {
    conditions[name] = condition;
    actions[name].push_back(action);
}

void EventManager::deleteEvent(const std::string& name) {
    eventsToDelete.push_back(name);
}

void EventManager::update(float dt) {
    for (const std::string& todelete: eventsToDelete) {
        conditions.erase(todelete);
        conditions.erase(todelete);
    }

    eventsToDelete.clear();

    for (auto& [name, condition] : conditions) {
        if (condition()) {
            for (auto& action : actions[name])
                action();
        }
    }
}

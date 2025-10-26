//
// Created by navin on 10/22/25.
//

#pragma once
#include <functional>
#include <string>

class EventManager {
    public:
        using Condition = std::function<bool()>;
        using Action = std::function<void()>;

        void define(const std::string& name, const Condition& condition);
        void on(const std::string& name, const Action& action);
        void defineOn(const std::string& name, const Condition& condition, const Action& action);
        void deleteEvent(const std::string& name);

        void update(float dt);

    private:
        std::unordered_map<std::string, Condition> conditions;
        std::unordered_map<std::string, std::vector<Action>> actions;

        std::vector<std::string> eventsToDelete;
};

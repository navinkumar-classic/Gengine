
#pragma once
#include <variant>
#include <string>
#include <unordered_map>

class GameState {
    public:
        using gameValue = std::variant<int, float, bool, std::string>;

    GameState() = default;

    template <typename T> void set(const std::string& key, T value) {
        data[key] = value;
    }

    template <typename T> T get(const std::string& key, T defaultValue = T{}) const {
        auto it = data.find(key);
        if (it != data.end()) {
            if (auto val = std::get_if<T>(&it->second)) {
                return *val;
            }
        }
        return defaultValue;
    }

    template <typename T> void increment(const std::string& key, T amount) {
        auto it = data.find(key);
        if (it != data.end()) {
            if (auto val = std::get_if<T>(&it->second)) {
                *val += amount;
            }
        }
    }

    std::string getString(const std::string& key, const std::string& defaultValue = "None") const;

private:
    std::pmr::unordered_map<std::string, gameValue> data;
};

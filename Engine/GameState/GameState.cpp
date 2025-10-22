
#include "GameState.h"
#include <sstream>

std::string GameState::getString(const std::string& key, const std::string& defaultValue) const {
    auto it = data.find(key);
    if (it == data.end()) {
        return defaultValue;
    }

    // Visit the variant and convert whatever type it holds into string
    return std::visit([](const auto& value) -> std::string {
        using T = std::decay_t<decltype(value)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        }
        else if constexpr (std::is_same_v<T, bool>) {
            return value ? "true" : "false";
        }
        else {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
    }, it->second);
}

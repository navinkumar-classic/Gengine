//
// Created by navin on 10/23/25.
//

#include "Scene.h"

#include <string>

void Scene::addEventToDelete(const std::string& event) {
    eventsToDelete.push_back(event);
}

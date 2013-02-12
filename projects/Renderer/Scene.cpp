/* 
 * File:   Scene.cpp
 * Author: deather
 * 
 * Created on February 10, 2013, 12:10 AM
 */

#include "Scene.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::addObject(Object *o) {
    if (o != NULL) {
        (this->objects).push_back(o);
    }
}


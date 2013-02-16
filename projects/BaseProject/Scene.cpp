/* 
 * File:   Scene.cpp
 * Author: deather
 * 
 * Created on February 10, 2013, 12:10 AM
 */

#include "Scene.h"

Scene::Scene() {
    this->objects = new std::vector<Object*>();
}

Scene::~Scene() {
}

void Scene::addObject(Object *o) {
    if (o != NULL) {
        printf("Added object to scene.\n");
        (this->objects)->push_back(o);
    }
}


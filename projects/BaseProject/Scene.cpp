
#include "Scene.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::addCube(Cube cube) {
    this->cubes.push_back(cube);
}



#ifndef SCENE_H
#define	SCENE_H

#include <vector>
#include "Object.h"

class Scene {
public:
    Scene();
    virtual ~Scene();

    float getEyeX() const {
        return eyeX;
    }

    void setEyeX(float eyeX) {
        this->eyeX = eyeX;
    }

    float getEyeY() const {
        return eyeY;
    }

    void setEyeY(float eyeY) {
        this->eyeY = eyeY;
    }

    float getEyeZ() const {
        return eyeZ;
    }

    void setEyeZ(float eyeZ) {
        this->eyeZ = eyeZ;
    }

    float getLookAtX() const {
        return lookAtX;
    }

    void setLookAtX(float lookAtX) {
        this->lookAtX = lookAtX;
    }

    float getLookAtY() const {
        return lookAtY;
    }

    void setLookAtY(float lookAtY) {
        this->lookAtY = lookAtY;
    }

    float getLookAtZ() const {
        return lookAtZ;
    }

    void setLookAtZ(float lookAtZ) {
        this->lookAtZ = lookAtZ;
    }

    void setQuality(int quality) {
        this->quality = quality;
    }

    int getQuality() {
        return this->quality;
    }

    void setWidth(int width) {
        this->width = width;
    }

    void setHeight(int height) {
        this->height = height;
    }

    int getWidth() {
        return this->width;
    }

    int getHeight() {
        return this->height;
    }

    void addObject(Object *o);

    std::vector<Object*> *getObjects() {
        return &objects;
    }
private:
    float eyeX, eyeY, eyeZ;
    float lookAtX, lookAtY, lookAtZ;
    int quality;
    int width, height;
    std::vector<Object*> objects;
};

#endif	/* SCENE_H */



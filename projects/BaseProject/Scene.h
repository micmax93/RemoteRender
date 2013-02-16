
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
    
    void addObject(Object *o);
    
    std::vector<Object*> *getObjects() {
        return objects;
    }
private:
    float eyeX, eyeY, eyeZ;
    float lookAtX, lookAtY, lookAtZ;
    std::vector<Object*> *objects;
};

#endif	/* SCENE_H */



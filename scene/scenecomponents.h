#ifndef SCENECOMPONENTS_H
#define SCENECOMPONENTS_H

#include <QMatrix4x4>

struct RenderLight {
    RenderLight() {
        transform.setToIdentity();
    }
    QMatrix4x4 transform;
};

struct RenderModel {
    RenderModel() {
        transform.setToIdentity();
    }
    QMatrix4x4 transform;
};

#endif // SCENECOMPONENTS_H

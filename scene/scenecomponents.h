#ifndef SCENECOMPONENTS_H
#define SCENECOMPONENTS_H

#include <QMatrix4x4>

struct RenderLight {
    RenderLight() {
        transform.setToIdentity();
    }
    QMatrix4x4 transform;
};

struct MeshData {
    std::vector<QVector3D> vertices;
    std::vector<QVector3D> normals;
    std::vector<quint32> indices;
};

struct RenderModel {
    RenderModel() {
        transform.setToIdentity();
    }
    MeshData mesh;
    QMatrix4x4 transform;
};


#endif // SCENECOMPONENTS_H

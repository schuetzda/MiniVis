#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <qtypes.h>
#include <scene/camera.h>
#include <string>
#include <vector>

enum class SceneType {
    Model,
    Light,
    Camera
};

struct SceneNode {
    std::string name;
    quint32 entityID;
    SceneType type;
};

struct SceneData {
    std::string name;
    std::vector<SceneNode> nodes;
};

#endif // SCENEGRAPH_H

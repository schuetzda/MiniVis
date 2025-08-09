#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <qtypes.h>
#include <scene/camera.h>
#include <vector>

enum class SceneType {
    Model = 0,
    Light = 1,
    Camera = 2
};

struct SceneNode {
    QString name;
    quint32 entityID;
    SceneType type;
};

class SceneData {
public:
    SceneData(quint32 cameraEntity)
    {
        nodes.emplace_back("Camera", cameraEntity, SceneType::Camera);
    }

    void setName(const QString& _name)
    {
        name = _name;
    }

    void addNode(SceneType type)
    {
        switch (type) {
        case SceneType::Light:
            lightCount++;
            // TODO Create a Light Object
            nodes.emplace_back(QString("Light%1").arg(lightCount), 1, type);
            break;
        case SceneType::Model:
            modelCount++;
            // TODO Create Model Object
            nodes.emplace_back(QString("Model%1").arg(modelCount), 1, type);
            break;
        case SceneType::Camera:
            qWarning() << "Lights can not be added to a Scene. Instead edit the existing light source.";
            break;
        default:
            qWarning() << "Type not supported";
            break;
        }
    }

    const SceneNode* get(quint32 index) const
    {
        if(index >= nodes.size())
            return nullptr;
        return &nodes[index];
    }

    quint64 size() const
    {
        return nodes.size();
    }

    void deleteNode(quint32 index)
    {
        nodes.erase(nodes.begin() + index);
    }

private:
    QString name;
    std::vector<SceneNode> nodes;
    quint32 modelCount;
    quint32 lightCount;
};

#endif // SCENEGRAPH_H

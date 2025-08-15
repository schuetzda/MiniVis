#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "ecs/Registry.h"
#include "importer/stlimporter.h"
#include "scenecomponents.h"
#include <qtypes.h>
#include <scene/camera.h>
#include <vector>

namespace mini {
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
    SceneData(Registry& r)
        : registry(r)
    {
        registry.initNewComponent<QuaternionCamera>(1);
        registry.initNewComponent<RenderLight>(5);
        registry.initNewComponent<RenderModel>(5);
        quint32 cameraEntity = registry.registerEntity();
        registry.emplace<QuaternionCamera>(cameraEntity);
        nodes.emplace_back("Camera", cameraEntity, SceneType::Camera);
    }

    void setName(const QString& _name)
    {
        name = _name;
    }

    void addNode(SceneType type)
    {
        switch (type) {
        case SceneType::Light: {
            lightId++;
            quint32 lightEntity = registry.registerEntity();
            registry.emplace<RenderLight>(lightEntity);
            nodes.emplace_back(QString("Light%1").arg(lightId), lightEntity, type);
            break;
        }
        case SceneType::Model: {
            modelId++;
            quint32 modelEntity = registry.registerEntity();
            registry.emplace<RenderModel>(modelEntity);
            nodes.emplace_back(QString("Model%1").arg(modelId), modelEntity, type);
            break;
        }
        case SceneType::Camera:
            qWarning() << "Lights can not be added to a Scene. Instead edit the existing light source.";
            break;
        default:
            qWarning() << "Type not supported";
            break;
        }
    }

    void addModel(const QString& path)
    {
        modelId++;
        quint32 modelEntity = registry.registerEntity();
        registry.emplace<RenderModel>(modelEntity);
        nodes.emplace_back(QString("Model%1").arg(modelId), modelEntity, SceneType::Model);
        RenderModel* currentModel = registry.getComponent<RenderModel>(modelEntity);
        mini::importer::loadBinaryStl(path, currentModel->mesh);
    }

    const SceneNode* get(quint32 index) const
    {
        if (index >= nodes.size())
            return nullptr;
        return &nodes[index];
    }

    QMatrix4x4* getMatrix(quint32 index)
    {
        if (index > size()) {
            qWarning() << "Scenegraph getMatrix: index out of bounds";
            return nullptr;
        }
        quint32 entityID = nodes[index].entityID;
        switch (nodes[index].type) {
        case SceneType::Light: {
            RenderLight* light = registry.getComponent<RenderLight>(entityID);
            return &light->transform;
            break;
        }
        case SceneType::Model: {
            RenderModel* model = registry.getComponent<RenderModel>(entityID);
            return &model->transform;
            break;
        }
        case SceneType::Camera: {
            QuaternionCamera* camera = registry.getComponent<QuaternionCamera>(entityID);
            return camera->getViewPtr();
            break;
        }
        default:
            qWarning() << "Type not supported";
            break;
        }
        return nullptr;
    }

    quint64 size() const
    {
        return nodes.size();
    }

    void deleteNode(quint32 index)
    {
        registry.deleteEntity(nodes[index].entityID);
        nodes.erase(nodes.begin() + index);
    }

private:
    QString name;
    std::vector<SceneNode> nodes {};
    quint32 modelId { 0 };
    quint32 lightId { 0 };
    Registry& registry;
};
}
#endif // SCENEGRAPH_H

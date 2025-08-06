#ifndef SCENETREEMODEL_H
#define SCENETREEMODEL_H

#include "scenegraph.h"
#include <QAbstractItemModel>
#include <QObject>

namespace mini {
class SceneTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit SceneTreeModel(QObject* parent = nullptr)
        : QAbstractItemModel(parent)
    {
        sceneData.name = "Hello";
        sceneData.nodes.emplace_back("Camera", 1, SceneType::Camera);
        sceneData.nodes.emplace_back("My Minifigure", 1, SceneType::Model);
        sceneData.nodes.emplace_back("Light", 1, SceneType::Light);
    }
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role=Qt::EditRole) override;
    Q_INVOKABLE void removeNode(quint32 row);

private:
    SceneData sceneData;
};
}

#endif // SCENETREEMODEL_H

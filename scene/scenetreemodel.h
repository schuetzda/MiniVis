#ifndef SCENETREEMODEL_H
#define SCENETREEMODEL_H

#include "matrixmodel.h"
#include "scenegraph.h"
#include <QAbstractItemModel>
#include <QObject>
#include <QUrl>
#include "ecs/Registry.h"

namespace mini {
class SceneTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit SceneTreeModel(Registry& registry, QObject* parent = nullptr)
        : QAbstractItemModel(parent), sceneData(registry)
    {
        sceneData.addNode(SceneType::Model);
        sceneData.addNode(SceneType::Light);
    }

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void removeNode(int row);
    Q_INVOKABLE void addNode(quint32 type);
    Q_INVOKABLE void addModel(const QUrl& path);
    Q_INVOKABLE MatrixModel* getMatrix(int row);

private:
    SceneData sceneData;
};
}

#endif // SCENETREEMODEL_H

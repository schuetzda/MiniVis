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
        : QAbstractItemModel(parent), sceneData(0)
    {
        sceneData.addNode(SceneType::Model);
        sceneData.addNode(SceneType::Light);
    }

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void removeNode(int row);
    Q_INVOKABLE void addNode(quint32 type);

private:
    SceneData sceneData;
};
}

#endif // SCENETREEMODEL_H

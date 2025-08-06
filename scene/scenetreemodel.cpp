#include "scenetreemodel.h"

namespace mini {
QModelIndex SceneTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        // Root → top-level nodes
        return createIndex(row, column, &sceneData.nodes[row]);
    }
    // Children → none in your flat hierarchy
    return QModelIndex();
}

QModelIndex SceneTreeModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int SceneTreeModel::rowCount(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return sceneData.nodes.size();
    }
    return 0;
}

int SceneTreeModel::columnCount(const QModelIndex& index) const
{
    return 1;
}

QVariant SceneTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const SceneNode* node = static_cast<SceneNode*>(index.internalPointer());

    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(node->name);
        break;
    case Qt::UserRole + 1:
        switch (node->type) {
        case SceneType::Model:
            return QStringLiteral("qrc:/scene/icons/model.png");
            break;
        case SceneType::Light:
            return QStringLiteral("qrc:/scene/icons/light.png");
            break;
        case SceneType::Camera:
            return QStringLiteral("qrc:/scene/icons/camera.png");
            break;
        }
    case Qt::UserRole + 2:
        switch (node->type) {
        case SceneType::Model:
            return static_cast<int>(SceneType::Model);
            break;
        case SceneType::Light:
            return static_cast<int>(SceneType::Light);
            break;
        case SceneType::Camera:
            return static_cast<int>(SceneType::Camera);
            break;
        }
    }

    return QVariant();
}

QHash<int, QByteArray> SceneTreeModel::roleNames() const
{
    auto roles = QAbstractItemModel::roleNames();
    roles[Qt::UserRole + 1] = "icon";
    roles[Qt::UserRole + 2] = "type";
    return roles;
}

bool SceneTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

}

void SceneTreeModel::removeNode(quint32 row)
{
    if (row < 0 || row >= sceneData.nodes.size()) {
        qWarning() << "Trying to delete a node out of index range";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    sceneData.nodes.erase(sceneData.nodes.begin() + row);
    endRemoveRows();
}
}

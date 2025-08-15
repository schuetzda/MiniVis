#include "scenetreemodel.h"
#include <QMatrix4x4>

namespace mini {
QModelIndex SceneTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid() && row >= 0 && row < sceneData.size()) {
        // Accessing data in the data() function will be done over the row counter
        return createIndex(row, column, nullptr);
    }
    return QModelIndex();
}

QModelIndex SceneTreeModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int SceneTreeModel::rowCount(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return sceneData.size();
    }
    return 0;
}

int SceneTreeModel::columnCount(const QModelIndex& index) const
{
    return 1;
}

QVariant SceneTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= sceneData.size())
        return QVariant();

    const SceneNode* node = sceneData.get(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return node->name;
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
        break;
    case Qt::UserRole + 2:
            return static_cast<int>(node->type);
            break;
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
void SceneTreeModel::removeNode(int row)
{
    if (row < 0 || row >= sceneData.size()) {
        qWarning() << "Trying to delete a node out of index range"<< row;
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    sceneData.deleteNode(row);
    endRemoveRows();
}

void SceneTreeModel::addNode(quint32 type)
{
    const quint32 lastRow = sceneData.size();
    beginInsertRows(QModelIndex(), lastRow, lastRow);
    sceneData.addNode(static_cast<SceneType>(type));
    endInsertRows();
    emit dataChanged(createIndex(0, 0), createIndex(lastRow-1, lastRow-1));
}

void SceneTreeModel::addModel(const QUrl &path)
{
    const quint32 lastRow = sceneData.size();
    beginInsertRows(QModelIndex(), lastRow, lastRow);
    sceneData.addModel(path.toLocalFile());
    endInsertRows();
    emit dataChanged(createIndex(0, 0), createIndex(lastRow-1, lastRow-1));

}

MatrixModel* SceneTreeModel::getMatrix(int row)
{
    QMatrix4x4* matrix = sceneData.getMatrix(row);
    return new MatrixModel(matrix, this);
}
}

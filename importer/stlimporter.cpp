#include "stlimporter.h"
namespace mini::importer
{
bool loadBinaryStl(const QString& path, MeshData& model, bool smoothShading)
{
    std::ifstream file(path.toStdString(), std::ios::binary);
    if (!file) {
        qDebug() << path << " not found";
        return false;
    }
    // Skip the 80 bytes header
    file.seekg(80);

    quint32 triangleCount = 0;
    file.read(reinterpret_cast<char*>(&triangleCount), 4);

    const quint32 verticesCount = triangleCount * 3; // 3 vertices per triangle
    model.vertices.resize(verticesCount);
    model.normals.resize(verticesCount);

    for (quint32 i = 0; i < triangleCount; i++) {
        QVector3D normal;
        file.read(reinterpret_cast<char*>(&normal), 12);
        file.read(reinterpret_cast<char*>(&model.vertices[i]), 12);
        file.read(reinterpret_cast<char*>(&model.vertices[i + 1]), 12);
        file.read(reinterpret_cast<char*>(&model.vertices[i + 2]), 12);
        file.ignore(2);
    }
    return true;
}
bool loadStlFile(const QString& path, MeshData& model, bool smoothShading)
{
    if (loadBinaryStl(path, model)) {
        return true;
    }
    qDebug() << path << " not found";
    return false;
}
}

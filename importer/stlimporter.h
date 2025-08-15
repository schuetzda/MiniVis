#ifndef STLIMPORTER_H
#define STLIMPORTER_H
#include "scene/scenecomponents.h"
#include <QString>
#include <fstream>
namespace mini::importer {

bool loadBinaryStl(const QString& path, MeshData& model, bool smoothShading = true);
bool loadStlFile(const QString& path, MeshData& model, bool smoothShading = true);
}
#endif // STLIMPORTER_H

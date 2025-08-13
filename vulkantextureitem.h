// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef VULKANTEXTUREIMPORT_H
#define VULKANTEXTUREIMPORT_H

#include "ecs/Registry.h"
#include <QtQuick/QQuickItem>

namespace mini {
class VulkanTextureNode;

//! [1]
class VulkanTextureItem : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(mini::Registry* registry READ registry WRITE setRegistry NOTIFY registryChanged)

public:
    VulkanTextureItem();

    void setRegistry(Registry* r)
    {
        m_registry = r;
    }

    Registry* registry() const { return m_registry; }
signals:
    void registryChanged();

protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;
    void geometryChange(const QRectF& newGeometry,
        const QRectF& oldGeometry) override;

private slots:
    void invalidateSceneGraph();

private:
    void releaseResources() override;

    VulkanTextureNode* m_node = nullptr;
    Registry* m_registry = nullptr;
};
} // namespace mini
//! [1]

#endif // VULKANTEXTUREIMPORT_H

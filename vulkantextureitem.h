// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef VULKANTEXTUREIMPORT_H
#define VULKANTEXTUREIMPORT_H

#include <QtQuick/QQuickItem>

namespace mini {
class VulkanTextureNode;

//! [1]
class VulkanTextureItem : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT

public:
    VulkanTextureItem();

protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;
    void geometryChange(const QRectF& newGeometry,
        const QRectF& oldGeometry) override;

private slots:
    void invalidateSceneGraph();

private:
    void releaseResources() override;

    VulkanTextureNode* m_node = nullptr;
};
} // namespace mini
//! [1]

#endif // VULKANTEXTUREIMPORT_H

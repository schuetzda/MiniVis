#ifndef SIMPLEFORWARDRENDERER_H
#define SIMPLEFORWARDRENDERER_H
#include "renderer/framegraph/framegraph.h"
#include "renderer/framegraph/framegraphbuilder.h"
#include "renderer/framegraph/rendervalues.h"
#include "renderer/types/rendererfactory.h"
#include <QMatrix4x4>

namespace mini {
class SimpleForwardRenderer : RendererFactory {
    virtual FrameGraph getFrameGraph(quint32 viewMatrixEntity)
    {
        FrameGraphBuilder builder;
        builder
            .addAttachment("color", Format::R8G8B8A8_UNORM)
            .addAttachment("depth", Format::DEPTH)
            .addResource("viewMatrix", viewMatrixEntity)
            .addNode({ "viewMatrix" }, { "color" }, "depth")
            .build();
    }
};
}
#endif // SIMPLEFORWARDRENDERER_H

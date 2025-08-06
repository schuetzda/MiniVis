#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include <renderer/framegraph/framegraph.h>
namespace mini {
class RendererFactory {
    virtual FrameGraph getFrameGraph() = 0;
};
}
#endif // RENDERERFACTORY_H

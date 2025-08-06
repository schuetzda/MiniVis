#ifndef FRAMEGRAPHBUILDER_H
#define FRAMEGRAPHBUILDER_H

#include "framegraph.h"
#include <vector>

namespace mini {
class FrameGraphBuilder {
public:
    FrameGraphBuilder();

    FrameGraphBuilder& addNode(const std::vector<std::string>& inputs, const std::vector<std::string>& renderAttachments, const std::string& depthAttachment = "")
    {
        frameGraph.nodes.emplace_back(inputs, renderAttachments, depthAttachment);
        return *this;
    }

    FrameGraphBuilder& addResource(const std::string& id, quint32 resourceEntity)
    {
        frameGraph.resources.emplace(id, resourceEntity);
        return *this;
    }

    FrameGraphBuilder& addAttachment(const std::string& id, Format format)
    {
        frameGraph.attachments.emplace(id, format);
        return *this;
    }

    FrameGraph build()
    {
        // FrameGraphNodes and RenderCycles need to have the same size, since they are in a 1:1 relationship
        //Q_ASSERT(frameGraph.nodes.size() == frameGraph.cycles.size());
        return frameGraph;
    }

private:
    FrameGraph frameGraph;
};
} // namespace mini
#endif // FRAMEGRAPHBUILDER_H

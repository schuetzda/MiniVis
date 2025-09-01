#ifndef FRAMEGRAPHBUILDER_H
#define FRAMEGRAPHBUILDER_H

#include "framegraph.h"
#include <vector>
#include <renderer/types/rendercycle.h>

namespace mini {
class FrameGraphBuilder {
public:
    FrameGraphBuilder() = default;

    FrameGraphBuilder& addNode(std::unique_ptr<RenderCycle> cycle, const std::vector<std::string>& inputs, const std::vector<std::string>& renderAttachments, const std::string& depthAttachment = "")
    {
        frameGraph.nodes.emplace_back(std::move(cycle), inputs, renderAttachments, depthAttachment);
        return *this;
    }

    FrameGraphBuilder& addResource(const std::string& id, quint32 resourceEntity)
    {
        frameGraph.resources.emplace(id, resourceEntity);
        return *this;
    }

    FrameGraphBuilder& addAttachment(const std::string& id, Format format, const RenderCycle& cycle)
    {
        frameGraph.attachments.emplace(id, format);
        return *this;
    }

    FrameGraph build()
    {
        FrameGraph result = std::move(frameGraph);
        frameGraph = FrameGraph();
        return result;
    }

private:
    FrameGraph frameGraph{};
};
} // namespace mini
#endif // FRAMEGRAPHBUILDER_H

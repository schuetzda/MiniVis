#ifndef FRAMEGRAPH_H
#define FRAMEGRAPH_H
#include "renderer/types/rendercycle.h"
#include "rendervalues.h"
#include "util/stringviewhash.h"
#include <bits/unique_ptr.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace mini {

enum class ResourceType { Attachment,
    Texture,
    Buffer };

struct FrameGraphResource {
    quint32 resourceEntity;

    FrameGraphResource(quint32 resourceEntity_)
        : resourceEntity(resourceEntity_)
    {
    }
};

struct FrameGraphAttachment {
    std::string id;
    Format format;

    FrameGraphAttachment(std::string id_, Format format_)
        : id(std::move(id_))
        , format(format_)
    {
    }
};

struct FrameGraphInput {
    std::string id;
    ResourceType type;
    quint32 bindingSlot;

    FrameGraphInput(std::string id_, ResourceType type_, quint32 bindingSlot_)
        : id(std::move(id_))
        , type(type_)
        , bindingSlot(bindingSlot_)
    {
    }
};

struct FrameGraphNode {
    std::unique_ptr<RenderCycle> cycle;
    std::vector<std::string> inputs {};
    std::vector<std::string> attachments {};
    std::string depthAttachment {};

    FrameGraphNode() = default;
    FrameGraphNode(
        std::unique_ptr<RenderCycle> cycle_,
        std::vector<std::string> inputs_,
        std::vector<std::string> attachments_,
        std::string depthAttachment_)
        : cycle(std::move(cycle_)), inputs(std::move(inputs_))
        , attachments(std::move(attachments_))
        , depthAttachment(std::move(depthAttachment_))
    {
    }
};

struct FrameGraph {
    FrameGraph() = default;
    std::vector<FrameGraphNode> nodes {};
    // std::vector<std::unique_ptr<RenderCycle>> cycles {};
    std::unordered_map<std::string, FrameGraphResource, StringViewHash,
        std::equal_to<>>
        resources {};
    std::unordered_map<std::string, FrameGraphAttachment, StringViewHash,
        std::equal_to<>>
        attachments {};
};
} // namespace mini
#endif // FRAMEGRAPH_H

#ifndef PIPELINEBUILDER_H
#define PIPELINEBUILDER_H

#include <filesystem>
#include "renderer/framegraph/framegraph.h"
namespace mini
{
struct PipelineProperties {

};

class Pipeline {
public:
    Pipeline() = default;
    Pipeline(std::filesystem::path shaderPath, const FrameGraphNode& node, const PipelineProperties& properties = PipelineProperties()) {

    }
private:

};
}
#endif // PIPELINEBUILDER_H

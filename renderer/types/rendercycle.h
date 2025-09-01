#ifndef RENDERCYCLE_H
#define RENDERCYCLE_H
#include <QVulkanFunctions>
#include <vector>
#include "shaderdescription.h"

namespace mini {
class RenderCycle {
public:
    RenderCycle() = default;
    virtual void init(VkPhysicalDevice physDevice, VkDevice device, QVulkanFunctions* f,
        QVulkanDeviceFunctions* df)
        = 0;
    virtual void recordCommands() = 0;
    virtual void cleanup(VkDevice device) = 0;
private:
    std::vector<ShaderDescription> shaderDesc;
};
}
#endif // RENDERCYCLE_H

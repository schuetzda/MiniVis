#ifndef RENDERCYCLE_H
#define RENDERCYCLE_H
#include <QVulkanFunctions>

namespace mini {
class RenderCycle {
public:
    RenderCycle() = default;
    virtual void init(VkPhysicalDevice physDevice, VkDevice device, QVulkanFunctions* f,
        QVulkanDeviceFunctions* df)
        = 0;
    virtual void recordCommands() = 0;
    virtual void cleanup(VkDevice device) = 0;
};
}
#endif // RENDERCYCLE_H

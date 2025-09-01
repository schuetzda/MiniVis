#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#include "framegraph/framegraph.h"
#include <qvulkanfunctions.h>
namespace mini {
class VulkanRenderer {
public:
    void init(VkPhysicalDevice physDevice, VkDevice device, QVulkanFunctions* f,
        QVulkanDeviceFunctions* df, FrameGraph frameGraph);
    void draw(QVulkanInstance* instance, VkPhysicalDevice physDevice,
        VkDevice device, QVulkanDeviceFunctions* df, QVulkanFunctions* f,
        VkCommandBuffer cb, VkImage outputImage, VkImageLayout);

private:
    FrameGraph frameGraph;
};
} // namespace mini
#endif

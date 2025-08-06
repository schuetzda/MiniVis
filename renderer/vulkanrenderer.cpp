#include "vulkanrenderer.h"

namespace mini {

void VulkanRenderer::init(VkPhysicalDevice physDevice, VkDevice device,
                          QVulkanFunctions *f, QVulkanDeviceFunctions *df, FrameGraph frameGraph) {
    for (FrameGraphNode node: frameGraph.nodes) {

    }
}

void VulkanRenderer::draw(QVulkanInstance *instance,
                          VkPhysicalDevice physDevice, VkDevice device,
                          QVulkanDeviceFunctions *df, QVulkanFunctions *f,
                          VkCommandBuffer cb, VkImage outputImage,
                          VkImageLayout) {

}

} // namespace mini

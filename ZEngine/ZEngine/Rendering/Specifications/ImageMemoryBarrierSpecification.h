#pragma once
#include <Rendering/Specifications/FormatSpecification.h>
#include <vulkan/vulkan.h>

namespace ZEngine::Rendering::Specifications
{
    struct ImageMemoryBarrierSpecification
    {
        ImageLayout             OldLayout;
        ImageLayout             NewLayout;
        VkImage                 ImageHandle;
        VkAccessFlags           SourceAccessMask;
        VkAccessFlags           DestinationAccessMask;
        VkImageAspectFlagBits   ImageAspectMask;
        VkPipelineStageFlagBits SourceStageMask;
        VkPipelineStageFlagBits DestinationStageMask;
        uint32_t                LayerCount = 1;
    };
} // namespace ZEngine::Rendering::Specifications
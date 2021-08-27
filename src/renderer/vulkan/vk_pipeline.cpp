#include "../../../inc/core/shader_loader.h"

#include "../../../inc/renderer/vulkan/vk_pipeline.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_pipeline;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_pipeline::vk_pipeline(const VkDevice device, const VkRenderPass render_pass, const VkExtent2D& swapchain_extent)
    : pipeline(VK_NULL_HANDLE),
    pipeline_layout(VK_NULL_HANDLE),
    device(device)
{
    create_pipeline(device, render_pass, swapchain_extent);
}

vk_pipeline::~vk_pipeline()
{
    vkDestroyPipeline(device, pipeline, nullptr);
    vkDestroyPipelineLayout(device, pipeline_layout, nullptr);
}

const VkPipeline vk_pipeline::get_pipeline() const 
{
    return pipeline;
}

const VkPipelineLayout vk_pipeline::get_pipeline_layout() const 
{
    return pipeline_layout;
}

void vk_pipeline::create_pipeline(const VkDevice device, const VkRenderPass render_pass, const VkExtent2D& swapchain_extent)
{
    auto vert_shader_code = shader_loader::load("/home/joshua/Desktop/joszva_engine/shaders/vert.spv");
    auto frag_shader_code = shader_loader::load("/home/joshua/Desktop/joszva_engine/shaders/frag.spv");

    VkShaderModule vert_shader_module = create_shader_module(vert_shader_code);
    VkShaderModule frag_shader_module = create_shader_module(frag_shader_code); 

    VkPipelineShaderStageCreateInfo vert_shader_stage_info{};
    vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_shader_stage_info.module = vert_shader_module;
    vert_shader_stage_info.pName = "main";

    VkPipelineShaderStageCreateInfo frag_shader_stage_info{};
    frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_shader_stage_info.module = frag_shader_module;
    frag_shader_stage_info.pName = "main";

    VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

    VkPipelineVertexInputStateCreateInfo vertex_input_info{};
    vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_info.vertexBindingDescriptionCount = 0;
    vertex_input_info.pVertexBindingDescriptions = nullptr;
    vertex_input_info.vertexAttributeDescriptionCount = 0;
    vertex_input_info.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo input_assembly_info{};
    input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly_info.primitiveRestartEnable = VK_FALSE;

    /* create a viewport */
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain_extent.width);
    viewport.height = static_cast<float>(swapchain_extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.extent = swapchain_extent;
    scissor.offset = {0, 0};

    VkPipelineViewportStateCreateInfo view_port_create_info{};
    view_port_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    view_port_create_info.viewportCount = 1;
    view_port_create_info.pViewports = &viewport;
    view_port_create_info.scissorCount = 1;
    view_port_create_info.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer_create_info{};
    rasterizer_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer_create_info.depthClampEnable = VK_FALSE;
    rasterizer_create_info.rasterizerDiscardEnable = VK_FALSE;
    rasterizer_create_info.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer_create_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer_create_info.lineWidth = 1.0f;
    rasterizer_create_info.depthBiasEnable = VK_FALSE;
    rasterizer_create_info.depthBiasConstantFactor = 0.0f;
    rasterizer_create_info.depthBiasClamp = 0.0f;
    rasterizer_create_info.depthBiasSlopeFactor = 0.0f;

    VkPipelineMultisampleStateCreateInfo multisampling_create_info{};
    multisampling_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling_create_info.sampleShadingEnable = VK_FALSE;
    multisampling_create_info.minSampleShading = 1.0f;
    multisampling_create_info.pSampleMask = nullptr;
    multisampling_create_info.alphaToCoverageEnable = VK_FALSE;
    multisampling_create_info.alphaToOneEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState color_blend_attachment{};
    color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    color_blend_attachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo color_blend_create_info{};
    color_blend_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend_create_info.logicOpEnable = VK_FALSE;
    color_blend_create_info.logicOp = VK_LOGIC_OP_COPY;
    color_blend_create_info.attachmentCount = 1;
    color_blend_create_info.pAttachments = &color_blend_attachment;
    color_blend_create_info.blendConstants[0] = 0.0f;
    color_blend_create_info.blendConstants[1] = 0.0f;
    color_blend_create_info.blendConstants[2] = 0.0f;
    color_blend_create_info.blendConstants[3] = 0.0f;

    /* create pipeline layout */
    VkPipelineLayoutCreateInfo pipeline_layout_create_info{};
    pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if (vkCreatePipelineLayout(device, &pipeline_layout_create_info, nullptr, &pipeline_layout) != VK_SUCCESS)
    {
        _logger->error("Failed to create graphics pipeline layout");
    }

    VkGraphicsPipelineCreateInfo pipeline_create_info{};
    pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_create_info.stageCount = 2;
    pipeline_create_info.pStages = shader_stages;
    pipeline_create_info.pVertexInputState = &vertex_input_info;
    pipeline_create_info.pInputAssemblyState = &input_assembly_info;
    pipeline_create_info.pViewportState = &view_port_create_info;
    pipeline_create_info.pRasterizationState = &rasterizer_create_info;
    pipeline_create_info.pMultisampleState = &multisampling_create_info;
    pipeline_create_info.pDepthStencilState = nullptr;
    pipeline_create_info.pColorBlendState = &color_blend_create_info;
    pipeline_create_info.pDynamicState = nullptr;
    pipeline_create_info.layout = pipeline_layout;
    pipeline_create_info.renderPass = render_pass;
    pipeline_create_info.subpass = 0;
    pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipeline_create_info, nullptr, &pipeline) != VK_SUCCESS)
    {
        _logger->error("Failed to create graphics pipeline");
    }

    vkDestroyShaderModule(device, vert_shader_module, nullptr);
    vkDestroyShaderModule(device, frag_shader_module, nullptr);
}

VkShaderModule vk_pipeline::create_shader_module(const std::vector<char>& shader_code)
{
    VkShaderModuleCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = shader_code.size();
    create_info.pCode = reinterpret_cast<const uint32_t*>(shader_code.data());

    VkShaderModule shader_module;
    if (vkCreateShaderModule(device, &create_info, nullptr, &shader_module) != VK_SUCCESS)
    {
        _logger->error("Failed to create shader module");
    }

    return shader_module;
}
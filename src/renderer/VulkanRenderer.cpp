// Clean-room Vulkan offscreen renderer. No EA code, no decompiler output.
#include "renderer/VulkanRenderer.hpp"

#include <array>
#include <cstdio>
#include <cstring>

// SPIR-V blobs generated at build time from shaders/*.glsl via
// glslangValidator.
#include "shaders_spv.h"

namespace openspore {
namespace {

void logError(const char *what, VkResult result) {
  std::fprintf(stderr, "[VulkanRenderer] %s failed (VkResult=%d)\n", what,
               static_cast<int>(result));
}

bool vkCheck(VkResult result, const char *what) {
  if (result != VK_SUCCESS) {
    logError(what, result);
    return false;
  }
  return true;
}

VkShaderModule makeShaderModule(VkDevice device, const uint32_t *code,
                                size_t wordCount) {
  VkShaderModuleCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  info.codeSize = wordCount * sizeof(uint32_t);
  info.pCode = code;
  VkShaderModule module = VK_NULL_HANDLE;
  if (!vkCheck(vkCreateShaderModule(device, &info, nullptr, &module),
               "vkCreateShaderModule")) {
    return VK_NULL_HANDLE;
  }
  return module;
}

// Records a single color-image layout barrier into an arbitrary command buffer
// (used by the one-time texture upload path, which does not use the frame's
// command buffer).
void imageBarrier(VkCommandBuffer cmd, VkImage image, VkImageLayout oldLayout,
                  VkImageLayout newLayout, VkPipelineStageFlags srcStage,
                  VkPipelineStageFlags dstStage, VkAccessFlags srcAccess,
                  VkAccessFlags dstAccess) {
  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
  barrier.srcAccessMask = srcAccess;
  barrier.dstAccessMask = dstAccess;
  vkCmdPipelineBarrier(cmd, srcStage, dstStage, 0, 0, nullptr, 0, nullptr, 1,
                      &barrier);
}

} // namespace

VulkanRenderer::VulkanRenderer() = default;

VulkanRenderer::~VulkanRenderer() { shutdown(); }

bool VulkanRenderer::init(uint32_t width, uint32_t height) {
  if (initialized_) {
    return true;
  }
  width_ = width;
  height_ = height;
  if (!createInstance() || !pickPhysicalDevice() || !createDevice() ||
      !createCommandPool() || !createTargets() || !createRenderPass() ||
      !createPipeline() || !createTextureSupport() || !createLitPipeline() ||
      !createSync()) {
    shutdown();
    return false;
  }
  initialized_ = true;
  std::fprintf(stderr, "[VulkanRenderer] ready on '%s' (%ux%u offscreen)\n",
               deviceName_.c_str(), width_, height_);
  return true;
}

void VulkanRenderer::shutdown() {
  if (device_ != VK_NULL_HANDLE) {
    vkDeviceWaitIdle(device_);
  }
  for (Mesh &mesh : meshes_) {
    destroyMeshResources(mesh);
  }
  meshes_.clear();
  for (TexMesh &tm : texMeshes_) {
    destroyTexMeshResources(tm);
  }
  texMeshes_.clear();
  for (Texture &tex : textures_) {
    destroyTextureResources(tex);
  }
  textures_.clear();
  if (litPipeline_ != VK_NULL_HANDLE) {
    vkDestroyPipeline(device_, litPipeline_, nullptr);
    litPipeline_ = VK_NULL_HANDLE;
  }
  if (litPipelineLayout_ != VK_NULL_HANDLE) {
    vkDestroyPipelineLayout(device_, litPipelineLayout_, nullptr);
    litPipelineLayout_ = VK_NULL_HANDLE;
  }
  if (descPool_ != VK_NULL_HANDLE) {
    vkDestroyDescriptorPool(device_, descPool_, nullptr);
    descPool_ = VK_NULL_HANDLE;
  }
  if (texSetLayout_ != VK_NULL_HANDLE) {
    vkDestroyDescriptorSetLayout(device_, texSetLayout_, nullptr);
    texSetLayout_ = VK_NULL_HANDLE;
  }
  if (texSampler_ != VK_NULL_HANDLE) {
    vkDestroySampler(device_, texSampler_, nullptr);
    texSampler_ = VK_NULL_HANDLE;
  }
  if (pipeline_ != VK_NULL_HANDLE) {
    vkDestroyPipeline(device_, pipeline_, nullptr);
    pipeline_ = VK_NULL_HANDLE;
  }
  if (pipelineLayout_ != VK_NULL_HANDLE) {
    vkDestroyPipelineLayout(device_, pipelineLayout_, nullptr);
    pipelineLayout_ = VK_NULL_HANDLE;
  }
  if (framebuffer_ != VK_NULL_HANDLE) {
    vkDestroyFramebuffer(device_, framebuffer_, nullptr);
    framebuffer_ = VK_NULL_HANDLE;
  }
  if (renderPass_ != VK_NULL_HANDLE) {
    vkDestroyRenderPass(device_, renderPass_, nullptr);
    renderPass_ = VK_NULL_HANDLE;
  }
  if (colorView_ != VK_NULL_HANDLE) {
    vkDestroyImageView(device_, colorView_, nullptr);
    colorView_ = VK_NULL_HANDLE;
  }
  if (colorImage_ != VK_NULL_HANDLE) {
    vkDestroyImage(device_, colorImage_, nullptr);
    colorImage_ = VK_NULL_HANDLE;
  }
  if (colorMemory_ != VK_NULL_HANDLE) {
    vkFreeMemory(device_, colorMemory_, nullptr);
    colorMemory_ = VK_NULL_HANDLE;
  }
  if (depthView_ != VK_NULL_HANDLE) {
    vkDestroyImageView(device_, depthView_, nullptr);
    depthView_ = VK_NULL_HANDLE;
  }
  if (depthImage_ != VK_NULL_HANDLE) {
    vkDestroyImage(device_, depthImage_, nullptr);
    depthImage_ = VK_NULL_HANDLE;
  }
  if (depthMemory_ != VK_NULL_HANDLE) {
    vkFreeMemory(device_, depthMemory_, nullptr);
    depthMemory_ = VK_NULL_HANDLE;
  }
  if (readbackImage_ != VK_NULL_HANDLE) {
    vkDestroyImage(device_, readbackImage_, nullptr);
    readbackImage_ = VK_NULL_HANDLE;
  }
  if (readbackMemory_ != VK_NULL_HANDLE) {
    vkFreeMemory(device_, readbackMemory_, nullptr);
    readbackMemory_ = VK_NULL_HANDLE;
  }
  if (frameFence_ != VK_NULL_HANDLE) {
    vkDestroyFence(device_, frameFence_, nullptr);
    frameFence_ = VK_NULL_HANDLE;
  }
  if (commandPool_ != VK_NULL_HANDLE) {
    vkDestroyCommandPool(device_, commandPool_, nullptr);
    commandPool_ = VK_NULL_HANDLE;
    commandBuffer_ = VK_NULL_HANDLE;
  }
  if (device_ != VK_NULL_HANDLE) {
    vkDestroyDevice(device_, nullptr);
    device_ = VK_NULL_HANDLE;
    graphicsQueue_ = VK_NULL_HANDLE;
  }
  if (instance_ != VK_NULL_HANDLE) {
    vkDestroyInstance(instance_, nullptr);
    instance_ = VK_NULL_HANDLE;
  }
  physicalDevice_ = VK_NULL_HANDLE;
  recording_ = false;
  initialized_ = false;
}

MeshHandle VulkanRenderer::createMesh(const Vertex *vertices,
                                      size_t vertexCount,
                                      const uint32_t *indices,
                                      size_t indexCount) {
  if (!initialized_ || vertices == nullptr || vertexCount == 0 ||
      indices == nullptr || indexCount == 0) {
    return kInvalidMesh;
  }
  Mesh mesh{};
  const VkDeviceSize vbSize = vertexCount * sizeof(Vertex);
  const VkDeviceSize ibSize = indexCount * sizeof(uint32_t);
  const VkMemoryPropertyFlags hostFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                          VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  if (!createBuffer(vbSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, hostFlags,
                    &mesh.vertexBuffer, &mesh.vertexMemory) ||
      !createBuffer(ibSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, hostFlags,
                    &mesh.indexBuffer, &mesh.indexMemory)) {
    destroyMeshResources(mesh);
    return kInvalidMesh;
  }
  void *mapped = nullptr;
  if (!vkCheck(vkMapMemory(device_, mesh.vertexMemory, 0, vbSize, 0, &mapped),
               "vkMapMemory(vb)")) {
    destroyMeshResources(mesh);
    return kInvalidMesh;
  }
  std::memcpy(mapped, vertices, static_cast<size_t>(vbSize));
  vkUnmapMemory(device_, mesh.vertexMemory);
  if (!vkCheck(vkMapMemory(device_, mesh.indexMemory, 0, ibSize, 0, &mapped),
               "vkMapMemory(ib)")) {
    destroyMeshResources(mesh);
    return kInvalidMesh;
  }
  std::memcpy(mapped, indices, static_cast<size_t>(ibSize));
  vkUnmapMemory(device_, mesh.indexMemory);
  mesh.indexCount = static_cast<uint32_t>(indexCount);
  mesh.valid = true;
  // Reuse dead slots so handles stay small.
  for (size_t i = 0; i < meshes_.size(); ++i) {
    if (!meshes_[i].valid) {
      meshes_[i] = mesh;
      return static_cast<MeshHandle>(i);
    }
  }
  meshes_.push_back(mesh);
  return static_cast<MeshHandle>(meshes_.size() - 1);
}

void VulkanRenderer::destroyMesh(MeshHandle mesh) {
  if (mesh < meshes_.size() && meshes_[mesh].valid) {
    destroyMeshResources(meshes_[mesh]);
    meshes_[mesh] = Mesh{};
  }
}

void VulkanRenderer::beginFrame(float r, float g, float b, float a) {
  if (!initialized_) {
    return;
  }
  vkWaitForFences(device_, 1, &frameFence_, VK_TRUE, UINT64_MAX);
  vkResetFences(device_, 1, &frameFence_);
  vkResetCommandBuffer(commandBuffer_, 0);

  VkCommandBufferBeginInfo begin{};
  begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  if (!vkCheck(vkBeginCommandBuffer(commandBuffer_, &begin),
               "vkBeginCommandBuffer")) {
    return;
  }
  VkClearValue clear[2]{};
  clear[0].color = {{r, g, b, a}};
  clear[1].depthStencil = {1.0F, 0};
  VkRenderPassBeginInfo pass{};
  pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  pass.renderPass = renderPass_;
  pass.framebuffer = framebuffer_;
  pass.renderArea = {{0, 0}, {width_, height_}};
  pass.clearValueCount = 2;
  pass.pClearValues = clear;
  vkCmdBeginRenderPass(commandBuffer_, &pass, VK_SUBPASS_CONTENTS_INLINE);
  recording_ = true;
}

void VulkanRenderer::drawMesh(MeshHandle mesh) {
  if (!recording_) {
    std::fprintf(stderr, "[VulkanRenderer] drawMesh outside begin/end frame\n");
    return;
  }
  if (mesh >= meshes_.size() || !meshes_[mesh].valid) {
    std::fprintf(stderr, "[VulkanRenderer] drawMesh with invalid handle %u\n",
                 mesh);
    return;
  }
  const Mesh &m = meshes_[mesh];
  vkCmdBindPipeline(commandBuffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_);
  const VkDeviceSize offset = 0;
  vkCmdBindVertexBuffers(commandBuffer_, 0, 1, &m.vertexBuffer, &offset);
  vkCmdBindIndexBuffer(commandBuffer_, m.indexBuffer, 0, VK_INDEX_TYPE_UINT32);
  vkCmdDrawIndexed(commandBuffer_, m.indexCount, 1, 0, 0, 0);
}

void VulkanRenderer::endFrame() {
  if (!recording_) {
    return;
  }
  vkCmdEndRenderPass(commandBuffer_);
  recording_ = false;

  // Make color-attachment writes visible to the copy engine. The render pass
  // already moved the image to TRANSFER_SRC_OPTIMAL (finalLayout).
  transitionImage(
      colorImage_, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
      VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_ASPECT_COLOR_BIT,
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_TRANSFER_READ_BIT,
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT);
  transitionImage(readbackImage_, VK_IMAGE_LAYOUT_UNDEFINED,
                  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                  VK_IMAGE_ASPECT_COLOR_BIT, 0, VK_ACCESS_TRANSFER_WRITE_BIT,
                  VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT);

  VkImageCopy copy{};
  copy.srcSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1};
  copy.dstSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1};
  copy.extent = {width_, height_, 1};
  vkCmdCopyImage(commandBuffer_, colorImage_,
                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, readbackImage_,
                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);

  transitionImage(readbackImage_, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                  VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_ASPECT_COLOR_BIT,
                  VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_HOST_READ_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_HOST_BIT);

  if (!vkCheck(vkEndCommandBuffer(commandBuffer_), "vkEndCommandBuffer")) {
    return;
  }
  VkSubmitInfo submit{};
  submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit.commandBufferCount = 1;
  submit.pCommandBuffers = &commandBuffer_;
  if (!vkCheck(vkQueueSubmit(graphicsQueue_, 1, &submit, frameFence_),
               "vkQueueSubmit")) {
    return;
  }
  vkWaitForFences(device_, 1, &frameFence_, VK_TRUE, UINT64_MAX);
}

ImageRGBA VulkanRenderer::readbackPixels() {
  ImageRGBA out{width_, height_, std::vector<uint8_t>(width_ * height_ * 4, 0)};
  if (!initialized_) {
    return out;
  }
  VkSubresourceLayout layout{};
  const VkImageSubresource sub{VK_IMAGE_ASPECT_COLOR_BIT, 0, 0};
  void *mapped = nullptr;
  vkGetImageSubresourceLayout(device_, readbackImage_, &sub, &layout);
  if (!vkCheck(
          vkMapMemory(device_, readbackMemory_, 0, VK_WHOLE_SIZE, 0, &mapped),
          "vkMapMemory(readback)")) {
    return out;
  }
  const auto *base = static_cast<const uint8_t *>(mapped) + layout.offset;
  for (uint32_t y = 0; y < height_; ++y) {
    std::memcpy(out.pixels.data() + static_cast<size_t>(y) * width_ * 4,
                base + static_cast<size_t>(y) * layout.rowPitch, width_ * 4);
  }
  vkUnmapMemory(device_, readbackMemory_);
  return out;
}

bool VulkanRenderer::createInstance() {
  VkApplicationInfo app{};
  app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app.pApplicationName = "OpenSpore";
  app.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  app.apiVersion = VK_API_VERSION_1_0;
  VkInstanceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  info.pApplicationInfo = &app;
  return vkCheck(vkCreateInstance(&info, nullptr, &instance_),
                 "vkCreateInstance");
}

bool VulkanRenderer::pickPhysicalDevice() {
  uint32_t count = 0;
  if (!vkCheck(vkEnumeratePhysicalDevices(instance_, &count, nullptr),
               "vkEnumeratePhysicalDevices(count)") ||
      count == 0) {
    std::fprintf(stderr, "[VulkanRenderer] no physical devices found\n");
    return false;
  }
  std::vector<VkPhysicalDevice> devices(count);
  if (!vkCheck(vkEnumeratePhysicalDevices(instance_, &count, devices.data()),
               "vkEnumeratePhysicalDevices")) {
    return false;
  }
  int bestScore = -1;
  for (VkPhysicalDevice dev : devices) {
    VkPhysicalDeviceProperties props{};
    vkGetPhysicalDeviceProperties(dev, &props);
    int score = 0;
    switch (props.deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
      score = 300;
      break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
      score = 200;
      break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
      score = 100;
      break;
    default:
      score = 0;
      break;
    }
    std::fprintf(stderr, "[VulkanRenderer] candidate: %s (type=%d, score=%d)\n",
                 props.deviceName, static_cast<int>(props.deviceType), score);
    if (score > bestScore) {
      bestScore = score;
      physicalDevice_ = dev;
      deviceName_ = props.deviceName;
    }
  }
  if (physicalDevice_ == VK_NULL_HANDLE) {
    return false;
  }
  std::fprintf(stderr, "[VulkanRenderer] selected: %s\n", deviceName_.c_str());
  return true;
}

bool VulkanRenderer::createDevice() {
  uint32_t familyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &familyCount,
                                           nullptr);
  if (familyCount == 0) {
    return false;
  }
  std::vector<VkQueueFamilyProperties> families(familyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &familyCount,
                                           families.data());
  bool found = false;
  for (uint32_t i = 0; i < familyCount; ++i) {
    if ((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0 &&
        families[i].queueCount > 0) {
      graphicsQueueFamily_ = i;
      found = true;
      break;
    }
  }
  if (!found) {
    std::fprintf(stderr, "[VulkanRenderer] no graphics queue family\n");
    return false;
  }
  const float priority = 1.0F;
  VkDeviceQueueCreateInfo queue{};
  queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue.queueFamilyIndex = graphicsQueueFamily_;
  queue.queueCount = 1;
  queue.pQueuePriorities = &priority;
  VkDeviceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  info.queueCreateInfoCount = 1;
  info.pQueueCreateInfos = &queue;
  if (!vkCheck(vkCreateDevice(physicalDevice_, &info, nullptr, &device_),
               "vkCreateDevice")) {
    return false;
  }
  vkGetDeviceQueue(device_, graphicsQueueFamily_, 0, &graphicsQueue_);
  return true;
}

bool VulkanRenderer::createCommandPool() {
  VkCommandPoolCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  info.queueFamilyIndex = graphicsQueueFamily_;
  if (!vkCheck(vkCreateCommandPool(device_, &info, nullptr, &commandPool_),
               "vkCreateCommandPool")) {
    return false;
  }
  VkCommandBufferAllocateInfo alloc{};
  alloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc.commandPool = commandPool_;
  alloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc.commandBufferCount = 1;
  return vkCheck(vkAllocateCommandBuffers(device_, &alloc, &commandBuffer_),
                 "vkAllocateCommandBuffers");
}

bool VulkanRenderer::createTargets() {
  if (!createImage(
          width_, height_, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL,
          VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &colorImage_, &colorMemory_)) {
    return false;
  }
  VkImageViewCreateInfo view{};
  view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view.image = colorImage_;
  view.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view.format = VK_FORMAT_R8G8B8A8_UNORM;
  view.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
  if (!vkCheck(vkCreateImageView(device_, &view, nullptr, &colorView_),
               "vkCreateImageView(color)")) {
    return false;
  }
  depthFormat_ = findDepthFormat();
  if (depthFormat_ == VK_FORMAT_UNDEFINED) {
    std::fprintf(stderr,
                 "[VulkanRenderer] no depth format with attachment support\n");
    return false;
  }
  if (!createImage(width_, height_, depthFormat_, VK_IMAGE_TILING_OPTIMAL,
                   VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &depthImage_,
                   &depthMemory_)) {
    return false;
  }
  VkImageAspectFlags depthAspect = VK_IMAGE_ASPECT_DEPTH_BIT;
  if (depthFormat_ == VK_FORMAT_D24_UNORM_S8_UINT ||
      depthFormat_ == VK_FORMAT_D32_SFLOAT_S8_UINT) {
    depthAspect |= VK_IMAGE_ASPECT_STENCIL_BIT;
  }
  view.image = depthImage_;
  view.format = depthFormat_;
  view.subresourceRange.aspectMask = depthAspect;
  if (!vkCheck(vkCreateImageView(device_, &view, nullptr, &depthView_),
               "vkCreateImageView(depth)")) {
    return false;
  }
  // Linear host-visible image: the render never touches it, the copy engine
  // writes it, the host maps it.
  if (!createImage(width_, height_, VK_FORMAT_R8G8B8A8_UNORM,
                   VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                   &readbackImage_, &readbackMemory_)) {
    return false;
  }
  return true;
}

bool VulkanRenderer::createRenderPass() {
  VkAttachmentDescription color{};
  color.format = VK_FORMAT_R8G8B8A8_UNORM;
  color.samples = VK_SAMPLE_COUNT_1_BIT;
  color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
  VkAttachmentDescription depth{};
  depth.format = depthFormat_;
  depth.samples = VK_SAMPLE_COUNT_1_BIT;
  depth.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depth.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depth.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  const VkAttachmentDescription attachments[2] = {color, depth};

  VkAttachmentReference colorRef{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
  VkAttachmentReference depthRef{
      1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorRef;
  subpass.pDepthStencilAttachment = &depthRef;

  VkSubpassDependency dep{};
  dep.srcSubpass = VK_SUBPASS_EXTERNAL;
  dep.dstSubpass = 0;
  dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.srcAccessMask = 0;
  dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  VkRenderPassCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  info.attachmentCount = 2;
  info.pAttachments = attachments;
  info.subpassCount = 1;
  info.pSubpasses = &subpass;
  info.dependencyCount = 1;
  info.pDependencies = &dep;
  if (!vkCheck(vkCreateRenderPass(device_, &info, nullptr, &renderPass_),
               "vkCreateRenderPass")) {
    return false;
  }
  const VkImageView views[2] = {colorView_, depthView_};
  VkFramebufferCreateInfo fb{};
  fb.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  fb.renderPass = renderPass_;
  fb.attachmentCount = 2;
  fb.pAttachments = views;
  fb.width = width_;
  fb.height = height_;
  fb.layers = 1;
  return vkCheck(vkCreateFramebuffer(device_, &fb, nullptr, &framebuffer_),
                 "vkCreateFramebuffer");
}

bool VulkanRenderer::createPipeline() {
  VkShaderModule vert =
      makeShaderModule(device_, kTriangleVertSpv, kTriangleVertSpvWordCount);
  VkShaderModule frag =
      makeShaderModule(device_, kTriangleFragSpv, kTriangleFragSpvWordCount);
  if (vert == VK_NULL_HANDLE || frag == VK_NULL_HANDLE) {
    if (vert != VK_NULL_HANDLE) {
      vkDestroyShaderModule(device_, vert, nullptr);
    }
    if (frag != VK_NULL_HANDLE) {
      vkDestroyShaderModule(device_, frag, nullptr);
    }
    return false;
  }
  VkPipelineShaderStageCreateInfo stages[2]{};
  stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  stages[0].module = vert;
  stages[0].pName = "main";
  stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  stages[1].module = frag;
  stages[1].pName = "main";

  VkVertexInputBindingDescription binding{};
  binding.binding = 0;
  binding.stride = sizeof(Vertex);
  binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  VkVertexInputAttributeDescription attrs[2]{};
  attrs[0] = {0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0};
  attrs[1] = {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color)};
  VkPipelineVertexInputStateCreateInfo vertexInput{};
  vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInput.vertexBindingDescriptionCount = 1;
  vertexInput.pVertexBindingDescriptions = &binding;
  vertexInput.vertexAttributeDescriptionCount = 2;
  vertexInput.pVertexAttributeDescriptions = attrs;

  VkPipelineInputAssemblyStateCreateInfo assembly{};
  assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  VkViewport viewport{
      0.0F, 0.0F, static_cast<float>(width_), static_cast<float>(height_),
      0.0F, 1.0F};
  VkRect2D scissor{{0, 0}, {width_, height_}};
  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo raster{};
  raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  raster.polygonMode = VK_POLYGON_MODE_FILL;
  raster.cullMode = VK_CULL_MODE_NONE;
  raster.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  raster.lineWidth = 1.0F;

  VkPipelineMultisampleStateCreateInfo msaa{};
  msaa.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  msaa.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineDepthStencilStateCreateInfo depth{};
  depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depth.depthTestEnable = VK_TRUE;
  depth.depthWriteEnable = VK_TRUE;
  depth.depthCompareOp = VK_COMPARE_OP_LESS;

  VkPipelineColorBlendAttachmentState blend{};
  blend.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  VkPipelineColorBlendStateCreateInfo blending{};
  blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blending.attachmentCount = 1;
  blending.pAttachments = &blend;

  VkPipelineLayoutCreateInfo layout{};
  layout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  bool ok = vkCheck(
      vkCreatePipelineLayout(device_, &layout, nullptr, &pipelineLayout_),
      "vkCreatePipelineLayout");
  if (ok) {
    VkGraphicsPipelineCreateInfo pipeline{};
    pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline.stageCount = 2;
    pipeline.pStages = stages;
    pipeline.pVertexInputState = &vertexInput;
    pipeline.pInputAssemblyState = &assembly;
    pipeline.pViewportState = &viewportState;
    pipeline.pRasterizationState = &raster;
    pipeline.pMultisampleState = &msaa;
    pipeline.pDepthStencilState = &depth;
    pipeline.pColorBlendState = &blending;
    pipeline.layout = pipelineLayout_;
    pipeline.renderPass = renderPass_;
    pipeline.subpass = 0;
    ok = vkCheck(vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1,
                                           &pipeline, nullptr, &pipeline_),
                 "vkCreateGraphicsPipelines");
  }
  vkDestroyShaderModule(device_, vert, nullptr);
  vkDestroyShaderModule(device_, frag, nullptr);
  return ok;
}

bool VulkanRenderer::createSync() {
  VkFenceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  return vkCheck(vkCreateFence(device_, &info, nullptr, &frameFence_),
                 "vkCreateFence");
}

uint32_t VulkanRenderer::findMemoryType(uint32_t typeFilter,
                                        VkMemoryPropertyFlags props) {
  VkPhysicalDeviceMemoryProperties mem{};
  vkGetPhysicalDeviceMemoryProperties(physicalDevice_, &mem);
  for (uint32_t i = 0; i < mem.memoryTypeCount; ++i) {
    if (((typeFilter & (1u << i)) != 0u) &&
        ((mem.memoryTypes[i].propertyFlags & props) == props)) {
      return i;
    }
  }
  return 0xFFFFFFFFu;
}

bool VulkanRenderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                                  VkMemoryPropertyFlags props,
                                  VkBuffer *outBuffer,
                                  VkDeviceMemory *outMemory) {
  VkBufferCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  info.size = size;
  info.usage = usage;
  info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (!vkCheck(vkCreateBuffer(device_, &info, nullptr, outBuffer),
               "vkCreateBuffer")) {
    return false;
  }
  VkMemoryRequirements req{};
  vkGetBufferMemoryRequirements(device_, *outBuffer, &req);
  const uint32_t type = findMemoryType(req.memoryTypeBits, props);
  if (type == 0xFFFFFFFFu) {
    std::fprintf(stderr, "[VulkanRenderer] no memory type for buffer\n");
    vkDestroyBuffer(device_, *outBuffer, nullptr);
    *outBuffer = VK_NULL_HANDLE;
    return false;
  }
  VkMemoryAllocateInfo alloc{};
  alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc.allocationSize = req.size;
  alloc.memoryTypeIndex = type;
  if (!vkCheck(vkAllocateMemory(device_, &alloc, nullptr, outMemory),
               "vkAllocateMemory(buffer)")) {
    vkDestroyBuffer(device_, *outBuffer, nullptr);
    *outBuffer = VK_NULL_HANDLE;
    return false;
  }
  if (!vkCheck(vkBindBufferMemory(device_, *outBuffer, *outMemory, 0),
               "vkBindBufferMemory")) {
    vkFreeMemory(device_, *outMemory, nullptr);
    vkDestroyBuffer(device_, *outBuffer, nullptr);
    *outBuffer = VK_NULL_HANDLE;
    *outMemory = VK_NULL_HANDLE;
    return false;
  }
  return true;
}

bool VulkanRenderer::createImage(uint32_t w, uint32_t h, VkFormat format,
                                 VkImageTiling tiling, VkImageUsageFlags usage,
                                 VkMemoryPropertyFlags props, VkImage *outImage,
                                 VkDeviceMemory *outMemory) {
  VkImageCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  info.imageType = VK_IMAGE_TYPE_2D;
  info.format = format;
  info.extent = {w, h, 1};
  info.mipLevels = 1;
  info.arrayLayers = 1;
  info.samples = VK_SAMPLE_COUNT_1_BIT;
  info.tiling = tiling;
  info.usage = usage;
  info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if (!vkCheck(vkCreateImage(device_, &info, nullptr, outImage),
               "vkCreateImage")) {
    return false;
  }
  VkMemoryRequirements req{};
  vkGetImageMemoryRequirements(device_, *outImage, &req);
  const uint32_t type = findMemoryType(req.memoryTypeBits, props);
  if (type == 0xFFFFFFFFu) {
    std::fprintf(stderr, "[VulkanRenderer] no memory type for image\n");
    vkDestroyImage(device_, *outImage, nullptr);
    *outImage = VK_NULL_HANDLE;
    return false;
  }
  VkMemoryAllocateInfo alloc{};
  alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc.allocationSize = req.size;
  alloc.memoryTypeIndex = type;
  if (!vkCheck(vkAllocateMemory(device_, &alloc, nullptr, outMemory),
               "vkAllocateMemory(image)")) {
    vkDestroyImage(device_, *outImage, nullptr);
    *outImage = VK_NULL_HANDLE;
    return false;
  }
  if (!vkCheck(vkBindImageMemory(device_, *outImage, *outMemory, 0),
               "vkBindImageMemory")) {
    vkFreeMemory(device_, *outMemory, nullptr);
    vkDestroyImage(device_, *outImage, nullptr);
    *outImage = VK_NULL_HANDLE;
    *outMemory = VK_NULL_HANDLE;
    return false;
  }
  return true;
}

VkFormat VulkanRenderer::findDepthFormat() {
  const std::array<VkFormat, 3> candidates = {
      VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D16_UNORM};
  for (VkFormat format : candidates) {
    VkFormatProperties props{};
    vkGetPhysicalDeviceFormatProperties(physicalDevice_, format, &props);
    if ((props.optimalTilingFeatures &
         VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) != 0) {
      return format;
    }
  }
  return VK_FORMAT_UNDEFINED;
}

void VulkanRenderer::transitionImage(
    VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout,
    VkImageAspectFlags aspect, VkAccessFlags srcAccess, VkAccessFlags dstAccess,
    VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage) {
  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange = {aspect, 0, 1, 0, 1};
  barrier.srcAccessMask = srcAccess;
  barrier.dstAccessMask = dstAccess;
  vkCmdPipelineBarrier(commandBuffer_, srcStage, dstStage, 0, 0, nullptr, 0,
                       nullptr, 1, &barrier);
}

void VulkanRenderer::destroyMeshResources(Mesh &mesh) {
  if (mesh.vertexBuffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(device_, mesh.vertexBuffer, nullptr);
    mesh.vertexBuffer = VK_NULL_HANDLE;
  }
  if (mesh.vertexMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device_, mesh.vertexMemory, nullptr);
    mesh.vertexMemory = VK_NULL_HANDLE;
  }
  if (mesh.indexBuffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(device_, mesh.indexBuffer, nullptr);
    mesh.indexBuffer = VK_NULL_HANDLE;
  }
  if (mesh.indexMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device_, mesh.indexMemory, nullptr);
    mesh.indexMemory = VK_NULL_HANDLE;
  }
  mesh.indexCount = 0;
  mesh.valid = false;
}

bool VulkanRenderer::createTextureSupport() {
  VkSamplerCreateInfo sampler{};
  sampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler.magFilter = VK_FILTER_NEAREST;
  sampler.minFilter = VK_FILTER_NEAREST;
  sampler.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
  sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  sampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  sampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  sampler.anisotropyEnable = VK_FALSE;
  sampler.maxAnisotropy = 1.0F;
  sampler.compareEnable = VK_FALSE;
  sampler.mipLodBias = 0.0F;
  sampler.minLod = 0.0F;
  sampler.maxLod = 0.0F;
  sampler.borderColor = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
  if (!vkCheck(vkCreateSampler(device_, &sampler, nullptr, &texSampler_),
               "vkCreateSampler")) {
    return false;
  }
  VkDescriptorSetLayoutBinding binding{};
  binding.binding = 0;
  binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  binding.descriptorCount = 1;
  binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  VkDescriptorSetLayoutCreateInfo layout{};
  layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layout.bindingCount = 1;
  layout.pBindings = &binding;
  if (!vkCheck(vkCreateDescriptorSetLayout(device_, &layout, nullptr,
                                           &texSetLayout_),
               "vkCreateDescriptorSetLayout")) {
    return false;
  }
  VkDescriptorPoolSize poolSize{};
  poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSize.descriptorCount = 16;
  VkDescriptorPoolCreateInfo pool{};
  pool.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool.maxSets = 16;
  pool.poolSizeCount = 1;
  pool.pPoolSizes = &poolSize;
  return vkCheck(vkCreateDescriptorPool(device_, &pool, nullptr, &descPool_),
                 "vkCreateDescriptorPool");
}

bool VulkanRenderer::createLitPipeline() {
  VkShaderModule vert =
      makeShaderModule(device_, kLitVertSpv, kLitVertSpvWordCount);
  VkShaderModule frag =
      makeShaderModule(device_, kLitFragSpv, kLitFragSpvWordCount);
  if (vert == VK_NULL_HANDLE || frag == VK_NULL_HANDLE) {
    if (vert != VK_NULL_HANDLE) {
      vkDestroyShaderModule(device_, vert, nullptr);
    }
    if (frag != VK_NULL_HANDLE) {
      vkDestroyShaderModule(device_, frag, nullptr);
    }
    return false;
  }
  VkPipelineShaderStageCreateInfo stages[2]{};
  stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  stages[0].module = vert;
  stages[0].pName = "main";
  stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  stages[1].module = frag;
  stages[1].pName = "main";

  VkVertexInputBindingDescription binding{};
  binding.binding = 0;
  binding.stride = sizeof(TexVertex);
  binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  VkVertexInputAttributeDescription attrs[3]{};
  attrs[0] = {0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0};
  attrs[1] = {1, 0, VK_FORMAT_R32G32B32_SFLOAT,
              static_cast<uint32_t>(offsetof(TexVertex, normal))};
  attrs[2] = {2, 0, VK_FORMAT_R32G32_SFLOAT,
              static_cast<uint32_t>(offsetof(TexVertex, uv))};
  VkPipelineVertexInputStateCreateInfo vertexInput{};
  vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInput.vertexBindingDescriptionCount = 1;
  vertexInput.pVertexBindingDescriptions = &binding;
  vertexInput.vertexAttributeDescriptionCount = 3;
  vertexInput.pVertexAttributeDescriptions = attrs;

  VkPipelineInputAssemblyStateCreateInfo assembly{};
  assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  VkViewport viewport{
      0.0F, 0.0F, static_cast<float>(width_), static_cast<float>(height_),
      0.0F, 1.0F};
  VkRect2D scissor{{0, 0}, {width_, height_}};
  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo raster{};
  raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  raster.polygonMode = VK_POLYGON_MODE_FILL;
  raster.cullMode = VK_CULL_MODE_NONE;
  raster.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  raster.lineWidth = 1.0F;

  VkPipelineMultisampleStateCreateInfo msaa{};
  msaa.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  msaa.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineDepthStencilStateCreateInfo depth{};
  depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depth.depthTestEnable = VK_TRUE;
  depth.depthWriteEnable = VK_TRUE;
  depth.depthCompareOp = VK_COMPARE_OP_LESS;

  VkPipelineColorBlendAttachmentState blend{};
  blend.blendEnable = VK_TRUE;
  blend.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  blend.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  blend.colorBlendOp = VK_BLEND_OP_ADD;
  blend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  blend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  blend.alphaBlendOp = VK_BLEND_OP_ADD;
  blend.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  VkPipelineColorBlendStateCreateInfo blending{};
  blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blending.attachmentCount = 1;
  blending.pAttachments = &blend;

  VkPushConstantRange push{};
  push.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  push.offset = 0;
  push.size = 16; // vec4 light
  VkPipelineLayoutCreateInfo layout{};
  layout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  layout.setLayoutCount = 1;
  layout.pSetLayouts = &texSetLayout_;
  layout.pushConstantRangeCount = 1;
  layout.pPushConstantRanges = &push;
  bool ok = vkCheck(vkCreatePipelineLayout(device_, &layout, nullptr,
                                           &litPipelineLayout_),
                    "vkCreatePipelineLayout(lit)");
  if (ok) {
    VkGraphicsPipelineCreateInfo pipeline{};
    pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline.stageCount = 2;
    pipeline.pStages = stages;
    pipeline.pVertexInputState = &vertexInput;
    pipeline.pInputAssemblyState = &assembly;
    pipeline.pViewportState = &viewportState;
    pipeline.pRasterizationState = &raster;
    pipeline.pMultisampleState = &msaa;
    pipeline.pDepthStencilState = &depth;
    pipeline.pColorBlendState = &blending;
    pipeline.layout = litPipelineLayout_;
    pipeline.renderPass = renderPass_;
    pipeline.subpass = 0;
    ok = vkCheck(vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1, &pipeline,
                                          nullptr, &litPipeline_),
                 "vkCreateGraphicsPipelines(lit)");
  }
  vkDestroyShaderModule(device_, vert, nullptr);
  vkDestroyShaderModule(device_, frag, nullptr);
  return ok;
}

void VulkanRenderer::submitOneTime(VkCommandBuffer cmd) {
  VkFence fence = VK_NULL_HANDLE;
  VkFenceCreateInfo fi{};
  fi.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  if (!vkCheck(vkCreateFence(device_, &fi, nullptr, &fence),
               "vkCreateFence(upload)")) {
    return;
  }
  VkSubmitInfo submit{};
  submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit.commandBufferCount = 1;
  submit.pCommandBuffers = &cmd;
  if (!vkCheck(vkQueueSubmit(graphicsQueue_, 1, &submit, fence),
               "vkQueueSubmit(upload)")) {
    vkDestroyFence(device_, fence, nullptr);
    return;
  }
  vkWaitForFences(device_, 1, &fence, VK_TRUE, UINT64_MAX);
  vkDestroyFence(device_, fence, nullptr);
}

TextureHandle VulkanRenderer::createTexture(const ImageRGBA &image) {
  if (!initialized_ || image.width == 0 || image.height == 0 ||
      image.pixels.size() <
          static_cast<size_t>(image.width) * image.height * 4) {
    return kInvalidTexture;
  }
  const uint32_t w = image.width;
  const uint32_t h = image.height;
  const VkDeviceSize dataSize =
      static_cast<VkDeviceSize>(w) * h * 4;
  const VkMemoryPropertyFlags hostFlags =
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  VkBuffer staging = VK_NULL_HANDLE;
  VkDeviceMemory stagingMem = VK_NULL_HANDLE;
  if (!createBuffer(dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, hostFlags,
                    &staging, &stagingMem)) {
    return kInvalidTexture;
  }
  void *mapped = nullptr;
  if (!vkCheck(vkMapMemory(device_, stagingMem, 0, dataSize, 0, &mapped),
               "vkMapMemory(tex)")) {
    vkDestroyBuffer(device_, staging, nullptr);
    vkFreeMemory(device_, stagingMem, nullptr);
    return kInvalidTexture;
  }
  std::memcpy(mapped, image.pixels.data(), static_cast<size_t>(dataSize));
  vkUnmapMemory(device_, stagingMem);

  Texture tex{};
  tex.width = w;
  tex.height = h;
  bool imageOk =
      createImage(w, h, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL,
                  VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &tex.image, &tex.memory);
  if (imageOk) {
    VkImageViewCreateInfo view{};
    view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view.image = tex.image;
    view.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view.format = VK_FORMAT_R8G8B8A8_UNORM;
    view.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    imageOk = vkCheck(vkCreateImageView(device_, &view, nullptr, &tex.view),
                      "vkCreateImageView(tex)");
  }

  if (imageOk) {
    VkCommandBuffer upload = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo alloc{};
    alloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc.commandPool = commandPool_;
    alloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc.commandBufferCount = 1;
    VkCommandBufferBeginInfo begin{};
    begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkCheck(vkAllocateCommandBuffers(device_, &alloc, &upload),
                "vkAllocateCommandBuffers(tex)") &&
        vkCheck(vkBeginCommandBuffer(upload, &begin),
                "vkBeginCommandBuffer(tex)")) {
      imageBarrier(upload, tex.image, VK_IMAGE_LAYOUT_UNDEFINED,
                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                   VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
                   VK_ACCESS_TRANSFER_WRITE_BIT);
      VkBufferImageCopy region{};
      region.bufferOffset = 0;
      region.bufferRowLength = 0;
      region.bufferImageHeight = h;
      region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1};
      region.imageOffset = {0, 0, 0};
      region.imageExtent = {w, h, 1};
      vkCmdCopyBufferToImage(upload, staging, tex.image,
                             VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
      imageBarrier(upload, tex.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                   VK_PIPELINE_STAGE_TRANSFER_BIT,
                   VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                   VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT);
      vkEndCommandBuffer(upload);
      submitOneTime(upload);
    }
    vkFreeCommandBuffers(device_, commandPool_, 1, &upload);
  }
  vkDestroyBuffer(device_, staging, nullptr);
  vkFreeMemory(device_, stagingMem, nullptr);
  if (!imageOk) {
    destroyTextureResources(tex);
    return kInvalidTexture;
  }

  VkDescriptorSetAllocateInfo setAlloc{};
  setAlloc.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  setAlloc.descriptorPool = descPool_;
  setAlloc.descriptorSetCount = 1;
  setAlloc.pSetLayouts = &texSetLayout_;
  if (vkCheck(vkAllocateDescriptorSets(device_, &setAlloc, &tex.set),
              "vkAllocateDescriptorSets") &&
      tex.set != VK_NULL_HANDLE) {
    VkDescriptorImageInfo imgInfo{};
    imgInfo.sampler = texSampler_;
    imgInfo.imageView = tex.view;
    imgInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = tex.set;
    write.dstBinding = 0;
    write.dstArrayElement = 0;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &imgInfo;
    vkUpdateDescriptorSets(device_, 1, &write, 0, nullptr);
  }
  tex.valid = tex.set != VK_NULL_HANDLE;
  if (!tex.valid) {
    destroyTextureResources(tex);
    return kInvalidTexture;
  }
  for (size_t i = 0; i < textures_.size(); ++i) {
    if (!textures_[i].valid) {
      textures_[i] = tex;
      return static_cast<TextureHandle>(i);
    }
  }
  textures_.push_back(tex);
  return static_cast<TextureHandle>(textures_.size() - 1);
}

void VulkanRenderer::destroyTextureResources(Texture &tex) {
  if (tex.view != VK_NULL_HANDLE) {
    vkDestroyImageView(device_, tex.view, nullptr);
    tex.view = VK_NULL_HANDLE;
  }
  if (tex.image != VK_NULL_HANDLE) {
    vkDestroyImage(device_, tex.image, nullptr);
    tex.image = VK_NULL_HANDLE;
  }
  if (tex.memory != VK_NULL_HANDLE) {
    vkFreeMemory(device_, tex.memory, nullptr);
    tex.memory = VK_NULL_HANDLE;
  }
  tex.set = VK_NULL_HANDLE;
  tex.valid = false;
}

void VulkanRenderer::destroyTexture(TextureHandle texture) {
  if (texture < textures_.size() && textures_[texture].valid) {
    destroyTextureResources(textures_[texture]);
    textures_[texture] = Texture{};
  }
}

MeshHandle VulkanRenderer::createTexMesh(const TexVertex *vertices,
                                         size_t vertexCount,
                                         const uint32_t *indices,
                                         size_t indexCount) {
  if (!initialized_ || vertices == nullptr || vertexCount == 0 ||
      indices == nullptr || indexCount == 0) {
    return kInvalidMesh;
  }
  TexMesh mesh{};
  const VkDeviceSize vbSize = vertexCount * sizeof(TexVertex);
  const VkDeviceSize ibSize = indexCount * sizeof(uint32_t);
  const VkMemoryPropertyFlags hostFlags =
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  if (!createBuffer(vbSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, hostFlags,
                    &mesh.vertexBuffer, &mesh.vertexMemory) ||
      !createBuffer(ibSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, hostFlags,
                    &mesh.indexBuffer, &mesh.indexMemory)) {
    destroyTexMeshResources(mesh);
    return kInvalidMesh;
  }
  void *mapped = nullptr;
  if (!vkCheck(vkMapMemory(device_, mesh.vertexMemory, 0, vbSize, 0, &mapped),
               "vkMapMemory(tvb)")) {
    destroyTexMeshResources(mesh);
    return kInvalidMesh;
  }
  std::memcpy(mapped, vertices, static_cast<size_t>(vbSize));
  vkUnmapMemory(device_, mesh.vertexMemory);
  if (!vkCheck(vkMapMemory(device_, mesh.indexMemory, 0, ibSize, 0, &mapped),
               "vkMapMemory(tib)")) {
    destroyTexMeshResources(mesh);
    return kInvalidMesh;
  }
  std::memcpy(mapped, indices, static_cast<size_t>(ibSize));
  vkUnmapMemory(device_, mesh.indexMemory);
  mesh.indexCount = static_cast<uint32_t>(indexCount);
  mesh.valid = true;
  for (size_t i = 0; i < texMeshes_.size(); ++i) {
    if (!texMeshes_[i].valid) {
      texMeshes_[i] = mesh;
      return static_cast<MeshHandle>(i);
    }
  }
  texMeshes_.push_back(mesh);
  return static_cast<MeshHandle>(texMeshes_.size() - 1);
}

void VulkanRenderer::destroyTexMeshResources(TexMesh &mesh) {
  if (mesh.vertexBuffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(device_, mesh.vertexBuffer, nullptr);
    mesh.vertexBuffer = VK_NULL_HANDLE;
  }
  if (mesh.vertexMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device_, mesh.vertexMemory, nullptr);
    mesh.vertexMemory = VK_NULL_HANDLE;
  }
  if (mesh.indexBuffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(device_, mesh.indexBuffer, nullptr);
    mesh.indexBuffer = VK_NULL_HANDLE;
  }
  if (mesh.indexMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device_, mesh.indexMemory, nullptr);
    mesh.indexMemory = VK_NULL_HANDLE;
  }
  mesh.indexCount = 0;
  mesh.valid = false;
}

void VulkanRenderer::destroyTexMesh(MeshHandle mesh) {
  if (mesh < texMeshes_.size() && texMeshes_[mesh].valid) {
    destroyTexMeshResources(texMeshes_[mesh]);
    texMeshes_[mesh] = TexMesh{};
  }
}

void VulkanRenderer::drawTextured(MeshHandle mesh, TextureHandle texture,
                                  const MaterialState &material) {
  if (!recording_) {
    std::fprintf(stderr,
                 "[VulkanRenderer] drawTextured outside begin/end frame\n");
    return;
  }
  if (mesh >= texMeshes_.size() || !texMeshes_[mesh].valid) {
    std::fprintf(stderr, "[VulkanRenderer] drawTextured invalid mesh %u\n",
                 mesh);
    return;
  }
  if (texture >= textures_.size() || !textures_[texture].valid) {
    std::fprintf(stderr, "[VulkanRenderer] drawTextured invalid texture %u\n",
                 texture);
    return;
  }
  const TexMesh &m = texMeshes_[mesh];
  const Texture &t = textures_[texture];
  vkCmdBindPipeline(commandBuffer_, VK_PIPELINE_BIND_POINT_GRAPHICS,
                   litPipeline_);
  VkDescriptorSet set = t.set;
  vkCmdBindDescriptorSets(commandBuffer_, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          litPipelineLayout_, 0, 1, &set, 0, nullptr);
  float push[4] = {material.lightDir[0], material.lightDir[1],
                   material.lightDir[2], material.ambient};
  vkCmdPushConstants(commandBuffer_, litPipelineLayout_,
                     VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(push), push);
  const VkDeviceSize offset = 0;
  vkCmdBindVertexBuffers(commandBuffer_, 0, 1, &m.vertexBuffer, &offset);
  vkCmdBindIndexBuffer(commandBuffer_, m.indexBuffer, 0, VK_INDEX_TYPE_UINT32);
  vkCmdDrawIndexed(commandBuffer_, m.indexCount, 1, 0, 0, 0);
}

} // namespace openspore

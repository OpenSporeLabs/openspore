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
      !createTextureSupport() ||
      !createPipelinePair(renderPass_, pipeline_, litPipeline_) ||
      !createSync()) {
    shutdown();
    return false;
  }
  initialized_ = true;
  std::fprintf(stderr, "[VulkanRenderer] ready on '%s' (%ux%u offscreen)\n",
                deviceName_.c_str(), width_, height_);
  return true;
}

bool VulkanRenderer::initPresent(uint32_t width, uint32_t height,
                                 VkSurfaceKHR surface) {
  if (initialized_) {
    return true;
  }
  if (!presentMode_ || instance_ == VK_NULL_HANDLE ||
      surface == VK_NULL_HANDLE) {
    std::fprintf(stderr, "[VulkanRenderer] initPresent before surface mode\n");
    return false;
  }
  width_ = width;
  height_ = height;
  surface_ = surface;
  if (!pickPhysicalDevice() || !createDevice() || !createCommandPool() ||
      !createPresentSupport() || !createSwapchain() ||
      !createPresentRenderPass() || !createTextureSupport() ||
      !createPipelinePair(presentRenderPass_, presentPipeline_,
                          presentLitPipeline_) ||
      !createPresentTargets()) {
    shutdown();
    return false;
  }
  initialized_ = true;
  std::fprintf(
      stderr,
      "[VulkanRenderer] ready on '%s' (%ux%u present, %u swapchain images, "
      "format=%d)\n",
      deviceName_.c_str(), swapWidth_, swapHeight_,
      static_cast<uint32_t>(presentTargets_.size()),
      static_cast<int>(presentFormat_));
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
  destroyPresentSupport();
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
  activePipeline_ = pipeline_;
  activeLitPipeline_ = litPipeline_;
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
  vkCmdBindPipeline(commandBuffer_, VK_PIPELINE_BIND_POINT_GRAPHICS,
                   activePipeline_);
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
  if (instance_ != VK_NULL_HANDLE) {
    return true;
  }
  VkApplicationInfo app{};
  app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app.pApplicationName = "OpenSpore";
  app.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  app.apiVersion = VK_API_VERSION_1_0;
  VkInstanceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  info.pApplicationInfo = &app;
  if (presentMode_) {
    info.enabledExtensionCount =
        static_cast<uint32_t>(surfaceExtNames_.size());
    info.ppEnabledExtensionNames = surfaceExtNames_.data();
  }
  return vkCheck(vkCreateInstance(&info, nullptr, &instance_),
                  "vkCreateInstance");
}

bool VulkanRenderer::beginSurfaceMode(const char *const *extNames,
                                      uint32_t extCount) {
  if (instance_ != VK_NULL_HANDLE) {
    return false;
  }
  presentMode_ = true;
  surfaceExtNames_.clear();
  for (uint32_t i = 0; i < extCount; ++i) {
    surfaceExtNames_.push_back(extNames[i]);
  }
  return createInstance();
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
    if (presentMode_) {
      // Present mode: the chosen graphics queue family must also support
      // presenting to our surface (RADV reports the present-capable family
      // via vkGetPhysicalDeviceSurfaceSupportKHR).
      uint32_t famCount = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(dev, &famCount, nullptr);
      std::vector<VkQueueFamilyProperties> fams(famCount);
      vkGetPhysicalDeviceQueueFamilyProperties(dev, &famCount, fams.data());
      bool canPresent = false;
      for (uint32_t i = 0; i < famCount; ++i) {
        if ((fams[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0 ||
            fams[i].queueCount == 0) {
          continue;
        }
        VkBool32 supported = VK_FALSE;
        if (vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, surface_, &supported) ==
                VK_SUCCESS &&
            supported == VK_TRUE) {
          graphicsQueueFamily_ = i;
          canPresent = true;
          break;
        }
      }
      if (!canPresent) {
        std::fprintf(stderr,
                     "[VulkanRenderer] physical device: no queue presents to "
                     "the surface, skipping\n");
        continue;
      }
    }
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
  if (presentMode_) {
    static const char *kSwapchainExt = "VK_KHR_swapchain";
    info.enabledExtensionCount = 1;
    info.ppEnabledExtensionNames = &kSwapchainExt;
  }
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

// Shared per-pipeline state (viewport/raster/depth) for both pipelines.
namespace {

struct PipelineCommon {
  VkPipelineInputAssemblyStateCreateInfo assembly{};
  VkViewport viewport{};
  VkRect2D scissor{};
  VkPipelineViewportStateCreateInfo viewportState{};
  VkPipelineRasterizationStateCreateInfo raster{};
  VkPipelineMultisampleStateCreateInfo msaa{};
  VkPipelineDepthStencilStateCreateInfo depth{};

  void build(uint32_t w, uint32_t h) {
    assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    viewport = {0.0F, 0.0F, static_cast<float>(w), static_cast<float>(h),
                0.0F, 1.0F};
    scissor = {{0, 0}, {w, h}};
    viewportState.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;
    raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.cullMode = VK_CULL_MODE_NONE;
    raster.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    raster.lineWidth = 1.0F;
    msaa.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    msaa.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth.depthTestEnable = VK_TRUE;
    depth.depthWriteEnable = VK_TRUE;
    depth.depthCompareOp = VK_COMPARE_OP_LESS;
  }
};

} // namespace

bool VulkanRenderer::createPipelinePair(VkRenderPass pass, VkPipeline &plain,
                                       VkPipeline &lit) {
  VkShaderModule vert =
      makeShaderModule(device_, kTriangleVertSpv, kTriangleVertSpvWordCount);
  VkShaderModule frag =
      makeShaderModule(device_, kTriangleFragSpv, kTriangleFragSpvWordCount);
  VkShaderModule litVert =
      makeShaderModule(device_, kLitVertSpv, kLitVertSpvWordCount);
  VkShaderModule litFrag =
      makeShaderModule(device_, kLitFragSpv, kLitFragSpvWordCount);
  const bool anyModule =
      vert != VK_NULL_HANDLE || frag != VK_NULL_HANDLE ||
      litVert != VK_NULL_HANDLE || litFrag != VK_NULL_HANDLE;
  if ((vert == VK_NULL_HANDLE || frag == VK_NULL_HANDLE) ||
      (litVert == VK_NULL_HANDLE || litFrag == VK_NULL_HANDLE)) {
    if (anyModule) {
      vkDestroyShaderModule(device_, vert, nullptr);
      vkDestroyShaderModule(device_, frag, nullptr);
      vkDestroyShaderModule(device_, litVert, nullptr);
      vkDestroyShaderModule(device_, litFrag, nullptr);
    }
    return false;
  }

  PipelineCommon common;
  common.build(width_, height_);

  // ---- Flat-color pipeline -------------------------------------------------
  {
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
      pipeline.pInputAssemblyState = &common.assembly;
      pipeline.pViewportState = &common.viewportState;
      pipeline.pRasterizationState = &common.raster;
      pipeline.pMultisampleState = &common.msaa;
      pipeline.pDepthStencilState = &common.depth;
      pipeline.pColorBlendState = &blending;
      pipeline.layout = pipelineLayout_;
      pipeline.renderPass = pass;
      pipeline.subpass = 0;
      ok = vkCheck(vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1,
                                             &pipeline, nullptr, &plain),
                   "vkCreateGraphicsPipelines");
    }
    if (!ok) {
      plain = VK_NULL_HANDLE;
    }
  }

  // ---- Normal-lit textured pipeline ----------------------------------------
  {
    VkPipelineShaderStageCreateInfo stages[2]{};
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    stages[0].module = litVert;
    stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    stages[1].module = litFrag;
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
      pipeline.pInputAssemblyState = &common.assembly;
      pipeline.pViewportState = &common.viewportState;
      pipeline.pRasterizationState = &common.raster;
      pipeline.pMultisampleState = &common.msaa;
      pipeline.pDepthStencilState = &common.depth;
      pipeline.pColorBlendState = &blending;
      pipeline.layout = litPipelineLayout_;
      pipeline.renderPass = pass;
      pipeline.subpass = 0;
      ok = vkCheck(vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1, &pipeline,
                                             nullptr, &lit),
                    "vkCreateGraphicsPipelines(lit)");
    }
    if (!ok) {
      lit = VK_NULL_HANDLE;
    }
  }

  vkDestroyShaderModule(device_, vert, nullptr);
  vkDestroyShaderModule(device_, frag, nullptr);
  vkDestroyShaderModule(device_, litVert, nullptr);
  vkDestroyShaderModule(device_, litFrag, nullptr);

  if (plain == VK_NULL_HANDLE || lit == VK_NULL_HANDLE) {
    if (plain != VK_NULL_HANDLE) {
      vkDestroyPipeline(device_, plain, nullptr);
    }
    if (lit != VK_NULL_HANDLE) {
      vkDestroyPipeline(device_, lit, nullptr);
    }
    return false;
  }
  return true;
}

bool VulkanRenderer::createSync() {
  VkFenceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  return vkCheck(vkCreateFence(device_, &info, nullptr, &frameFence_),
                  "vkCreateFence");
}

// ---- Present (WSI) mode ----------------------------------------------------

bool VulkanRenderer::createPresentSupport() {
  if (!vkCheck(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice_,
                                                        surface_, &surfaceCaps_),
                "vkGetPhysicalDeviceSurfaceCapabilitiesKHR")) {
    return false;
  }
  // Pick a swapchain format the driver presents well. RADV reports a short
  // list; prefer an 8888 color format (with or without alpha).
  uint32_t fCount = 0;
  if (vkCheck(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice_, surface_,
                                                  &fCount, nullptr),
              "vkGetPhysicalDeviceSurfaceFormatsKHR") &&
      fCount > 0) {
    std::vector<VkSurfaceFormatKHR> formats(fCount);
    if (vkCheck(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice_, surface_,
                                                    &fCount, formats.data()),
                "vkGetPhysicalDeviceSurfaceFormatsKHR(list)")) {
      static const VkFormat kPreferred[] = {
          VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
          VK_FORMAT_B8G8R8A8_SRGB,  VK_FORMAT_R8G8B8A8_SRGB};
      bool chosen = false;
      for (VkFormat want : kPreferred) {
        for (const VkSurfaceFormatKHR &f : formats) {
          if (f.format == want) {
            presentFormat_ = want;
            chosen = true;
            break;
          }
        }
        if (chosen) {
          break;
        }
      }
      if (!chosen) {
        presentFormat_ = formats[0].format;
      }
    }
  }
  if (presentFormat_ == VK_FORMAT_UNDEFINED) {
    presentFormat_ = VK_FORMAT_B8G8R8A8_UNORM;
  }
  // Vsync (FIFO) present mode; fall back to the first reported mode.
  uint32_t mCount = 0;
  if (vkCheck(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice_,
                                                       surface_, &mCount, nullptr),
              "vkGetPhysicalDeviceSurfacePresentModesKHR") &&
      mCount > 0) {
    std::vector<VkPresentModeKHR> modes(mCount);
    if (vkCheck(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice_,
                                                        surface_, &mCount,
                                                        modes.data()),
                "vkGetPhysicalDeviceSurfacePresentModesKHR(list)")) {
      for (VkPresentModeKHR m : modes) {
        if (m == VK_PRESENT_MODE_FIFO_KHR) {
          presentModeKind_ = m;
          break;
        }
      }
    }
  }
  return true;
}

bool VulkanRenderer::createSwapchain() {
  const VkSurfaceCapabilitiesKHR &caps = surfaceCaps_;
  uint32_t w = width_;
  if (w < caps.minImageExtent.width) {
    w = caps.minImageExtent.width;
  }
  if (caps.maxImageExtent.width > 0 && w > caps.maxImageExtent.width) {
    w = caps.maxImageExtent.width;
  }
  uint32_t h = height_;
  if (h < caps.minImageExtent.height) {
    h = caps.minImageExtent.height;
  }
  if (caps.maxImageExtent.height > 0 && h > caps.maxImageExtent.height) {
    h = caps.maxImageExtent.height;
  }
  swapWidth_ = w;
  swapHeight_ = h;

  uint32_t count = 3;
  if (caps.minImageCount > count) {
    count = caps.minImageCount;
  }
  if (caps.maxImageCount > 0 && count > caps.maxImageCount) {
    count = caps.maxImageCount;
  }

  VkSwapchainCreateInfoKHR info{};
  info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  info.surface = surface_;
  info.minImageCount = count;
  info.imageFormat = presentFormat_;
  info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  info.imageExtent = VkExtent2D{w, h};
  info.imageArrayLayers = 1;
  info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  info.queueFamilyIndexCount = 0;
  info.preTransform = caps.currentTransform;
  info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  info.presentMode = presentModeKind_;
  info.clipped = VK_TRUE;
  info.oldSwapchain = VK_NULL_HANDLE;
  if (!vkCheck(vkCreateSwapchainKHR(device_, &info, nullptr, &swapchain_),
                "vkCreateSwapchainKHR")) {
    return false;
  }
  uint32_t imgCount = 0;
  if (!vkCheck(vkGetSwapchainImagesKHR(device_, swapchain_, &imgCount, nullptr),
                "vkGetSwapchainImagesKHR(count)")) {
    return false;
  }
  std::vector<VkImage> images(imgCount);
  if (!vkCheck(vkGetSwapchainImagesKHR(device_, swapchain_, &imgCount,
                                      images.data()),
                "vkGetSwapchainImagesKHR")) {
    return false;
  }
  presentTargets_.assign(imgCount, PresentTarget{});
  for (uint32_t i = 0; i < imgCount; ++i) {
    presentTargets_[i].image = images[i];
  }
  return true;
}

bool VulkanRenderer::createPresentRenderPass() {
  VkAttachmentDescription color{};
  color.format = presentFormat_;
  color.samples = VK_SAMPLE_COUNT_1_BIT;
  color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  if (depthFormat_ == VK_FORMAT_UNDEFINED) {
    depthFormat_ = findDepthFormat();
  }
  if (depthFormat_ == VK_FORMAT_UNDEFINED) {
    std::fprintf(stderr,
                 "[VulkanRenderer] no depth format with attachment support\n");
    return false;
  }
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
  return vkCheck(vkCreateRenderPass(device_, &info, nullptr,
                                    &presentRenderPass_),
                  "vkCreateRenderPass(present)");
}

bool VulkanRenderer::createPresentTargets() {
  prevPresentImage_ = -1;
  bool ok = true;
  VkImageAspectFlags depthAspect = VK_IMAGE_ASPECT_DEPTH_BIT;
  if (depthFormat_ == VK_FORMAT_D24_UNORM_S8_UINT ||
      depthFormat_ == VK_FORMAT_D32_SFLOAT_S8_UINT) {
    depthAspect |= VK_IMAGE_ASPECT_STENCIL_BIT;
  }
  for (PresentTarget &t : presentTargets_) {
    // Color view for this swapchain image.
    VkImageViewCreateInfo view{};
    view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view.image = t.image;
    view.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view.format = presentFormat_;
    view.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    if (!vkCheck(vkCreateImageView(device_, &view, nullptr, &t.view),
                  "vkCreateImageView(present)")) {
      ok = false;
      break;
    }
    if (!createImage(swapWidth_, swapHeight_, depthFormat_,
                     VK_IMAGE_TILING_OPTIMAL,
                     VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &t.depthImage,
                     &t.depthMemory)) {
      ok = false;
      break;
    }
    view.image = t.depthImage;
    view.format = depthFormat_;
    view.subresourceRange.aspectMask = depthAspect;
    if (!vkCheck(vkCreateImageView(device_, &view, nullptr, &t.depthView),
                  "vkCreateImageView(present depth)")) {
      ok = false;
      break;
    }
    const VkImageView views[2] = {t.view, t.depthView};
    VkFramebufferCreateInfo fb{};
    fb.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fb.renderPass = presentRenderPass_;
    fb.attachmentCount = 2;
    fb.pAttachments = views;
    fb.width = swapWidth_;
    fb.height = swapHeight_;
    fb.layers = 1;
    if (!vkCheck(vkCreateFramebuffer(device_, &fb, nullptr, &t.framebuffer),
                  "vkCreateFramebuffer(present)")) {
      ok = false;
      break;
    }
    VkFenceCreateInfo fence{};
    fence.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VkSemaphoreCreateInfo sem{};
    sem.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    if (!vkCheck(vkCreateFence(device_, &fence, nullptr, &t.fence),
                  "vkCreateFence(present)") ||
        !vkCheck(vkCreateSemaphore(device_, &sem, nullptr, &t.present),
                  "vkCreateSemaphore(present)")) {
      ok = false;
      break;
    }
  }
  if (!ok) {
    destroyPresentTargets();
    return false;
  }
  if (presentAcquire_ == VK_NULL_HANDLE) {
    VkSemaphoreCreateInfo sem{};
    sem.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    if (!vkCheck(vkCreateSemaphore(device_, &sem, nullptr, &presentAcquire_),
                  "vkCreateSemaphore(presentAcquire)")) {
      destroyPresentTargets();
      return false;
    }
  }
  return true;
}

void VulkanRenderer::destroyPresentTargets() {
  // Any submitted present frame must finish before we tear down its buffers.
  if (device_ != VK_NULL_HANDLE) {
    vkDeviceWaitIdle(device_);
  }
  prevPresentImage_ = -1;
  for (PresentTarget &t : presentTargets_) {
    if (t.present != VK_NULL_HANDLE) {
      vkDestroySemaphore(device_, t.present, nullptr);
      t.present = VK_NULL_HANDLE;
    }
    if (t.fence != VK_NULL_HANDLE) {
      vkDestroyFence(device_, t.fence, nullptr);
      t.fence = VK_NULL_HANDLE;
    }
    if (t.framebuffer != VK_NULL_HANDLE) {
      vkDestroyFramebuffer(device_, t.framebuffer, nullptr);
      t.framebuffer = VK_NULL_HANDLE;
    }
    if (t.depthView != VK_NULL_HANDLE) {
      vkDestroyImageView(device_, t.depthView, nullptr);
      t.depthView = VK_NULL_HANDLE;
    }
    if (t.depthImage != VK_NULL_HANDLE) {
      vkDestroyImage(device_, t.depthImage, nullptr);
      t.depthImage = VK_NULL_HANDLE;
    }
    if (t.depthMemory != VK_NULL_HANDLE) {
      vkFreeMemory(device_, t.depthMemory, nullptr);
      t.depthMemory = VK_NULL_HANDLE;
    }
    if (t.view != VK_NULL_HANDLE) {
      vkDestroyImageView(device_, t.view, nullptr);
      t.view = VK_NULL_HANDLE;
    }
    t.image = VK_NULL_HANDLE;
  }
  presentTargets_.clear();
}

void VulkanRenderer::destroyPresentSupport() {
  if (device_ != VK_NULL_HANDLE) {
    destroyPresentTargets();
    if (presentAcquire_ != VK_NULL_HANDLE) {
      vkDestroySemaphore(device_, presentAcquire_, nullptr);
      presentAcquire_ = VK_NULL_HANDLE;
    }
    if (swapchain_ != VK_NULL_HANDLE) {
      vkDestroySwapchainKHR(device_, swapchain_, nullptr);
      swapchain_ = VK_NULL_HANDLE;
    }
    if (presentRenderPass_ != VK_NULL_HANDLE) {
      vkDestroyRenderPass(device_, presentRenderPass_, nullptr);
      presentRenderPass_ = VK_NULL_HANDLE;
    }
    if (presentPipeline_ != VK_NULL_HANDLE) {
      vkDestroyPipeline(device_, presentPipeline_, nullptr);
      presentPipeline_ = VK_NULL_HANDLE;
    }
    if (presentLitPipeline_ != VK_NULL_HANDLE) {
      vkDestroyPipeline(device_, presentLitPipeline_, nullptr);
      presentLitPipeline_ = VK_NULL_HANDLE;
    }
  }
  if (presentMode_ && surface_ != VK_NULL_HANDLE && instance_ != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(instance_, surface_, nullptr);
  }
  surface_ = VK_NULL_HANDLE;
  presentMode_ = false;
}

bool VulkanRenderer::beginPresentFrame(uint32_t *imageIndex, float r, float g,
                                       float b) {
  if (!initialized_ || presentTargets_.empty()) {
    return false;
  }
  const uint32_t n = static_cast<uint32_t>(presentTargets_.size());
  // The command buffer and the shared acquire semaphore are singletons; the
  // previously submitted frame must finish before we reuse them.
  if (prevPresentImage_ >= 0) {
    if (!vkCheck(vkWaitForFences(
              device_, 1, &presentTargets_[prevPresentImage_].fence, VK_TRUE,
              UINT64_MAX),
              "vkWaitForFences(prevPresent)")) {
      return false;
    }
  }
  uint32_t idx = 0;
  // Acquire first; the image's own fence/semaphores gate this frame.
  VkResult ar = vkAcquireNextImageKHR(device_, swapchain_, UINT64_MAX,
                                      presentAcquire_, VK_NULL_HANDLE, &idx);
  if (ar != VK_SUCCESS && ar != VK_SUBOPTIMAL_KHR) {
    logError("vkAcquireNextImageKHR", ar);
    return false;
  }
  if (idx >= n) {
    idx = 0;
  }
  activeImage_ = idx;
  PresentTarget &t = presentTargets_[idx];
  if (!vkCheck(vkWaitForFences(device_, 1, &t.fence, VK_TRUE, UINT64_MAX),
                "vkWaitForFences(present)")) {
    return false;
  }
  if (!vkCheck(vkResetFences(device_, 1, &t.fence),
                "vkResetFences(present)")) {
    return false;
  }

  vkResetCommandBuffer(commandBuffer_, 0);
  VkCommandBufferBeginInfo begin{};
  begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  if (!vkCheck(vkBeginCommandBuffer(commandBuffer_, &begin),
                "vkBeginCommandBuffer(present)")) {
    return false;
  }
  VkClearValue clear[2]{};
  clear[0].color = {{r, g, b, 1.0F}};
  clear[1].depthStencil = {1.0F, 0};
  VkRenderPassBeginInfo pass{};
  pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  pass.renderPass = presentRenderPass_;
  pass.framebuffer = presentTargets_[idx].framebuffer;
  pass.renderArea = {{0, 0}, {swapWidth_, swapHeight_}};
  pass.clearValueCount = 2;
  pass.pClearValues = clear;
  vkCmdBeginRenderPass(commandBuffer_, &pass, VK_SUBPASS_CONTENTS_INLINE);
  recording_ = true;
  activePipeline_ = presentPipeline_;
  activeLitPipeline_ = presentLitPipeline_;
  if (imageIndex != nullptr) {
    *imageIndex = idx;
  }
  return true;
}

void VulkanRenderer::endPresentFrame() {
  if (!recording_) {
    return;
  }
  vkCmdEndRenderPass(commandBuffer_);
  recording_ = false;
  if (!vkCheck(vkEndCommandBuffer(commandBuffer_),
                "vkEndCommandBuffer(present)")) {
    return;
  }
  PresentTarget &t = presentTargets_[activeImage_];
  VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  VkSubmitInfo submit{};
  submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit.commandBufferCount = 1;
  submit.pCommandBuffers = &commandBuffer_;
  submit.waitSemaphoreCount = 1;
  submit.pWaitSemaphores = &presentAcquire_;
  submit.pWaitDstStageMask = &waitStage;
  submit.signalSemaphoreCount = 1;
  submit.pSignalSemaphores = &t.present;
  if (!vkCheck(vkQueueSubmit(graphicsQueue_, 1, &submit, t.fence),
                "vkQueueSubmit(present)")) {
    return;
  }
  prevPresentImage_ = activeImage_;
  VkPresentInfoKHR present{};
  present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present.waitSemaphoreCount = 1;
  present.pWaitSemaphores = &t.present;
  present.swapchainCount = 1;
  present.pSwapchains = &swapchain_;
  present.pImageIndices = &activeImage_;
  VkResult pr = vkQueuePresentKHR(graphicsQueue_, &present);
  if (pr == VK_ERROR_OUT_OF_DATE_KHR || pr == VK_SUBOPTIMAL_KHR) {
    // Surface resized: rebuild the swapchain at its current size.
    resizePresent(width_, height_);
  } else if (pr != VK_SUCCESS) {
    logError("vkQueuePresentKHR", pr);
  }
}

bool VulkanRenderer::resizePresent(uint32_t width, uint32_t height) {
  if (!initialized_ || !presentMode_) {
    return false;
  }
  width_ = width;
  height_ = height;
  vkDeviceWaitIdle(device_);
  destroyPresentTargets();
  if (swapchain_ != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(device_, swapchain_, nullptr);
    swapchain_ = VK_NULL_HANDLE;
  }
  // The present pipelines bake their viewport from width_/height_; rebuild
  // them for the new size (the present render pass is size-agnostic).
  if (presentPipeline_ != VK_NULL_HANDLE) {
    vkDestroyPipeline(device_, presentPipeline_, nullptr);
    presentPipeline_ = VK_NULL_HANDLE;
  }
  if (presentLitPipeline_ != VK_NULL_HANDLE) {
    vkDestroyPipeline(device_, presentLitPipeline_, nullptr);
    presentLitPipeline_ = VK_NULL_HANDLE;
  }
  if (!createSwapchain() ||
      !createPipelinePair(presentRenderPass_, presentPipeline_,
                          presentLitPipeline_) ||
      !createPresentTargets()) {
    std::fprintf(stderr, "[VulkanRenderer] swapchain resize failed\n");
    shutdown();
    return false;
  }
  std::fprintf(stderr, "[VulkanRenderer] swapchain resized to %ux%u\n",
                swapWidth_, swapHeight_);
  return true;
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
                    activeLitPipeline_);
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

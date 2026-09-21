// Vulkan offscreen backend for openspore::IRenderer. Clean-room implementation.
#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include "renderer/Renderer.hpp"

namespace openspore {

class VulkanRenderer : public IRenderer {
public:
  VulkanRenderer();
  ~VulkanRenderer() override;

  VulkanRenderer(const VulkanRenderer &) = delete;
  VulkanRenderer &operator=(const VulkanRenderer &) = delete;

  bool init(uint32_t width, uint32_t height) override;
  void shutdown() override;

  MeshHandle createMesh(const Vertex *vertices, size_t vertexCount,
                        const uint32_t *indices, size_t indexCount) override;
  void destroyMesh(MeshHandle mesh) override;

  TextureHandle createTexture(const ImageRGBA &image) override;
  void destroyTexture(TextureHandle texture) override;

  MeshHandle createTexMesh(const TexVertex *vertices, size_t vertexCount,
                           const uint32_t *indices, size_t indexCount) override;
  void destroyTexMesh(MeshHandle mesh);

  void beginFrame(float r, float g, float b, float a) override;
  void drawMesh(MeshHandle mesh) override;
  void drawTextured(MeshHandle mesh, TextureHandle texture,
                    const MaterialState &material) override;
  void endFrame() override;

  ImageRGBA readbackPixels() override;

  // Human-readable name of the physical device selected at init().
  const std::string &deviceName() const { return deviceName_; }

private:
  struct Mesh {
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexMemory = VK_NULL_HANDLE;
    uint32_t indexCount = 0;
    bool valid = false;
  };
  struct TexMesh {
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexMemory = VK_NULL_HANDLE;
    uint32_t indexCount = 0;
    bool valid = false;
  };
  struct Texture {
    VkImage image = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkImageView view = VK_NULL_HANDLE;
    VkDescriptorSet set = VK_NULL_HANDLE;
    uint32_t width = 0;
    uint32_t height = 0;
    bool valid = false;
  };

  bool createInstance();
  bool pickPhysicalDevice();
  bool createDevice();
  bool createCommandPool();
  bool createTargets();
  bool createRenderPass();
  bool createPipeline();
  bool createTextureSupport();
  bool createLitPipeline();
  bool createSync();
  void submitOneTime(VkCommandBuffer cmd);

  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags props);
  bool createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                    VkMemoryPropertyFlags props, VkBuffer *outBuffer,
                    VkDeviceMemory *outMemory);
  bool createImage(uint32_t w, uint32_t h, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags props, VkImage *outImage,
                   VkDeviceMemory *outMemory);
  VkFormat findDepthFormat();
  void transitionImage(VkImage image, VkImageLayout oldLayout,
                       VkImageLayout newLayout, VkImageAspectFlags aspect,
                       VkAccessFlags srcAccess, VkAccessFlags dstAccess,
                       VkPipelineStageFlags srcStage,
                       VkPipelineStageFlags dstStage);
   void destroyMeshResources(Mesh &mesh);
   void destroyTextureResources(Texture &tex);
   void destroyTexMeshResources(TexMesh &tex);

   uint32_t width_ = 0;
  uint32_t height_ = 0;
  bool initialized_ = false;
  bool recording_ = false;
  std::string deviceName_;

  VkInstance instance_ = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
  VkDevice device_ = VK_NULL_HANDLE;
  uint32_t graphicsQueueFamily_ = 0;
  VkQueue graphicsQueue_ = VK_NULL_HANDLE;
  VkCommandPool commandPool_ = VK_NULL_HANDLE;
  VkCommandBuffer commandBuffer_ = VK_NULL_HANDLE;
  VkFence frameFence_ = VK_NULL_HANDLE;

  VkImage colorImage_ = VK_NULL_HANDLE;
  VkDeviceMemory colorMemory_ = VK_NULL_HANDLE;
  VkImageView colorView_ = VK_NULL_HANDLE;
  VkImage depthImage_ = VK_NULL_HANDLE;
  VkDeviceMemory depthMemory_ = VK_NULL_HANDLE;
  VkImageView depthView_ = VK_NULL_HANDLE;
  VkFormat depthFormat_ = VK_FORMAT_UNDEFINED;
  VkImage readbackImage_ = VK_NULL_HANDLE;
  VkDeviceMemory readbackMemory_ = VK_NULL_HANDLE;

  VkRenderPass renderPass_ = VK_NULL_HANDLE;
  VkFramebuffer framebuffer_ = VK_NULL_HANDLE;
  VkPipelineLayout pipelineLayout_ = VK_NULL_HANDLE;
  VkPipeline pipeline_ = VK_NULL_HANDLE;

  VkSampler texSampler_ = VK_NULL_HANDLE;
  VkDescriptorSetLayout texSetLayout_ = VK_NULL_HANDLE;
  VkDescriptorPool descPool_ = VK_NULL_HANDLE;
  VkPipelineLayout litPipelineLayout_ = VK_NULL_HANDLE;
  VkPipeline litPipeline_ = VK_NULL_HANDLE;

  std::vector<Mesh> meshes_;
  std::vector<TexMesh> texMeshes_;
  std::vector<Texture> textures_;
};

} // namespace openspore

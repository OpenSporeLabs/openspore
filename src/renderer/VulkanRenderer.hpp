// Vulkan offscreen + WSI backend for openspore::IRenderer.
// Clean-room implementation. X11 (Xlib) surface support: this box runs X.Org;
// SDL3 creates its window surface on the same X11 platform.
#define VK_USE_PLATFORM_XLIB_KHR

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

  // ---- Present (WSI) mode, Obj17b -----------------------------------------
  // Additive path: renders into a swapchain on an app-provided surface
  // (SDL window) and presents vsynced. The offscreen init() path above is
  // untouched. beginSurfaceMode() creates the instance with the platform WSI
  // extensions (from SDL_Vulkan_GetInstanceExtensions); the app then creates
  // its surface against vkInstance() and passes it to initPresent().
  // The renderer takes ownership of the surface (destroys it in shutdown()).
  bool beginSurfaceMode(const char *const *extNames, uint32_t extCount);
  VkInstance vkInstance() const { return instance_; }
  bool initPresent(uint32_t width, uint32_t height, VkSurfaceKHR surface);
  // Acquires the next swapchain image, opens the pass into it cleared to
  // (r,g,b,a); draws go through the same drawMesh/drawTextured calls as the
  // offscreen path.
  bool beginPresentFrame(uint32_t *imageIndex, float r, float g, float b);
  // Closes the pass, submits (acquire-wait / present-signal) and presents
  // with the vsync (FIFO) present mode.
  void endPresentFrame();
  // Rebuilds the swapchain + per-image targets at the new size.
  bool resizePresent(uint32_t width, uint32_t height);
  uint32_t presentImageCount() const {
    return static_cast<uint32_t>(presentTargets_.size());
  }

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
  // Builds both the flat-color and the normal-lit textured pipelines against
  // the given render pass (offscreen and present paths each call this).
  bool createPipelinePair(VkRenderPass pass, VkPipeline &plain, VkPipeline &lit);
  bool createTextureSupport();
  bool createSync();

  bool createPresentSupport();
  bool createSwapchain();
  bool createPresentRenderPass();
  bool createPresentTargets();
  void destroyPresentTargets();
  void destroyPresentSupport();
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

  // Present (WSI) mode state.
  bool presentMode_ = false;
  VkSurfaceKHR surface_ = VK_NULL_HANDLE;
  std::vector<const char *> surfaceExtNames_;
  VkSurfaceCapabilitiesKHR surfaceCaps_{};
  VkFormat presentFormat_ = VK_FORMAT_UNDEFINED;
  VkPresentModeKHR presentModeKind_ = VK_PRESENT_MODE_FIFO_KHR;
  VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
  uint32_t swapWidth_ = 0;
  uint32_t swapHeight_ = 0;

  struct PresentTarget {
    VkImage image = VK_NULL_HANDLE;
    VkImageView view = VK_NULL_HANDLE;
    VkImage depthImage = VK_NULL_HANDLE;
    VkDeviceMemory depthMemory = VK_NULL_HANDLE;
    VkImageView depthView = VK_NULL_HANDLE;
    VkFramebuffer framebuffer = VK_NULL_HANDLE;
    VkFence fence = VK_NULL_HANDLE;
    VkSemaphore present = VK_NULL_HANDLE;
  };
  std::vector<PresentTarget> presentTargets_;
  // One shared acquire semaphore: vkAcquireNextImageKHR signals it; the index
  // of the acquired image is only known after the call, so per-image acquire
  // semaphores are not usable.
  VkSemaphore presentAcquire_ = VK_NULL_HANDLE;
  VkRenderPass presentRenderPass_ = VK_NULL_HANDLE;
  VkPipeline presentPipeline_ = VK_NULL_HANDLE;
  VkPipeline presentLitPipeline_ = VK_NULL_HANDLE;

  // Pipelines active for the frame being recorded (offscreen or present).
  VkPipeline activePipeline_ = VK_NULL_HANDLE;
  VkPipeline activeLitPipeline_ = VK_NULL_HANDLE;
  uint32_t activeImage_ = 0;
  // Image whose frame was last submitted; its fence gates reuse of the shared
  // command buffer + acquire semaphore (-1 = none submitted yet).
  int prevPresentImage_ = -1;

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

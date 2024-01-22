#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <iostream>
#include <cstring>
#include <stdio.h>

int main()
{
      // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }
    
    if (!glfwVulkanSupported())
    {
      std::cout << "vulkan not available, at least for compute" << std::endl;
    }
    PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)
      glfwGetInstanceProcAddress(NULL, "vkCreateInstance");

    PFN_vkCreateDevice pfnCreateDevice = (PFN_vkCreateDevice)
      glfwGetInstanceProcAddress(VkInstance, "vkCreateDevice");

    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)
      glfwGetInstanceProcAddress(VkInstance, "vkGetDeviceProcAddr");

    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);

    VkInstanceCreateInfo ici;

    memset(&ici, 0, sizeof(ici));
    ici.enabledExtensionCount = count;
    ici.ppEnabledExtensionNames = extensions;

    if (!glfwGetPhysicalDevicePresentationSupport(VkInstance, VkPhysicalDevice, queue_family_index))
    {
      // Queue family supports image presentation
      std::cout << "queue family does not support image presentation" << std::endl;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Window Title", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    VkSurfaceKHR surface;
    VkResult err = glfwCreateWindowSurface(VkInstance, window, NULL, &surface);
    if (err)
    {
      // Window surface creation failed
      std::cout << "window surface creation failed with: " << err << std::endl;
    }

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <ZEngine/Rendering/Swapchain.h>
#include <ZEngine/Windows/CoreWindow.h>
#include <ZEngine/Windows/WindowConfiguration.h>
#include <ZEngine/ZEngineDef.h>

namespace Tetragrama
{
    class EditorWindow : public ZEngine::Windows::CoreWindow
    {
    public:
        EditorWindow(const ZEngine::Windows::WindowConfiguration& configuration);
        virtual ~EditorWindow();

        uint32_t                                        GetHeight() const override;
        uint32_t                                        GetWidth() const override;
        std::string_view                                GetTitle() const override;
        bool                                            IsMinimized() const override;
        void                                            SetTitle(std::string_view title) override;
        bool                                            IsVSyncEnable() const override;
        void                                            SetVSync(bool value) override;
        void                                            SetCallbackFunction(const EventCallbackFn& callback) override;
        void*                                           GetNativeWindow() const override;
        virtual const ZEngine::Windows::WindowProperty& GetWindowProperty() const override;

        virtual void  Initialize() override;
        virtual void  InitializeLayer() override;
        virtual void  Deinitialize() override;
        virtual void  PollEvent() override;
        virtual float GetTime() override;
        virtual float GetDeltaTime() override;
        virtual void  Update(ZEngine::Core::TimeStep delta_time) override;
        virtual void  Render() override;

        virtual bool                                CreateSurface(void* instance, void** out_window_surface) override;
        virtual std::vector<std::string>            GetRequiredExtensionLayers() override;
        ZEngine::Ref<ZEngine::Rendering::Swapchain> GetSwapchain() const override;

    public:
        bool OnEvent(ZEngine::Core::CoreEvent& event) override;

    protected:
        virtual bool OnKeyPressed(ZEngine::Windows::Events::KeyPressedEvent&) override;
        virtual bool OnKeyReleased(ZEngine::Windows::Events::KeyReleasedEvent&) override;

        virtual bool OnMouseButtonPressed(ZEngine::Windows::Events::MouseButtonPressedEvent&) override;
        virtual bool OnMouseButtonReleased(ZEngine::Windows::Events::MouseButtonReleasedEvent&) override;
        virtual bool OnMouseButtonMoved(ZEngine::Windows::Events::MouseButtonMovedEvent&) override;
        virtual bool OnMouseButtonWheelMoved(ZEngine::Windows::Events::MouseButtonWheelEvent&) override;

        virtual bool OnTextInputRaised(ZEngine::Windows::Events::TextInputEvent&) override;

        virtual bool OnWindowClosed(ZEngine::Windows::Events::WindowClosedEvent&) override;
        virtual bool OnWindowResized(ZEngine::Windows::Events::WindowResizedEvent&) override;
        virtual bool OnWindowMinimized(ZEngine::Windows::Events::WindowMinimizedEvent&) override;
        virtual bool OnWindowMaximized(ZEngine::Windows::Events::WindowMaximizedEvent&) override;
        virtual bool OnWindowRestored(ZEngine::Windows::Events::WindowRestoredEvent&) override;

        static void __OnGlfwWindowClose(GLFWwindow*);
        static void __OnGlfwWindowResized(GLFWwindow*, int width, int height);
        static void __OnGlfwWindowMaximized(GLFWwindow*, int maximized);
        static void __OnGlfwWindowMinimized(GLFWwindow*, int minimized);

        static void __OnGlfwMouseButtonRaised(GLFWwindow*, int button, int action, int mods);
        static void __OnGlfwMouseScrollRaised(GLFWwindow*, double xoffset, double yoffset);
        static void __OnGlfwCursorMoved(GLFWwindow*, double xpos, double ypos);
        static void __OnGlfwTextInputRaised(GLFWwindow*, unsigned int character);

        static void __OnGlfwKeyboardRaised(GLFWwindow*, int key, int scancode, int action, int mods);

        static void __OnGlfwFrameBufferSizeChanged(GLFWwindow*, int width, int height);

    private:
        GLFWwindow*                                 m_native_window{nullptr};
        ZEngine::Ref<ZEngine::Rendering::Swapchain> m_swapchain;
    };

} // namespace Tetragrama

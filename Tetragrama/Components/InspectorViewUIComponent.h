#pragma once
#include <Message.h>
#include <UIComponent.h>
#include <ZEngine/Rendering/Scenes/GraphicScene.h>
#include <ZEngine/ZEngineDef.h>
#include <imgui.h>
#include <future>
#include <mutex>
#include <string>

namespace Tetragrama::Components
{
    class InspectorViewUIComponent : public UIComponent
    {
    public:
        InspectorViewUIComponent(std::string_view name = "Inspector", bool visibility = true);
        virtual ~InspectorViewUIComponent();

        void Update(ZEngine::Core::TimeStep dt) override;

        virtual void Render() override;

    public:
        std::future<void> SceneAvailableMessageHandlerAsync(Messengers::GenericMessage<ZEngine::Ref<ZEngine::Rendering::Scenes::GraphicScene>>&);
        std::future<void> SceneEntitySelectedMessageHandlerAsync(Messengers::GenericMessage<ZEngine::Rendering::Scenes::SceneEntity>&);
        std::future<void> SceneEntityUnSelectedMessageHandlerAsync(Messengers::EmptyMessage&);
        std::future<void> SceneEntityDeletedMessageHandlerAsync(Messengers::EmptyMessage&);
        std::future<void> RequestStartOrPauseRenderMessageHandlerAsync(Messengers::GenericMessage<bool>&);

    private:
        ImGuiTreeNodeFlags                                         m_node_flag;
        bool                                                       m_recieved_unselected_request{false};
        bool                                                       m_recieved_deleted_request{false};
        ZEngine::WeakRef<ZEngine::Rendering::Scenes::GraphicScene> m_active_scene;
        ZEngine::Rendering::Scenes::SceneEntity                    m_scene_entity;
        std::mutex                                                 m_mutex;
    };
} // namespace Tetragrama::Components

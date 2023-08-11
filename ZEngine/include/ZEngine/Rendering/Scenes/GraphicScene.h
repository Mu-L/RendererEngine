﻿#pragma once
#include <vector>
#include <functional>
#include <future>
#include <Rendering/Cameras/Camera.h>
#include <ZEngineDef.h>
#include <Core/IRenderable.h>
#include <Core/IInitializable.h>
#include <Core/IUpdatable.h>
#include <Controllers/ICameraController.h>
#include <Rendering/Meshes/Mesh.h>
#include <Rendering/Renderers/GraphicRenderer.h>
#include <Rendering/Entities/GraphicSceneEntity.h>
#include <Window/CoreWindow.h>
#include <entt/entt.hpp>
#include <uuid.h>
#include <mutex>

namespace ZEngine::Serializers
{
    class GraphicScene3DSerializer;
}

namespace ZEngine::Rendering::Scenes
{
    class GraphicScene : public Core::IInitializable, public Core::IUpdatable, public Core::IRenderable, public Core::IEventable
    {

    public:
        GraphicScene()
        {
            m_entity_registry = CreateRef<entt::registry>();
        }

        virtual ~GraphicScene();

        void         Initialize() override;
        virtual void Deinitialize() override;
        void         Update(Core::TimeStep dt) override;
        virtual bool OnEvent(Event::CoreEvent&) override;
        virtual void Render() override;

        virtual void UploadFrameInfo(uint32_t frame_index, VkQueue& present_queue);

        virtual std::future<void> RequestNewSizeAsync(float, float);
        uint32_t     ToTextureRepresentation() const;

        void SetShouldReactToEvent(bool value);
        bool ShouldReactToEvent() const;

        void                             SetCameraController(const Ref<Controllers::ICameraController>& camera_controller);
        void                             SetWindowParent(const ZEngine::Ref<ZEngine::Window::CoreWindow>& window);
        Ref<ZEngine::Window::CoreWindow> GetWindowParent() const;

        Entities::GraphicSceneEntity GetPrimariyCameraEntity() const;

    public:
        Entities::GraphicSceneEntity CreateEntity(std::string_view entity_name = "empty entity");
        Entities::GraphicSceneEntity CreateEntity(uuids::uuid uuid, std::string_view entity_name = "empty entity");
        Entities::GraphicSceneEntity CreateEntity(std::string_view uuid_string, std::string_view entity_name = "empty entity");
        Entities::GraphicSceneEntity GetEntity(std::string_view entity_name);
        Entities::GraphicSceneEntity GetEntity(int mouse_pos_x, int mouse_pos_y);
        void                         RemoveEntity(const Entities::GraphicSceneEntity& entity);
        void                         RemoveAllEntities();
        void                         RemoveInvalidEntities();
        void                         InvalidateAllEntities();
        Ref<entt::registry>          GetRegistry() const;

        bool HasEntities() const;
        bool HasInvalidEntities() const;
        bool IsValidEntity(const Entities::GraphicSceneEntity&) const;

        int32_t                  AddMesh(Meshes::MeshVNext&& mesh);
        const Meshes::MeshVNext& GetMesh(int32_t mesh_id) const;
        Meshes::MeshVNext&       GetMesh(int32_t mesh_id);

        std::function<void(Renderers::Contracts::FramebufferViewLayout)> OnSceneRenderCompleted;

    protected:
        WeakRef<Controllers::ICameraController> m_camera_controller;
        WeakRef<Cameras::Camera>                m_scene_camera;
        std::vector<Meshes::MeshVNext>          m_mesh_vnext_list;

    private:
        bool                                          m_should_react_to_event{true};
        std::pair<float, float>                       m_scene_requested_size{0.0f, 0.0f};
        std::pair<float, float>                       m_last_scene_requested_size{0.0f, 0.0f};
        Ref<entt::registry>                           m_entity_registry;
        ZEngine::WeakRef<ZEngine::Window::CoreWindow> m_parent_window;
        mutable std::mutex                            m_mutex;

        friend class ZEngine::Serializers::GraphicScene3DSerializer;
    };
} // namespace ZEngine::Rendering::Scenes

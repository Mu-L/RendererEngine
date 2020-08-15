#pragma once

#include <memory>

#include "WindowProperty.h"
#include "../Event/CoreEvent.h"
#include "../Event/WindowClosedEvent.h"
#include "../Event/WindowResizeEvent.h"
#include "../Event/EventDispatcher.h"
#include "../Event/TextInputEvent.h"
#include "../Core/TimeStep.h"

#include "../Inputs/IKeyboardEventCallback.h"
#include "../Inputs/IMouseEventCallback.h"
#include "../Inputs/ITextInputEventCallback.h"


namespace Z_Engine {
	class Engine;
}


using namespace Z_Engine::Event;

namespace Z_Engine::Window {


	class CoreWindow : public Inputs::IKeyboardEventCallback, 
		Inputs::IMouseEventCallback, 
		Inputs::ITextInputEventCallback {

	public:
		using EventCallbackFn = std::function<void(CoreEvent&)>;

	public:
		CoreWindow() = default;
		virtual ~CoreWindow() = default;

		virtual unsigned int GetHeight()	const = 0;
		virtual unsigned int GetWidth()		const = 0;
		virtual const std::string& GetTitle()		const = 0;
		virtual bool IsVSyncEnable()		const = 0;
		virtual	void SetVSync(bool value) = 0;
		virtual void SetCallbackFunction(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void* GetNativeContext() const = 0;

		virtual const WindowProperty& GetWindowProperty() const = 0;
		
		virtual void SetAttachedEngine(Z_Engine::Engine* const engine) {
			m_engine = engine;
		}

		virtual void PollEvent() = 0;
		virtual void Update(Core::TimeStep delta_time) = 0;
		virtual void Render() = 0;


	public:
		virtual void OnEvent(Event::CoreEvent& event) = 0;

	protected:
		virtual bool OnWindowClosed(WindowClosedEvent&) = 0;
		virtual bool OnWindowResized(WindowResizeEvent&) = 0;


	protected:
		static const char* ATTACHED_PROPERTY;

		WindowProperty m_property;
		Z_Engine::Engine* m_engine { nullptr };
	};
		
	CoreWindow* Create(WindowProperty prop = {});

}
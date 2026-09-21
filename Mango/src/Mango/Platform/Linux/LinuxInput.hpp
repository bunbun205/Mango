#pragma once

#include "Mango/Core/Input.hpp"

namespace Mango{
	class LinuxInput: public Input {
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual void SetCursorModeImpl(CursorMode mode) override;
	};
} // Mango

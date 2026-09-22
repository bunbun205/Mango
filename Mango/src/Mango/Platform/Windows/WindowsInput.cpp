//
// Created by mayan on 9/22/2026.
//

#include "WindowsInput.hpp"

#ifdef MANGO_PLATFORM_WINDOWS

#include <Mango/Core/Application.hpp>

#include "Win32Keymap.hpp"

namespace Mango
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(KeyCode keycode) {
        int vk = MangoKeyCodeToWin32Code(keycode);
        if (vk == 0)
            return false;

        SHORT state = GetAsyncKeyState(vk);
        return (state & 0x8000) != 0;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(MouseButton button) {
        int vkButton;
        switch ((int)button) {
        case 0:  vkButton = VK_LBUTTON; break;
        case 1:  vkButton = VK_RBUTTON; break;
        case 2:  vkButton = VK_MBUTTON; break;
        default: vkButton = VK_LBUTTON; break;
        }
        SHORT state = GetAsyncKeyState(vkButton);
        return (state & 0x8000) != 0;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl() {
        POINT point;
        GetCursorPos(&point);

        HWND window = (HWND)Application::Get().GetWindow().GetNativeWindow();
        ScreenToClient(window, &point);

        return { (float)point.x, (float)point.y };
    }

    float WindowsInput::GetMouseXImpl() {
        auto [x, y] = GetMousePosImpl();
        return x;
    }
    float WindowsInput::GetMouseYImpl() {
        auto [x, y] = GetMousePosImpl();
        return y;
    }

    void WindowsInput::SetCursorModeImpl(CursorMode mode) {
        HWND window = (HWND)Application::Get().GetWindow().GetNativeWindow();

        switch ((int)mode) {
        case 0: { // Normal
            ClipCursor(nullptr);
            while (ShowCursor(TRUE) < 0);
            break;
        }
        case 1: { // Hidden
            while (ShowCursor(FALSE) >= 0);
            break;
        }
        case 2: { // Disabled — hidden and locked to the window's client area
            while (ShowCursor(FALSE) >= 0);

            RECT rect;
            GetClientRect(window, &rect);
            POINT topLeft{ rect.left, rect.top };
            POINT bottomRight{ rect.right, rect.bottom };
            ClientToScreen(window, &topLeft);
            ClientToScreen(window, &bottomRight);
            RECT clip{ topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
            ClipCursor(&clip);
            break;
        }
        }
    }
} // Mango

#endif
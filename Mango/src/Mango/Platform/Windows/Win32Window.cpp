//
// Created by mayan on 9/22/2026.
//

#include "Win32Window.hpp"

#ifdef MANGO_PLATFORM_WINDOWS

#include <windowsx.h>

#include "Mango/Core/Log.hpp"
#include <Mango/Core/Core.hpp>

#include "Mango/Events/ApplicationEvent.hpp"
#include "Mango/Events/KeyEvent.hpp"
#include "Mango/Events/MouseEvent.hpp"

#include "Win32Keymap.hpp"

namespace Mango
{
    static bool s_Win32ClassRegistered = false;
    static const wchar_t* s_WindowClassName = L"MangoWindowClass";

    Window* Window::Create(const WindowProps& props)
    {
        return new Win32Window(props);
    }

    Win32Window::Win32Window(const WindowProps& props)
    {
        Init(props);
    }

    Win32Window::~Win32Window()
    {
        Shutdown();
    }

    void Win32Window::OnUpdate()
    {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    void Win32Window::SetVSync(bool enabled)
    {
        m_Data.VSync = enabled;
    }

    bool Win32Window::IsVSync() const
    {
        return m_Data.VSync;
    }

    void Win32Window::Close()
    {
        WindowCloseEvent event;
        m_Data.EventCallback(event);
    }

    void Win32Window::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        HINSTANCE instance = GetModuleHandle(nullptr);

        if (!s_Win32ClassRegistered)
        {
            WNDCLASSW wc = {};

            wc.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
            {
                auto* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                if (!data)
                    return DefWindowProcW(hwnd, msg, wParam, lParam);

                switch (msg)
                {
                case WM_SIZE:
                    {
                        unsigned int width = LOWORD(wParam);
                        unsigned int height = HIWORD(wParam);
                        data->Width = width;
                        data->Height = height;
                        WindowResizeEvent event(width, height);
                        data->EventCallback(event);
                        return 0;
                    }

                case WM_CLOSE:
                    {
                        WindowCloseEvent event;
                        data->EventCallback(event);
                        return 0;
                    }

                case WM_KEYDOWN:
                case WM_SYSKEYDOWN:
                    {
                        auto keyCode = Win32ToMangoKeyCode(wParam, lParam);
                        if (keyCode)
                        {
                            bool repeat = (lParam & (1 << 30) != 0);
                            KeyPressedEvent event(*keyCode, repeat ? 1 : 0);
                            data->EventCallback(event);
                        }
                        return 0;
                    }

                case WM_KEYUP:
                case WM_SYSKEYUP: {
                    auto keyCode = Win32ToMangoKeyCode(wParam, lParam);
                    if (keyCode) {
                        KeyReleasedEvent event(*keyCode);
                        data->EventCallback(event);
                    }
                    return 0;
                }
                case WM_LBUTTONDOWN: {
                    MouseButtonPressedEvent event((MouseButton)0);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_LBUTTONUP: {
                    MouseButtonReleasedEvent event((MouseButton)0);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_RBUTTONDOWN: {
                    MouseButtonPressedEvent event((MouseButton)1);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_RBUTTONUP: {
                    MouseButtonReleasedEvent event((MouseButton)1);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_MBUTTONDOWN: {
                    MouseButtonPressedEvent event((MouseButton)2);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_MBUTTONUP: {
                    MouseButtonReleasedEvent event((MouseButton)2);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_MOUSEWHEEL: {
                    float delta = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
                    MouseScrolledEvent event(0.0f, delta);
                    data->EventCallback(event);
                    return 0;
                }
                case WM_MOUSEMOVE: {
                    float x = (float)GET_X_LPARAM(lParam);
                    float y = (float)GET_Y_LPARAM(lParam);
                    MouseMovedEvent event(x, y);
                    data->EventCallback(event);
                    return 0;
                }
                }

                return DefWindowProcW(hwnd, msg, wParam, lParam);
            };

            wc.hInstance = instance;
            wc.lpszClassName = s_WindowClassName;
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

            ATOM registered = RegisterClassW(&wc);
            MANGO_CORE_ASSERT(registered, "Could not register Win32 window class!");
            s_Win32ClassRegistered = true;
        }

        RECT rect = { 0, 0, (LONG)props.Width, (LONG)props.Height };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        int titleLen = MultiByteToWideChar(CP_UTF8, 0, props.Title.c_str(), -1, nullptr, 0);
        std::wstring wideTitle(titleLen, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, props.Title.c_str(), -1, wideTitle.data(), titleLen);

        HWND hwnd = CreateWindowExW(
            0,
            s_WindowClassName,
            wideTitle.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            rect.right - rect.left, rect.bottom - rect.top,
            nullptr, nullptr, instance, nullptr
        );
        MANGO_CORE_ASSERT(hwnd, "Window could not be created!");
        m_Window = (void*)hwnd;

        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)&m_Data);
        SetVSync(true);

        ShowWindow(hwnd, SW_SHOW);
    }

    void Win32Window::Shutdown()
    {
        DestroyWindow((HWND)m_Window);
    }
} // Mango

#endif
//
// Created by mayan on 9/22/2026.
//

#pragma once

#include <string>

#include "Mango/Core/Window.hpp"

namespace Mango
{
    class Win32Window : public Window
    {
    public:
        Win32Window(const WindowProps& props);
        virtual ~Win32Window();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        virtual void* GetNativeWindow() override { return m_Window; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void Close() override;
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        void* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
} // Mango


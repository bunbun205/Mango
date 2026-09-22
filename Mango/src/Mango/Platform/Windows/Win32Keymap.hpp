//
// Created by mayan on 9/22/2026.
//

#pragma once

#include <Mango/Core/KeyCodes.hpp>

#ifdef MANGO_PLATFORM_WINDOWS

#include <Windows.h>
#include <optional>

namespace Mango
{
    std::optional<KeyCode> Win32ToMangoKeyCode(WPARAM wParam, LPARAM lParam);

    int MangoKeyCodeToWin32Code(KeyCode keyCode);
} // Mango

#endif


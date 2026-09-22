//
// Created by mayan on 9/22/2026.
//

#include "Win32Keymap.hpp"

namespace Mango
{
    static std::optional<KeyCode> Win32ToMangoKeyCodeTable(int vk)
    {
        switch (vk)
        {
        case VK_OEM_7:      return KeyCode::Apostrophe;
        case VK_OEM_COMMA:  return KeyCode::Comma;
        case VK_OEM_MINUS:  return KeyCode::Minus;
        case VK_OEM_PERIOD: return KeyCode::Period;
        case VK_OEM_2:      return KeyCode::Slash;
        case VK_OEM_1:      return KeyCode::Semicolon;
        case VK_OEM_PLUS:   return KeyCode::Equal;
        case VK_OEM_4:      return KeyCode::LeftBracket;
        case VK_OEM_5:      return KeyCode::Backslash;
        case VK_OEM_6:      return KeyCode::RightBracket;
        case VK_OEM_3:      return KeyCode::GraveAccent;

        case VK_ESCAPE:   return KeyCode::Escape;
        case VK_TAB:      return KeyCode::Tab;
        case VK_BACK:     return KeyCode::Backspace;
        case VK_INSERT:   return KeyCode::Insert;
        case VK_DELETE:   return KeyCode::Delete;
        case VK_RIGHT:    return KeyCode::Right;
        case VK_LEFT:     return KeyCode::Left;
        case VK_DOWN:     return KeyCode::Down;
        case VK_UP:       return KeyCode::Up;
        case VK_PRIOR:    return KeyCode::PageUp;
        case VK_NEXT:     return KeyCode::PageDown;
        case VK_HOME:     return KeyCode::Home;
        case VK_END:      return KeyCode::End;
        case VK_CAPITAL:  return KeyCode::CapsLock;
        case VK_SCROLL:   return KeyCode::ScrollLock;
        case VK_NUMLOCK:  return KeyCode::NumLock;
        case VK_SNAPSHOT: return KeyCode::PrintScreen;
        case VK_PAUSE:    return KeyCode::Pause;

        case VK_DECIMAL:  return KeyCode::KPDecimal;
        case VK_DIVIDE:   return KeyCode::KPDivide;
        case VK_MULTIPLY: return KeyCode::KPMultiply;
        case VK_SUBTRACT: return KeyCode::KPSubtract;
        case VK_ADD:      return KeyCode::KPAdd;

        case VK_LWIN: return KeyCode::LeftSuper;
        case VK_RWIN: return KeyCode::RightSuper;
        case VK_APPS: return KeyCode::Menu;

        default: break;
        }
    }

    std::optional<KeyCode> Win32ToMangoKeyCode(WPARAM wParam, LPARAM lParam)
    {
	    bool isExtended = (lParam & (1 << 24)) != 0;

    	switch (wParam)
    	{
    	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
    	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
    	case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
    	case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
    	case 'Y': case 'Z':
    	case '0': case '1': case '2': case '3': case '4':
    	case '5': case '6': case '7': case '8': case '9':
    	case VK_SPACE:
    		return (KeyCode)wParam;

    	case VK_SHIFT: {
    		UINT scancode = (lParam >> 16) & 0xFF;
    		UINT vk = MapVirtualKeyW(scancode, MAPVK_VSC_TO_VK_EX);
    		return vk == VK_RSHIFT ? KeyCode::RightShift : KeyCode::LeftShift;
    	}

    	case VK_CONTROL:
    		return isExtended ? KeyCode::RightControl : KeyCode::LeftControl;
    	case VK_MENU:
    		return isExtended ? KeyCode::RightAlt : KeyCode::LeftAlt;

    	case VK_RETURN:
    	return isExtended ? KeyCode::KPEnter : KeyCode::Enter;

    	default:
    	return Win32ToMangoKeyCodeTable((int)wParam);
    }
    }

    int MangoKeyCodeToWin32Code(KeyCode key)
    {
        switch (key) {
			case KeyCode::Space: return VK_SPACE;

			case KeyCode::Apostrophe:   return VK_OEM_7;
			case KeyCode::Comma:        return VK_OEM_COMMA;
			case KeyCode::Minus:        return VK_OEM_MINUS;
			case KeyCode::Period:       return VK_OEM_PERIOD;
			case KeyCode::Slash:        return VK_OEM_2;
			case KeyCode::Semicolon:    return VK_OEM_1;
			case KeyCode::Equal:        return VK_OEM_PLUS;
			case KeyCode::LeftBracket:  return VK_OEM_4;
			case KeyCode::Backslash:    return VK_OEM_5;
			case KeyCode::RightBracket: return VK_OEM_6;
			case KeyCode::GraveAccent:  return VK_OEM_3;

			case KeyCode::Escape:      return VK_ESCAPE;
			case KeyCode::Enter:       return VK_RETURN;
			case KeyCode::Tab:         return VK_TAB;
			case KeyCode::Backspace:   return VK_BACK;
			case KeyCode::Insert:      return VK_INSERT;
			case KeyCode::Delete:      return VK_DELETE;
			case KeyCode::Right:       return VK_RIGHT;
			case KeyCode::Left:        return VK_LEFT;
			case KeyCode::Down:        return VK_DOWN;
			case KeyCode::Up:          return VK_UP;
			case KeyCode::PageUp:      return VK_PRIOR;
			case KeyCode::PageDown:    return VK_NEXT;
			case KeyCode::Home:        return VK_HOME;
			case KeyCode::End:         return VK_END;
			case KeyCode::CapsLock:    return VK_CAPITAL;
			case KeyCode::ScrollLock:  return VK_SCROLL;
			case KeyCode::NumLock:     return VK_NUMLOCK;
			case KeyCode::PrintScreen: return VK_SNAPSHOT;
			case KeyCode::Pause:       return VK_PAUSE;

			case KeyCode::KPDecimal:  return VK_DECIMAL;
			case KeyCode::KPDivide:   return VK_DIVIDE;
			case KeyCode::KPMultiply: return VK_MULTIPLY;
			case KeyCode::KPSubtract: return VK_SUBTRACT;
			case KeyCode::KPAdd:      return VK_ADD;
			case KeyCode::KPEnter:    return VK_RETURN;

			case KeyCode::LeftShift:    return VK_LSHIFT;
			case KeyCode::LeftControl:  return VK_LCONTROL;
			case KeyCode::LeftAlt:      return VK_LMENU;
			case KeyCode::LeftSuper:    return VK_LWIN;
			case KeyCode::RightShift:   return VK_RSHIFT;
			case KeyCode::RightControl: return VK_RCONTROL;
			case KeyCode::RightAlt:     return VK_RMENU;
			case KeyCode::RightSuper:   return VK_RWIN;
			case KeyCode::Menu:         return VK_APPS;

			default: break;
		}

		int k = (int)key;

		if (k >= (int)KeyCode::A && k <= (int)KeyCode::Z)
			return k;
		if (k >= (int)KeyCode::D0 && k <= (int)KeyCode::D9)
			return k;
		if (k >= (int)KeyCode::F1 && k <= (int)KeyCode::F24)
			return VK_F1 + (k - (int)KeyCode::F1);
		if (k >= (int)KeyCode::KP0 && k <= (int)KeyCode::KP9)
			return VK_NUMPAD0 + (k - (int)KeyCode::KP0);

		return 0;
    }
} // Mango
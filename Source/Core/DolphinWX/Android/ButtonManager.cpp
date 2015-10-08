// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <unordered_map>

#include "Common/FileUtil.h"
#include "Common/IniFile.h"
#include "Common/Thread.h"
#include "DolphinWX/Android/ButtonManager.h"

namespace ButtonManager
{
	const std::string touchScreenKey = "Touchscreen";
	std::unordered_map<std::string, InputDevice*> m_controllers;
	std::vector<std::string> configStrings = {
		// GC
		"InputA",
		"InputB",
		"InputStart",
		"InputX",
		"InputY",
		"InputZ",
		"DPadUp",
		"DPadDown",
		"DPadLeft",
		"DPadRight",
		"MainUp",
		"MainDown",
		"MainLeft",
		"MainRight",
		"CStickUp",
		"CStickDown",
		"CStickLeft",
		"CStickRight",
		"InputL",
		"InputR",
		// Wiimote
		"WiimoteA",
		"WiimoteB",
		"WiimoteMinus",
		"WiimotePlus",
		"WiimoteHome",
		"Wiimote1",
		"Wiimote2",
		"WiimoteUp",
		"WiimoteDown",
		"WiimoteLeft",
		"WiimoteRight",
	};
	std::vector<ButtonType> configTypes = {
		// GC
		BUTTON_A,
		BUTTON_B,
		BUTTON_START,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_Z,
		BUTTON_UP,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		STICK_MAIN_UP,
		STICK_MAIN_DOWN,
		STICK_MAIN_LEFT,
		STICK_MAIN_RIGHT,
		STICK_C_UP,
		STICK_C_DOWN,
		STICK_C_LEFT,
		STICK_C_RIGHT,
		TRIGGER_L,
		TRIGGER_R,
		// Wiimote
		WIIMOTE_BUTTON_A,
		WIIMOTE_BUTTON_B,
		WIIMOTE_BUTTON_MINUS,
		WIIMOTE_BUTTON_PLUS,
		WIIMOTE_BUTTON_HOME,
		WIIMOTE_BUTTON_1,
		WIIMOTE_BUTTON_2,
		WIIMOTE_UP,
		WIIMOTE_DOWN,
		WIIMOTE_LEFT,
		WIIMOTE_RIGHT,
	};

	static void AddBind(const std::string& dev, sBind *bind)
	{
		auto it = m_controllers.find(dev);
		if (it != m_controllers.end())
		{
			it->second->AddBind(bind);
			return;
		}
		m_controllers[dev] = new InputDevice(dev);
		m_controllers[dev]->AddBind(bind);
	}

	void Init()
	{
		// Initialize our touchScreenKey buttons
		for (int a = 0; a < 8; ++a)
		{
			// GC
			AddBind(touchScreenKey, new sBind(a, BUTTON_A, BIND_BUTTON, BUTTON_A, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_B, BIND_BUTTON, BUTTON_B, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_START, BIND_BUTTON, BUTTON_START, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_X, BIND_BUTTON, BUTTON_X, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_Y, BIND_BUTTON, BUTTON_Y, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_Z, BIND_BUTTON, BUTTON_Z, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_UP, BIND_BUTTON, BUTTON_UP, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_DOWN, BIND_BUTTON, BUTTON_DOWN, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_LEFT, BIND_BUTTON, BUTTON_LEFT, 1.0f));
			AddBind(touchScreenKey, new sBind(a, BUTTON_RIGHT, BIND_BUTTON, BUTTON_RIGHT, 1.0f));

			AddBind(touchScreenKey, new sBind(a, STICK_MAIN_UP, BIND_AXIS, STICK_MAIN_UP, -1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_MAIN_DOWN, BIND_AXIS, STICK_MAIN_DOWN, 1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_MAIN_LEFT, BIND_AXIS, STICK_MAIN_LEFT, -1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_MAIN_RIGHT, BIND_AXIS, STICK_MAIN_RIGHT, 1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_C_UP, BIND_AXIS, STICK_C_UP, -1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_C_DOWN, BIND_AXIS, STICK_C_DOWN, 1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_C_LEFT, BIND_AXIS, STICK_C_LEFT, -1.0f));
			AddBind(touchScreenKey, new sBind(a, STICK_C_RIGHT, BIND_AXIS, STICK_C_RIGHT, 1.0f));
			AddBind(touchScreenKey, new sBind(a, TRIGGER_L, BIND_AXIS, TRIGGER_L, 1.0f));
			AddBind(touchScreenKey, new sBind(a, TRIGGER_R, BIND_AXIS, TRIGGER_R, 1.0f));

			// Wiimote
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_A, BIND_BUTTON, WIIMOTE_BUTTON_A, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_B, BIND_BUTTON, WIIMOTE_BUTTON_B, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_MINUS, BIND_BUTTON, WIIMOTE_BUTTON_MINUS, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_PLUS, BIND_BUTTON, WIIMOTE_BUTTON_PLUS, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_HOME, BIND_BUTTON, WIIMOTE_BUTTON_HOME, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_1, BIND_BUTTON, WIIMOTE_BUTTON_1, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_BUTTON_2, BIND_BUTTON, WIIMOTE_BUTTON_2, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_UP, BIND_BUTTON, WIIMOTE_UP, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_DOWN, BIND_BUTTON, WIIMOTE_DOWN, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_LEFT, BIND_BUTTON, WIIMOTE_LEFT, 1.0f));
			AddBind(touchScreenKey, new sBind(a, WIIMOTE_RIGHT, BIND_BUTTON, WIIMOTE_RIGHT, 1.0f));
		}
		// Init our controller bindings
		IniFile ini;
		ini.Load(File::GetUserPath(D_CONFIG_IDX) + std::string("Dolphin.ini"));
		for (u32 a = 0; a < configStrings.size(); ++a)
		{
			for (int padID = 0; padID < 8; ++padID)
			{
				std::ostringstream config;
				config << configStrings[a] << "_" << padID;
				BindType type;
				int bindnum;
				char dev[128];
				bool hasbind = false;
				char modifier = '+';
				std::string value;
				ini.GetOrCreateSection("Android")->Get(config.str(), &value, "None");
				if (value == "None")
					continue;
				if (std::string::npos != value.find("Axis"))
				{
					hasbind = true;
					type = BIND_AXIS;
					sscanf(value.c_str(), "Device '%127[^\']'-Axis %d%c", dev, &bindnum, &modifier);
				}
				else if (std::string::npos != value.find("Button"))
				{
					hasbind = true;
					type = BIND_BUTTON;
					sscanf(value.c_str(), "Device '%127[^\']'-Button %d", dev, &bindnum);
				}
				if (hasbind)
					AddBind(std::string(dev), new sBind(padID, configTypes[a], type, bindnum, modifier == '-' ? -1.0f : 1.0f));
			}
		}

	}
	bool GetButtonPressed(int padID, ButtonType button)
	{
		bool pressed = m_controllers[touchScreenKey]->ButtonValue(padID, button);

		for (const auto& ctrl : m_controllers)
			pressed |= ctrl.second->ButtonValue(padID, button);

		return pressed;
	}
	float GetAxisValue(int padID, ButtonType axis)
	{
		float value = m_controllers[touchScreenKey]->AxisValue(padID, axis);
		if (value == 0.0f)
		{
			for (const auto& ctrl : m_controllers)
			{
				value = ctrl.second->AxisValue(padID, axis);
				if (value != 0.0f)
					return value;
			}
		}
		return value;
	}
	bool GamepadEvent(const std::string& dev, int button, int action)
	{
		auto it = m_controllers.find(dev);
		if (it != m_controllers.end())
			return it->second->PressEvent(button, action);
	}
	void GamepadAxisEvent(const std::string& dev, int axis, float value)
	{
		auto it = m_controllers.find(dev);
		if (it != m_controllers.end())
			it->second->AxisEvent(axis, value);
	}
	void Shutdown()
	{
		for (const auto& controller : m_controllers)
			delete controller.second;
		m_controllers.clear();
	}

	// InputDevice
	bool InputDevice::PressEvent(int button, int action)
	{
		bool handled = false;
		for (const auto& binding : _inputbinds)
		{
			if (binding.second->_bind == button)
			{
				if (binding.second->_bindtype == BIND_BUTTON)
					_buttons[binding.second->_buttontype] = action == BUTTON_PRESSED ? true : false;
				else
					_axises[binding.second->_buttontype] = action == BUTTON_PRESSED ? 1.0f : 0.0f;
				handled = true;
			}
		}
		return handled;
	}
	void InputDevice::AxisEvent(int axis, float value)
	{
		for (const auto& binding : _inputbinds)
		{
			if (binding.second->_bind == axis)
			{
				if (binding.second->_bindtype == BIND_AXIS)
					_axises[binding.second->_buttontype] = value;
				else
					_buttons[binding.second->_buttontype] = value > 0.5f ? true : false;
			}
		}
	}
	bool InputDevice::ButtonValue(int padID, ButtonType button)
	{
		const auto& binding = _inputbinds.find(std::make_pair(padID, button));
		if (binding == _inputbinds.end())
			return false;

		if (binding->second->_bindtype == BIND_BUTTON)
			return _buttons[binding->second->_buttontype];
		else
			return (_axises[binding->second->_buttontype] * binding->second->_neg) > 0.5f;
	}
	float InputDevice::AxisValue(int padID, ButtonType axis)
	{
		const auto& binding = _inputbinds.find(std::make_pair(padID, axis));
		if (binding == _inputbinds.end())
			return 0.0f;

		if (binding->second->_bindtype == BIND_AXIS)
			return _axises[binding->second->_buttontype] * binding->second->_neg;
		else
			return _buttons[binding->second->_buttontype] == BUTTON_PRESSED ? 1.0f : 0.0f;
	}
}

/*!
 * \file App.h
 * \date 2020/09/14 13:02
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A basic application class that is responsible for application specific code managing
 *
 * TODO:
 *
 * \note For some testing purposes you can inherit from this class and make tests in separate class.
 * * Make sure you make necessary functions virtual
*/
#pragma once

#include "Window.h"
#include "IronTimer.h"
#include "Bindable.h"
#include "Camera.h"
#include "ImGuiManager.h"
#include "PointLight.h"

#include <set>

class AppMess
{
public:
	AppMess();

	/**
	 * @brief Starts application frame. Processes window messages 
	 * @return Integer exit code
	*/
	int BeginFrame();

private:
	/**
	 * @brief Processes main application frame
	*/
	void ProcessFrame();

	void SpawnActiveBoxWindows();

	void SpawnSimulationWindow();

	void SpawnBoxWindowManagerWindow();

private:
	ImguiManager imguim;
	Camera camera;
	Window wnd;
	PointLight pointLight;
	IronTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	std::vector<class Box*> boxes;
	float simulationSpeedFactor = 1.f;
	bool isSimulationRunning = true;
	static constexpr size_t MAX_NDRAWABLES = 180;
	std::optional<uint32_t> comboBoxIndex;
	std::set<uint32_t> boxControlIndexes;
};
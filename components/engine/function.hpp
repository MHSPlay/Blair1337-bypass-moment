//#pragma once
//#ifndef MOUSE
//#define MOUSE
//#include <iostream>
//#include <coroutine>
//#include "C:\Users\1\Documents\master peg\components\bypass\memory.cpp"
//#include <WinUser.h>
//#include "matrices.hpp"
//
//using namespace ac;
//using namespace engine;
//
//
//static auto aimfunction(float x, float y) -> void
//{
//	float ScreenCenterX = (defines::width / 2);
//	float ScreenCenterY = (defines::height / 2);
//	int AimSpeed = elements::smooth;
//	float TargetX = 0;
//	float TargetY = 0;
//
//	if (x != 0)
//	{
//		if (x > ScreenCenterX)
//		{
//			TargetX = -(ScreenCenterX - x);
//			TargetX /= AimSpeed;
//			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
//		}
//
//		if (x < ScreenCenterX)
//		{
//			TargetX = x - ScreenCenterX;
//			TargetX /= AimSpeed;
//			if (TargetX + ScreenCenterX < 0) TargetX = 0;
//		}
//	}
//
//	if (y != 0)
//	{
//		if (y > ScreenCenterY)
//		{
//			TargetY = -(ScreenCenterY - y);
//			TargetY /= AimSpeed;
//			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
//		}
//
//		if (y < ScreenCenterY)
//		{
//			TargetY = y - ScreenCenterY;
//			TargetY = y - ScreenCenterY;
//			TargetY /= AimSpeed;
//			if (TargetY + ScreenCenterY < 0) TargetY = 0;
//		}
//	}
//
//
//	//SPOOF_CALL(mouse_event, MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
//	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
//	/*driver.write(cachedplayercontroller + 0x520, TargetX);
//	driver.write(cachedplayercontroller + 0x520, TargetY);*/
//	return;
//}
//
//void aimbott(DWORD_PTR entity) {
//	uintptr_t cachedgworld = ac::read<uintptr_t>(defines::image + offsets::world);
//	uintptr_t cachedgameinstance = ac::read<uintptr_t>(cachedgworld + offsets::game_instance);
//	uintptr_t cachedlocalplayers = ac::read<uintptr_t>(cachedgameinstance + offsets::local_players);
//	uintptr_t cachedlocalplayer = ac::read<uintptr_t>(cachedlocalplayers);
//	uintptr_t cachedplayercontroller = ac::read<uintptr_t>(cachedlocalplayer + offsets::playercontroller);
//	engine::fvector2d screen_center = { static_cast<double>(defines::width) / 2, static_cast<double>(defines::height) / 2 };
//	engine::fvector2d target{};
//	engine::fvector2d bone;
//	uint64_t currentactormesh = ac::read<uint64_t>(entity + offsets::mesh);
//	/*if (bone == 0) {
//		bone = world_to_screen(get_bone_location(currentactormesh));
//	}
//	else if (bone == 1) {
//		bone = engine::world_to_screen(get_bone_location(currentactormesh));
//	}
//	else if (bone == 2) {
//		engine::fvector2d chest_left = world_to_screen(get_bone_location(currentactormesh, bones::HumanLUpperarm));
//		engine::fvector2d chest_right = world_to_screen(get_bone_location(currentactormesh, bones::HumanRUpperarm));
//		bone = { chest_left.x + (chest_right.x - chest_left.x) / 2, chest_left.y };
//	}*/
//
//	target.x = (bone.x > screen_center.x) ? -(screen_center.x - bone.x) : bone.x - screen_center.x;
//	target.x /= elements::smooth;
//	target.x = (target.x + screen_center.x > screen_center.x * 2 || target.x + screen_center.x > 0) ? 0 : target.x;
//
//	target.y = (bone.y > screen_center.y) ? -(screen_center.y - bone.y) : bone.y - screen_center.y;
//	target.y /= elements::smooth;
//	target.y = (target.y + screen_center.y > screen_center.y * 2 || target.y + screen_center.y > 0) ? 0 : target.y;
//
//	engine::fvector Angles(-target.y / elements::smooth, target.x / elements::smooth, 0);
//
//	engine::fvector original1(0, 0, 0);
//	//if (elements::enable && (Controller::IsPressingLeftTrigger() || GetAsyncKeyState(aimkey) < 0)) {
//	//ac::WriteMemory(cachedplayercontroller + 0x520, Angles.x);
//	//ac::WriteMemory(cachedplayercontroller + 0x520 + 0x8, Angles.y);
//
//	//}
//	//if (elements::triggerbot) { //&& ( Controller::IsPressingLeftTrigger() || GetAsyncKeyState(aimkey) < 0)) {
//
//	//	std::thread t(trigger);
//
//	//	// Wait for the thread to finish
//	//	t.join();
//	//}
//
//}
//#endif 

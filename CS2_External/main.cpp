#include "Offsets.h"
#include "Cheats.h"
#include "Utils/Format.hpp"
#include <iostream>
#include <iomanip>
#include <Shlobj.h>
#include <filesystem>
#include <Windows.h>

int main()
{
	TCHAR documentsPath[MAX_PATH];
	if (SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath) != S_OK) {
		return 0;
	}
	char narrowPath[MAX_PATH];
	if (WideCharToMultiByte(CP_UTF8, 0, documentsPath, -1, narrowPath, sizeof(narrowPath), NULL, NULL) == 0) {
		return 0;
	}
	std::string documentsDir(narrowPath);
	std::string configFilePath = documentsDir + "\\.Aeonix\\";
	namespace fs = std::filesystem;
	if (!fs::is_directory(configFilePath)) {
		if (fs::create_directory(configFilePath)) {
			std::cout << "[Success] Configuration directory created: " << configFilePath << std::endl;
		}
		else {
			std::cerr << "[Error] Could not create the configuration directory." << std::endl;
		}
	}
	else {
		std::cout << "[Success] Configuration directory already exists: " << configFilePath << std::endl;
	}

	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[ERROR] Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
		goto END;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[ERROR] Failed to update offsets." << std::endl;
		goto END;
	}

	if (!gGame.InitAddress())
	{
		std::cout << "[ERROR] Failed to call InitAddress()." << std::endl;
		goto END;
	}

	std::cout << Format("[Game] Pid:%d\n", ProcessMgr.ProcessID);
	std::cout << Format("[Game] Client:%llX\n", gGame.GetClientDLLAddress());

	std::cout << Format("[Offset] EntityList:%llX\n", Offset::EntityList);
	std::cout << Format("[Offset] Matrix:%llX\n", Offset::Matrix);
	std::cout << Format("[Offset] LocalPlayerController:%llX\n", Offset::LocalPlayerController);
	std::cout << Format("[Offset] ViewAngles:%llX\n", Offset::ViewAngle);
	std::cout << Format("[Offset] LocalPlayerPawn:%llX\n", Offset::LocalPlayerPawn);
	std::cout << Format("[Offset] ForceJump:%llX\n", Offset::ForceJump);

	std::cout << "[Success] Runing..." << std::endl;

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

END:
	system("pause");
	return 0;
}
#include "Offsets.h"
#include "Cheats.h"
#include <iostream>
#include <iomanip>
#include <Shlobj.h>
#include <filesystem>
#include <Windows.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

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
			std::cout << "Configuration directory created: " << configFilePath << std::endl;
		}
		else {
			std::cerr << "Error: Could not create the configuration directory." << std::endl;
		}
	}
	else {
		std::cout << "Configuration directory already exists: " << configFilePath << std::endl;
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
		std::cout << "[ERROR] Failed to call InitAddress()."<< std::endl;
		goto END;
	}

	std::cout << "[Pid]:" << ProcessMgr.ProcessID << std::endl;
	std::cout << "[Client]:" << gGame.GetClientDLLAddress() << std::endl;

	std::cout << "[EntityList]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::EntityList << std::endl;
	std::cout << "[Matrix]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::Matrix << std::endl;
	std::cout << "[LocalPlayerController]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerController << std::endl;
	std::cout << "[ViewAngles]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::ViewAngle << std::endl;
	std::cout << "[LocalPlayerPawn]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerPawn << std::endl;
	std::cout << "[ForceJump]:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::ForceJump << std::endl;

	std::cout << "Running..." << std::endl;

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

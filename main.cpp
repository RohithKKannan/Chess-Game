#include <functional>
#include "Libraries/Spinach/spinach/core/spn_core.h"
#include "Game/gameManager.h"
#include "Utils/utilities.h"

int main() {
	spn::SpinachCore sc(640, 480);
	
	if (sc.IsInitFailed()){
		return -1;
	}
	
	Utilities::GetInstance().InitializePieceImages();
	
	GameManager gm;
	
	gm.InitGame();
	
	sc.SetWindowTitle("2D Chess Game");
	
	sc.SetUpdateAndRenderHandler(std::bind(&GameManager::Update, &gm, std::placeholders::_1));
	
	sc.SetInputHandler(std::bind(&GameManager::ProcessInput, &gm, std::placeholders::_1));
		
	sc.MainLoop();

	return 0;
}
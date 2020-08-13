#include "ClientViewRenderHook.h"
#include "Interfaces.h"
#include "BasePlayer.h"
#include "IMaterial.h"

void __fastcall MyHooks::MyClientViewRender(IBaseClientDll* client, void* edx, vrect_t* rect)
{
	//std::cout << "View Render Client!" << std::endl;

	//const CViewSetup* setup = Interfaces::Get().ViewRender->GetViewSetup();
	//if (!Interfaces::Get().Engine->isTakingScreenshot()) 
	//{
	//	float colormod[3] = { 1.f,1.f,1.f };
	//	IMaterial* DebugWhite = Interfaces::Get().MaterialSystem->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
	//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
	//	DebugWhite->AddRef();

	//	Interfaces::Get().RenderView->Push3DView((const CViewSetup&)setup, 0, nullptr, Interfaces::Get().ViewRender->GetFrustum());

	//	for (int i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	//	{
	//		CBasePlayer* ply = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

	//		if (!ply || !ply->isDormant() || ply == CBasePlayer::GetLocalPlayer() || ply->GetHealth() <= 0) continue;
	//	
	//		Interfaces::Get().ModelRender->ForcedMaterialOverride(DebugWhite);
	//		Interfaces::Get().RenderView->SetColorModulation(colormod);
	//		ply->DrawModel(STUDIO_RENDER);
	//		Interfaces::Get().ModelRender->ForcedMaterialOverride(nullptr);
	//	}

	//	Interfaces::Get().RenderView->PopView(Interfaces::Get().ViewRender->GetFrustum());
	//}
}
#include "RenderViewHook.h"
#include "Settings.h"
#include "GLOBALS.h"
#include "IMaterial.h"
#include "BasePlayer.h"


namespace MyHooks
{
	void __fastcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw)
	{
		G::Get().GetOthervars()->GameFOV = view.fov;

		if (CoreSettings::Get().GetHackSettings()->VISUAL->bCustomFov)
			view.fov = CoreSettings::Get().GetHackSettings()->VISUAL->iCustomFov;

		if (CoreSettings::Get().GetHackSettings()->VISUAL->bCustomViewmodelFov)
			view.fovViewmodel = CoreSettings::Get().GetHackSettings()->VISUAL->iCustomViewmodelFov;
		
		//Interfaces::Get().ViewRender->m_view = view;

		//if (!Interfaces::Get().Engine->isTakingScreenshot()) {
		//	float colormod[3] = { 1.f,1.f,1.f };
		//	IMaterial* DebugWhite = Interfaces::Get().MaterialSystem->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//	DebugWhite->AddRef();

		//	Interfaces::Get().RenderView->Push3DView(view, 0, nullptr, Interfaces::Get().ViewRender->GetFrustum());

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
		//G::Get().GetOthervars()->GameFOV = view.fov;
	}
}
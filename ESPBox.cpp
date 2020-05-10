#include "ESPBox.h"
#include "Settings.h"
#include "BasePlayer.h"
#include "imgui/imgui.h"
#include "GameTools.h"
#include "ImGuiBaseDraw.h"
#include "color.h"

void ESPBox::Render()
{
	if (!CoreSettings::Get().GetHackSettings()->ESP->IsActive)
		return;

	if (!Interfaces::Get().Engine->isInGame())
		return;

	ImDrawList* drawlist = ImGui::GetOverlayDrawList();

	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent) continue;
		
		//std::cout << "Health = " << ent->GetHealth() << " IsDormant = " << ent->isDormant() <<"\n";

		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || !ent->isDormant()) continue;

		Math::CVector vOrigin = ent->GetOrigin();
		Math::CVector vHead = GameTools::GetEntityBone(ent, ECSPlayerBones::head_0);

		vHead += 15.0f;

		Math::CVector vScreenOrigin, vScreenHead;

		if (GameTools::WorldToScreen(vHead, vScreenHead) && GameTools::WorldToScreen(vOrigin, vScreenOrigin))
		{
			float h = abs(vScreenHead.y - vScreenOrigin.y);
			float w = h * 0.65f;

			float x1, x2, y1, y2;

			x1 = vScreenOrigin.x - w / 2;
			y1 = vScreenOrigin.y;
			x2 = x1 + w;
			y2 = -h + y1;

			//std::cout << "Box color = " << "r = " << CoreSettings::Get().GetHackSettings()->ESP->BoxColor[0] << " g = " << CoreSettings::Get().GetHackSettings()->ESP->BoxColor[1] << " b = " << CoreSettings::Get().GetHackSettings()->ESP->BoxColor[2] <<"\n";
			DXDraw::RenderOutlinedRect(drawlist, x1, y1, x2, y2, CColor(CoreSettings::Get().GetHackSettings()->ESP->BoxColor));

			auto health = ent->GetHealth();

			auto offset = (std::min)(static_cast<float>(health) / ent->GetMaxHealth(), 1.f);
			int green = int(health * 2.55f);
			int red = 255 - green;
			DXDraw::RenderRectFilled(drawlist, x1 - 5.f, y1 - 1.f, x1 - 2.f, y2 + 1.f, CColor(0, 0, 0));
			if (health > 0)
				DXDraw::RenderRectFilled(drawlist, x1 - 4.f, y1, x1 - 3.f, y1 - offset * (y1 - y2), CColor(red, green, 0));

		}

	}
}
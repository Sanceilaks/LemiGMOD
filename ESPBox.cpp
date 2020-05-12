#include "ESPBox.h"
#include "Settings.h"
#include "BasePlayer.h"
#include "imgui/imgui.h"
#include "GameTools.h"
#include "ImGuiBaseDraw.h"
#include "color.h"

#pragma warning( push )
#pragma warning( disable : 4244) //4244


void ESPBox::Render()
{
	if (!CoreSettings::Get().GetHackSettings()->ESP->IsActive)
		return;
	if (!Interfaces::Get().Engine->isInGame())
		return;

	auto get_box = [](Math::CVector feet, Math::CVector head) -> RECT {
		RECT ret;

		auto h_ = fabs(head.y - feet.y);
		auto w_ = h_ / 2.0f;

		ret.left = (int)(feet.x - w_ * 0.5f);
		ret.right = (int)(ret.left + w_);
		ret.bottom = (feet.y > head.y ? (int)(feet.y) : (int)(head.y));
		ret.top = (feet.y > head.y ? (int)(head.y) : (int)(feet.y));

		return ret;
	};

	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent) continue;
		
		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || !ent->isDormant()) continue;

		if (CBasePlayer::GetLocalPlayer()->GetDistance(ent) >= CoreSettings::Get().GetHackSettings()->ESP->MaxEspDistance);

		Math::CVector vOrigin = ent->GetOrigin();
		Math::CVector vHead = GameTools::GetEntityBone(ent, ECSPlayerBones::head_0);

		vHead += 15.0f;

		Math::CVector vScreenOrigin, vScreenHead;

		if (GameTools::WorldToScreen(vHead, vScreenHead) && GameTools::WorldToScreen(vOrigin, vScreenOrigin))
		{
			auto Box = get_box(vScreenOrigin, vScreenHead);

			DXDraw::RenderOutlinedRect(Box.left, Box.top, Box.right, Box.bottom, CColor(CoreSettings::Get().GetHackSettings()->ESP->BoxColor));

			if (CoreSettings::Get().GetHackSettings()->ESP->DrawHealth)
			{
				float CurHealth = ent->GetHealth();
				float maxHp = ent->GetMaxHealth();

				DXDraw::RenderRectFilled(Box.left - 6, Box.top, Box.left - 3, Box.bottom, CColor(0.f, 0.f, 0.f), 5, 0);

				auto x_start = Box.left - 5;
				auto y_start = Box.top + 1;
				auto y_end = Box.bottom - 1;

				auto y_size = (y_end - y_start) / maxHp * CurHealth;

				DXDraw::RenderLine(x_start, y_end - y_size, x_start, y_end, CColor(0.f, 1.f, 0.f));
			}
		}

	}
}

#pragma warning( pop )
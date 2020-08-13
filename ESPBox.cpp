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

	if (CoreSettings::Get().GetHackSettings()->VISUAL->Dtype == dx)
		DXRender::Get().Begin();

	auto get_box = [](Math::CVector feet, Math::CVector head) -> RECT {
		RECT ret;

		auto h_ = fabs(head.y - feet.y);
		auto w_ = h_ / 2.0f;

		ret.left = (feet.x - w_ * 0.5f);
		ret.right = ((LONG)ret.left + (LONG)w_);
		ret.bottom = ((LONG)feet.y > (LONG)head.y ? (LONG)(feet.y) : (LONG)(head.y));
		ret.top = ((LONG)feet.y > (LONG)head.y ? (LONG)(head.y) : (LONG)(feet.y));

		return ret;
	};

	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent) continue;
		
		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || !ent->isDormant()) continue;

		if (CBasePlayer::GetLocalPlayer()->GetDistance(ent) >= CoreSettings::Get().GetHackSettings()->ESP->MaxEspDistance);

		Math::CVector vOrigin = ent->GetOrigin();
		Math::CVector vHead = ent->GetEyePosition();

		vHead += 15.0f;

		Math::CVector vScreenOrigin, vScreenHead;

		if (GameTools::WorldToScreen(vHead, vScreenHead) && GameTools::WorldToScreen(vOrigin, vScreenOrigin))
		{
			auto Box = get_box(vScreenOrigin, vScreenHead);

			//if (CoreSettings::Get().GetHackSettings()->VISUAL->Dtype == imgui)
			auto color = GameTools::IsVisible(CBasePlayer::GetLocalPlayer()->GetEyePosition(), ent->GetEyePosition(), ent)
				? CoreSettings::Get().GetHackSettings()->ESP->VBoxColor
				: CoreSettings::Get().GetHackSettings()->ESP->IBoxColor;
			DXDraw::RenderOutlinedRect((LONG)Box.left, (LONG)Box.top, (LONG)Box.right, (LONG)Box.bottom, CColor(color));
			//else
			//{
			//	auto color = D3DCOLOR_RGBA(CoreSettings::Get().GetHackSettings()->ESP->BoxColor[0], CoreSettings::Get().GetHackSettings()->ESP->BoxColor[1], CoreSettings::Get().GetHackSettings()->ESP->BoxColor, 255)
			//	DXRender::Get().RenderBorderedBox(Vec2(Box.left, Box.top), Box.right - Box.left, Box.bottom - Box.top, 3, D3DCOLOR());
			//}

			if (CoreSettings::Get().GetHackSettings()->ESP->DrawHealth)
			{
				//				int x = Box.left, y = Box.top, w = Box.right - Box.left, h = Box.bottom - Box.top;
				float CurHealth = ent->GetHealth();
				float maxHp = ent->GetMaxHealth();
				//if (CoreSettings::Get().GetHackSettings()->VISUAL->Dtype == imgui)
				DXDraw::RenderRectFilled(Box.left - 6, Box.top, Box.left - 3, Box.bottom, CColor(0.f, 0.f, 0.f), 5, 0);
				//else
				//	DXRender::Get().RenderFilledBox(Vec2(Box.left - 6, Box.top), Box.right - (Box.left - 3), Box.bottom - Box.top, D3DCOLOR(0.f, 0.f, 0.f))

				auto x_start = Box.left - 5;
				auto y_start = Box.top + 1;
				auto y_end = Box.bottom - 1;

				auto y_size = (y_end - y_start) / maxHp * CurHealth;

				DXDraw::RenderLine(x_start, y_end - y_size, x_start, y_end, CColor(0, 255, 0));
			}
		}
	}
	if (CoreSettings::Get().GetHackSettings()->VISUAL->Dtype == dx)
		DXRender::Get().End();
}

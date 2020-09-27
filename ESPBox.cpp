#include "ESPBox.h"
#include "Settings.h"
#include "BasePlayer.h"
#include "imgui/imgui.h"
#include "GameTools.h"
#include "ImGuiBaseDraw.h"
#include "color.h"

struct Box {
	int x, y, w, h;
	Box() = default;
	Box(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

bool get_player_box(CBasePlayer* ent, Box& box_in)
{
	Math::CVector origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	origin = ent->GetOrigin();
	min = ent->Collideable()->mins() + origin;
	max = ent->Collideable()->maxs() + origin;

	Math::CVector points[] = {
		Math::CVector(min.x, min.y, min.z),
		Math::CVector(min.x, max.y, min.z),
		Math::CVector(max.x, max.y, min.z),
		Math::CVector(max.x, min.y, min.z),
		Math::CVector(max.x, max.y, max.z),
		Math::CVector(min.x, max.y, max.z),
		Math::CVector(min.x, min.y, max.z),
		Math::CVector(max.x, min.y, max.z)
	};

	if (!GameTools::WorldToScreen(points[3], flb) || !GameTools::WorldToScreen(points[5], brt)
		|| !GameTools::WorldToScreen(points[0], blb) || !GameTools::WorldToScreen(points[4], frt)
		|| !GameTools::WorldToScreen(points[2], frb) || !GameTools::WorldToScreen(points[1], brb)
		|| !GameTools::WorldToScreen(points[6], blt) || !GameTools::WorldToScreen(points[7], flt))
		return false;

	Math::CVector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	if (left < 0 || top < 0 || right < 0 || bottom < 0)
		return false;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	box_in.x = (int)left;
	box_in.y = (int)top;
	box_in.w = int(right - left);
	box_in.h = int(bottom - top);

	return true;
}



void ESPBox::Render()
{
	DXRender::Get().Begin();

	if (!CoreSettings::Get().GetHackSettings()->ESP->IsActive)
	{
		DXRender::Get().End(); 
		return;
	}
	if (!Interfaces::Get().Engine->isInGame())
	{
		DXRender::Get().End();
		return;
	}

	CBasePlayer* local_player = CBasePlayer::GetLocalPlayer();

	if (!local_player)
	{
		DXRender::Get().End();
		return;
	}


	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent || ent == nullptr) continue;
		
		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || ent->isDormant()) continue;

		if (CBasePlayer::GetLocalPlayer()->GetDistance(ent) >= CoreSettings::Get().GetHackSettings()->ESP->MaxEspDistance);

		Box box;

		if (!get_player_box(ent, box))
			continue;

		auto color = GameTools::IsVisible(CBasePlayer::GetLocalPlayer()->GetEyePosition(), ent->GetEyePosition(), ent)
			? CoreSettings::Get().GetHackSettings()->ESP->VBoxColor
			: CoreSettings::Get().GetHackSettings()->ESP->IBoxColor;

		DXRender::Get().DrawBorderBox(box.x, box.y, box.w, box.h, 2, CColor(color));

		if (CoreSettings::Get().GetHackSettings()->ESP->DrawHealth)
		{

			float CurHealth = ent->GetHealth();
			float maxHp = ent->GetMaxHealth();

			int x1, y1, w1, h1;

			x1 = box.x - 5;
			y1 = box.y;
			w1 = box.x - (box.x - 6);
			h1 = box.h;


			//DXRender::Get().DrawFilledRect(box.x - 6, box.y, box.x - (box.x - 6), box.h, CColor(0, 0, 0));


			auto x_start = box.x - 5;
			auto y_start = box.y + 1;
			auto y_end = box.y + box.h - 1;

			auto y_size = (y_end - y_start) / maxHp * CurHealth;


			DXRender::Get().DrawLine(x_start, y_end - y_size, x_start, y_end, 1, CColor(0, 255, 0));

		}

		if (CoreSettings::Get().GetHackSettings()->ESP->DrawName)
		{
			auto getName = [](CBasePlayer* entity) -> std::string
			{
				auto glua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);

				if (!glua)
					return {};

				glua->PushSpecial((int)LUA::Special::glob);
				glua->GetField(-1, "Entity");
				glua->PushNumber(entity->index());
				glua->Call(1, 1);

				glua->GetField(-1, "Name");
				glua->Push(-2);
				glua->Call(1, 1);

				std::string name = glua->GetString(-1);
				glua->Pop(3);

				return name;
			};

			auto name = getName(ent);

			float d = local_player->GetDistance(ent);

			if (d < 2000)
				DXRender::Get().DrawString(box.x, box.y + box.h, name.c_str(), CColor(255, 255, 255), DXRender::Get().DefaultFont[16]);
			else if (d < 4000)
				DXRender::Get().DrawString(box.x, box.y + box.h, name.c_str(), CColor(255, 255, 255), DXRender::Get().DefaultFont[12]);
			else if (d < 6000)
				DXRender::Get().DrawString(box.x, box.y + box.h, name.c_str(), CColor(255, 255, 255), DXRender::Get().DefaultFont[8]);
			else if (d < 8000)
				DXRender::Get().DrawString(box.x, box.y + box.h, name.c_str(), CColor(255, 255, 255), DXRender::Get().DefaultFont[4]);
		}

	}
	//if (CoreSettings::Get().GetHackSettings()->VISUAL->Dtype == dx)
	DXRender::Get().End();
}

#include "LockCursorHook.h"
#include "Interfaces.h"
#include "menu.h"
#include "GLOBALS.h"


namespace MyHooks
{
	bool __stdcall MyLockCursor()
	{
		if (G::Get().GetMenuVars()->MenuIsOpen)
		{
			Interfaces::Get().Surface->UnlockCursor();
			//Interfaces::Get().InputSystem->ResetInputState();
			return true;
		}
		return false;
	}
}
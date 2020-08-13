#include "ReadPixelsHook.h"
#include "MemTools.h"
#include <intrin.h>
#pragma intrinsic(_ReturnAddress)


//Not work(





uint8_t* g_render_capture = CMemTools::PatternScaner("client.dll", "FF 50 ? 6A 20 8D 4D" + 3);	//https://i.imgur.com/DM3aojc.png

void __fastcall MyHooks::MyReadPixels(IMatRenderContext* self, uintptr_t edx, int x, int y, int w, int h, uint8_t* data, int dst)
{
	CViewSetup* setup;

	if ((uint8_t*)_ReturnAddress() == g_render_capture)
	{
		std::cout << "Grab!" << std::endl;
		//self->ClearBuffers(true, true, true);
	}

}

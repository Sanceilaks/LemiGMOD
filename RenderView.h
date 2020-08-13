#pragma once
#include "CViewSetup.h"
#include "MaterialSystemStuff.h"

class VPlane;
enum
{
	FRUSTUM_RIGHT = 0,
	FRUSTUM_LEFT = 1,
	FRUSTUM_TOP = 2,
	FRUSTUM_BOTTOM = 3,
	FRUSTUM_NEARZ = 4,
	FRUSTUM_FARZ = 5,
	FRUSTUM_NUMPLANES = 6
};
typedef VPlane Frustum[FRUSTUM_NUMPLANES];


class IRenderView //Not ViewRender
{
public:
	void Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void* frustumPlanes)
	{
		using fn = void(__thiscall*)(IRenderView*, const CViewSetup&, int, ITexture*, void*);
		return (*(fn**)this)[38](this, view, nFlags, pRenderTarget, frustumPlanes);
	}

	void Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes, ITexture* pDepthTexture)
	{
		using fn = void(__thiscall*)(IRenderView*, const CViewSetup&, int, ITexture*, Frustum, ITexture*);
		return (*(fn**)this)[39](this, view, nFlags, pRenderTarget, frustumPlanes, pDepthTexture);
	}

	void PopView(Frustum frustumPlanes)
	{
		using fn = void(__thiscall*)(IRenderView*, Frustum);
		return (*(fn**)this)[41](this, frustumPlanes);
	}

	void SetColorModulation(float const* blend)
	{
		using fn = void(__thiscall*)(IRenderView*, float const*);
		return (*(fn**)this)[6](this, blend);
	}
};
#pragma once
#include "vector.h"
#include "CBaseEntity.h"

#define  Assert( _exp ) ((void)0)

struct Ray_t
{
	Math::CVectorAligned  m_Start;    // starting point, centered within the extents
	Math::CVectorAligned  m_Delta;    // direction + length of the ray
	Math::CVectorAligned  m_StartOffset;    // Add this to m_Start to get the actual ray start
	Math::CVectorAligned  m_Extents;    // Describes an axis aligned box extruded along a ray
	//const matrix3x4_t *m_pWorldAxisTransform;
	bool    m_IsRay;    // are the extents zero?
	bool    m_IsSwept;    // is delta != 0?

	void Init(Math::CVector& vecStart, Math::CVector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents[0] = m_Extents[1] = m_Extents[2] = 0.0f;
		m_IsRay = true;

		m_StartOffset[0] = m_StartOffset[1] = m_StartOffset[2] = 0.0f;

		m_Start = vecStart;
	}
private:
};


struct cplane_t
{
	Math::CVector	normal;
	float	dist;
	unsigned char type;			// for fast side tests
	unsigned char signbits;		// signx + (signy<<1) + (signz<<1)
	unsigned char pad[2];

	cplane_t() {}

private:
	// No copy constructors allowed if we're in optimal mode
	cplane_t(const cplane_t& vOther);
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

struct trace_t
{
	Math::CVector startpos;
	Math::CVector endpos;
	cplane_t	plane;
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startsolid;
	float fractionleftsolid;
	csurface_t	surface;
	int hitgroup;
	short physicsbone;
	void* m_pEnt;
	int hitbox;
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool			ShouldHitEntity(void* pEntity, int mask) = 0;
	virtual TraceType_t            GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

typedef bool(*ShouldHitFunc_t)(void* pHandleEntity, int contentsMask);
class CTraceFilterSimple : public CTraceFilter
{
public:
	// It does have a base, but we'll never network anything below here..

	CTraceFilterSimple(const void* passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
	virtual bool ShouldHitEntity(void* pHandleEntity, int contentsMask);
	virtual void SetPassEntity(const void* pPassEntity) { m_pPassEnt = pPassEntity; }
	virtual void SetCollisionGroup(int iCollisionGroup) { m_collisionGroup = iCollisionGroup; }

	const void* GetPassEntity(void) { return m_pPassEnt; }

private:
	const void* m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;

};

class IHandleEntity;
class CTraceListData;
class CPhysCollide;

class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(IHandleEntity* pHandleEntity) = 0;
};

class IEngineTrace
{
public:
	virtual void unused_0() = 0;
	virtual void unused_1() = 0;
	virtual void unused_2() = 0;
	virtual void unused_3() = 0;
	virtual	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
};
#include <cmath>
#include "Vector2D.h"


namespace Math
{
	CVector2D::CVector2D(void) {
	}

	CVector2D::CVector2D(vec_t X, vec_t Y) {
		x = X; y = Y;
	}

	CVector2D::CVector2D(vec_t* clr) {
		x = clr[0]; y = clr[1];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void CVector2D::Init(vec_t ix, vec_t iy) {
		x = ix; y = iy;
	}

	void CVector2D::Random(float minVal, float maxVal) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	void CVector2DClear(CVector2D& a) {
		a.x = a.y = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	CVector2D& CVector2D::operator=(const CVector2D& vOther) {
		x = vOther.x; y = vOther.y;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------

	vec_t& CVector2D::operator[](int i) {
		return ((vec_t*)this)[i];
	}

	vec_t CVector2D::operator[](int i) const {
		return ((vec_t*)this)[i];
	}

	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------

	vec_t* CVector2D::Base() {
		return (vec_t*)this;
	}

	vec_t const* CVector2D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool CVector2D::IsValid() const {
		return !isinf(x) && !isinf(y);
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool CVector2D::operator==(const CVector2D& src) const {
		return (src.x == x) && (src.y == y);
	}

	bool CVector2D::operator!=(const CVector2D& src) const {
		return (src.x != x) || (src.y != y);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------

	void CVector2DCopy(const CVector2D& src, CVector2D& dst) {
		dst.x = src.x;
		dst.y = src.y;
	}

	void	CVector2D::CopyToArray(float* rgfl) const {
		rgfl[0] = x; rgfl[1] = y;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------

	void CVector2D::Negate() {
		x = -x; y = -y;
	}

	void CVector2DAdd(const CVector2D& a, const CVector2D& b, CVector2D& c) {
		c.x = a.x + b.x;
		c.y = a.y + b.y;
	}

	void CVector2DSubtract(const CVector2D& a, const CVector2D& b, CVector2D& c) {
		c.x = a.x - b.x;
		c.y = a.y - b.y;
	}

	void CVector2DMultiply(const CVector2D& a, vec_t b, CVector2D& c) {
		c.x = a.x * b;
		c.y = a.y * b;
	}

	void CVector2DMultiply(const CVector2D& a, const CVector2D& b, CVector2D& c) {
		c.x = a.x * b.x;
		c.y = a.y * b.y;
	}


	void CVector2DDivide(const CVector2D& a, vec_t b, CVector2D& c) {
		vec_t oob = 1.0f / b;
		c.x = a.x * oob;
		c.y = a.y * oob;
	}

	void CVector2DDivide(const CVector2D& a, const CVector2D& b, CVector2D& c) {
		c.x = a.x / b.x;
		c.y = a.y / b.y;
	}

	void CVector2DMA(const CVector2D& start, float s, const CVector2D& dir, CVector2D& result) {
		result.x = start.x + s * dir.x;
		result.y = start.y + s * dir.y;
	}

	// FIXME: Remove
	// For backwards compatability
	void	CVector2D::MulAdd(const CVector2D& a, const CVector2D& b, float scalar) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
	}

	void CVector2DLerp(const CVector2D& src1, const CVector2D& src2, vec_t t, CVector2D& dest) {
		dest[0] = src1[0] + (src2[0] - src1[0]) * t;
		dest[1] = src1[1] + (src2[1] - src1[1]) * t;
	}

	//-----------------------------------------------------------------------------
	// dot, cross
	//-----------------------------------------------------------------------------
	vec_t DotProduct2D(const CVector2D& a, const CVector2D& b) {
		return(a.x * b.x + a.y * b.y);
	}

	// for backwards compatability
	vec_t CVector2D::Dot(const CVector2D& vOther) const {
		return DotProduct2D(*this, vOther);
	}

	vec_t CVector2DNormalize(CVector2D& v) {
		vec_t l = v.Length();
		if (l != 0.0f) {
			v /= l;
		}
		else {
			v.x = v.y = 0.0f;
		}
		return l;
	}

	//-----------------------------------------------------------------------------
	// length
	//-----------------------------------------------------------------------------
	vec_t CVector2DLength(const CVector2D& v) {
		return (vec_t)sqrt(v.x * v.x + v.y * v.y);
	}

	vec_t CVector2D::NormalizeInPlace() {
		return CVector2DNormalize(*this);
	}

	bool CVector2D::IsLengthGreaterThan(float val) const {
		return LengthSqr() > val* val;
	}

	bool CVector2D::IsLengthLessThan(float val) const {
		return LengthSqr() < val * val;
	}

	vec_t CVector2D::Length(void) const {
		return CVector2DLength(*this);
	}


	void CVector2DMin(const CVector2D& a, const CVector2D& b, CVector2D& result) {
		result.x = (a.x < b.x) ? a.x : b.x;
		result.y = (a.y < b.y) ? a.y : b.y;
	}


	void CVector2DMax(const CVector2D& a, const CVector2D& b, CVector2D& result) {
		result.x = (a.x > b.x) ? a.x : b.x;
		result.y = (a.y > b.y) ? a.y : b.y;
	}

	//-----------------------------------------------------------------------------
	// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
	//-----------------------------------------------------------------------------
	void ComputeClosestPoint2D(const CVector2D& vecStart, float flMaxDist, const CVector2D& vecTarget, CVector2D* pResult) {
		CVector2D vecDelta;
		CVector2DSubtract(vecTarget, vecStart, vecDelta);
		float flDistSqr = vecDelta.LengthSqr();
		if (flDistSqr <= flMaxDist * flMaxDist) {
			*pResult = vecTarget;
		}
		else {
			vecDelta /= sqrt(flDistSqr);
			CVector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
		}
	}

	//-----------------------------------------------------------------------------
	// Returns a CVector2D with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------

	CVector2D CVector2D::Min(const CVector2D& vOther) const {
		return CVector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
	}

	CVector2D CVector2D::Max(const CVector2D& vOther) const {
		return CVector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	CVector2D CVector2D::operator-(void) const {
		return CVector2D(-x, -y);
	}

	CVector2D CVector2D::operator+(const CVector2D& v) const {
		CVector2D res;
		CVector2DAdd(*this, v, res);
		return res;
	}

	CVector2D CVector2D::operator-(const CVector2D& v) const {
		CVector2D res;
		CVector2DSubtract(*this, v, res);
		return res;
	}

	CVector2D CVector2D::operator*(float fl) const {
		CVector2D res;
		CVector2DMultiply(*this, fl, res);
		return res;
	}

	CVector2D CVector2D::operator*(const CVector2D& v) const {
		CVector2D res;
		CVector2DMultiply(*this, v, res);
		return res;
	}

	CVector2D CVector2D::operator/(float fl) const {
		CVector2D res;
		CVector2DDivide(*this, fl, res);
		return res;
	}

	CVector2D CVector2D::operator/(const CVector2D& v) const {
		CVector2D res;
		CVector2DDivide(*this, v, res);
		return res;
	}

	CVector2D operator*(float fl, const CVector2D& v) {
		return v * fl;
	}
}
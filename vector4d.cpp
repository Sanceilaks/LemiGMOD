#include <cmath>
#include "Vector4D.h"
#include <limits>

namespace Math
{

	void VectorCopy(const CVector4D& src, CVector4D& dst) {
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
		dst.w = src.w;
	}
	void VectorLerp(const CVector4D& src1, const CVector4D& src2, vec_t t, CVector4D& dest) {
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
		dest.w = src1.w + (src2.w - src1.w) * t;
	}
	float VectorLength(const CVector4D& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	vec_t NormalizeVector(CVector4D& v) {
		vec_t l = v.Length();
		if (l != 0.0f) {
			v /= l;
		}
		else {
			v.x = v.y = v.z = v.w = 0.0f;
		}
		return l;
	}

	CVector4D::CVector4D(void) {
		Invalidate();
	}
	CVector4D::CVector4D(vec_t X, vec_t Y, vec_t Z, vec_t W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
	CVector4D::CVector4D(vec_t* clr) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
		w = clr[3];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void CVector4D::Init(vec_t ix, vec_t iy, vec_t iz, vec_t iw) {
		x = ix; y = iy; z = iz; w = iw;
	}

	void CVector4D::Random(vec_t minVal, vec_t maxVal) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
	void CVector4D::Zero() {
		x = y = z = w = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	CVector4D& CVector4D::operator=(const CVector4D& vOther) {
		x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
		return *this;
	}


	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------
	vec_t& CVector4D::operator[](int i) {
		return ((vec_t*)this)[i];
	}

	vec_t CVector4D::operator[](int i) const {
		return ((vec_t*)this)[i];
	}


	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------
	vec_t* CVector4D::Base() {
		return (vec_t*)this;
	}

	vec_t const* CVector4D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool CVector4D::IsValid() const {
		return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
	}

	//-----------------------------------------------------------------------------
	// Invalidate
	//-----------------------------------------------------------------------------

	void CVector4D::Invalidate() {
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = w = std::numeric_limits<float>::infinity();
		//#endif
		//#endif
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool CVector4D::operator==(const CVector4D& src) const {
		return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
	}

	bool CVector4D::operator!=(const CVector4D& src) const {
		return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------
	void	CVector4D::CopyToArray(float* rgfl) const {
		rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------
	// #pragma message("TODO: these should be SSE")

	void CVector4D::Negate() {
		x = -x; y = -y; z = -z; w = -w;
	}

	// get the component of this vector parallel to some other given vector
	CVector4D CVector4D::ProjectOnto(const CVector4D& onto) {
		return onto * (this->Dot(onto) / (onto.LengthSqr()));
	}

	// FIXME: Remove
	// For backwards compatability
	void	CVector4D::MulAdd(const CVector4D& a, const CVector4D& b, float scalar) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
		w = a.w + b.w * scalar;
	}

	CVector4D VectorLerp(const CVector4D& src1, const CVector4D& src2, vec_t t) {
		CVector4D result;
		VectorLerp(src1, src2, t, result);
		return result;
	}

	vec_t CVector4D::Dot(const CVector4D& b) const {
		return (x * b.x + y * b.y + z * b.z + w * b.w);
	}
	void VectorClear(CVector4D& a) {
		a.x = a.y = a.z = a.w = 0.0f;
	}

	vec_t CVector4D::Length(void) const {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	// check a point against a box
	bool CVector4D::WithinAABox(CVector4D const& boxmin, CVector4D const& boxmax) {
		return (
			(x >= boxmin.x) && (x <= boxmax.x) &&
			(y >= boxmin.y) && (y <= boxmax.y) &&
			(z >= boxmin.z) && (z <= boxmax.z) &&
			(w >= boxmin.w) && (w <= boxmax.w)
			);
	}

	//-----------------------------------------------------------------------------
	// Get the distance from this vector to the other one 
	//-----------------------------------------------------------------------------
	vec_t CVector4D::DistTo(const CVector4D& vOther) const {
		CVector4D delta;
		delta = *this - vOther;
		return delta.Length();
	}

	//-----------------------------------------------------------------------------
	// Returns a vector with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------
	CVector4D CVector4D::Min(const CVector4D& vOther) const {
		return CVector4D(x < vOther.x ? x : vOther.x,
			y < vOther.y ? y : vOther.y,
			z < vOther.z ? z : vOther.z,
			w < vOther.w ? w : vOther.w);
	}

	CVector4D CVector4D::Max(const CVector4D& vOther) const {
		return CVector4D(x > vOther.x ? x : vOther.x,
			y > vOther.y ? y : vOther.y,
			z > vOther.z ? z : vOther.z,
			w > vOther.w ? w : vOther.w);
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	CVector4D CVector4D::operator-(void) const {
		return CVector4D(-x, -y, -z, -w);
	}

	CVector4D CVector4D::operator+(const CVector4D& v) const {
		return CVector4D(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	CVector4D CVector4D::operator-(const CVector4D& v) const {
		return CVector4D(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	CVector4D CVector4D::operator*(float fl) const {
		return CVector4D(x * fl, y * fl, z * fl, w * fl);
	}

	CVector4D CVector4D::operator*(const CVector4D& v) const {
		return CVector4D(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	CVector4D CVector4D::operator/(float fl) const {
		return CVector4D(x / fl, y / fl, z / fl, w / fl);
	}

	CVector4D CVector4D::operator/(const CVector4D& v) const {
		return CVector4D(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	CVector4D operator*(float fl, const CVector4D& v) {
		return v * fl;
	}
}
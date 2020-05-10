#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

namespace Math
{
	typedef float vec_t;

	class CVector
	{
	public:
		// Members
		vec_t x, y, z;

		// Construction/destruction:
		CVector(void);
		CVector(vec_t X, vec_t Y, vec_t Z);
		CVector(vec_t* clr);

		// Initialization
		void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
		// TODO (Ilya): Should there be an init that takes a single float for consistency?

		// Got any nasty NAN's?
		bool IsValid() const;
		void Invalidate();

		// array access...
		vec_t operator[](int i) const;
		vec_t& operator[](int i);

		// Base address...
		vec_t* Base();
		vec_t const* Base() const;

		// Initialization methods
		void Random(vec_t minVal, vec_t maxVal);
		void Zero(); ///< zero out a CVector

		// equality
		bool operator==(const CVector& v) const;
		bool operator!=(const CVector& v) const;

		// arithmetic operations
		CVector& operator+=(const CVector& v) {
			x += v.x; y += v.y; z += v.z;
			return *this;
		}

		CVector& operator-=(const CVector& v) {
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}

		CVector& operator*=(float fl) {
			x *= fl;
			y *= fl;
			z *= fl;
			return *this;
		}

		CVector& operator*=(const CVector& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		CVector& operator/=(const CVector& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}

		// this ought to be an opcode.
		CVector& operator+=(float fl) {
			x += fl;
			y += fl;
			z += fl;
			return *this;
		}

		// this ought to be an opcode.
		CVector& operator/=(float fl) {
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}
		CVector& operator-=(float fl) {
			x -= fl;
			y -= fl;
			z -= fl;
			return *this;
		}

		// negate the CVector components
		void	Negate();

		// Get the CVector's magnitude.
		vec_t	Length() const;

		// Get the CVector's magnitude squared.
		vec_t LengthSqr(void) const {
			return (x * x + y * y + z * z);
		}

		// return true if this CVector is (0,0,0) within tolerance
		bool IsZero(float tolerance = 0.01f) const {
			return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance &&
				z > -tolerance && z < tolerance);
		}

		vec_t	NormalizeInPlace();
		CVector	Normalized() const;
		bool	IsLengthGreaterThan(float val) const;
		bool	IsLengthLessThan(float val) const;

		// check if a CVector is within the box defined by two other CVectors
		bool WithinAABox(CVector const& boxmin, CVector const& boxmax);

		// Get the distance from this CVector to the other one.
		vec_t	DistTo(const CVector& vOther) const;

		// Get the distance from this CVector to the other one squared.
		// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
		// may be able to tidy this up after switching to VC7
		vec_t DistToSqr(const CVector& vOther) const {
			CVector delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;
			delta.z = z - vOther.z;

			return delta.LengthSqr();
		}

		// Copy
		void	CopyToArray(float* rgfl) const;

		// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
		// is about 12% faster than the actual CVector equation (because it's done per-component
		// rather than per-CVector).
		void	MulAdd(const CVector& a, const CVector& b, float scalar);

		// Dot product.
		vec_t	Dot(const CVector& vOther) const;

		// assignment
		CVector& operator=(const CVector& vOther);

		// 2d
		vec_t	Length2D(void) const {
			return sqrt(x * x + y * y);
		}
		vec_t	Length2DSqr(void) const;

		/// get the component of this CVector parallel to some other given CVector
		CVector  ProjectOnto(const CVector& onto);

		// copy constructors
		//	CVector(const CVector &vOther);

		// arithmetic operations
		CVector	operator-(void) const;

		CVector	operator+(const CVector& v) const;
		CVector	operator-(const CVector& v) const;
		CVector	operator*(const CVector& v) const;
		CVector	operator/(const CVector& v) const;
		CVector	operator*(float fl) const;
		CVector	operator/(float fl) const;

		// Cross product between two CVectors.
		CVector	Cross(const CVector& vOther) const;

		// Returns a CVector with the min or max in X, Y, and Z.
		CVector	Min(const CVector& vOther) const;
		CVector	Max(const CVector& vOther) const;
	};

	void CVectorCopy(const CVector& src, CVector& dst);
	float CVectorLength(const CVector& v);
	void CVectorLerp(const CVector& src1, const CVector& src2, vec_t t, CVector& dest);
	void CVectorCrossProduct(const CVector& a, const CVector& b, CVector& result);
	vec_t NormalizeCVector(CVector& v);


	class __declspec(align(16)) CVectorAligned : public CVector {
	public:
		inline CVectorAligned(void) {};
		inline CVectorAligned(vec_t X, vec_t Y, vec_t Z) {
			Init(X, Y, Z);
		}

	public:
		explicit CVectorAligned(const CVector& vOther) {
			Init(vOther.x, vOther.y, vOther.z);
		}

		CVectorAligned& operator=(const CVector& vOther) {
			Init(vOther.x, vOther.y, vOther.z);
			return *this;
		}

		//CVectorAligned& operator=(const CVectorAligned& vOther) {
		//	_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
		//	return *this;
		//}

		float w;
	};
}
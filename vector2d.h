#pragma once

namespace Math
{

	typedef float vec_t;
	// 2D Vector
	class CVector2D {
	public:
		// Members
		vec_t x, y;

		// Construction/destruction:
		CVector2D(void);
		CVector2D(vec_t X, vec_t Y);
		CVector2D(vec_t* clr);

		//CVector2D::CVector2D(const CVector2D& vOther) {
		//	x = vOther.x; y = vOther.y;
		//}

		// Initialization
		void Init(vec_t ix = 0.0f, vec_t iy = 0.0f);
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
		void Zero(); ///< zero out a vector

		// equality
		bool operator==(const CVector2D& v) const;
		bool operator!=(const CVector2D& v) const;

		// arithmetic operations
		CVector2D& operator+=(const CVector2D& v) {
			x += v.x; y += v.y;
			return *this;
		}

		CVector2D& operator-=(const CVector2D& v) {
			x -= v.x; y -= v.y;
			return *this;
		}

		CVector2D& operator*=(float fl) {
			x *= fl;
			y *= fl;
			return *this;
		}

		CVector2D& operator*=(const CVector2D& v) {
			x *= v.x;
			y *= v.y;
			return *this;
		}

		CVector2D& operator/=(const CVector2D& v) {
			x /= v.x;
			y /= v.y;
			return *this;
		}

		// this ought to be an opcode.
		CVector2D& operator+=(float fl) {
			x += fl;
			y += fl;
			return *this;
		}

		// this ought to be an opcode.
		CVector2D& operator/=(float fl) {
			x /= fl;
			y /= fl;
			return *this;
		}
		CVector2D& operator-=(float fl) {
			x -= fl;
			y -= fl;
			return *this;
		}

		// negate the vector components
		void	Negate();

		// Get the vector's magnitude.
		vec_t	Length() const;

		// Get the vector's magnitude squared.
		vec_t LengthSqr(void) const {
			return (x * x + y * y);
		}

		// return true if this vector is (0,0,0) within tolerance
		bool IsZero(float tolerance = 0.01f) const {
			return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance);
		}

		vec_t	NormalizeInPlace();
		CVector2D	Normalized() const;
		bool	IsLengthGreaterThan(float val) const;
		bool	IsLengthLessThan(float val) const;

		// check if a vector is within the box defined by two other vectors
		bool WithinAABox(CVector2D const& boxmin, CVector2D const& boxmax);

		// Get the distance from this vector to the other one.
		vec_t	DistTo(const CVector2D& vOther) const;

		// Get the distance from this vector to the other one squared.
		// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
		// may be able to tidy this up after switching to VC7
		vec_t DistToSqr(const CVector2D& vOther) const {
			CVector2D delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;

			return delta.LengthSqr();
		}

		// Copy
		void	CopyToArray(float* rgfl) const;

		// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
		// is about 12% faster than the actual vector equation (because it's done per-component
		// rather than per-vector).
		void	MulAdd(const CVector2D& a, const CVector2D& b, float scalar);

		// Dot product.
		vec_t	Dot(const CVector2D& vOther) const;

		// assignment
		CVector2D& operator=(const CVector2D& vOther);

		// 2d
		vec_t	Length2D(void) const;
		vec_t	Length2DSqr(void) const;

		/// get the component of this vector parallel to some other given vector
		CVector2D  ProjectOnto(const CVector2D& onto);

		// copy constructors
		//	CVector2D(const CVector2D &vOther);

		// arithmetic operations
		CVector2D	operator-(void) const;

		CVector2D	operator+(const CVector2D& v) const;
		CVector2D	operator-(const CVector2D& v) const;
		CVector2D	operator*(const CVector2D& v) const;
		CVector2D	operator/(const CVector2D& v) const;
		CVector2D	operator*(float fl) const;
		CVector2D	operator/(float fl) const;

		// Cross product between two vectors.
		CVector2D	Cross(const CVector2D& vOther) const;

		// Returns a vector with the min or max in X, Y, and Z.
		CVector2D	Min(const CVector2D& vOther) const;
		CVector2D	Max(const CVector2D& vOther) const;
	};
}
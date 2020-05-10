#pragma once

#include "QAngle.h"
namespace Math {

	//struct cplane_t
	//{
	//	CVector	normal;
	//	float	dist;
	//	byte	type;			// for fast side tests +
	//	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	//	byte	pad[2];

	//};

	class matrix3x4_t {
	public:
		matrix3x4_t() {}
		matrix3x4_t(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23) {
			m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
			m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
			m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
		}
		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		void Init(const CVector& xAxis, const CVector& yAxis, const CVector& zAxis, const CVector& vecOrigin) {
			m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
			m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
			m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
		}

		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		matrix3x4_t(const CVector& xAxis, const CVector& yAxis, const CVector& zAxis, const CVector& vecOrigin) {
			Init(xAxis, yAxis, zAxis, vecOrigin);
		}

		inline void SetOrigin(CVector const& p) {
			m_flMatVal[0][3] = p.x;
			m_flMatVal[1][3] = p.y;
			m_flMatVal[2][3] = p.z;
		}

		inline void Invalidate(void) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					m_flMatVal[i][j] = std::numeric_limits<float>::infinity();;
				}
			}
		}

		float* operator[](int i) { return m_flMatVal[i]; }
		const float* operator[](int i) const { return m_flMatVal[i]; }
		float* Base() { return &m_flMatVal[0][0]; }
		const float* Base() const { return &m_flMatVal[0][0]; }

		float m_flMatVal[3][4];
	};
	class VMatrix {
	public:

		VMatrix();
		VMatrix(
			vec_t m00, vec_t m01, vec_t m02, vec_t m03,
			vec_t m10, vec_t m11, vec_t m12, vec_t m13,
			vec_t m20, vec_t m21, vec_t m22, vec_t m23,
			vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);

		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		VMatrix(const CVector& forward, const CVector& left, const CVector& up);

		// Construct from a 3x4 matrix
		VMatrix(const matrix3x4_t& matrix3x4);

		// Set the values in the matrix.
		void		Init(
			vec_t m00, vec_t m01, vec_t m02, vec_t m03,
			vec_t m10, vec_t m11, vec_t m12, vec_t m13,
			vec_t m20, vec_t m21, vec_t m22, vec_t m23,
			vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);


		// Initialize from a 3x4
		void		Init(const matrix3x4_t& matrix3x4);

		// array access
		inline float* operator[](int i) {
			return m[i];
		}

		inline const float* operator[](int i) const {
			return m[i];
		}

		// Get a pointer to m[0][0]
		inline float* Base() {
			return &m[0][0];
		}

		inline const float* Base() const {
			return &m[0][0];
		}

		void		SetLeft(const CVector& vLeft);
		void		SetUp(const CVector& vUp);
		void		SetForward(const CVector& vForward);

		void		GetBasisCVectors(CVector& vForward, CVector& vLeft, CVector& vUp) const;
		void		SetBasisCVectors(const CVector& vForward, const CVector& vLeft, const CVector& vUp);

		// Get/set the translation.
		CVector& GetTranslation(CVector& vTrans) const;
		void		SetTranslation(const CVector& vTrans);

		void		PreTranslate(const CVector& vTrans);
		void		PostTranslate(const CVector& vTrans);

		matrix3x4_t& As3x4();
		const matrix3x4_t& As3x4() const;
		void		CopyFrom3x4(const matrix3x4_t& m3x4);
		void		Set3x4(matrix3x4_t& matrix3x4) const;

		bool		operator==(const VMatrix& src) const;
		bool		operator!=(const VMatrix& src) const { return !(*this == src); }

		// Access the basis CVectors.
		CVector		GetLeft() const;
		CVector		GetUp() const;
		CVector		GetForward() const;
		CVector		GetTranslation() const;


		// Matrix->CVector operations.
	public:
		// Multiply by a 3D CVector (same as operator*).
		void		V3Mul(const CVector& vIn, CVector& vOut) const;

		// Multiply by a 4D CVector.
		//void		V4Mul( const CVector4D &vIn, CVector4D &vOut ) const;

		// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
		CVector		ApplyRotation(const CVector& vVec) const;

		// Multiply by a CVector (divides by w, assumes input w is 1).
		CVector		operator*(const CVector& vVec) const;

		// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
		CVector		VMul3x3(const CVector& vVec) const;

		// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
		CVector		VMul3x3Transpose(const CVector& vVec) const;

		// Multiply by the upper 3 rows.
		CVector		VMul4x3(const CVector& vVec) const;

		// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
		CVector		VMul4x3Transpose(const CVector& vVec) const;


		// Matrix->plane operations.
	//public:
		// Transform the plane. The matrix can only contain translation and rotation.
		//void		TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

		// Just calls TransformPlane and returns the result.
		//VPlane		operator*(const VPlane &thePlane) const;

		// Matrix->matrix operations.
	public:

		VMatrix& operator=(const VMatrix& mOther);

		// Multiply two matrices (out = this * vm).
		void		MatrixMul(const VMatrix& vm, VMatrix& out) const;

		// Add two matrices.
		const VMatrix& operator+=(const VMatrix& other);

		// Just calls MatrixMul and returns the result.	
		VMatrix		operator*(const VMatrix& mOther) const;

		// Add/Subtract two matrices.
		VMatrix		operator+(const VMatrix& other) const;
		VMatrix		operator-(const VMatrix& other) const;

		// Negation.
		VMatrix		operator-() const;

		// Return inverse matrix. Be careful because the results are undefined 
		// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
		VMatrix		operator~() const;

		// Matrix operations.
	public:
		// Set to identity.
		void		Identity();

		bool		IsIdentity() const;

		// Setup a matrix for origin and angles.
		void		SetupMatrixOrgAngles(const CVector& origin, const QAngle& vAngles);

		// General inverse. This may fail so check the return!
		bool		InverseGeneral(VMatrix& vInverse) const;

		// Does a fast inverse, assuming the matrix only contains translation and rotation.
		void		InverseTR(VMatrix& mRet) const;

		// Usually used for debug checks. Returns true if the upper 3x3 contains
		// unit CVectors and they are all orthogonal.
		bool		IsRotationMatrix() const;

		// This calls the other InverseTR and returns the result.
		VMatrix		InverseTR() const;

		// Get the scale of the matrix's basis CVectors.
		CVector		GetScale() const;

		// (Fast) multiply by a scaling matrix setup from vScale.
		VMatrix		Scale(const CVector& vScale);

		// Normalize the basis CVectors.
		VMatrix		NormalizeBasisCVectors() const;

		// Transpose.
		VMatrix		Transpose() const;

		// Transpose upper-left 3x3.
		VMatrix		Transpose3x3() const;

	public:
		// The matrix.
		vec_t		m[4][4];
	};
}
#include "VMatrix.h"

namespace Math
{
	inline VMatrix::VMatrix() {
	}

	inline VMatrix::VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33) {
		Init(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		);
	}


	inline VMatrix::VMatrix(const matrix3x4_t& matrix3x4) {
		Init(matrix3x4);
	}


	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix(const CVector& xAxis, const CVector& yAxis, const CVector& zAxis) {
		Init(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	inline void VMatrix::Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}


	//-----------------------------------------------------------------------------
	// Initialize from a 3x4
	//-----------------------------------------------------------------------------
	inline void VMatrix::Init(const matrix3x4_t& matrix3x4) {
		memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// CVector3DMultiplyPosition treats src2 as if it's a point (adds the translation)
	//-----------------------------------------------------------------------------
	// NJS: src2 is passed in as a full CVector rather than a reference to prevent the need
	// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
	// reference is the same as the dst reference ).
	inline void CVector3DMultiplyPosition(const VMatrix& src1, const CVector& src2, CVector& dst) {
		dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
		dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
		dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
	}

	//-----------------------------------------------------------------------------
	// Methods related to the basis CVectors of the matrix
	//-----------------------------------------------------------------------------

	inline CVector VMatrix::GetForward() const {
		return CVector(m[0][0], m[1][0], m[2][0]);
	}

	inline CVector VMatrix::GetLeft() const {
		return CVector(m[0][1], m[1][1], m[2][1]);
	}

	inline CVector VMatrix::GetUp() const {
		return CVector(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetForward(const CVector& vForward) {
		m[0][0] = vForward.x;
		m[1][0] = vForward.y;
		m[2][0] = vForward.z;
	}

	inline void VMatrix::SetLeft(const CVector& vLeft) {
		m[0][1] = vLeft.x;
		m[1][1] = vLeft.y;
		m[2][1] = vLeft.z;
	}

	inline void VMatrix::SetUp(const CVector& vUp) {
		m[0][2] = vUp.x;
		m[1][2] = vUp.y;
		m[2][2] = vUp.z;
	}

	inline void VMatrix::GetBasisCVectors(CVector& vForward, CVector& vLeft, CVector& vUp) const {
		vForward.Init(m[0][0], m[1][0], m[2][0]);
		vLeft.Init(m[0][1], m[1][1], m[2][1]);
		vUp.Init(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetBasisCVectors(const CVector& vForward, const CVector& vLeft, const CVector& vUp) {
		SetForward(vForward);
		SetLeft(vLeft);
		SetUp(vUp);
	}


	//-----------------------------------------------------------------------------
	// Methods related to the translation component of the matrix
	//-----------------------------------------------------------------------------

	inline CVector VMatrix::GetTranslation() const {
		return CVector(m[0][3], m[1][3], m[2][3]);
	}

	inline CVector& VMatrix::GetTranslation(CVector& vTrans) const {
		vTrans.x = m[0][3];
		vTrans.y = m[1][3];
		vTrans.z = m[2][3];
		return vTrans;
	}

	inline void VMatrix::SetTranslation(const CVector& vTrans) {
		m[0][3] = vTrans.x;
		m[1][3] = vTrans.y;
		m[2][3] = vTrans.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the input space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PreTranslate(const CVector& vTrans) {
		CVector tmp;
		CVector3DMultiplyPosition(*this, vTrans, tmp);
		m[0][3] = tmp.x;
		m[1][3] = tmp.y;
		m[2][3] = tmp.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the output space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PostTranslate(const CVector& vTrans) {
		m[0][3] += vTrans.x;
		m[1][3] += vTrans.y;
		m[2][3] += vTrans.z;
	}

	inline const matrix3x4_t& VMatrix::As3x4() const {
		return *((const matrix3x4_t*)this);
	}

	inline matrix3x4_t& VMatrix::As3x4() {
		return *((matrix3x4_t*)this);
	}

	inline void VMatrix::CopyFrom3x4(const matrix3x4_t& m3x4) {
		memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;
	}

	inline void	VMatrix::Set3x4(matrix3x4_t& matrix3x4) const {
		memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
	}


	//-----------------------------------------------------------------------------
	// Matrix math operations
	//-----------------------------------------------------------------------------
	inline const VMatrix& VMatrix::operator+=(const VMatrix& other) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] += other.m[i][j];
			}
		}

		return *this;
	}

	inline VMatrix VMatrix::operator+(const VMatrix& other) const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
		}
		return ret;
	}

	inline VMatrix VMatrix::operator-(const VMatrix& other) const {
		VMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return ret;
	}

	inline VMatrix VMatrix::operator-() const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = -((float*)m)[i];
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	// CVector transformation
	//-----------------------------------------------------------------------------


	inline CVector VMatrix::operator*(const CVector& vVec) const {
		CVector vRet;
		vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
		vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
		vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

		return vRet;
	}

	inline CVector VMatrix::VMul4x3(const CVector& vVec) const {
		CVector vResult;
		CVector3DMultiplyPosition(*this, vVec, vResult);
		return vResult;
	}


	inline CVector VMatrix::VMul4x3Transpose(const CVector& vVec) const {
		CVector tmp = vVec;
		tmp.x -= m[0][3];
		tmp.y -= m[1][3];
		tmp.z -= m[2][3];

		return CVector(
			m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
			m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
			m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
		);
	}

	inline CVector VMatrix::VMul3x3(const CVector& vVec) const {
		return CVector(
			m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
			m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
			m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
		);
	}

	inline CVector VMatrix::VMul3x3Transpose(const CVector& vVec) const {
		return CVector(
			m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
			m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
			m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
		);
	}


	inline void VMatrix::V3Mul(const CVector& vIn, CVector& vOut) const {
		vec_t rw;

		rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
		vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
		vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
		vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
	}

	//-----------------------------------------------------------------------------
	// Other random stuff
	//-----------------------------------------------------------------------------
	inline void VMatrix::Identity() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}


	inline bool VMatrix::IsIdentity() const {
		return
			m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
			m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
			m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
			m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
	}

	inline CVector VMatrix::ApplyRotation(const CVector& vVec) const {
		return VMul3x3(vVec);
	}

	inline VMatrix VMatrix::operator~() const {
		VMatrix mRet;
		InverseGeneral(mRet);
		return mRet;
	}
}
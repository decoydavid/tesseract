#pragma once

class RingsGenerator : public Generator
{
public:

	struct Ring_s
	{
		UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
		{
			int iResolution = xLattice.GetResolution();
			float x = float(i) / float(iResolution - 1) - 0.5f;
			float y = float(j) / float(iResolution - 1) - 0.5f;
			float z = float(k) / float(iResolution - 1) - 0.5f;

			static float fTimer = 0.0f;
			fTimer += 0.0001f;

			matrix3f mRot1 = matrix3f::IDENTITY;
			mRot1.rotate_y(fTimer);
			matrix3f mRot2 = matrix3f::IDENTITY;
			mRot2.rotate_x(fTimer * 0.5f);
			matrix3f mRot3 = matrix3f::IDENTITY;
			multiply<4,4,float>(mRot1, mRot2, mRot3);

			matrix3f mTrans = matrix3f::IDENTITY;
			mTrans.set_translation(vector3f(x, y, z));

			matrix3f mResult;
			matrix3f mResult2;
			multiply<4,4,float>(mRot3, mTrans, mResult2);
			multiply<4,4,float>(m_BaseRotation, mResult2, mResult);
			vector3f v;
			mResult.get_translation(v);

			float R = 0.5f;
			float r = 0.1f;

			float fA = (Sqr(R - sqrtf(Sqr(v.x()) + Sqr(v.y()))) + Sqr(v.z()));
			if (fA < Sqr(r))
			{
				float fDist = sqrtf(fA);
				float fScale = (r - fDist) / r;
				return m_ucValue * fScale;
			}

			return 0;
		}

		matrix3f		m_BaseRotation;
		UCHAR			m_ucValue;
	};

	RingsGenerator()
	{
		m_xRing1.m_BaseRotation = matrix3f::IDENTITY;
		m_xRing2.m_BaseRotation = matrix3f::IDENTITY;
		m_xRing3.m_BaseRotation = matrix3f::IDENTITY;
		m_xRing2.m_BaseRotation.rotate_x(3.141592f / 2.0f);
		//m_xRing3.m_BaseRotation.rotate_y(3.141592f / 2.0f);

		m_xRing1.m_ucValue = 255;
		m_xRing2.m_ucValue = 255;
		m_xRing3.m_ucValue = 255;

		fTime = 0.0f;
	}
	virtual ~RingsGenerator()
	{}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		fTime += 0.01f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		return m_xRing1.GenerateValue(xLattice, i, j, k) +
			m_xRing2.GenerateValue(xLattice, i, j, k) +
			m_xRing3.GenerateValue(xLattice, i, j, k);
	}

private:
	Ring_s m_xRing1;
	Ring_s m_xRing2;
	Ring_s m_xRing3;

	float fTime;
};
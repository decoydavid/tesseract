#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class SpherifyGenerator : public Generator
{
public:
	SpherifyGenerator()
		: m_fRadius(0.0f)
		, m_fTimer(0.0f)
	{
/*
		m_vecPoints.push_back(vector3f(+1, -1, -1));
		m_vecPoints.push_back(vector3f(-1, -1, -1));
		m_vecPoints.push_back(vector3f(+1, +1, -1));
		m_vecPoints.push_back(vector3f(-1, +1, -1));
		m_vecPoints.push_back(vector3f(+1, -1, +1));
		m_vecPoints.push_back(vector3f(-1, -1, +1));
		m_vecPoints.push_back(vector3f(+1, +1, +1));
		m_vecPoints.push_back(vector3f(-1, +1, +1));*/
	}

	virtual void Update(Lattice &xLattice)
	{
		m_fTimer += 0.5f;

		m_fRadius = (sinf(m_fTimer*0.01f)+1.0f)*0.2f;

		if (((rand() % 20) == 0) && m_vecPoints.size() < 20)
		{
			vector3f v(GetRandFloatNeg(), GetRandFloatNeg(), GetRandFloatNeg());
			v.normalize();
			v *= 0.01f;
			m_vecPoints.push_back(v);
		}

		for (std::vector<vector3f>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			vector3f vForce = -(*iter);
			for (std::vector<vector3f>::iterator iter2 = m_vecPoints.begin(); iter2 != m_vecPoints.end(); ++iter2)
			{
				vector3f vDiff = (*iter2) - *iter;
				float fLen = std::max(vDiff.length(), 0.001f);
				float fInvLen = 1.0f / fLen;
				
				vForce -= (vDiff / fLen) * fInvLen;
			}

			(*iter) += vForce * 0.01f;
		}

		Generator::Update(xLattice);
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float x = float(i) / float(iResolution - 1);
		float y = float(j) / float(iResolution - 1);
		float z = float(k) / float(iResolution - 1);

		vector3f vPos(x - 0.5f, y - 0.5f, z - 0.5f);
		vPos = vPos;

		matrix3f mRot1 = matrix3f::IDENTITY;
		mRot1.rotate_x(m_fTimer * 0.01f);
		matrix3f mRot2 = matrix3f::IDENTITY;
		mRot2.rotate_y(m_fTimer * 0.1f);
		matrix3f mRot3 = matrix3f::IDENTITY;
		multiply<4,4,float>(mRot1, mRot2, mRot3);

		matrix3f mTrans = matrix3f::IDENTITY;
		mTrans.set_translation(vPos);

		matrix3f mResult;
		multiply<4,4,float>(mRot3, mTrans, mResult);
		mResult.get_translation(vPos);


		for (std::vector<vector3f>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			float fDist = (vPos - (*iter) * m_fRadius).length();
			const float fMaxDist = (1.0f/float(iResolution-1)) * m_fRadius * 8.0f;
			if (fDist <= fMaxDist)
			{
				return UCHAR(((fMaxDist - fDist) / fMaxDist) * 255);
			}
		}

		return 0;
	}

private:
	float	m_fRadius;
	float	m_fTimer;
	std::vector<vector3f>		m_vecPoints;

};
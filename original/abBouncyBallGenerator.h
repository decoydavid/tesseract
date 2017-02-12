#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class BouncyBallGenerator : public Generator
{
public:
	BouncyBallGenerator()
		: m_fTimer(0.0f)
	{
		m_vVelocity = vector3f(GetRandFloatNeg(), GetRandFloatNeg(), GetRandFloatNeg());
		m_vPosition = vector3f(GetRandFloat(), GetRandFloat(), GetRandFloat());
	}

	virtual void Update(Lattice &xLattice)
	{
		m_vPosition += m_vVelocity * 0.08f;

		for( int i = 0; i < 3; i++ )
		{
			if (m_vPosition[i] < 0.0f || m_vPosition[i] > 1.0f)
				m_vVelocity[i] = -m_vVelocity[i];
		}

		m_fTimer += 0.003f;

		Generator::Update(xLattice);
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float x = float(i) / float(iResolution - 1);
		float y = float(j) / float(iResolution - 1);
		float z = float(k) / float(iResolution - 1);

		float fDist = (vector3f(x,y,z) - m_vPosition).length();
		const float fMaxDist = (sinf(m_fTimer * 3.0f) + 1.0f) * 0.35f + 0.05f;
		if( std::abs(fDist - fMaxDist) < 0.05f )
		{
			return 255;//UCHAR(((fMaxDist - fDist) / fMaxDist) * 255);
		}

		return 0;
	}

private:
	vector3f	m_vVelocity;
	vector3f	m_vPosition;
	float		m_fTimer;

};
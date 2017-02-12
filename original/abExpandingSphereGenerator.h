#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class ExpandingSphereGenerator : public Generator
{
public:
	ExpandingSphereGenerator()
		: m_fRadius(0.0f)
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		static float fTimer = 0.0f;
		fTimer += 0.01f;

		m_fRadius = cosf(fTimer)*0.8f;

		Generator::Update(xLattice);
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float x = float(i) / float(iResolution - 1);
		float y = float(j) / float(iResolution - 1);
		float z = float(k) / float(iResolution - 1);

		vector3f vPos(x-0.5f,y-0.5f,z-0.5f);

		float fDist = std::abs(vPos.length() - std::abs(m_fRadius));
		const float fMaxDist = 0.1f;
		if( fDist <= fMaxDist )
		{
			return UCHAR(((fMaxDist - fDist) / fMaxDist) * 255);
		}

		return 0;
	}

private:
	float	m_fRadius;

};
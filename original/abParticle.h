#pragma once

#include "abLattice.h"

struct Particle_s
{
	UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float x = float(i) / float(iResolution - 1);
		float y = float(j) / float(iResolution - 1);
		float z = float(k) / float(iResolution - 1);

		float fDist = (vector3f(x, y, z) - m_vPosition).length();
		const float fMaxDist = m_fRadius;
		if (fDist < fMaxDist)
		{
			return UCHAR(((fMaxDist - fDist) / fMaxDist) * 255);
		}

		return 0;
	}

	void Update(Lattice &xLattice)
	{
		++m_iLifeTick;
		m_vPosition += m_vVelocity * 0.05f * (m_vPosition.z() + 0.5f);
	}

	vector3f	m_vVelocity;
	vector3f	m_vPosition;
	float		m_fRadius;
	int			m_iLifeTick;
};
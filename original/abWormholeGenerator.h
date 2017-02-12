#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"

class WormholeGenerator : public Generator
{
public:

	WormholeGenerator()
		: m_fTime(0.0f)
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		m_fTime += 0.05f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float fDelayedTime = m_fTime + 0.05f * float(i*i);

		vector3f v(0.0f, float(j)/(iResolution-1), float(k)/(iResolution-1));
		
		vector3f vWHCentre(0.0f, (sinf(fDelayedTime)) * 0.25f + 0.5f, (cosf(fDelayedTime)) * 0.25f + 0.5f);

		vector3f vDiff = vWHCentre - v;

		const float fMaxDist = 0.3f + sinf(fDelayedTime * 0.1f) * 0.1f;
		const float fMinDist = 0.2f + sinf(fDelayedTime * 0.1f) * 0.1f;
		float fDist = vDiff.length();
		if( fDist < fMaxDist )
		{
			float fNormalized = (fDist - fMinDist) / (fMaxDist - fMinDist);
			fNormalized = std::max(fNormalized, 0.0f);
			return 255 * (1.0f - fNormalized);
		}
		
		return (UCHAR)0;
	}

private:
	float		m_fTime;

};
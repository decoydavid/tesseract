#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"

class CheckerboardGenerator : public Generator
{
public:

	CheckerboardGenerator()
		: m_fTime(0.0f)
		, m_fTime2(0.0f)
		, m_fTime3(0.0f)
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		m_fTime += 0.25f * sinf(m_fTime2);
		m_fTime2 += 0.01f;
		m_fTime3 += 0.01f * cosf(m_fTime2 * 2.0f) + 0.001f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		
		int iTime = ((int)m_fTime) % 2;
		int iTime3 = ((int)m_fTime3) % 8;

		bool bOn = false;

		if( ((i/2) + (j/2) + (k/2)) % 2 == iTime )
			bOn = true;

		return bOn ? 255 : 0;
	}

private:
	float		m_fTime;
	float		m_fTime2;
	float		m_fTime3;

};
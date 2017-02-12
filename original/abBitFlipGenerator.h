#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"

class BitFlipGenerator : public Generator
{
public:

	struct Point_s
	{
		float fHeight;
		float fVelocity;
	};

	BitFlipGenerator(int iResolution)
		: m_fTime(0.0f)
		, m_fNextFlip(0.0f)
	{
		m_vecPoints.resize(iResolution * iResolution);

		for (std::vector<Point_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			Point_s &xPoint = *iter;
			xPoint.fHeight = (rand() % 2);
			xPoint.fVelocity = 0.0f;
		}
	}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		m_fTime += 0.3f;

		m_fNextFlip -= 0.01f;
		if ( m_fNextFlip < 0.0f )
		{
			int iNumBitsToFlip = 35;
			for (int i = 0; i < iNumBitsToFlip; i++)
			{
				int iBitToFlip = rand() % m_vecPoints.size();
				if (m_vecPoints[iBitToFlip].fVelocity == 0.0f)
				{
					m_vecPoints[iBitToFlip].fVelocity = (((rand() % 2) == 0) ? -1.0f : 1.0f) * (GetRandFloat() + 0.5f);
				}
			}
			m_fNextFlip = 1.0f + GetRandFloat() * 2.0f;
		}

		const float fMoveSpeed = 0.08f;
		for (std::vector<Point_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			float fMultiplier = ((iter->fHeight) + 0.1f);
			if ((*iter).fVelocity < 0.0f)
				fMultiplier *= 1.0f;

			(*iter).fHeight += (*iter).fVelocity * fMoveSpeed * fMultiplier;
			if ((*iter).fHeight >= 1.0f)
			{
				(*iter).fHeight = 1.0f;
				(*iter).fVelocity = 0.0f;
			}
			if ((*iter).fHeight <= 0.0f)
			{
				(*iter).fHeight = 0.0f;
				(*iter).fVelocity = 0.0f;
			}
		}
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();

		unsigned char ucValue = 0;
		float x = float(i) / float(iResolution - 1);
		float y = float(j) / float(iResolution - 1);
		float z = float(k) / float(iResolution - 1);

		float fDist = std::abs(z - m_vecPoints[j*iResolution + i].fHeight);

		if (fDist < 0.1f)
			return 255;

		return 0;
	}

private:
	float		m_fTime;
	float		m_fNextFlip;

	std::vector<Point_s>	m_vecPoints;

};
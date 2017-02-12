#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class BubblesGenerator : public Generator
{
public:
	struct Bubble_s
	{
		Bubble_s()
		{

		}

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
			m_vPosition += m_vVelocity * 0.05f * (m_vPosition.z() + 0.5f);
		}

		vector3f	m_vVelocity;
		vector3f	m_vPosition;
		float		m_fRadius;

	};

	BubblesGenerator()
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		for (std::vector<Bubble_s>::iterator iter = m_vecBubbles.begin(); iter != m_vecBubbles.end();)
		{
			Bubble_s &xBubble = *iter;
			xBubble.Update(xLattice);

			if( xBubble.m_vPosition.z() >= 1.0f + xBubble.m_fRadius )
				iter = m_vecBubbles.erase(iter);
			else
				++iter;
		}

		if( GetRandFloat() >= 0.96f )
		{
			Bubble_s xBubble;
			xBubble.m_fRadius = GetRandFloat() * 0.1f + 0.2f;
			xBubble.m_vPosition = vector3f(GetRandFloat(), GetRandFloat(), -xBubble.m_fRadius);
			xBubble.m_vVelocity = vector3f(0.0f, 0.0f, 0.2f * GetRandFloat() + 0.1f);
			m_vecBubbles.push_back(xBubble);
		}

		Generator::Update(xLattice);
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iTotalVal = 0;
		for (std::vector<Bubble_s>::iterator iter = m_vecBubbles.begin(); iter != m_vecBubbles.end(); ++iter)
		{
			Bubble_s &xBubble = *iter;
			iTotalVal += xBubble.GenerateValue(xLattice, i, j, k);
		}
		iTotalVal = std::min(iTotalVal, 255);
		return (UCHAR)iTotalVal;
	}

private:

	std::vector<Bubble_s>		m_vecBubbles;

};
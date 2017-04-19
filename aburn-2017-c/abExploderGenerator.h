#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"

class ExploderGenerator : public Generator
{
public:

	ExploderGenerator()
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		for (std::vector<Particle_s>::iterator iter = m_vecParticles.begin(); iter != m_vecParticles.end();)
		{
			Particle_s &xParticle = *iter;
			xParticle.Update(xLattice);

			// Gravity
			xParticle.m_vVelocity += vector3f(0.0f, 0.0f, -0.05f);

			if (xParticle.m_vPosition.z() < -xParticle.m_fRadius)
			{
				xParticle.m_vPosition.z() = -xParticle.m_fRadius;
				xParticle.m_vVelocity.z() *= -0.8f;
			}

			if( xParticle.m_iLifeTick > 100 )
				iter = m_vecParticles.erase(iter);
			else
				++iter;
		}

		if (GetRandFloat() >= 0.96f)
		{
			int iNumParticles = 10;
			vector3f vPos(GetRandFloat(), GetRandFloat(), GetRandFloat() * 0.5f + 0.5f);
			for( int i = 0; i < iNumParticles; i++ )
			{
				Particle_s xParticle;
				xParticle.m_fRadius = GetRandFloat() * 0.1f + 0.2f;
				xParticle.m_vPosition = vPos;
				xParticle.m_iLifeTick = 0;
				xParticle.m_vVelocity = vector3f(GetRandFloatNeg(), GetRandFloatNeg(), GetRandFloat()) * 0.5f;
				m_vecParticles.push_back(xParticle);
			}
		}

		Generator::Update(xLattice);
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iTotalVal = 0;
		for (std::vector<Particle_s>::iterator iter = m_vecParticles.begin(); iter != m_vecParticles.end(); ++iter)
		{
			Particle_s &xParticle = *iter;
			iTotalVal += xParticle.GenerateValue(xLattice, i, j, k);
		}
		iTotalVal = std::min(iTotalVal, 255);
		return (UCHAR)iTotalVal;
	}

private:

	std::vector<Particle_s>		m_vecParticles;

};
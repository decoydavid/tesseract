#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class FlockGenerator : public Generator
{
public:

	struct PointData_s
	{
		void Init()
		{
			vPosition = vector3f(GetRandFloat(), GetRandFloat(), GetRandFloat());
			vVelocity = vector3f(GetRandFloat(), GetRandFloat(), GetRandFloat());
		}
		void Bounce()
		{
			for (int i = 0; i < 3; i++)
			{
				if (vPosition[i] < 0.0f)
				{
					vVelocity[i] = -vVelocity[i];
					vPosition[i] = 0.0f;
				}
				if (vPosition[i] >= 1.0f)
				{
					vVelocity[i] = -vVelocity[i];
					vPosition[i] = 1.0f;
				}
			}
		}
		vector3f vPosition;
		vector3f vVelocity;
	};

	FlockGenerator(int iNumPoints, float fSpeed)
		: m_fSpeed(fSpeed)
	{
		for (int i = 0; i < iNumPoints; i++)
		{
			PointData_s xData;
			xData.Init();
			m_vecPoints.push_back(xData);
		}
		m_xAttractor.Init();
		m_xAttractor.vVelocity *= 0.2f;
		m_xRepulsor.Init();
		m_xRepulsor.vVelocity *= 0.2f;
	}

	virtual void Update(Lattice &xLattice)
	{
		static float fTimer = 0.0f;
		fTimer += 0.01f;

		m_xAttractor.vPosition += m_xAttractor.vVelocity * m_fSpeed * 3.0f;
		m_xRepulsor.vPosition += m_xRepulsor.vVelocity * m_fSpeed;
		m_xAttractor.vVelocity.normalize();
		m_xAttractor.vVelocity *= sinf(fTimer) * 3.0f;
		m_xRepulsor.vVelocity.normalize();
		m_xRepulsor.vVelocity *= sinf(fTimer);
		m_xAttractor.Bounce();
		m_xRepulsor.Bounce();

		for (std::vector<PointData_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			PointData_s &xData = *iter;
			vector3f vVecToAttractor = (m_xAttractor.vPosition - xData.vPosition);
			vector3f vVecToRepulsor = (m_xRepulsor.vPosition - xData.vPosition);
			float fDistToAttractor = vVecToAttractor.length();
			float fDistToRepulsor = vVecToRepulsor.length();

			xData.vVelocity += vVecToAttractor * 1.0f;
			//xData.vVelocity -= vVecToRepulsor * 0.05f;
			//xData.vVelocity += vector3f(0.0f, 0.0f, -0.01f);

			for (std::vector<PointData_s>::iterator iter2 = m_vecPoints.begin(); iter2 != m_vecPoints.end(); ++iter2)
			{
				if( iter == iter2 )
					continue;
				vector3f vDiff = iter2->vPosition - xData.vPosition;
				
				const float fMinDist = 0.3f;
				if( vDiff.squared_length() < fMinDist * fMinDist )
				{
					float fLength = std::max(vDiff.length(), 0.01f);
					vDiff.normalize();
					vDiff *= 1.0f / fLength;
					xData.vVelocity -= vDiff * 0.01f;
				}
			}

			xData.vPosition += xData.vVelocity * m_fSpeed * 0.01f;

			for( int i = 0; i < 3; i++ )
			{
				if (xData.vPosition[i] >= 0.99f)
				{
					xData.vPosition[i] = 0.99f;
					xData.vVelocity[i] = -xData.vVelocity[i] * 0.5f;
				}
				if (xData.vPosition[i] <= 0.0f)
				{
					xData.vPosition[i] = 0.0f;
					xData.vVelocity[i] = -xData.vVelocity[i] * 0.5f;
				}
			}

		}

		// Clear field
		Generator::Update(xLattice);

		int iResolution = xLattice.GetResolution();
		for (std::vector<PointData_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			PointData_s &xData = *iter;

			int iX = xData.vPosition.x() * (iResolution);
			int iY = xData.vPosition.y() * (iResolution);
			int iZ = xData.vPosition.z() * (iResolution);
			for (int i = iX - 1; i <= iX + 1; i++)
			for (int j = iY - 1; j <= iY + 1; j++)
			for (int k = iZ - 1; k <= iZ + 1; k++)
				xLattice.ModifyValue(i, j, k, 20);

			xLattice.ModifyValue(iX, iY, iZ, 50);
		}
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		return 0;
	}



private:
	PointData_s					m_xRepulsor;
	PointData_s					m_xAttractor;
	std::vector<PointData_s>	m_vecPoints;
	float						m_fSpeed;

};
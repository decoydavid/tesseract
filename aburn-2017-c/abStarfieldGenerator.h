#pragma once

#include "abGenerator.h"
#include "abLattice.h"

class StarfieldGenerator : public Generator
{
public:

	struct StarData_s
	{
		void Init(bool bRandStartPos)
		{
			fVelocity = GetRandFloat() * 0.3f + 0.7f;
			vPosition = vector3f(bRandStartPos ? GetRandFloat() : 0.0f, GetRandFloat(), GetRandFloat());
		}
		vector3f vPosition;
		float fVelocity;
	};
	StarfieldGenerator(int iNumPoints, float fSpeed)
		: m_fSpeed(fSpeed)
	{
		for( int i = 0; i < iNumPoints; i++ )
		{
			StarData_s xData;
			xData.Init(true);
			m_vecPoints.push_back(xData);
		}
	}

	virtual void Update(Lattice &xLattice)
	{
		static float fTimer = 0.0f;

		for (std::vector<StarData_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			StarData_s &xData = *iter;
			xData.vPosition.x() += xData.fVelocity * m_fSpeed;
			if( xData.vPosition.x() >= 1.0f )
			{
				xData.Init(false);
			}
		}

		// Clear field
		Generator::Update(xLattice);
		
		int iResolution = xLattice.GetResolution();
		for (std::vector<StarData_s>::iterator iter = m_vecPoints.begin(); iter != m_vecPoints.end(); ++iter)
		{
			StarData_s &xData = *iter;

			int iX = xData.vPosition.x() * (iResolution);
			int iY = xData.vPosition.y() * (iResolution);
			int iZ = xData.vPosition.z() * (iResolution);
			int iCurrentVal = int(xLattice.GetValue(iX, iY, iZ));
			iCurrentVal += 150;
			iCurrentVal = std::min(iCurrentVal, 255);
			xLattice.SetValue(iX, iY, iZ, (UCHAR)iCurrentVal);
		}
	}


private:
	std::vector<StarData_s>		m_vecPoints;
	float						m_fSpeed;

};
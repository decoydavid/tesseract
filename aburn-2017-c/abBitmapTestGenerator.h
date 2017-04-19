#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"
#include "abBitmap.h"

class BitmapTestGenerator : public Generator
{
public:

	BitmapTestGenerator()
		: m_fTime(0.0f)
	{
		for (int i = 0; i < 5; i++)
		{
			Bitmap *pBitmap = new Bitmap();
			std::stringstream ss;
			ss << "../../img" << (i+1) << ".bmp";
			std::string strFilename = ss.str();
			pBitmap->LoadFromFile(strFilename);
			m_vecFrames.push_back(pBitmap);
		}
	}

	virtual void Update(Lattice &xLattice) override
	{
		Generator::Update(xLattice);

		m_fTime += 0.1f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k) override
	{
		int iResolution = xLattice.GetResolution();

		int iTime = ((int)m_fTime) % m_vecFrames.size();
		if( i == 3 )
		{
			Bitmap *pFrame = m_vecFrames[iTime];
			vector3i vColor = pFrame->GetColor(j, k);
			return 255-vColor.x();
		}


		return 0;
	}

private:
	float		m_fTime;
	std::vector<Bitmap *>	m_vecFrames;

};
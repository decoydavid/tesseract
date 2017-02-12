#pragma once

#include "abGenerator.h"
#include "abLattice.h"
#include "abParticle.h"

class SpinnyClothGenerator : public Generator
{
public:

	SpinnyClothGenerator()
		: m_fTime(0.0f)
	{
	}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		m_fTime += 0.3f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		
		unsigned char ucValue = 0;
		float x = float(i) / float(iResolution - 1) - 0.5f;
		float y = float(j) / float(iResolution - 1) - 0.5f;
		float z = float(k) / float(iResolution - 1) - 0.5f;

		matrix3f mRot1 = matrix3f::IDENTITY;
		mRot1.rotate_x(m_fTime * 0.01f);
		matrix3f mRot2 = matrix3f::IDENTITY;
		mRot2.rotate_y(m_fTime * 0.1f);
		matrix3f mRot3 = matrix3f::IDENTITY;
		multiply<4,4,float>(mRot1, mRot2, mRot3);

		matrix3f mTrans = matrix3f::IDENTITY;
		mTrans.set_translation(vector3f(x, y, z));

		matrix3f mResult;
		multiply<4,4,float>(mRot3, mTrans, mResult);
		vector3f v;
		mResult.get_translation(v);

		vector3f vPosition(v.x()+0.5f,v.y()+0.5f,v.z()+0.5f);
		vector3f vVecToCentre = vector3f(0.5f, 0.5f, 0.5f) - vPosition;
		float fDist = vVecToCentre.length();

		float fZMax = (sinf(fDist * 5.0f * (sinf(m_fTime * 0.1f) * 0.5f - 0.5f)) * 0.5f + 0.5f);
		float fDistToZMax = std::abs(vPosition.z() - fZMax);
		if( fDistToZMax < 0.1f )
			return 255;

		return 0;
	}

private:
	float		m_fTime;

};
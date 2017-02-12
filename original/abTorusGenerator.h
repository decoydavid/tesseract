#pragma once

class TorusGenerator: public Generator
{
public:
	TorusGenerator()
	{
		fTimer = 0.0f;
	}
	virtual ~TorusGenerator()
	{}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);
		fTimer += 0.1f;
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		float x = float(i) / float(iResolution - 1) - 0.5f;
		float y = float(j) / float(iResolution - 1) - 0.5f;
		float z = float(k) / float(iResolution - 1) - 0.5f;


		matrix3f mRot1 = matrix3f::IDENTITY;
		mRot1.rotate_y(fTimer);
		matrix3f mRot2 = matrix3f::IDENTITY;
		mRot2.rotate_x(fTimer * 0.5f);
		matrix3f mRot3 = matrix3f::IDENTITY;
		multiply<4,4,float>(mRot1, mRot2, mRot3);

		matrix3f mTrans = matrix3f::IDENTITY;
		mTrans.set_translation(vector3f(x, y, z));

		matrix3f mResult;
		multiply<4,4,float>(mRot3, mTrans, mResult);
		vector3f v;
		mResult.get_translation(v);

		float R = 0.4f + sinf(fTimer * 0.1f) * 0.1f;
		float r = 0.2f + cosf(fTimer * 0.2f) * 0.1f;

		float fA = (Sqr(R - sqrtf(Sqr(v.x())+Sqr(v.y()))) + Sqr(v.z()));
		if( fA < Sqr(r) )
		{
			float fDist = sqrtf(fA);
			float fScale = (r - fDist) / r;
			return 255 * fScale;
		}

		return 0;
	}

private:
	float fTimer;


};
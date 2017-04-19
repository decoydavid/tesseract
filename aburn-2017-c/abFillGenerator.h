#pragma once

class FillGenerator : public Generator
{
public:


	FillGenerator(int iResolution)
	{
		m_pData = new unsigned char[iResolution * iResolution * iResolution];
		fTime = 0.0f;
	}

	virtual ~FillGenerator()
	{}

	virtual void Update(Lattice &xLattice)
	{
		Generator::Update(xLattice);

		fTime += 0.01f;

		int iResolution = xLattice.GetResolution();
		if( GetRandFloat() > 0.96f )
		{

		}
	}

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		int iResolution = xLattice.GetResolution();
		return m_pData[i * iResolution * iResolution + j * iResolution + k];
	}

private:
	unsigned char *	m_pData;
	float fTime;
};
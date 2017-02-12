#include "stdafx.h"
#include "abGenerator.h"
#include "abLattice.h"

void Generator::Update(Lattice &xLattice)
{
	int iResolution = xLattice.GetResolution();

	static float fTimer = 0.0f;
	fTimer += 0.05f;
	for (int i = 0; i < iResolution; i++)
	{
		for (int j = 0; j < iResolution; j++)
		{
			for (int k = 0; k < iResolution; k++)
			{
				unsigned char ucValue = 0;
				xLattice.SetValue(i, j, k, GenerateValue(xLattice, i, j, k));
			}
		}
	}
}


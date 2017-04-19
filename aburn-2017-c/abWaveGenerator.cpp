#include "stdafx.h"
#include "abWaveGenerator.h"
#include "abLattice.h"

#include <cmath>
#include <algorithm>

void WaveGenerator::Update(Lattice &xLattice)
{
	int iResolution = xLattice.GetResolution();

	static float fTimer2 = 0.0f;
	fTimer2 += 0.01f;

	static float fTimer = 0.0f;
	fTimer += (sinf(fTimer2) + 2.5f) * 0.025f;
	for (int i = 0; i < iResolution; i++)
	{
		for (int j = 0; j < iResolution; j++)
		{
			for (int k = 0; k < iResolution; k++)
			{
				unsigned char ucValue = 0;
				float x = float(i) / float(iResolution - 1);
				float y = float(j) / float(iResolution - 1);
				float z = float(k) / float(iResolution - 1);
				float fMinZ = 4.0f + ((sinf(fTimer + x * 2.5f + y * 2.5f) + sinf(fTimer + x * 5.5f + y * 5.5f) * 0.2f) * 3.0f);
				float fDistToMinZ = std::abs(fMinZ - k) * 1.0f;
				float fMax = 1.0f;
				fDistToMinZ = std::min(fDistToMinZ, fMax);
				fDistToMinZ = std::max(fDistToMinZ, 0.0f);
				ucValue = (unsigned char)(((fMax - fDistToMinZ) / fMax) * 255.0f);
				xLattice.SetValue(i, j, k, ucValue);
			}
		}
	}
}
#pragma once

#include "abGenerator.h"

class TextFileGenerator : public Generator
{
public:
	struct TextPage_s
	{
		vector3i	vStart;
		vector3i	vHorizDir;
		vector3i	vVertDir;
		int			iWidth;
	};

	TextFileGenerator(int iResolution);

	virtual void Update(Lattice &xLattice);

	void RenderString(Lattice &xLattice, const std::string &strText, const vector2i &vStart);
	vector3i MapToWoorldCoord(const vector2i &vVirtualPos) const;
	int MeasureString(const std::string &strText) const;

private:
	std::vector<TextPage_s> m_vecPages;
  float fTimer;
	int vecStringsPos;
	std::vector<std::string> m_vecStrings;
	unsigned char ReverseBits(unsigned char b);
};

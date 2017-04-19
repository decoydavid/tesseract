#pragma once

#include "abGenerator.h"

class TextGenerator : public Generator
{
public:
	struct TextPage_s
	{
		vector3i	vStart;
		vector3i	vHorizDir;
		vector3i	vVertDir;
		int			iWidth;
	};

	TextGenerator(int iResolution);

	virtual void Update(Lattice &xLattice);

	void RenderString(Lattice &xLattice, const std::string &strText, const vector2i &vStart);
	vector3i MapToWoorldCoord(const vector2i &vVirtualPos) const;
	int MeasureString(const std::string &strText) const;
private:

	std::vector<TextPage_s>		m_vecPages;

};
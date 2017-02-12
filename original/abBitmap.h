#pragma once

class Bitmap
{
public:
	Bitmap();

	bool LoadFromFile(const std::string &strFilename);

	vector3i GetColor(int iX, int iY) const;

private:

	uint_8*		m_pData;
	vector2i	m_iResolution;
};
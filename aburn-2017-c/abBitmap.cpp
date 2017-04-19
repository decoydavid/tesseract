#ifdef OPENGL_RENDER
#include "stdafx.h"
#include "abBitmap.h"

Bitmap::Bitmap()
	: m_pData(NULL)
{

}


bool Bitmap::LoadFromFile(const std::string &strFilename)
{
	uint_8* datBuff[2] = { NULL, NULL }; // Header buffers

	BITMAPFILEHEADER* bmpHeader = NULL; // Header
	BITMAPINFOHEADER* bmpInfo = NULL; // Info 

	// The file... We open it with it's constructor
	std::ifstream file(strFilename, std::ios::binary);
	if (!file)
	{
		std::cout << "Failure to open bitmap file.\n";

		return false;
	}

	// Allocate byte memory that will hold the two headers
	datBuff[0] = new uint_8[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new uint_8[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	// Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo = (BITMAPINFOHEADER*)datBuff[1];


	// Check if the file is an actual BMP file
	if (bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File \"" << strFilename << "\" isn't a bitmap file\n";
		return false;
	}

	// First allocate pixel memory
	int iSize = bmpInfo->biWidth * bmpInfo->biHeight * 3;
	m_pData = new uint_8[iSize];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)m_pData, iSize);

	m_iResolution = vector2i(bmpInfo->biWidth, bmpInfo->biHeight);

	return true;
}


vector3i Bitmap::GetColor(int iX, int iY) const
{
	uint_8 *pPixel = &(m_pData[iY * m_iResolution.x() * 3 + iX * 3]);
	return vector3i(pPixel[0], pPixel[1], pPixel[2]);
}

#endif
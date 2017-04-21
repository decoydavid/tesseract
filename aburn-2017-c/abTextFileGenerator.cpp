#include "stdafx.h"
#include "abTextFileGenerator.h"

#include "abLattice.h"
#include "abFont.h"

#include <cmath>
#include <algorithm>


TextFileGenerator::TextFileGenerator(int iResolution)
{
	fTimer = 0.0f;
	TextPage_s xPage;
	xPage.vVertDir = vector3i(0, 0, -1);
	xPage.iWidth = iResolution - 1;

	xPage.vStart = vector3i(0, iResolution/2, iResolution - 1);
	xPage.vHorizDir = vector3i(1, 0, 0);
	m_vecPages.push_back(xPage);
 	/*xPage.vStart = vector3i(iResolution - 1, 0, iResolution - 1);
 	xPage.vHorizDir = vector3i(0, 1, 0);
 	m_vecPages.push_back(xPage);
 	xPage.vStart = vector3i(iResolution - 1, iResolution - 1, iResolution - 1);
 	xPage.vHorizDir = vector3i(-1, 0, 0);
 	m_vecPages.push_back(xPage);
 	xPage.vStart = vector3i(0, iResolution - 1, iResolution - 1);
 	xPage.vHorizDir = vector3i(0, -1, 0);
 	m_vecPages.push_back(xPage);*/
}


vector3i TextFileGenerator::MapToWoorldCoord(const vector2i &vVirtualP) const
{
	vector3i vWorldPos(-1,-1,-1);
	vector2i vVirtualPos = vVirtualP;
	int iOffset = vVirtualPos.x();
	std::vector<TextPage_s>::const_iterator iterCurrentPage = m_vecPages.begin();
	while( 1 )
	{
		if( vVirtualPos.x() > iterCurrentPage->iWidth )
		{
			vVirtualPos.x() -= iterCurrentPage->iWidth;
			++iterCurrentPage;
			if (iterCurrentPage == m_vecPages.end() )
				return vector3i(-999,-999,-999);
				//iterCurrentPage = m_vecPages.begin();
			continue;
		}

		vWorldPos = iterCurrentPage->vStart;

		vWorldPos += iterCurrentPage->vHorizDir * vVirtualPos.x();
		vWorldPos += iterCurrentPage->vVertDir * vVirtualPos.y();
		//vWorldPos.y() += sinf((float(iOffset) * 0.1f) * 4.0f) * 2.0f;
		return vWorldPos;
	}

	return vWorldPos;
}

unsigned char TextFileGenerator::ReverseBits(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}


void TextFileGenerator::RenderString(Lattice &xLattice, const std::string &strText, const vector2i &vStart)
{
	int iResolution = xLattice.GetResolution();

	uint_8 uiStartChar = microsoftSansSerif_7ptFontInfo.startChar;

	vector2i vCharStart = vStart;

	for( int k = 0; k < strText.size(); k++ )
	{
		UCHAR ucChar = strText[k];
		FONT_CHAR_INFO xCharInfo = microsoftSansSerif_7ptFontInfo.charInfo[ucChar - uiStartChar];

		vector2i vCurrent = vCharStart;
		for (int i = 0; i < microsoftSansSerif_7ptFontInfo.heightPages * 8; i++)
		{
			uint_8 uiData = 0;
			if( ucChar != 0x20 )
			{
				uiData = microsoftSansSerif_7ptFontInfo.data[xCharInfo.offset + i];
				uiData = ReverseBits(uiData);
			}

			vector2i vCurrent2 = vCurrent;
			for (int j = 0; j < xCharInfo.widthBits; j++)
			{
				vector3i vWorldCoord = MapToWoorldCoord(vCurrent2);
				if ((uiData & 1) != 0)
				{
					xLattice.SetValue(vWorldCoord.x(), vWorldCoord.y(), vWorldCoord.z(), 255);
				}
				uiData = uiData >> 1;
				vCurrent2.x() += 1;
			}

			vCurrent.y() += 1;
		}
		if( ucChar != 0x20 )
			vCharStart.x() += xCharInfo.widthBits + 1;
		else
			vCharStart.x() += microsoftSansSerif_7ptFontInfo.spacePixels;
	}
}

void TextFileGenerator::Update(Lattice &xLattice)
{
	Generator::Update(xLattice);
	fTimer += 0.01f;
	std::string strText = "AFRIKA BURN 2017";
	static float fStart = 9.0f;
	fStart -= 0.14f;

	int iResolution = xLattice.GetResolution();
	vector2i vStart((int)fStart, 0);

  	if( MapToWoorldCoord(vStart).x() == -(MeasureString(strText)) )
  		fStart = 9.0f;
	RenderString(xLattice, strText, vStart);


}


int TextFileGenerator::MeasureString(const std::string &strText) const
{
	uint_8 uiStartChar = microsoftSansSerif_7ptFontInfo.startChar;

	int iResult = 0;
	for (int k = 0; k < strText.size(); k++)
	{
		UCHAR ucChar = strText[k];
		FONT_CHAR_INFO xCharInfo = microsoftSansSerif_7ptFontInfo.charInfo[ucChar - uiStartChar];
		if( ucChar != 0x20 )
			iResult += xCharInfo.widthBits + 1;
		else
			iResult += microsoftSansSerif_7ptFontInfo.spacePixels;
	}

	return iResult;
}

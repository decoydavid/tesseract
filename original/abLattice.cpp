#include "stdafx.h" 
#include "abLattice.h"

Lattice::Lattice(int iResolution, float fSize)
	: m_fSize(fSize)
	, m_iResolution(iResolution)
{
	m_pData = new unsigned char[iResolution * iResolution * iResolution];

#ifdef OPENGL_RENDER
	m_pCylinderQuadric = gluNewQuadric();
	gluQuadricDrawStyle(m_pCylinderQuadric, GLU_FILL);
	m_pCylinderCapQuadric = gluNewQuadric();
#endif
}


Lattice::~Lattice()
{
	delete[] m_pData;
#ifdef OPENGL_RENDER
	gluDeleteQuadric(m_pCylinderQuadric);
	m_pCylinderQuadric = NULL;
#endif

}


#ifdef OPENGL_RENDER
void Lattice::Render()
{
	glColor4ub(139, 119, 101, 255);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

	const float fFrameRadius1 = 0.01f;
	const float fFrameRadius2 = 0.0165f;
	const float fFrameSize = 2.0f;

	{
		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, -fFrameSize*0.5f, -fFrameSize*0.5f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius1, fFrameRadius1, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(fFrameSize*0.5f, -fFrameSize*0.5f, -fFrameSize*0.5f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius1, fFrameRadius1, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(fFrameSize*0.5f, fFrameSize*0.5f, -fFrameSize*0.5f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius1, fFrameRadius1, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, fFrameSize*0.5f, -fFrameSize*0.5f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius1, fFrameRadius1, fFrameSize, 8, 8);
		glPopMatrix();
	}

	{
		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, -fFrameSize*0.5f, -fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, 0.0f, -fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, fFrameSize*0.5f, -fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		//////////////////////////////////////////////////////////////////////////


		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, -fFrameSize*0.5f, fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, 0.0f, fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, fFrameSize*0.5f, fFrameSize*0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

	}

	{
		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, fFrameSize*0.5f, fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, fFrameSize*0.5f, fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(fFrameSize*0.5f, fFrameSize*0.5f, fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		//////////////////////////////////////////////////////////////////////////

		glPushMatrix();
		glTranslatef(-fFrameSize*0.5f, fFrameSize*0.5f, -fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, fFrameSize*0.5f, -fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(fFrameSize*0.5f, fFrameSize*0.5f, -fFrameSize*0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(m_pCylinderQuadric, fFrameRadius2, fFrameRadius2, fFrameSize, 8, 8);
		glPopMatrix();

	}

	glPushMatrix();
	glTranslatef(-m_fSize*0.5f, -m_fSize*0.5f, -m_fSize*0.5f);
	//glTranslatef(-(m_fSize / float(m_iResolution)) * 0.5f, -(m_fSize / float(m_iResolution)) * 0.5f, -(m_fSize / float(m_iResolution)) * 0.5f);

	for (int i = 0; i < m_iResolution; i++)
	{
		for (int j = 0; j < m_iResolution; j++)
		{
			for (int k = 0; k < m_iResolution; k++)
			{
				glPushMatrix();
				glTranslatef(m_fSize * (i / float(m_iResolution-1)),
					m_fSize * (j / float(m_iResolution-1)),
					m_fSize * (k / float(m_iResolution-1)));

				unsigned char ucValue = GetValue(i, j, k);
				glColor4f(1.0f, 1.0f, 1.0f, float(ucValue)/255.0f);
				RenderCylinder();
				glPopMatrix();
			}
		}
	}
	glPopMatrix();

}
#endif


unsigned char Lattice::GetValue(int i, int j, int k) const
{
	return m_pData[i * m_iResolution * m_iResolution + j * m_iResolution + k];
}


void Lattice::SetValue(int i, int j, int k, unsigned char ucValue)
{
	if( i >= m_iResolution || j >= m_iResolution || k >= m_iResolution || i < 0 || j < 0 || k < 0 )
		return;
	m_pData[i * m_iResolution * m_iResolution + j * m_iResolution + k] = ucValue;
}

void Lattice::ModifyValue(int i, int j, int k, int iDelta)
{
	int iCurrentValue = int(GetValue(i,j,k));
	iCurrentValue += iDelta;
	iCurrentValue = std::min(std::max(iCurrentValue, 0), 255);
	SetValue(i,j,k, UCHAR(iCurrentValue));
}


#ifdef OPENGL_RENDER
void Lattice::RenderCylinder()
{
	float fCylinderHeight = 0.06f;
	float fCylinderRadius = 0.02f;
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -fCylinderHeight*0.5f);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	gluCylinder(m_pCylinderQuadric, fCylinderRadius, fCylinderRadius, fCylinderHeight, 8, 8);
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	gluDisk(m_pCylinderCapQuadric, 0.0f, fCylinderRadius, 5, 1);
	glTranslatef(0.0f, 0.0f, fCylinderHeight);
	gluDisk(m_pCylinderCapQuadric, 0.0f, fCylinderRadius, 5, 1);
	glTranslatef(0.0f, 0.0f, -fCylinderHeight);

	glPopMatrix();

}
#endif
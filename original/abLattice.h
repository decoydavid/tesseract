#pragma once

class Lattice
{
public:
	Lattice(int iResolution, float fSize);
	~Lattice();

	void Render();
	unsigned char GetValue(int i, int j, int k) const;
	void SetValue(int i, int j, int k, unsigned char ucValue);
	void ModifyValue(int i, int j, int k, int iDelta);

	int GetResolution() const { return m_iResolution; }

private:
	void RenderCylinder();

	unsigned char *	m_pData;
	float			m_fSize;
	int				m_iResolution;
#ifdef OPENGL_RENDER
	GLUquadricObj *	m_pCylinderQuadric;
	GLUquadricObj *	m_pCylinderCapQuadric;
#endif
};
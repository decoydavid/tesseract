#ifdef OPENGL_RENDER
#include "stdafx.h"
#include "abBitmap.h"

Bitmap::Bitmap()
	: surf(NULL)
{

}


bool Bitmap::LoadFromFile(const std::string &strFilename)
{
	surf = SDL_LoadBMP(strFilename.c_str());
	m_iResolution = vector2i(surf->w, surf->h);
	return true;
}


vector3i Bitmap::GetColor(int iX, int iY) const
{
	SDL_LockSurface(surf);
	uint_8 r, g, b;
	Uint32 *p = (Uint32 *) surf->pixels + iY * surf->pitch + iX;
  SDL_GetRGB(*p, surf->format, &r, &g, &b);
	SDL_UnlockSurface(surf);
	return vector3i(r, g, b);
}

#endif

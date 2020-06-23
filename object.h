
#ifndef __obbject_h__
#define __object_h__

#include "gobject.h"

class CObject : public CGObject
{
public:
	CObject();
	~CObject();
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface, int x, int y);
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame);
};



#endif

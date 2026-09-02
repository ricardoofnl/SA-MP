
#include "../main.h"

BOOL unnamed_100B2AF0();

//----------------------------------------------------

CTextDrawPool::CTextDrawPool()
{
	int x=0;
	while(x!=MAX_TEXT_DRAWS) {
		field_2400[x] = 0;
		field_0[x] = 0;
		x++;
	}
	unnamed_100B2AF0();
}

//----------------------------------------------------

void CTextDrawPool::FUNC_1001E7F0(unsigned short TextDrawID)
{
	CTextDraw *pTextDraw = (CTextDraw *)field_2400[TextDrawID];
	if(pTextDraw) {
		delete pTextDraw;
		field_2400[TextDrawID] = 0;
		field_0[TextDrawID] = 0;
	}
}

//----------------------------------------------------

void CTextDrawPool::FUNC_1001E8D0()
{
	for(int i = 0; i < MAX_TEXT_DRAWS; i++) {
		CTextDraw *pTextDraw = (CTextDraw *)field_2400[i];
		if(pTextDraw) {
			delete pTextDraw;
			field_2400[i] = 0;
			field_0[i] = 0;
		}
	}
}

//----------------------------------------------------

void CTextDrawPool::FUNC_1001E870()
{
	for(int i = 0; i != MAX_TEXT_DRAWS; i++) {
		if(field_0[i]) ((CTextDraw *)field_2400[i])->FUNC_100B34A0();
	}
}

//----------------------------------------------------

void CTextDrawPool::FUNC_1001E8A0()
{
	for(int i = 0; i != MAX_TEXT_DRAWS; i++) {
		if(field_0[i]) ((CTextDraw *)field_2400[i])->FUNC_100B36B0();
	}
}

//----------------------------------------------------

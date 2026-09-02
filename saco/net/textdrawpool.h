
#pragma once

//----------------------------------------------------

class CTextDraw
{
public:
	~CTextDraw(); // .text:100B2F50
};

//----------------------------------------------------

class CTextDrawPool
{
private:
	int field_0[MAX_TEXT_DRAWS];
	int field_2400[MAX_TEXT_DRAWS];
public:
	CTextDrawPool();

	void FUNC_1001E7F0(unsigned short TextDrawID); // .text:1001E7F0

	void FUNC_1001E870(); // .text:1001E870

	void FUNC_1001E8D0(); // .text:1001E8D0
};

//----------------------------------------------------

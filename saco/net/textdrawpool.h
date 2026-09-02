
#pragma once

//----------------------------------------------------

class CTextDraw
{
public:
	~CTextDraw(); // .text:100B2F50

	void FUNC_100B3480(); // .text:100B3480
	void FUNC_100B34A0(); // .text:100B34A0
	void FUNC_100B36B0(); // .text:100B36B0
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

	void FUNC_1001E830(); // .text:1001E830

	void FUNC_1001E870(); // .text:1001E870

	void FUNC_1001E8D0(); // .text:1001E8D0

	void FUNC_1001E8A0(); // .text:1001E8A0
};

//----------------------------------------------------

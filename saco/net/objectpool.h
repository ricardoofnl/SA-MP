
#pragma once

// samp object; holds the material/text data
class CObject
{
public:
	char _gap0[68];
	int field_44;
	char _gap48[12];
	float field_54;
	char _gap58[4403];
	int field_118B;
	char _gap118F[10];
	BYTE field_1199;

public:
	void FUNC_100A7E20();
	void FUNC_100A9E30();
	void FUNC_100A9E70();
};

class CObjectPool
{
public:
	int field_0;
	int field_4[MAX_OBJECTS];
	int field_FA4[MAX_OBJECTS];
public:
	char FUNC_10012DE0(VECTOR *vecStart, VECTOR *vecEnd); // .text:10012DE0

	CObjectPool();

	void FUNC_10012A50(); // .text:10012A50
	void FUNC_10012B10(); // .text:10012B10
	void FUNC_10012B90(); // .text:10012B90
	void FUNC_10012BD0(); // .text:10012BD0

	CObject * FUNC_100129D0(ENTITY_TYPE *pEntity); // todo: implement
};

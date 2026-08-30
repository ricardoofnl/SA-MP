
#pragma once

class CObjectPool
{
private:
	int field_0;
	int field_4[MAX_OBJECTS];
	int field_FA4[MAX_OBJECTS];
public:
	CEntity * FUNC_100129D0(ENTITY_TYPE *pEntity); // .text:100129D0

	CObjectPool();

	void FUNC_10012B90(); // .text:10012B90
	void FUNC_10012BD0(); // .text:10012BD0

	class CObject *FUNC_100129D0(ENTITY_TYPE *pEntity); // todo: implement
};

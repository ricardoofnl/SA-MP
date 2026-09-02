
#pragma once

typedef struct _LABEL
{
	char *szText;
	char _gap4[25];
} LABEL;

class CLabelPool
{
public:
	LABEL m_Labels[MAX_LABELS];
	BOOL m_bLabelSlotState[MAX_LABELS];
public:
	CLabelPool();
	~CLabelPool();

	BOOL Delete(WORD wLabelID);

	void FUNC_10001350(); // .text:10001350

};

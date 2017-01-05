#include "stdafx.h"
#include <iostream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "subwayline.h"
#include "subwayPrice.h"
#include "subwayCommon.h"
#include "subwayError.h"
#include "subwayCmdParse/subwayCmdParse.h"
#include "subwayOutput/subwayOutput.h"
using namespace std;

/*
@ ������Ʊ
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //��ȡ����վ��������� GetSubwayStationDis
	unsigned int dis, cardNo=1;
	int basePrice=1;
	EN_RETURN_CODE status = EN_RETURN_SUCC;
	GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation, unCmd.stCmdSingleTicket.dstStation, dis);
	if (EN_RETURN_SUCC == status)
	{
		//��ȡ����վ���Ļ���Ʊ��  GetBasePrice
		basePrice = GetBasePrice(dis);
		if (basePrice >= 0)
		{	//�쵥�̿� AssignCard
			
			EN_RETURN_CODE temp = AssignCard(cardNo, EN_CARD_TYPE_SINGLE, basePrice);
			if (temp == EN_RETURN_CARD_OVERLOW)
				status = temp;
		}
		else
			status = EN_RETURN_INNER_ERR;
	}
    
    //����ַ���
    GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, status, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);

    return;
}
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
@ 办理单程票
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //获取两个站点间的里程数 GetSubwayStationDis
	unsigned int dis, cardNo=1;
	int basePrice=1;
	EN_RETURN_CODE status = EN_RETURN_SUCC;
	GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation, unCmd.stCmdSingleTicket.dstStation, dis);
	if (EN_RETURN_SUCC == status)
	{
		//获取两个站点间的基本票价  GetBasePrice
		basePrice = GetBasePrice(dis);
		if (basePrice >= 0)
		{	//办单程卡 AssignCard
			
			EN_RETURN_CODE temp = AssignCard(cardNo, EN_CARD_TYPE_SINGLE, basePrice);
			if (temp == EN_RETURN_CARD_OVERLOW)
				status = temp;
		}
		else
			status = EN_RETURN_INNER_ERR;
	}
    
    //输出字符串
    GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, status, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);

    return;
}
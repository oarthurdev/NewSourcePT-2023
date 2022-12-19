#include <fstream>
#include "smlib3d\\smd3d.h"
#include "SocketServer/smwsock.h"
#include "character.h"
#include "fileread.h"
#include "field.h"
#include "effectsnd.h"
#include "smreg.h"
#include "playmain.h"
#include "playsub.h"
#include "Language\\language.h"

#include "Server\\onserver.h"


int	NotItemSpecial = 0;

extern	int	quit;

static char decode[512];
static char line[512];



void ModelKeyWordEncode(DWORD dwFileCode, smMODELINFO *lpMODELINFO);
int  ModelKeyWordDecode(DWORD dwFileCode, smMODELINFO *lpMODELINFO);
void MotionKeyWordEncode(DWORD dwCode, smMODELINFO *lpMODELINFO);
int	 MotionKeyWordDecode(DWORD dwCode, smMODELINFO *lpMODELINFO);




#ifdef	_W_SERVER
#define	SVR_NPC_MSG_MAX		1024
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][256];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#else
#define	SVR_NPC_MSG_MAX		32
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][128];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#endif

int		NpcMsgCount = 0;


char	szShotCutMessage[10][100];




char	*SetNPCMsg(char *szMsg)
{
	char	*lpMsg;
	DWORD	dwCode;
	int		cnt;

	if(NpcMsgCount >= SVR_NPC_MSG_MAX) return NULL;

	dwCode = GetSpeedSum(szMsg);

	for(cnt = 0; cnt < NpcMsgCount; cnt++)
	{
		if(dwCode == dwSvr_NpcMsgCode[cnt] && lstrcmp(szSvr_NpcMsgs[cnt], szMsg) == 0)
		{
			break;
		}
	}

	if(cnt < NpcMsgCount)
	{
		return szSvr_NpcMsgs[cnt];
	}

	dwSvr_NpcMsgCode[NpcMsgCount] = dwCode;
	lpMsg = szSvr_NpcMsgs[NpcMsgCount++];
	strcpy_s(lpMsg, sizeof(szSvr_NpcMsgs[0]), szMsg);

	return lpMsg;
}


static char *GetWord(char *q, char *p)
{


	while((*p == 32) || (*p == 9))
	{
		p++;
	}

	while((*p != 32) && (*p != 9))
	{
		if(*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;



	return p;
}


char *szIniCommand[] = {
	"*��������",
	"*���۸���",
	"*�������",
	"*����̸�",
	"*���Ͽ���",
	"*������������",

	"*���и��",
	"*������",
	"*�������",

	"*XX�ȴµ���",
	"*XX���⵿ֱ��",

	"*���빫��",
	"*��������",
	"*�ش���ġ",
	"*������",



	"*ǥ�����Ͽ���",
	"*ǥ������",
	"*ǥ������",


	""
};

char *szIniRepeat = "�ݺ�";
char *szMotionWord = "����";

char *szRunWord = "�ٴ�";
char *szStandWord = "*���ֱ�";
char *szStandWord2 = "*����";
char *szWalkWord = "*�ȴ�";

char *szAttackWord = "����";
char *szDeadWord = "�ױ�";
char *szDeadWord2 = "�״�";
char *szDamageWord = "Ÿ��";
char *szDamageWord2 = "������";
char *szDamageWord3 = "����";

char *szWarpWord = "���";
char *szWarpWord2 = "����";

char *szSometimeWord = "����";

char *szFallDownWord = "����";
char *szFallStandLargeWord = "ū����";
char *szFallStandSmallWord = "��������";

char *szRestartWord = "�ٽý���";
char *szEatWord = "�Ա�";
char *szSkillWord = "���";
char *szYahooWord = "����";



char *szMotionTalkWord = "ǥ��";

char *szArTalkWord = "��ǥ��";
char *szETalkWord = "��ǥ��";
char *szOhTalkWord = "��ǥ��";
char *szEyeTalkWord = "������ǥ��";

char *szBlankTalkWord = "��ǥ��(�۵�����)";
char *szSmileTalkWord = "����ǥ��";
char *szGrumbleTalkWord = "ȭ��ǥ��";
char *szSorrowTalkWord = "����ǥ��";
char *szStartledTalkWord = "���ǥ��";
char *szNatureTalkWord = "����ǥ��";
char *szSpecialTalkWord = "Ư��ǥ��";



JOBNAME_BIT BitMaskJobNames[] = {
	{	"Fighter"		,	0x0001	},
	{	"Mechanician"	,	0x0002	},
	{	"Archer"		,	0x0004	},
	{	"Pikeman"		,	0x0008	},

	{	"Atalanta"		,	0x0010	},
	{	"Knight"		,	0x0020	},
	{	"Magician"		,	0x0040	},
	{	"Priest"		,	0x0080	},

	{	"" , 0 },

	{	"PureBody"		,	0x0040	},
	{	"PureBody"		,	0x0080	},
	{	"PureBody"		,	0x0100	},
	{	"PureBody"		,	0x0200	},
	{	"PureBody"		,	0x0400	},
	{	"PureBody"		,	0x0800	},
	{	"PureBody"		,	0x1000	}
};





int SetIniMotionInfo(smMOTIONINFO *motion, char *p, int *lpRate = NULL)

{
	char strBuff[256];
	int EventCount;

	EventCount = 0;


	p = GetWord(strBuff, p);
	motion->StartFrame = atoi(strBuff);
	p = GetWord(strBuff, p);
	motion->EndFrame = atoi(strBuff);

	motion->EventFrame[0] = 0;
	motion->EventFrame[1] = 0;
	motion->EventFrame[2] = 0;
	motion->EventFrame[3] = 0;

	while(1)
	{
		p = GetWord(strBuff, p);
		if(strBuff[0]<'0' || strBuff[0]>'9') break;
		if(EventCount >= 4) break;

		motion->EventFrame[EventCount] = (atoi(strBuff) - motion->StartFrame) * 160;
		EventCount++;
	}



	if(lstrcmp(strBuff, szIniRepeat) == 0)
	{
		motion->Repeat = TRUE;
	}




	if(strBuff[0] != '(' && strBuff[0] >= ' ' && strBuff[0] <= 0x7F)
		motion->KeyCode = strBuff[0];

	if(lpRate)
	{
		p = GetWord(strBuff, p);

		int  len = strlen(strBuff);
		char NumBuff[10] = { 0, };

		if(len > 2 && len < 6 && strBuff[0] == '(' && strBuff[len - 1] == ')')
		{
			::CopyMemory(NumBuff, &strBuff[1], len - 2);
			*lpRate = atoi(NumBuff);
			if(*lpRate > 100)
				*lpRate = 100;
		}
	}


	return TRUE;
}

static char *szFileExt = "inx";





int AddModelDecode(char *iniFile, smMODELINFO *Info)

{
	char *szDirecotry = nullptr;
	char strBuff[64] = { 0 };
	char *p = nullptr;
	char *pb = nullptr;
	int CmdNum = 0;
	int cnt = 0;
	_MODELGROUP *lpModelGroup = nullptr;
	int JobCount = 0;

	char *szMotionFileList[128] = { 0 };

	int MotionFileListCnt = 0;
	int MotionFrameList[100];
	smPAT3D *pat3d = nullptr;

	int MotionLastPos = 0;


	MotionFileListCnt = 0;
	ZeroMemory(MotionFrameList, sizeof(int) * 100);

	FILE* fp = nullptr;

	fopen_s(&fp, iniFile, "rb");
	if(fp == NULL)
		return FALSE;


	szDirecotry = SetDirectoryFromFile(iniFile);

	while(!feof(fp))
	{
		if(fgets(line, 512, fp) == NULL)
			break;

		p = GetWord(decode, line);

		CmdNum = 0;

		while(true)
		{

			if(lstrcmp(decode, szIniCommand[CmdNum]) == 0)
				break;

			if(szIniCommand[CmdNum][0] == NULL)
			{
				if(decode[0] == '*' && strstr(decode, szMotionWord))
				{



					if(Info->MotionCount < MOTION_INFO_MAX)
					{
						SetIniMotionInfo(&Info->MotionInfo[Info->MotionCount], p, &Info->NpcMotionRate[Info->MotionCount]);
					}



					Info->MotionInfo[Info->MotionCount].MotionFrame = MotionFileListCnt;
					Info->MotionInfo[Info->MotionCount].State = TRUE;


					if(strstr(decode, szRunWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_RUN;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}


					if(strstr(decode, szAttackWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_ATTACK;
					}

					if(strstr(decode, szDeadWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DEAD;
					}

					if(strstr(decode, szDeadWord2))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DEAD;
					}


					if(strstr(decode, szDamageWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}

					if(strstr(decode, szDamageWord2))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}

					if(strstr(decode, szDamageWord3))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}

					if(strstr(decode, szSometimeWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_SOMETIME;
					}


					if(strstr(decode, szFallDownWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLDOWN;
					}

					if(strstr(decode, szFallStandSmallWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLSTAND;
					}

					if(strstr(decode, szFallStandLargeWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLDAMAGE;
					}


					if(strstr(decode, szStandWord) || strstr(decode, szStandWord2))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_STAND;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}

					if(strstr(decode, szWalkWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_WALK;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}

					if(strstr(decode, szRestartWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_RESTART;
					}

					if(strstr(decode, szEatWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_EAT;
					}

					if(strstr(decode, szSkillWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_SKILL;
						Info->MotionInfo[Info->MotionCount].SkillCodeList[0] = 0;
					}


					if(strstr(decode, szWarpWord) || strstr(decode, szWarpWord2))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_WARP;
					}


					if(strstr(decode, szYahooWord))
					{
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_YAHOO;
					}


					if(Info->MotionInfo[Info->MotionCount].State == CHRMOTION_STATE_DEAD)
					{
						Info->MotionInfo[Info->MotionCount].EndFrame -= 8;
					}



					MotionLastPos = Info->MotionCount;
					Info->MotionCount++;
				}


				else if(decode[0] == '*' && strstr(decode, szMotionTalkWord) && MotionFileListCnt)
				{
					if(Info->TalkMotionCount < TALK_MOTION_INFO_MAX)
					{
						SetIniMotionInfo(&Info->TalkMotionInfo[Info->TalkMotionCount], p, &Info->TalkMotionRate[Info->TalkMotionCount]);
					}

					Info->TalkMotionInfo[Info->TalkMotionCount].MotionFrame = MotionFileListCnt - 1;


					if(strstr(decode, szArTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_AR;

					else if(strstr(decode, szETalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_E;

					else if(strstr(decode, szOhTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_OH;

					else if(strstr(decode, szEyeTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_EYE;

					else if(strstr(decode, szBlankTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_BLANK;

					else if(strstr(decode, szSmileTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SMILE;

					else if(strstr(decode, szGrumbleTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_GRUMBLE;

					else if(strstr(decode, szSorrowTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SORROW;

					else if(strstr(decode, szStartledTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_STARTLED;

					else if(strstr(decode, szNatureTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_NATURE;

					else if(strstr(decode, szSpecialTalkWord))
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SPECIAL;

					Info->TalkMotionCount++;
				}

				break;
			}

			CmdNum++;
		}



		switch(CmdNum)
		{
		case 0:

			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
			{
				p = GetString(strBuff, pb);
			}
			strcpy_s(Info->szMotionFile, szDirecotry);
			lstrcat(Info->szMotionFile, strBuff);
			break;



		case 17:


		case 1:
		{
			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
			{
				p = GetString(strBuff, pb);
			}

			const size_t arraySize = 64;
			szMotionFileList[MotionFileListCnt] = new char[arraySize];
			strcpy_s(szMotionFileList[MotionFileListCnt], arraySize, szDirecotry);
			lstrcat(szMotionFileList[MotionFileListCnt], strBuff);
			MotionFileListCnt++;
		}
		break;

		case 2:

			p = GetWord(strBuff, p);
			strcpy_s(Info->szModelFile, szDirecotry);
			lstrcat(Info->szModelFile, strBuff);
			break;

		case 3:

			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
			{
				p = GetString(strBuff, pb);
			}


			break;

		case 4:

			p = GetWord(strBuff, p);


			strcpy_s(Info->szLinkFile, szDirecotry);
			lstrcat(Info->szLinkFile, strBuff);
			break;


		case 5:

			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
			{
				p = GetString(strBuff, pb);
			}



			strcpy_s(Info->szSubModelFile, szDirecotry);
			lstrcat(Info->szSubModelFile, strBuff);

			break;

		case 6:
		case 7:
		case 8:

			switch(CmdNum)
			{
			case 6:

				lpModelGroup = &Info->HighModel;
				break;
			case 7:
				lpModelGroup = &Info->DefaultModel;
				break;
			case 8:
				lpModelGroup = &Info->LowModel;
				break;
			}

			for(cnt = 0; cnt < 4; cnt++)
			{
				pb = p;
				p = GetWord(strBuff, p);
				if(!strBuff[0]) break;

				if(strBuff[0] == 34)
				{
					p = GetString(strBuff, pb);
				}
				if(lpModelGroup->ModelNameCnt < 4)
				{
					strcpy_s(lpModelGroup->szModelName[lpModelGroup->ModelNameCnt++], strBuff);
				}
			}
			break;

		case 9:



			break;
		case 10:



			break;




		case 11:

			while(true)
			{
				if(p[0] == 0)
					break;
				strBuff[0] = 0;
				p = GetWord(strBuff, p);
				if(strBuff[0])
				{
					if(lstrcmp(strBuff, "���") == 0)
					{
						Info->MotionInfo[MotionLastPos].ItemCodeCount = 0; break;
					}

					if(lstrcmp(strBuff, "����") == 0)
					{
						Info->MotionInfo[MotionLastPos].ItemCodeList[Info->MotionInfo[MotionLastPos].ItemCodeCount++] = 0xFF;
					}
					else
					{

						for(cnt = 0; cnt < MAX_ITEM; cnt++)
						{
							if(lstrcmp(strBuff, sItem[cnt].LastCategory) == 0)
							{
								Info->MotionInfo[MotionLastPos].ItemCodeList[
									Info->MotionInfo[MotionLastPos].ItemCodeCount++] = cnt;
								break;
							}
						}
					}

				}
				else
					break;
			}

			break;
		case 12:


			Info->MotionInfo[MotionLastPos].dwJobCodeBit = 0;
			while(true)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0] == 0) break;
				JobCount = 0;
				while(true)
				{
					if(!BitMaskJobNames[JobCount].dwBitMask) break;
					if(lstrcmpi(strBuff, BitMaskJobNames[JobCount].szName) == 0)
					{
						Info->MotionInfo[MotionLastPos].dwJobCodeBit |= BitMaskJobNames[JobCount].dwBitMask;
						break;
					}
					JobCount++;
				}
			}

			break;
		case 13:

			p = GetWord(strBuff, p);
			cnt = 0;

			if(lstrcmp(strBuff, "����") == 0)
			{
				cnt |= 1;
			}
			if(lstrcmp(strBuff, "�ʵ�") == 0)
			{
				cnt |= 2;
			}

			p = GetWord(strBuff, p);
			if(strBuff[0])
			{
				if(lstrcmp(strBuff, "����") == 0)
				{
					cnt |= 1;
				}
				if(lstrcmp(strBuff, "�ʵ�") == 0)
				{
					cnt |= 2;
				}
			}

			if(cnt == 0 || Info->MotionInfo[MotionLastPos].State == CHRMOTION_STATE_SKILL)
				cnt = 3;

			Info->MotionInfo[MotionLastPos].MapPosition = cnt;
			break;

		case 14:

			if(Info->MotionInfo[MotionLastPos].State == CHRMOTION_STATE_SKILL)
			{
				JobCount = 0;
				while(true)
				{
					p = GetWord(strBuff, p);
					if(strBuff[0] == 0) break;
					cnt = 0;
					while(true)
					{
						if(!SkillDataCode[cnt].szSkillName[0])
							break;
						if(JobCount >= (MOTION_SKIL_MAX - 1)) break;
						if(lstrcmpi(SkillDataCode[cnt].szSkillName, strBuff) == 0)
						{
							Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount++] = cnt;
							break;
						}
						cnt++;
					}
				}
				Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount] = 0;
			}
			break;



		case 15:
			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
				p = GetString(strBuff, pb);



			strcpy_s(Info->szTalkLinkFile, szDirecotry);
			lstrcat(Info->szTalkLinkFile, strBuff);

			break;

		case 16:
			pb = p;
			p = GetWord(strBuff, p);
			if(strBuff[0] == 34)
				p = GetString(strBuff, pb);



			strcpy_s(Info->szTalkMotionFile, szDirecotry);
			lstrcat(Info->szTalkMotionFile, strBuff);
			break;



		}
	}

	fclose(fp);




	int MaxRateNum, MaxRatePos;


	if(Info->NpcMotionRate[CHRMOTION_EXT])
	{


		MaxRateNum = MaxRatePos = CmdNum = 0;
		for(cnt = CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++)
		{
			if(MaxRateNum < Info->NpcMotionRate[cnt])
			{
				MaxRateNum = Info->NpcMotionRate[cnt];
				MaxRatePos = cnt;
			}

			CmdNum += Info->NpcMotionRate[cnt];
		}

		if(CmdNum > 100)
		{
			MaxRateNum -= (CmdNum - 100);
			if(MaxRateNum <= 0)
			{


				Info->NpcMotionRate[CHRMOTION_EXT] = 0;
			}
			else
				Info->NpcMotionRate[MaxRatePos] = MaxRateNum;
		}
		else if(CmdNum < 100)
		{
			MaxRateNum += (100 - CmdNum);
			Info->NpcMotionRate[MaxRatePos] = MaxRateNum;
		}


		if(Info->NpcMotionRate[CHRMOTION_EXT])
		{
			MaxRatePos = 0;
			for(cnt = CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++)
			{
				for(CmdNum = 0; CmdNum < Info->NpcMotionRate[cnt]; CmdNum++)
				{
					Info->NpcMotionRateCnt[MaxRatePos] = cnt;
					MaxRatePos++;
				}
			}
		}
	}


	if(Info->TalkMotionRate[CHRMOTION_EXT])
	{


		int MotionCntBuff[TALK_MOTION_FILE_MAX][TALK_MOTION_INFO_MAX] = { 0, };
		int RateBuff[TALK_MOTION_FILE_MAX][TALK_MOTION_INFO_MAX] = { 0, };
		int RateCnt[TALK_MOTION_FILE_MAX] = { CHRMOTION_EXT, CHRMOTION_EXT };

		for(cnt = CHRMOTION_EXT; cnt < (int)Info->TalkMotionCount; cnt++)
		{
			if(Info->TalkMotionInfo[cnt].MotionFrame == TALK_MOTION_FILE)
			{
				MotionCntBuff[TALK_MOTION_FILE][RateCnt[TALK_MOTION_FILE]] = cnt;
				RateBuff[TALK_MOTION_FILE][RateCnt[TALK_MOTION_FILE]] = Info->TalkMotionRate[cnt];
				RateCnt[TALK_MOTION_FILE]++;
			}
			else if(Info->TalkMotionInfo[cnt].MotionFrame == FACIAL_MOTION_FILE)
			{
				MotionCntBuff[FACIAL_MOTION_FILE][RateCnt[FACIAL_MOTION_FILE]] = cnt;
				RateBuff[FACIAL_MOTION_FILE][RateCnt[FACIAL_MOTION_FILE]] = Info->TalkMotionRate[cnt];
				RateCnt[FACIAL_MOTION_FILE]++;
			}
		}



		for(int loop = 0; loop < TALK_MOTION_FILE_MAX; loop++)
		{


			MaxRateNum = MaxRatePos = CmdNum = 0;

			int *lpRateBuff = RateBuff[loop];
			for(cnt = CHRMOTION_EXT; cnt < RateCnt[loop]; cnt++)
			{
				if(MaxRateNum < lpRateBuff[cnt])
				{
					MaxRateNum = lpRateBuff[cnt];
					MaxRatePos = cnt;
				}

				CmdNum += lpRateBuff[cnt];
			}

			if(CmdNum > 100)
			{
				MaxRateNum -= (CmdNum - 100);
				if(MaxRateNum <= 0)
				{


					Info->TalkMotionRate[CHRMOTION_EXT] = 0;
				}
				else
					lpRateBuff[MaxRatePos] = MaxRateNum;
			}
			else if(CmdNum < 100)
			{
				MaxRateNum += (100 - CmdNum);
				lpRateBuff[MaxRatePos] = MaxRateNum;
			}


			if(Info->TalkMotionRate[CHRMOTION_EXT])
			{
				MaxRatePos = 0;
				for(cnt = CHRMOTION_EXT; cnt < RateCnt[loop]; cnt++)
				{
					for(CmdNum = 0; CmdNum < lpRateBuff[cnt]; CmdNum++)
					{
						Info->TalkMotionRateCnt[loop][MaxRatePos] = MotionCntBuff[loop][cnt];
						MaxRatePos++;
					}
				}
			}
		}
	}






	if(MotionFileListCnt)

	{
		if(smFindPatFile(Info->szMotionFile, "smb") == FALSE)
		{
			pat3d = smASE_MergeBone(Info->szMotionFile, szMotionFileList, MotionFileListCnt);

			if(pat3d)
			{
				delete pat3d;
				pat3d = nullptr;
			}

		}
		else if(smFindPatFile(Info->szTalkMotionFile, "smb") == FALSE)
		{
			pat3d = smASE_MergeBone(Info->szTalkMotionFile, szMotionFileList, MotionFileListCnt, 0);

			if(pat3d)
			{
				delete pat3d;
				pat3d = nullptr;
			}
		}

		for(cnt = MotionFileListCnt - 1; cnt >= 0; cnt--)
		{
			if(szMotionFileList[cnt])
			{
				delete szMotionFileList[cnt];
				szMotionFileList[cnt] = nullptr;
			}

		}
	}


	char *szFile = ChangeFileExt(iniFile, szFileExt);
	DWORD dwCode = GetSpeedSum(szFile);
	ModelKeyWordEncode(dwCode, Info);


	if(Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT)
		MotionKeyWordEncode(dwCode, Info);


	szFile = ChangeFileExt(iniFile, szFileExt);
	fopen_s(&fp, szFile, "wb");
	if(fp)
	{
		fwrite(Info, sizeof(smMODELINFO), 1, fp);
		fclose(fp);
	}


	if(Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT)
		MotionKeyWordDecode(dwCode, Info);


	return TRUE;
}





int smModelDecode(char *iniFile, smMODELINFO *Info)
{
	char szFile[64];
	DWORD dwFileLen;
	char *lpFile;
	FILE *fp = nullptr;
	int len;

	smMODELINFO smModelInfo;
	ZeroMemory(Info, sizeof(smMODELINFO));

	Info->TalkMotionCount = CHRMOTION_EXT;

	Info->MotionCount = CHRMOTION_EXT;
	Info->HighModel.ModelNameCnt = 0;
	Info->DefaultModel.ModelNameCnt = 0;
	Info->LowModel.ModelNameCnt = 0;

	len = lstrlen(iniFile);


	if(iniFile[len - 4] == '.' &&
		(iniFile[len - 3] == 'a' || iniFile[len - 3] == 'A') &&
		(iniFile[len - 2] == 's' || iniFile[len - 2] == 'S') &&
		(iniFile[len - 1] == 'e' || iniFile[len - 1] == 'E'))
	{

		strcpy_s(Info->szModelFile, iniFile);

		return TRUE;
	}


	for(int i = 0; i < 3; i++)
	{
		switch(i)
		{
		case 0:
			strcpy_s(szFile, iniFile);
			break;

		case 1:
			strcpy_s(szFile, Info->szLinkFile);
			break;

		case 2:
			strcpy_s(szFile, Info->szTalkLinkFile);
			break;
		}

		if(szFile[0])
		{
			lpFile = smFindFile(szFile, szFileExt, &dwFileLen);

			if(lpFile && dwFileLen == sizeof(smMODELINFO))
			{
				fopen_s(&fp, lpFile, "rb");
				if(fp)
				{
					ZeroMemory(&smModelInfo, sizeof(smMODELINFO));
					fread(&smModelInfo, sizeof(smMODELINFO), 1, fp);
					fclose(fp);

					DWORD dwCode = GetSpeedSum(lpFile);
					if(ModelKeyWordDecode(dwCode, &smModelInfo) == FALSE)
						return FALSE;

					if(Info->szModelFile[0] && i > 0)
					{
						if(smModelInfo.MotionCount > CHRMOTION_EXT && i == 1)
						{
							if(MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE)
								return FALSE;


							strcpy_s(Info->szMotionFile, smModelInfo.szMotionFile);
							CopyMemory(Info->MotionInfo, smModelInfo.MotionInfo, sizeof(smModelInfo.MotionInfo));
							Info->MotionCount = smModelInfo.MotionCount;


							CopyMemory(Info->NpcMotionRate, smModelInfo.NpcMotionRate, sizeof(smModelInfo.NpcMotionRate));
							CopyMemory(Info->NpcMotionRateCnt, smModelInfo.NpcMotionRateCnt, sizeof(smModelInfo.NpcMotionRateCnt));
						}
						else if(smModelInfo.TalkMotionCount > CHRMOTION_EXT && i == 2)
						{

							strcpy_s(Info->szTalkLinkFile, smModelInfo.szTalkLinkFile);
							strcpy_s(Info->szTalkMotionFile, smModelInfo.szTalkMotionFile);
							CopyMemory(Info->TalkMotionInfo, smModelInfo.TalkMotionInfo, sizeof(smModelInfo.TalkMotionInfo));
							Info->TalkMotionCount = smModelInfo.TalkMotionCount;


							CopyMemory(Info->TalkMotionRate, smModelInfo.TalkMotionRate, sizeof(smModelInfo.TalkMotionRate));
							CopyMemory(Info->TalkMotionRateCnt, smModelInfo.TalkMotionRateCnt, sizeof(smModelInfo.TalkMotionRateCnt));
						}
					}
					else
					{
						if(smModelInfo.MotionCount > CHRMOTION_EXT)
						{
							if(MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE)
								return FALSE;
						}

						memcpy(Info, &smModelInfo, sizeof(smMODELINFO));
					}
				}
				else
				{
					if(AddModelDecode(szFile, Info) == FALSE)
						return FALSE;
				}
			}
			else
			{
				if(AddModelDecode(szFile, Info) == FALSE)
					return FALSE;
			}
		}
	}

	return TRUE;
}

smCONFIG smConfig;


char *szWordTexQualty[4] = { "����" , "����" , "����" , "���ֳ���" };
char *InfoRegPath = "SOFTWARE\\Triglow Pictures\\PristonTale";


TRANS_SERVER_LIST	TransServerList;
rsSERVER_CONFIG	rsServerConfig;
static int	srAdminCmdCnt = 0;
DWORD GetSwapIPCode(char *szIP);



#ifdef _W_SERVER


int SetServerConfig(char *decode, char *lpPoint)
{

	int flag = 0;
	char *p = lpPoint;
	char *pb = nullptr;
	char strBuff[128] = { 0 };
	int cnt;

	flag = 0;

	if(lstrcmp(decode, "*�����ڵ��ȣ") == 0 ||
		lstrcmpi(decode, "*SERVER_CODE") == 0)
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.ServerCode = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ڵ�ĳ���ͻ��") == 0 ||
		lstrcmpi(decode, "*SERVER_AUTOPLAY") == 0))
	{
		rsServerConfig.AutoPlayer = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*������ۻ��") == 0 ||
		lstrcmpi(decode, "*SERVER_RECORD_MEM") == 0))
	{
		rsServerConfig.UseRecorMemory = TRUE;
		flag++;
	}


	if(!flag && lstrcmp(decode, "*�������") == 0)
	{
		rsServerConfig.DisableParty = TRUE;
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*���������ο�") == 0 ||
		lstrcmpi(decode, "*MAX_USERS") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.ConnectUserMax = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�׽�Ʈ����") == 0 ||
		lstrcmpi(decode, "*TEST_SERVER") == 0))
	{
		rsServerConfig.TestSeverMode = TRUE;
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
		{
			rsServerConfig.TestSeverMode = atoi(strBuff);
		}
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���Ӱ����ڵ�") == 0 ||
		lstrcmpi(decode, "*CONNECT_CLIENT_CODE") == 0))
	{
		for(cnt = 0; cnt < 32; cnt++)
		{
			p = GetWord(strBuff, p);
			if(!strBuff[0]) break;

			rsServerConfig.dwClientCheckSum[rsServerConfig.ClientCheckSumCount] = atoi(strBuff);
			rsServerConfig.ClientCheckSumCount++;
		}
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ڵ���������") == 0 ||
		lstrcmpi(decode, "*DISCONNECT_CLIENT_BADCODE") == 0))
	{
		rsServerConfig.ClientCheckOut = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���κ�ȣ�ڵ�") == 0 ||
		lstrcmpi(decode, "*CLSAFE_CODE") == 0))
	{

		for(cnt = 0; cnt < 32; cnt++)
		{
			p = GetWord(strBuff, p);
			if(!strBuff[0]) break;

			rsServerConfig.dwSafeClientCode[rsServerConfig.SafeClientCodeCount] = atoi(strBuff);
			rsServerConfig.SafeClientCodeCount++;
		}
		flag++;



	}
	if(!flag && (lstrcmp(decode, "*��ȣ�ڵ��������") == 0 ||
		lstrcmpi(decode, "*DISCONNECT_CLSAFE_CODE") == 0))
	{
		rsServerConfig.ClientCodeCheckOut = TRUE;
		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���ѹ���") == 0 ||
		lstrcmpi(decode, "*VERSION") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.LimitVersion = atoi(strBuff);

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*�����̸�") == 0 ||
		lstrcmpi(decode, "*SERVER_NAME") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		strcpy_s(rsServerConfig.szServerName, strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*PK�㰡") == 0 ||
		lstrcmpi(decode, "*ENABLE_PK") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PK = atoi(strBuff);
		if(rsServerConfig.Enable_PK == 0) rsServerConfig.Enable_PK = TRUE;

		flag++;
	}

	if (!flag && (lstrcmp(decode, "*PK�ʵ�") == 0 ||
		lstrcmpi(decode, "*PK_FIELD") == 0))
	{
		//Mapa PvP 1 - 
		pb = p; p = GetWord(strBuff, p); if (strBuff[0] == 62)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PKField = atoi(strBuff);
		if (rsServerConfig.Enable_PKField == 0) rsServerConfig.Enable_PKField = 9;

		flag++;
	}
	//Mapa PvP 2 - 
	if (!flag && (lstrcmp(decode, "*PK�ʵ�") == 0 ||
		lstrcmpi(decode, "*PK_FIELD1") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if (strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PKField1 = atoi(strBuff);
		if (rsServerConfig.Enable_PKField1 == 0) rsServerConfig.Enable_PKField1 = 21;

		flag++;
	}
	//Mapa PvP 3 - 
	if (!flag && (lstrcmp(decode, "*PK�ʵ�") == 0 ||
		lstrcmpi(decode, "*PK_FIELD2") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if (strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PKField2 = atoi(strBuff);
		if (rsServerConfig.Enable_PKField2 == 0) rsServerConfig.Enable_PKField2 = 60;

		flag++;
	}
	//Mapa PvP 4 - 
	if (!flag && (lstrcmp(decode, "*PK�ʵ�") == 0 ||
		lstrcmpi(decode, "*PK_FIELD3") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if (strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PKField3 = atoi(strBuff);
		if (rsServerConfig.Enable_PKField3 == 0) rsServerConfig.Enable_PKField3 = 61;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*PK����ʵ�") == 0 || lstrcmpi(decode, "*PK_FIELD_ALL") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Enable_PKField_All = atoi(strBuff);
		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���న��") == 0 ||
		lstrcmpi(decode, "*POTION_MONITOR") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.PotionMonitor = atoi(strBuff);
		else
			rsServerConfig.PotionMonitor = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���Ȱ˻�") == 0 ||
		lstrcmpi(decode, "*CL_PROTECT") == 0))
	{

		rsServerConfig.CheckProtect = TRUE;
		flag++;
	}


#ifdef LOG_THE_PK

	if(!flag && (lstrcmpi(decode, "*PK_LOG") == 0))
	{
		rsServerConfig.bPK_LOG = true;
		flag++;
	}
#endif


	if(!flag && (lstrcmp(decode, "*��������") == 0 ||
		lstrcmpi(decode, "*REMOVE_PROTECT_TIME") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.RemoveNProtectTime = atoi(strBuff);
		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���ܰ�") == 0 ||
		lstrcmpi(decode, "*BLOCK_LEVEL") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.BlockLevel = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���ƿ�") == 0 ||
		lstrcmpi(decode, "*BLOCK_LOGOUT") == 0))
	{
		rsServerConfig.BlockLevel_LogOut = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����ۿ�������") == 0 ||
		lstrcmpi(decode, "*DISCONNECT_ITEM_ERROR") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.ItemCodeOut = atoi(strBuff);
		else
			rsServerConfig.ItemCodeOut = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��ǰ˻�") == 0 ||
		lstrcmpi(decode, "*CLIENT_CHECK_FUNC") == 0))
	{
		rsServerConfig.ClientFuncCheckMode = 1;
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.ClientFuncCheckMode = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_MANDOO") == 0))
	{
		rsServerConfig.Event_Mandoo = TRUE;;
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*�ϵ��ھ��̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_HARDCORE") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_HardCore = atoi(strBuff);
		else
			rsServerConfig.Event_HardCore = 1;

		flag++;
	}
#ifdef	_LANGUAGE_JAPANESE 
	if(!flag && (lstrcmp(decode, "*���ݷ�Ȱ���̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_DAMAGEOFF") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_DamageOff = atoi(strBuff);
		else
			rsServerConfig.Event_DamageOff = 1;
		flag++;
	}
#else
	if(!flag && (lstrcmpi(decode, "*EVENT_DAMAGEOFF1") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_DamageOff1 = atoi(strBuff);
		else
			rsServerConfig.Event_DamageOff1 = 1;
		flag++;
	}
	if(!flag && (lstrcmpi(decode, "*EVENT_DAMAGEOFF2") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_DamageOff2 = atoi(strBuff);
		else
			rsServerConfig.Event_DamageOff2 = 1;
		flag++;
	}
#endif

	if(!flag && (lstrcmp(decode, "*���������̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_DEFENSEOFF") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_DefenseOff = atoi(strBuff);
		else
			rsServerConfig.Event_DefenseOff = 1;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_CHILD") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Child = atoi(strBuff);
		else
			rsServerConfig.Event_Child = 1;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*ũ����Ż�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_CRISTAL") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Cristal = atoi(strBuff);
		else
			rsServerConfig.Event_Cristal = 1;

		flag++;
	}
	if(!flag && (lstrcmp(decode, "*�����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_POTION") == 0))
	{

		p = GetWord(strBuff, p);
		rsServerConfig.Event_Potion = atoi(strBuff);
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*������Ʈ�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_STARPOINT") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_StarPointTicket = atoi(strBuff);
		else
			rsServerConfig.Event_StarPointTicket = 40;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_BIRTHDAY") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_ComicBirthDay = atoi(strBuff);
		else
			rsServerConfig.Event_ComicBirthDay = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_PUZZLE") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Puzzle = atoi(strBuff);
		else
			rsServerConfig.Event_Puzzle = 200;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ٺ����̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_BABELHORN") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_BabelHorn = atoi(strBuff);
		else
			rsServerConfig.Event_BabelHorn = 4;

		if(rsServerConfig.Event_BabelHorn > 10) rsServerConfig.Event_BabelHorn = 10;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*����ȣ�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_NINEFOX") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_NineFox = atoi(strBuff);
		else
			rsServerConfig.Event_NineFox = 20;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*ũ���������̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_CHRISTMAS") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.EVENT_Christmas = atoi(strBuff);
		else
			rsServerConfig.EVENT_Christmas = 100;

		flag++;
	}
	if(!flag && (lstrcmp(decode, "*�߷�Ÿ�ε���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_VALENTINEDAY") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_ValentineDay = atoi(strBuff);
		else
			rsServerConfig.Event_ValentineDay = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*Ŀ�ø�_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_COUPLERING") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_CoupleRing = atoi(strBuff);
		else
			rsServerConfig.Event_CoupleRing = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*����_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_WATERMELON") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Watermelon = atoi(strBuff);
		else
			rsServerConfig.Event_Watermelon = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*�߷�Ÿ��_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_VALENTINE") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Valentine = atoi(strBuff);
		else
			rsServerConfig.Event_Valentine = 100;

		flag++;
	}



	if(!flag && (lstrcmp(decode, "*ĵ������_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_CANDYDAYS") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Candydays = atoi(strBuff);
		else
			rsServerConfig.Event_Candydays = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���ϴüҿ�_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_STAR") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Star = atoi(strBuff);
		else
			rsServerConfig.Event_Star = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���ĺ�����_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_PRISTON_ALPHABET") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_PristonAlphabet = atoi(strBuff);
		else
			rsServerConfig.Event_PristonAlphabet = 100;
		flag++;
	}



	if(!flag && (lstrcmp(decode, "*ȭ��Ʈ��Ʈ��Ʈ_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_WHITECONTRAST") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_WhiteContrast = atoi(strBuff);
		else
			rsServerConfig.Event_WhiteContrast = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*����������ȥ_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_BLACKSMITH") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_BlackSmith = atoi(strBuff);
		else
			rsServerConfig.Event_BlackSmith = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*�����ñ׸�_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_MAGICALGREEN") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_MagicalGreen = atoi(strBuff);
		else
			rsServerConfig.Event_MagicalGreen = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*ī���Ǵ���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_TEAROFKARA") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_TearOfKara = atoi(strBuff);
		else
			rsServerConfig.Event_TearOfKara = 100;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*ȭ��Ʈ����_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_WHITEDAY") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_WhiteDay = atoi(strBuff);
		else
			rsServerConfig.Event_WhiteDay = 100;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����ǽ���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_MORIFSHELTOM") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_MorifSheltom = atoi(strBuff);
		else
			rsServerConfig.Event_MorifSheltom = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*������_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_WORLDCUP") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_WorldCup = atoi(strBuff);
		else
			rsServerConfig.Event_WorldCup = 5;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*���ڸ���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_WATERMELONMONSTER") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_WarerMelonMonster = atoi(strBuff);
		else
			rsServerConfig.Event_WarerMelonMonster = 1;

		flag++;
	}



	if(!flag && (lstrcmp(decode, "*�����ʹ���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_MOLLYWOLF") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_MollyWolf = atoi(strBuff);
		else
			rsServerConfig.Event_MollyWolf = 9;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*����_�̺�Ʈ") == 0 || lstrcmpi(decode, "*EVENT_CHICHEN_DAY") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Chichen_Day = atoi(strBuff);
		else
			rsServerConfig.Event_Chichen_Day = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��Ʈ_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_GHOST") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_Ghost = atoi(strBuff);
		else
			rsServerConfig.Event_Ghost = 2;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��Ÿ���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_SANTAGOBLIN") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_SantaGoblin = atoi(strBuff);
		else
			rsServerConfig.Event_SantaGoblin = 5;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_SUMMER_CHICKEN") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_SummerChicken = atoi(strBuff);
		else
			rsServerConfig.Event_SummerChicken = 5;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ǽù���_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_PCBANG_PET") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_PCBangPet = atoi(strBuff);
		else
			rsServerConfig.Event_PCBangPet = 1;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*����ġ��_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_EXPUP") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.Event_ExpUp = atoi(strBuff);
		else
			rsServerConfig.Event_ExpUp = 120;



		if (rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200)
		{
			rsServerConfig.Event_ExpUp = 100;
		}
		else if (rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300)
		{
			rsServerConfig.Event_ExpUp = 200;
		}
		else if (rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400)
		{
			rsServerConfig.Event_ExpUp = 300;
		}
		else if (rsServerConfig.Event_ExpUp >= 400 && rsServerConfig.Event_ExpUp < 500)
		{
			rsServerConfig.Event_ExpUp = 400;
		}
		else if (rsServerConfig.Event_ExpUp >= 500 && rsServerConfig.Event_ExpUp < 600)
		{
			rsServerConfig.Event_ExpUp = 500;
		}
		else if (rsServerConfig.Event_ExpUp >= 600 && rsServerConfig.Event_ExpUp < 700)
		{
			rsServerConfig.Event_ExpUp = 600;
		}
		else if (rsServerConfig.Event_ExpUp >= 700 && rsServerConfig.Event_ExpUp < 800)
		{
			rsServerConfig.Event_ExpUp = 700;
		}
		else if (rsServerConfig.Event_ExpUp >= 800 && rsServerConfig.Event_ExpUp < 900)
		{
			rsServerConfig.Event_ExpUp = 800;
		}
		else if (rsServerConfig.Event_ExpUp >= 900 && rsServerConfig.Event_ExpUp < 1000)
		{
			rsServerConfig.Event_ExpUp = 900;
		}
		else
		{
			rsServerConfig.Event_ExpUp = 100;
		}

		flag++;
	}

#ifdef _LANGUAGE_ARGENTINA

	if(!flag && (lstrcmp(decode, "*����ġ��_�̺�Ʈ_��ƾ") == 0 || lstrcmpi(decode, "*EVENT_EXPUP_LATIN") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
		{
			rsServerConfig.Event_ExpUp_latin = atoi(strBuff);
		}
		else
		{
			rsServerConfig.Event_ExpUp_latin = 100;
		}

		flag++;
	}

#endif




	if(!flag && (lstrcmp(decode, "*��������_�̺�Ʈ") == 0 ||
		lstrcmpi(decode, "*EVENT_HALLOWEEN") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
		{
			rsServerConfig.Event_GiftBox = atoi(strBuff);
		}
		else
		{
			rsServerConfig.Event_GiftBox = 0;
		}

		flag++;
	}



	if(!flag && (lstrcmp(decode, "*�ð�����ġ") == 0 || lstrcmpi(decode, "*EXP_GAMETIME") == 0))
	{
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.ExpGameTimeMode = atoi(strBuff);
		else
			rsServerConfig.ExpGameTimeMode = 1;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*����ĳ��") == 0 ||
		lstrcmpi(decode, "*EVENT_BLESSCASTLE") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.BlessCastleMode = atoi(strBuff);
		else
			rsServerConfig.BlessCastleMode = 1;

		flag++;
	}
	if(!flag && (lstrcmp(decode, "*�����ð�") == 0 ||
		lstrcmpi(decode, "*EVENT_SIEGE_TIME") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.sBlessCastle_StartTime[0] = atoi(strBuff);
		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.sBlessCastle_StartTime[1] = atoi(strBuff);

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�̺�Ʈ��Ʈ����") == 0 ||
		lstrcmpi(decode, "*EVENT_BITMASK") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.EventPlay_BitMask = atoi(strBuff);

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ű���������") == 0 ||
		lstrcmpi(decode, "*DEFAULT_ITEM_USER") == 0))
	{

		p = GetWord(strBuff, p);
		if(strBuff[0])
			rsServerConfig.StartUser_PresentItem = atoi(strBuff);
		else
			rsServerConfig.StartUser_PresentItem = TRUE;

		flag++;
	}


	if(!flag && (lstrcmp(decode, "*�����ڱ��") == 0 ||
		lstrcmpi(decode, "*RECORD_JOBCHANGER") == 0))
	{
		rsServerConfig.Record_JobChanger = TRUE;;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�������㰡") == 0 ||
		lstrcmpi(decode, "*ENABLE_BLOCK_FOREVER") == 0))
	{
		rsServerConfig.ForeverBlockMode = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*����ġ��������") == 0 ||
		lstrcmpi(decode, "*PERMIT_EXP") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Permit_Exp = atoi(strBuff);
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*����������") == 0 ||
		lstrcmpi(decode, "*PERMIT_MONEY") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Permit_Money = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���μ����ð�����") == 0 ||
		lstrcmpi(decode, "*CLIENT_CHECK_PROCESS_TIME") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.ClientProcessTimeChk = atoi(strBuff);
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*���μ����ð�����") == 0 ||
		lstrcmpi(decode, "*CLIENT_PROCESS_TIME_OUT") == 0))
	{
		rsServerConfig.ClientProcessTimeChkOut = TRUE;
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*���హ��Ȯ��") == 0 ||
		lstrcmpi(decode, "*CHECK_POTION_COUNT") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Dis_PotionError = atoi(strBuff);
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*��������ġ���") == 0 ||
		lstrcmpi(decode, "*ENABLE_SERVER_EXP") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

		if(strBuff[0]) rsServerConfig.ExpFixMode = atoi(strBuff);
		else rsServerConfig.ExpFixMode = 50;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���������") == 0 ||
		lstrcmpi(decode, "*BLOCK_USER_PATH") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		strcpy_s(rsServerConfig.szBlockUserPath, strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*���ð�ǥ��") == 0 ||
		lstrcmpi(decode, "*DISP_BILLING_TIME") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.DispBillingTime = atoi(strBuff);
		else
			rsServerConfig.DispBillingTime = 1;

		flag++;
	}

	//if(!flag && (lstrcmp(decode, "*�α��α���") == 0 ||
	//	lstrcmpi(decode, "*DISABLE_LOGIN") == 0))
	//{

	//	pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
	//	if(strBuff[0])
	//		rsServerConfig.Disable_LogIn = atoi(strBuff);
	//	else
	//		rsServerConfig.Disable_LogIn = 1;
	//	flag++;
	//}

	if(!flag &&	lstrcmpi(decode, "*ALLOWED_LOGIN") == 0)
	{
		pb = p; 
		p = GetWord(strBuff, p); 

		if(strBuff[0] == 34)
			p = GetString(strBuff, pb);

		if(strBuff[0])
			rsServerConfig.allowed_login = atoi(strBuff);
		else
			rsServerConfig.allowed_login = 0;

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�α�ť����") == 0 ||
		lstrcmpi(decode, "*DISABLE_LOGQUE") == 0))
	{
		rsServerConfig.Disable_LogQue = TRUE;
		flag++;
	}
	if(!flag && (lstrcmp(decode, "*�α׾ƿ�Ȯ�α���") == 0 ||
		lstrcmpi(decode, "*DISABLE_CHECK_LOGOUT") == 0))
	{
		rsServerConfig.Disable_CheckLogOut = TRUE;
		flag++;
	}

	//if(!flag && (lstrcmp(decode, "*�α�������") == 0 ||
	//	lstrcmpi(decode, "*DISABLE_LOGINX") == 0))
	//{
	//	rsServerConfig.Disable_LogIn2 = TRUE;
	//	flag++;
	//}


	if(!flag && (lstrcmp(decode, "*���᷹��") == 0 ||
		lstrcmpi(decode, "*FREE_LEVEL") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.FreeLevel = atoi(strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			strcpy_s(rsServerConfig.szFreeGpCode, strBuff);

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��������") == 0 ||
		lstrcmpi(decode, "*PRESENT_LEVEL") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.PresentLevel = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*������������") == 0 ||
		lstrcmpi(decode, "*ENABLE_PARTYITEM") == 0))
	{

		rsServerConfig.Enable_PartyItem = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�ʵ������˻�") == 0 ||
		lstrcmpi(decode, "*CHECK_PLAYFIELD") == 0))
	{

		rsServerConfig.CheckPlayField = TRUE;
		flag++;
	}


	if(!flag && (lstrcmp(decode, "*�����ϰ˻�") == 0 ||
		lstrcmpi(decode, "*CHECK_MODELFILE") == 0))
	{

		rsServerConfig.CheckModelFile = TRUE;
		flag++;
	}


	if(!flag && (lstrcmp(decode, "*��������IP") == 0 ||
		lstrcmpi(decode, "*DISABLE_IP") == 0))
	{

		if(rsServerConfig.DisableIP_Count < DISABLE_IP_MAX)
		{
			p = GetWord(strBuff, p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][0] = GetSwapIPCode(strBuff);
			p = GetWord(strBuff, p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][1] = GetSwapIPCode(strBuff);
			rsServerConfig.DisableIP_Count++;
		}

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����㰡IP") == 0 ||
		lstrcmpi(decode, "*ENABLE_IP") == 0))
	{

		if(rsServerConfig.EnableIP_Count < ENABLE_IP_MAX)
		{
			p = GetWord(strBuff, p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][0] = GetSwapIPCode(strBuff);
			p = GetWord(strBuff, p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][1] = GetSwapIPCode(strBuff);
			rsServerConfig.EnableIP_Count++;
		}

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��������IP") == 0 ||
		lstrcmpi(decode, "*ADMINISTRATOR_IP") == 0))
	{

		if(rsServerConfig.AdminIP_Count < ADMIN_IP_MAX)
		{
			p = GetWord(strBuff, p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode(strBuff);
			p = GetWord(strBuff, p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode(strBuff);
			rsServerConfig.AdminIP_Count++;
		}

		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����κ��丮") == 0 ||
		lstrcmpi(decode, "*SERVER_INVENTORY") == 0))
	{

		rsServerConfig.ServerInventoryMode = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��������̸�") == 0 ||
		lstrcmpi(decode, "*BACKUP_PATH") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		strcpy_s(rsServerConfig.szBackupPath, strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��ų����Ʈ���ҺҰ�") == 0 ||
		lstrcmpi(decode, "*DISABLE_DEC_SKILLPOINT") == 0))
	{

		rsServerConfig.Disable_DecSkillPoint = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*����Ʈ����") == 0 ||
		lstrcmpi(decode, "*DISABLE_QUEST") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		rsServerConfig.Disable_Quest = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����ʵ����") == 0 ||
		lstrcmpi(decode, "*START_FIELD") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.FixedStartField = atoi(strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�����۹�������") == 0 ||
		lstrcmpi(decode, "*DISABLE_THROWITEM") == 0))
	{

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.DisableThrowItem = atoi(strBuff);
		else
			rsServerConfig.DisableThrowItem = 1;

		flag++;
	}



	if(!flag && (lstrcmp(decode, "*ũ��������Ŷ") == 0 ||
		lstrcmpi(decode, "*CRAZY_PACKET") == 0))
	{

		rsServerConfig.CrazyPacketMode = TRUE;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*�뺸�ּ�") == 0 ||
		lstrcmpi(decode, "*NOTICE_URL") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		strcpy_s(rsServerConfig.szNoticeURL, strBuff);
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*������ɱ��") == 0 ||
		lstrcmpi(decode, "*REC_ADMIN_CMD") == 0))
	{
		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			rsServerConfig.RecordAdminCommand = atoi(strBuff);
		else
			rsServerConfig.RecordAdminCommand = 2;

		flag++;
	}




	if(!flag && (lstrcmp(decode, "*��������") == 0 ||
		lstrcmpi(decode, "*AREA_SERVER") == 0))
	{

		for(cnt = 0; cnt < 32; cnt++)
		{
			if(rsServerConfig.AreaServer.IP_Count >= SERVER_MAP_MAX) break;

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			if(!strBuff[0]) break;

			rsServerConfig.AreaServer.dwIP[rsServerConfig.AreaServer.IP_Count] = inet_addr(strBuff);

			rsServerConfig.AreaServer.IP_Count++;
			rsServerConfig.AreaServer.size = sizeof(TRANS_SEVER_MAP) - (sizeof(DWORD)*(SERVER_MAP_MAX - rsServerConfig.AreaServer.IP_Count));
			rsServerConfig.AreaServer.code = OpCode::OPCODE_AREA_SERVER_MAP;
		}
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*��ʸ�Ʈ��������") == 0 ||
		lstrcmpi(decode, "*TT_DATA_SERVER") == 0))
	{

		cnt = rsServerConfig.TT_DataServer_Count;

		if(cnt >= TT_DATA_SERVER_MAX) goto skip_t;

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(!strBuff[0]) goto skip_t;
		strcpy_s(rsServerConfig.TT_DataServer[cnt].szServerID, strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(!strBuff[0]) goto skip_t;
		strcpy_s(rsServerConfig.TT_DataServer[cnt].szServerPath, strBuff);

		rsServerConfig.TT_DataServer_Count++;
	skip_t:
		flag++;
	}


	return flag;
}

#else


int SetServerConfig(char *decode, char *lpPoint)
{

	return NULL;
}

#endif



int SetServerSelectList(char *decode, char *lpPoint)
{
	int flag;
	char *p = lpPoint;
	char *pb;
	char strBuff[128];
	int cnt;

	flag = 0;

	if(TransServerList.ServerCount >= TRANS_SERVER_MAX) return FALSE;

	if(lstrcmp(decode, "*���Ӽ�������") == 0 ||
		lstrcmpi(decode, "*GAME_SERVER") == 0)
	{
		cnt = TransServerList.ServerCount;

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
		{
			strcpy_s(TransServerList.ServerInfo[cnt].szServerName, strBuff);
		}

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
		{
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp1, strBuff);
			TransServerList.ServerInfo[cnt].dwServerPort1 = SERVER_TCP_PORT;
		}

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
		{
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp2, strBuff);
			TransServerList.ServerInfo[cnt].dwServerPort2 = SERVER_TCP_PORT;
		}

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
		{
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp3, strBuff);
			TransServerList.ServerInfo[cnt].dwServerPort3 = SERVER_TCP_PORT;
		}

		TransServerList.ServerCount++;
		flag++;
	}

	if(!flag && (lstrcmp(decode, "*Ŭ����������") == 0 ||
		lstrcmpi(decode, "*CLAN_SERVER") == 0))
	{

		cnt = TransServerList.ServerCount + TransServerList.ClanServerCount;

		strcpy_s(TransServerList.ServerInfo[cnt].szServerName, "Clan");

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp1, strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			TransServerList.ServerInfo[cnt].dwServerPort1 = atoi(strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp2, strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			TransServerList.ServerInfo[cnt].dwServerPort2 = atoi(strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			strcpy_s(TransServerList.ServerInfo[cnt].szServerIp3, strBuff);

		pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
		if(strBuff[0])
			TransServerList.ServerInfo[cnt].dwServerPort3 = atoi(strBuff);

		TransServerList.ClanServerCount++;
		flag++;
	}


	return flag;
}



smCONFIG *smConfigDecode(char *iniFile)
{
	smCONFIG *Config = &smConfig;

	srAdminCmdCnt = 0;

	ZeroMemory(Config, sizeof(smCONFIG));
	ZeroMemory(&TransServerList, sizeof(TRANS_SERVER_LIST));
	ZeroMemory(&rsServerConfig, sizeof(rsSERVER_CONFIG));

	Config->StageObjCnt = 0;
	Config->MapBright = DEFAULT_BRIGHT;
	Config->MapContrast = DEFAULT_CONTRAST;
	Config->MapLightVector.x = fONE;
	Config->MapLightVector.y = -fONE;
	Config->MapLightVector.z = fONE / 2;

	rsServerConfig.Enable_PKField = -1;
	rsServerConfig.Enable_PKField1 = -1;
	rsServerConfig.Enable_PKField2 = -1;
	rsServerConfig.Enable_PKField3 = -1;
	rsServerConfig.Enable_PKField_All = 0;

	std::ifstream filein(iniFile, std::ifstream::binary);

	if(filein.fail())
	{
		return nullptr;
	}

	for(std::string line; std::getline(filein, line);)
	{
		char *p = GetWord(decode, (char*)line.c_str());

#ifdef _W_SERVER
		if(SetServerSelectList(decode, p)) continue;
		if(SetServerConfig(decode, p)) continue;
#endif
	}

	filein.close();

	smMATRIX rX, rY, mVect;
	int vx, vy, vz;

	int MapLightAngY = 128 * 16;
	int MapLightAngX = (128 - 10) * 16;
	MapLightAngX = (MapLightAngX - ANGLE_90) & ANGCLIP;

	int x = 0;
	int y = 0;
	int z = (int)(1.5*fONE);

	smIdentityMatrix(rX);
	smIdentityMatrix(rY);

	smRotateYMatrix(rY, MapLightAngY);
	smRotateXMatrix(rX, MapLightAngX);
	smMatrixMult(mVect, rX, rY);

	vx = x * mVect._11 +
		y * mVect._21 +
		z * mVect._31;

	vy = x * mVect._12 +
		y * mVect._22 +
		z * mVect._32;

	vz = x * mVect._13 +
		y * mVect._23 +
		z * mVect._33;

	vx >>= FLOATNS;
	vy >>= FLOATNS;
	vz >>= FLOATNS;

	Config->MapLightVector.x = vx;
	Config->MapLightVector.y = vy;
	Config->MapLightVector.z = vz;

	Config->MapBright = 130;
	Config->MapContrast = 300;

	return &smConfig;
};


char *GetDirectoryFromFile(char *filename, char *szDirectory, size_t size)
{
	int len;
	int cnt;

	if(!szDirectory)
	{
		return NULL;
	}

	strcpy_s(szDirectory, size, filename);

	len = lstrlen(szDirectory);

	for(cnt = len; cnt >= 0; cnt--)
		if(szDirectory[cnt] == '\\') break;

	szDirectory[cnt + 1] = NULL;

	return szDirectory;
}




int DecodeItemInfo(char *szItemFile, sDEF_ITEMINFO *lpDefItem)
{
	FILE	*fp;
	char strBuff[128];
	char *p;
	char *pb;
	int cnt;
	int NextFlag;
	sITEMINFO	*lpItem;

	lpItem = &lpDefItem->Item;

	ZeroMemory(lpDefItem, sizeof(sDEF_ITEMINFO));

	fp = fopen(szItemFile, "rb");
	if(fp == NULL) return FALSE;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
			break;

		p = GetWord(decode, line);
		NextFlag = 0;


		if(lstrcmp(decode, "*�̸�") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			strcpy_s(lpItem->ItemName, strBuff);
			NextFlag = TRUE;
		}


#ifdef _LANGUAGE_BRAZIL
		if(lstrcmpi(decode, "*J_NAME") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			strcpy_s(lpItem->ItemName, strBuff);
			NextFlag = TRUE;
		}
#endif



		if(!NextFlag && lstrcmp(decode, "*�ڵ�") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			for(cnt = 0; cnt < MAX_ITEM; cnt++)
			{
				if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
				{
					lpItem->CODE = sItem[cnt].CODE; break;
				}
			}

			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*����ũ") == 0)
		{
			p = GetWord(strBuff, p);
			if(strBuff[0])
				lpItem->UniqueItem = atoi(strBuff);
			else
				lpItem->UniqueItem = TRUE;

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*����ũ����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->EffectColor[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->EffectColor[1] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->EffectColor[2] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->EffectColor[3] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->EffectBlink[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			if(strBuff[0])
				lpItem->ScaleBlink[0] = (int)(atof(strBuff)*fONE);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*����Ʈ����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->DispEffect = atoi(strBuff);
			NextFlag = TRUE;
		}





		if(!NextFlag && lstrcmp(decode, "*������") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sDurability[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sDurability[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Weight = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Price = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*��ü") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_BIONIC][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_BIONIC][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*���ڿ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_EARTH][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_EARTH][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_FIRE][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_FIRE][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*�ñ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_ICE][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_ICE][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_LIGHTING][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_LIGHTING][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_POISON][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_POISON][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_WATER][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_WATER][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if(!NextFlag && lstrcmp(decode, "*�ٶ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_WIND][0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sResistance[sITEMINFO_WIND][1] = atoi(strBuff);
			NextFlag = TRUE;
		}






		if(!NextFlag && lstrcmp(decode, "*���ݷ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sDamage[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sDamage[1] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sDamage[2] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sDamage[3] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*�����Ÿ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Shooting_Range = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*���ݼӵ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Attack_Speed = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*���߷�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sAttack_Rating[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sAttack_Rating[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*ũ��Ƽ��") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Critical_Hit = atoi(strBuff);
			NextFlag = TRUE;
		}





		if(!NextFlag && lstrcmp(decode, "*�����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->fAbsorb[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fAbsorb[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sDefence[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sDefence[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->fBlock_Rating[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fBlock_Rating[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*�̵��ӵ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->fSpeed[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fSpeed[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*��������") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Potion_Space = atoi(strBuff);
			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*�������õ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->fMagic_Mastery = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*�������") == 0 || lstrcmp(decode, "*������") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->fMana_Regen[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fMana_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*���������") == 0 || lstrcmp(decode, "*��������") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->fLife_Regen[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fLife_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*���׹̳����") == 0 || lstrcmp(decode, "*�ٷ����") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->fStamina_Regen[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fStamina_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;

		}

		if(!NextFlag && (lstrcmp(decode, "*�����߰�") == 0 || lstrcmp(decode, "*����߰�") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Mana[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Mana[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*�������߰�") == 0 || lstrcmp(decode, "*������߰�") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Life[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Life[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*���׹̳��߰�") == 0 || lstrcmp(decode, "*�ٷ��߰�") == 0))
		{
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Stamina[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->Increase_Stamina[1] = atoi(strBuff);
			NextFlag = TRUE;
		}





		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Level = atoi(strBuff);
			NextFlag = TRUE;
		}

		if (!NextFlag && lstrcmp(decode, "*BL") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->BattleLevel = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Strength = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*���ŷ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Spirit = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*���") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Talent = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*��ø��") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Dexterity = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*�ǰ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->Health = atoi(strBuff);
			NextFlag = TRUE;
		}





		if(!NextFlag && (lstrcmp(decode, "*���׹̳ʻ��") == 0 || lstrcmp(decode, "*�ٷ»��") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->Stamina[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->Stamina[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && (lstrcmp(decode, "*�������") == 0 || lstrcmp(decode, "*��»��") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->Mana[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->Mana[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && (lstrcmp(decode, "*���������") == 0 || lstrcmp(decode, "*����»��") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->Life[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->Life[1] = atoi(strBuff);
			NextFlag = TRUE;
		}






		if(!NextFlag && lstrcmp(decode, "**Ưȭ") == 0)
		{
			while(1)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0] == 0) break;
				cnt = 0;
				while(1)
				{
					if(!JobDataBase[cnt].szName[0]) break;
					if(lstrcmpi(JobDataBase[cnt].szName, strBuff) == 0)
					{

						lpItem->JobCodeMask = JobDataBase[cnt].JobBitCode;
						break;
					}
					cnt++;
				}
			}

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "**Ưȭ����") == 0)
		{
			while(1)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0] == 0) break;
				cnt = 0;
				while(1)
				{
					if(!JobDataBase[cnt].szName[0]) break;
					if(lstrcmpi(JobDataBase[cnt].szName, strBuff) == 0)
					{
						if(lpDefItem->JobBitCodeRandomCount >= SPECIAL_JOB_RANDOM_MAX) break;
						lpDefItem->dwJobBitCode_Random[lpDefItem->JobBitCodeRandomCount++] = JobDataBase[cnt].JobBitCode;

						break;
					}
					cnt++;
				}
			}

			NextFlag = TRUE;
		}







		if(!NextFlag && lstrcmp(decode, "**�����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_Absorb[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_Absorb[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sSpecial_Defence[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->sSpecial_Defence[1] = atoi(strBuff);


			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "**�̵��ӵ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_fSpeed[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_fSpeed[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**����") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Add_fBlock_Rating = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**���ݼӵ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Add_Attack_Speed = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**ũ��Ƽ��") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Add_Critical_Hit = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**�����Ÿ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Add_Shooting_Range = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**�������õ�") == 0)
		{
			p = GetWord(strBuff, p);

			lpDefItem->fSpecial_Magic_Mastery[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_Magic_Mastery[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}








		if(!NextFlag && (lstrcmp(decode, "**�����߰�") == 0 || lstrcmp(decode, "**����߰�") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Lev_Mana = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "**�������߰�") == 0 || lstrcmp(decode, "**������߰�") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Lev_Life = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**���߷�") == 0)
		{

			p = GetWord(strBuff, p);
			lpDefItem->Lev_Attack_Rating[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->Lev_Attack_Rating[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "**���ݷ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Lev_Damage[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpItem->JobItem.Lev_Damage[1] = atoi(strBuff);
			NextFlag = TRUE;
		}






		if(!NextFlag && (lstrcmp(decode, "**�������") == 0 || lstrcmp(decode, "**������") == 0))
		{
			p = GetWord(strBuff, p);

			lpDefItem->fSpecial_Mana_Regen[0] = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpDefItem->fSpecial_Mana_Regen[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "**���������") == 0 || lstrcmp(decode, "**��������") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Per_Life_Regen = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "**���׹̳����") == 0 || lstrcmp(decode, "**�ٷ����") == 0))
		{
			p = GetWord(strBuff, p);
			lpItem->JobItem.Per_Stamina_Regen = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*�߻�����") == 0)
		{
			p = GetWord(strBuff, p);
			lpDefItem->sGenDay[0] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*��������") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			char szNextFile[128];
			GetDirectoryFromFile(szItemFile, szNextFile, sizeof(szNextFile));
			lstrcat(szNextFile, strBuff);
			NextFlag = TRUE;
			fclose(fp);

			fp = fopen(szNextFile, "rb");
			if(fp == NULL) break;
		}

	}

	if(lpItem->EffectBlink[0])
	{
		lpItem->EffectBlink[1] =
			(lpItem->EffectColor[0] + lpItem->EffectColor[1] + lpItem->EffectColor[2] + lpItem->EffectColor[3] + (short)lpItem->DispEffect);
	}

	if(fp) fclose(fp);
	return TRUE;
}


struct szSTATE_CODE
{
	char	*szCodeName;
	DWORD	dwCode;
};

szSTATE_CODE	dwCharSoundCode[] = {
	{	"CYCLOPS"	,	snCHAR_SOUND_CYCLOPS },
	{	"HOBGOBLIN"	,	snCHAR_SOUND_HOBGOBLIN },
	{	"IMP"		,	snCHAR_SOUND_IMP },
	{	"MINIG"		,	snCHAR_SOUND_MINIG },
	{	"PLANT"		,	snCHAR_SOUND_PLANT },
	{	"SKELETON"	,	snCHAR_SOUND_SKELETON },
	{	"ZOMBI"		,	snCHAR_SOUND_ZOMBI },
	{	"OBIT"		,	snCHAR_SOUND_OBIT },

	{	"HOPT"		,	snCHAR_SOUND_HOPT },
	{	"BARGON"	,	snCHAR_SOUND_BARGON },
	{	"LEECH"		,	snCHAR_SOUND_LEECH },
	{	"MUSHROOM"	,	snCHAR_SOUND_MUSHROOM },

	{	"ARMA"		,	snCHAR_SOUND_ARMA },
	{	"ARMADIL"	,	snCHAR_SOUND_ARMA },
	{	"SCORPION"	,	snCHAR_SOUND_SCORPION },

	{	"HEADCUTTER",	snCHAR_SOUND_HEADCUTTER },
	{	"SANDLEM"	,	snCHAR_SOUND_SANDLEM },
	{	"WEB"		,	snCHAR_SOUND_WEB },
	{	"HOPYKING"	,	snCHAR_SOUND_HOPYKING },
	{	"CRIP"		,	snCHAR_SOUND_CRIP },
	{	"BUMA"		,	snCHAR_SOUND_BUMA },
	{	"DECOY"		,	snCHAR_SOUND_DECOY },
	{	"DORAL"		,	snCHAR_SOUND_DORAL },
	{	"FIGON"		,	snCHAR_SOUND_FIGON },
	{	"GOLEM"		,	snCHAR_SOUND_STONEGIANT },
	{	"GREVEN"	,	snCHAR_SOUND_GREVEN },
	{	"ILLUSIONKNIGHT" , snCHAR_SOUND_ILLUSIONKNIGHT },
	{	"SKELETONRANGE" , snCHAR_SOUND_SKELETONRANGE },
	{	"SKELETONMELEE" , snCHAR_SOUND_SKELETONMELEE },
	{	"WOLVERLIN" , snCHAR_SOUND_WOLVERLIN },



	{	"RABIE"			, snCHAR_SOUND_RABIE			},
	{	"MUDY"			, snCHAR_SOUND_MUDY				},
	{	"SEN"			, snCHAR_SOUND_SEN				},
	{	"EGAN"			, snCHAR_SOUND_EGAN				},
	{	"BEEDOG"		, snCHAR_SOUND_BEEDOG			},
	{	"MUTANTPLANT"	, snCHAR_SOUND_MUTANTPLANT		},
	{	"MUTANTRABIE"	, snCHAR_SOUND_MUTANTRABIE		},
	{	"MUTANTTREE"	, snCHAR_SOUND_MUTANTTREE		},
	{	"AVELISK"		, snCHAR_SOUND_AVELISK			},
	{	"NAZ"			, snCHAR_SOUND_NAZ				},
	{	"MUMMY"			, snCHAR_SOUND_MUMMY			},
	{	"HULK"			, snCHAR_SOUND_HULK				},
	{	"HUNGKY"		, snCHAR_SOUND_HUNGKY			},
	{	"SUCCUBUS"		, snCHAR_SOUND_SUCCUBUS			},
	{	"DAWLIN"		, snCHAR_SOUND_DAWLIN			},
	{	"SHADOW"		, snCHAR_SOUND_SHADOW			},
	{	"BERSERKER"		, snCHAR_SOUND_BERSERKER		},
	{	"IRONGUARD"		, snCHAR_SOUND_IRONGUARD		},
	{	"FURY"			, snCHAR_SOUND_FURY				},
	{	"SLIVER"		, snCHAR_SOUND_SLIVER			},

	{	"RATOO"			, snCHAR_SOUND_RATOO			},
	{	"STYGIANLORD"	, snCHAR_SOUND_STYGIANLORD		},
	{	"OMICRON"		, snCHAR_SOUND_OMICRON			},
	{	"D-MACHINE"		, snCHAR_SOUND_DMACHINE			},
	{	"METRON"		, snCHAR_SOUND_METRON			},
	{	"MRGHOST"		, snCHAR_SOUND_MRGHOST			},

	{	"VAMPIRICBAT"	, snCHAR_SOUND_VAMPIRICBAT		},
	{	"MIREKEEPER"	, snCHAR_SOUND_MIREKEEPER		},
	{	"MUFFIN"		, snCHAR_SOUND_MUFFIN			},
	{	"SOLIDSNAIL"	, snCHAR_SOUND_SOLIDSNAIL		},
	{	"BEEVIL"		, snCHAR_SOUND_BEEVIL			},
	{	"NIGHTMARE"		, snCHAR_SOUND_NIGHTMARE		},
	{	"STONEGOLEM"	, snCHAR_SOUND_STONEGOLEM		},
	{	"THORNCRAWLER"	, snCHAR_SOUND_THORNCRAWLER		},
	{	"HEAVYGOBLIN"	, snCHAR_SOUND_HEAVYGOBLIN		},
	{	"EVILPLANT"		, snCHAR_SOUND_EVILPLANT		},
	{	"HAUNTINGPLANT"	, snCHAR_SOUND_HAUNTINGPLANT	},
	{	"DARKKNIGHT"	, snCHAR_SOUND_DARKKNIGHT		},
	{	"GUARDIAN-SAINT", snCHAR_SOUND_GUARDIAN_SAINT	},



	{	"CHAINGOLEM"	, snCHAR_SOUND_CHAINGOLEM		},
	{	"DEADZONE"		, snCHAR_SOUND_DEADZONE			},
	{	"GROTESQUE"		, snCHAR_SOUND_GROTESQUE		},
	{	"HYPERMACHINE"	, snCHAR_SOUND_HYPERMACHINE		},
	{	"IRONFIST"		, snCHAR_SOUND_IRONFIST			},
	{	"MORGON"		, snCHAR_SOUND_MORGON			},
	{	"MOUNTAIN"		, snCHAR_SOUND_MOUNTAIN			},
	{	"RAMPAGE"		, snCHAR_SOUND_RAMPAGE			},
	{	"RUNICGUARDIAN"	, snCHAR_SOUND_RUNICGUARDIAN	},
	{	"SADNESS"		, snCHAR_SOUND_SADNESS			},
	{	"TOWERGOLEM"	, snCHAR_SOUND_TOWERGOLEM		},
	{	"VAMPIRICBEE"	, snCHAR_SOUND_VAMPRICBEE		},
	{	"VAMPIRICMACHINE", snCHAR_SOUND_VAMPRICMACHINE	},
	{	"AVELINARCHER"	, snCHAR_SOUND_AVELIN_ARCHER	},
	{	"AVELINQUEEN"	, snCHAR_SOUND_AVELIN_QUEEN		},
	{	"BABEL"			, snCHAR_SOUND_BABEL			},


	{	"MYSTIC"		, snCHAR_SOUND_MYSTIC			},
	{	"ICEGOBLIN"		, snCHAR_SOUND_ICEGOBLIN		},
	{	"COLDEYE"		, snCHAR_SOUND_COLDEYE			},
	{	"FROZEN"		, snCHAR_SOUND_FROZEN			},
	{	"ICEGOLEM"		, snCHAR_SOUND_ICEGOLEM			},
	{	"FROST"			, snCHAR_SOUND_FROST			},
	{	"CHAOSCARA"		, snCHAR_SOUND_CHAOSCARA		},
	{	"DEATHKNIGHT"	, snCHAR_SOUND_DEATHKNIGHT		},



	{	"GREATE_GREVEN"	, snCHAR_SOUND_GREATE_GREVEN	},
	{	"LIZARDFOLK"	, snCHAR_SOUND_LIZARDFOLK		},
	{	"M_LORD"		, snCHAR_SOUND_M_LORD			},
	{	"SPIDER"		, snCHAR_SOUND_SPIDER			},
	{	"STINGRAY"		, snCHAR_SOUND_STINGRAY			},
	{	"STRIDER"		, snCHAR_SOUND_STRIDER			},
	{	"OMU"			, snCHAR_SOUND_OMU				},


	{	"TURTLECANNON"	, snCHAR_SOUND_TURTLE_CANNON	},
	{	"DEVILBIRD"		, snCHAR_SOUND_DEVIL_BIRD		},
	{	"BLIZZARDGIANT"	, snCHAR_SOUND_BLIZZARD_GIANT	},
	{	"KELVEZU"		, snCHAR_SOUND_KELVEZU			},



	{	"DARKPHALANX"	, snCHAR_SOUND_DARKPHALANX		},
	{	"BLOODYKNIGHT"	, snCHAR_SOUND_BLOODYKNIGHT		},
	{	"CHIMERA"		, snCHAR_SOUND_CHIMERA			},
	{	"FIREWORM"		, snCHAR_SOUND_FIREWORM			},
	{	"HELLHOUND"		, snCHAR_SOUND_HELLHOUND		},
	{	"DARKGUARD"		, snCHAR_SOUND_DARKGUARD		},
	{	"DARKMAGE"		, snCHAR_SOUND_DARKMAGE			},

	{	"MONMOKOVA"		, snCHAR_SOUND_MOKOVA			},
	{	"MONTEMPLEGUARD", snCHAR_SOUND_TEMPLEGUARD		},
	{	"MONSETO"		, snCHAR_SOUND_SETO				},
	{	"MONKINGSPIDER"	, snCHAR_SOUND_KINGSPIDER		},

	{	"D_KN"			, snCHAR_SOUND_REVIVED_KNIGHT	},
	{	"D_MAGI"		, snCHAR_SOUND_REVIVED_MAGICIAN },
	{	"D_ATAL"		, snCHAR_SOUND_REVIVED_ATALANTA },
	{	"D_FI"			, snCHAR_SOUND_REVIVED_FIGTHER	},
	{	"D_AR"			, snCHAR_SOUND_REVIVED_ARCHER	},
	{	"D_MECA"		, snCHAR_SOUND_REVIVED_MECANICIAN },
	{	"D_PA"			, snCHAR_SOUND_REVIVED_PIKEMAN	},
	{	"D_PR"			, snCHAR_SOUND_REVIVED_PRIESTESS},
	{	"DEADHOPT"		, snCHAR_SOUND_DEADHOPT			},
	{	"DEADKINGHOPY"	, snCHAR_SOUND_DEADKINGHOPY		},
	{	"GORGON"		, snCHAR_SOUND_GORGON			},
	{	"HOBOGOLEM"		, snCHAR_SOUND_HOBOGOLEM		},


	{	"NIKEN"			, snCHAR_SOUND_NIKEN			},
	{	"MIMIC"			, snCHAR_SOUND_MIMIC			},
	{	"KINGBAT"		, snCHAR_SOUND_KINGBAT			},
	{	"GOBLINSHAMAN"	, snCHAR_SOUND_GOBLINSHAMAN		},
	{	"HEST"			, snCHAR_SOUND_HEST				},


	{	"RUCA"			, snCHAR_SOUND_RUCA				},
	{	"NAZSENIOR"		, snCHAR_SOUND_NAZSENIOR		},
	{	"IGOLATION"		, snCHAR_SOUND_IGOLATION		},
	{	"KAKOA"			, snCHAR_SOUND_KAKOA			},
	{	"SPRIN"			, snCHAR_SOUND_SPRIN			},
	{	"UNDEADMAPLE"	, snCHAR_SOUND_UNDEADMAPLE		},
	{	"XETAN"			, snCHAR_SOUND_XETAN			},



	{	"BEBECHICK"		, snCHAR_SOUND_BEBECHICK		},
	{	"PAPACHICK"		, snCHAR_SOUND_PAPACHICK		},



	{	"MORIF"			, snCHAR_SOUND_NPC_MORIF		},
	{	"MOLLYWOLF"		, snCHAR_SOUND_NPC_MOLLYWOLF	},
	{	"SKILLMASTER"	, snCHAR_SOUND_NPC_SKILLMASTER	},
	{	"MAGE"			, snCHAR_SOUND_NPC_MAGICMASTER	},
	{	"WORLDCUP"		, snCHAR_SOUND_WORLDCUP			},
	{	"WATERMELON"		, snCHAR_SOUND_WATERMELON			},



	{	"WOLVERIN"			, snCHAR_SOUND_S_WOLVERLIN		},
	{	"METALGOLEM"		, snCHAR_SOUND_S_METALGOLEM		},
	{	"FIREELEMENTAL"		, snCHAR_SOUND_S_F_ELEMENTAL	},



	{	"CASTLEDOOR"		, snCHAR_SOUND_CASTLE_DOOR		},
	{	"T_CRYSTAL_R"		, snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{	"T_CRYSTAL_G"		, snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{	"T_CRYSTAL_B"		, snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{	"T_CRYSTAL_N"		, snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{	"TOWER-B"			, snCHAR_SOUND_CASTLE_TOWER_B	},


	{	"SOLDIER_A"			, snCHAR_SOUND_CASTLE_SOLDER_A	},
	{	"SOLDIER_B"			, snCHAR_SOUND_CASTLE_SOLDER_B	},
	{	"SOLDIER_C"			, snCHAR_SOUND_CASTLE_SOLDER_C	},


	{	"S_AVELIN"				, snCHAR_SOUND_S_AVELIN	},
	{	"S_BAGON"				, snCHAR_SOUND_S_BAGON	},
	{	"S_BEEDOG"				, snCHAR_SOUND_S_BEEDOG	},
	{	"S_BEEVIL"				, snCHAR_SOUND_S_BEEVIL	},
	{	"S_BERSERKER"			, snCHAR_SOUND_S_BERSERKER	},
	{	"S_BUMA"					, snCHAR_SOUND_S_BUMA	},
	{	"S_COKRIS"				, snCHAR_SOUND_S_COKRIS	},
	{	"S_COLDEYE"			, snCHAR_SOUND_S_COLDEYE	},
	{	"S_CRYPT"				, snCHAR_SOUND_S_CRYPT	},
	{	"S_CYCLOPS"			, snCHAR_SOUND_S_CYCLOPS	},
	{	"S_DEADZONE"			, snCHAR_SOUND_S_DEADZONE	},
	{	"S_DECOY"				, snCHAR_SOUND_S_DECOY	},
	{	"S_D-Machine"			, snCHAR_SOUND_S_DMACHINE	},
	{	"S_EVILSNAIL"			, snCHAR_SOUND_S_EVILSNAIL	},
	{	"S_GREVEN"				, snCHAR_SOUND_S_GREVEN	},
	{	"S_GROTESQUE"		, snCHAR_SOUND_S_GROTESQUE	},
	{	"S_ICEGOBLIN"			, snCHAR_SOUND_S_ICEGOBLIN	},
	{	"S_ICEGOLEM"			, snCHAR_SOUND_S_ICEGOLEM	},
	{	"S_INCUBUS"				, snCHAR_SOUND_S_INCUBUS	},
	{	"S_KINGHOPY"			, snCHAR_SOUND_S_KINGHOPY	},
	{	"S_LEECH"				, snCHAR_SOUND_S_LEECH	},
	{	"S_LIZARDFOLK"		, snCHAR_SOUND_S_LIZARDFOLK	},
	{	"S_MEPHIT"				, snCHAR_SOUND_S_MEPHIT	},
	{	"S_METRON"				, snCHAR_SOUND_S_METRON	},
	{	"S_MUFFIN"				, snCHAR_SOUND_S_MUFFIN	},
	{	"S_MUMMY"				, snCHAR_SOUND_S_MUMMY	},
	{	"S_NAZ"					, snCHAR_SOUND_S_NAZ	},
	{	"S_OMEGA"				, snCHAR_SOUND_S_OMEGA	},
	{	"S_RAMPAGE"			, snCHAR_SOUND_S_RAMPAGE	},
	{	"S_SADNESS"			, snCHAR_SOUND_S_SADNESS	},
	{	"S_SLAUGHTER"			, snCHAR_SOUND_S_SLAUGHTER	},
	{	"S_SLAYON"				, snCHAR_SOUND_S_SLAYON	},
	{	"S_SLIVER"				, snCHAR_SOUND_S_SLIVER	},
	{	"S_TITAN"					, snCHAR_SOUND_S_TITAN	},
	{	"S_TOWERGOLEM"		, snCHAR_SOUND_S_TOWERGOLEM	},
	{	"S_TYPHOON"			, snCHAR_SOUND_S_TYPHOON	},
	{	"S_VAMPIRICBAT"		, snCHAR_SOUND_S_VAMPIRICBAT	},
	{	"S_WITCH"					, snCHAR_SOUND_S_WITCH	},
	{	"S_ZOMBIE"				, snCHAR_SOUND_S_ZOMBIE	},
	{	"S_ZOMBIE"				, snCHAR_SOUND_S_ZOMBIE	},

	{ "BOSS_MUNDO"			, snCHAR_SOUND_B_MUNDO },
	{ "B_SHY"					, snCHAR_SOUND_B_SHY },
	{ "B_TULLA"				, snCHAR_SOUND_B_TULLA },
	{ "B_DRAXOS"				, snCHAR_SOUND_B_DRAXOS },
	{ "B_MIDRANDA"			, snCHAR_SOUND_B_MIDRANDA },
	{ "B_GREEDY"				, snCHAR_SOUND_B_GREEDY },
	{ "WLord"				, snCHAR_SOUND_B_WLORD },


	{	"" , 0 }
};




char	*szCharSizeCodeName[] = {
	"����" , "����" , "�ߴ���" , "����" , ""
};



int ConvPercent8(int percent100)
{
	return (percent100 * 256) / 100;
}

int ConvMoveSpeed(float fSpeed)
{
	int sp;

	sp = (int)((fSpeed - 9) * 16) + fONE;

	return sp;
}


int smCharDecode(char *szCharFile, smCHAR_INFO *lpCharInfo, smCHAR_MONSTER_INFO	*lpMonInfo, char *lpDialogMessage, size_t DialogMessageSize)
{

	FILE	*fp;

	char strBuff[256];
	char szFile[128];
	char *p;
	char *pb;
	int NextFlag;
	int cnt;
	int	percent;
	int	DialogFlag;

	DWORD	dwItemCode[32];
	int		ItemCodeCnt;


	strcpy_s(szFile, szCharFile);

	fp = fopen(szFile, "rb");
	if(fp == NULL) return FALSE;




	lpCharInfo->szModelName2[0] = 0;
	lpCharInfo->wPlayClass[1] = 0;
	lpCharInfo->ArrowPosi[0] = 0;
	lpCharInfo->ArrowPosi[1] = 0;

	if(lpMonInfo)
	{
		ZeroMemory(lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
		lpMonInfo->MoveRange = 64 * fONE;
		lpMonInfo->FallItemCount = 0;
		lpMonInfo->FallItemMax = 0;
		lpMonInfo->FallItemPerMax = 0;

		lpMonInfo->DamageStunPers = 100;
		lpMonInfo->UseEventModel = 0;
	}

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)	break;

		p = GetWord(decode, line);

		NextFlag = 0;


		if(lstrcmp(decode, "*�̸�") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			strcpy_s(lpCharInfo->szName, strBuff);
			NextFlag = TRUE;
		}


#ifdef _LANGUAGE_BRAZIL
		if(lstrcmpi(decode, "*J_NAME") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			if(lpMonInfo)
				strcpy_s(lpMonInfo->szName, strBuff);
			else
				strcpy_s(lpCharInfo->szName, strBuff);

			NextFlag = TRUE;
		}
#endif

		if(!NextFlag && lstrcmp(decode, "*�������") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);



			strcpy_s(lpCharInfo->szModelName, strBuff);
			NextFlag = TRUE;
		}



		DialogFlag = 0;

		if(!NextFlag && lpDialogMessage && lstrcmp(decode, "*��ȭ") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			strcpy_s(lpDialogMessage, DialogMessageSize, strBuff);
			NextFlag = TRUE;
			DialogFlag++;
		}


#ifdef _LANGUAGE_BRAZIL
		if(lpDialogMessage && lstrcmpi(decode, "*J_CHAT") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			strcpy_s(lpDialogMessage, DialogMessageSize, strBuff);
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif


		if(DialogFlag && lpMonInfo)
		{
			if(lpMonInfo->NpcMsgCount < NPC_MESSAGE_MAX)
			{

				lpMonInfo->lpNpcMessage[lpMonInfo->NpcMsgCount++] = SetNPCMsg(lpDialogMessage);



			}
		}


		if(!NextFlag && lstrcmp(decode, "*�Ӽ�") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			if(lstrcmp(strBuff, "��") == 0)
				lpCharInfo->State = TRUE;
			else
				lpCharInfo->State = FALSE;

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*ũ��") == 0)
		{
			p = GetWord(strBuff, p);
			cnt = 0;

			lpCharInfo->SizeLevel = -1;

			while(1)
			{
				if(szCharSizeCodeName[cnt][0] == 0) break;
				if(lstrcmp(szCharSizeCodeName[cnt], strBuff) == 0)
				{
					lpCharInfo->SizeLevel = cnt;
				}
				cnt++;
			}
			NextFlag = TRUE;
		}


		if(!NextFlag && (lstrcmp(decode, "*�Ҹ�") == 0 || lstrcmp(decode, "*ȿ����") == 0))
		{
			p = GetWord(strBuff, p);
			cnt = 0;

			while(1)
			{
				if(dwCharSoundCode[cnt].dwCode == 0) break;
				if(lstrcmpi(dwCharSoundCode[cnt].szCodeName, strBuff) == 0)
				{
					lpCharInfo->dwCharSoundCode = dwCharSoundCode[cnt].dwCode;
				}
				cnt++;
			}
			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Level = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*�θ�") == 0)
		{

			lpCharInfo->wPlayClass[0] = MONSTER_CLASS_BOSS;
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*���") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->wPlayClass[0] = atoi(strBuff);
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*��ũ��") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->wPlayClass[1] = (short)(atof(strBuff)*fONE);
			if(lpCharInfo->wPlayClass[1] == fONE) lpCharInfo->wPlayClass[1] = 0;
			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmp(decode, "*�̵���") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Move_Speed = ConvMoveSpeed((float)atof(strBuff));
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*���ݷ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Attack_Damage[0] = atoi(strBuff);
			p = GetWord(strBuff, p);
			lpCharInfo->Attack_Damage[1] = atoi(strBuff);

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*���ݼӵ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Attack_Speed = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			lpCharInfo->Attack_Speed = (int)(atof(strBuff)*fONE);

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*���ݹ���") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Shooting_Range = atoi(strBuff)*fONE;
			NextFlag = TRUE;
		}




		if(!NextFlag && lstrcmp(decode, "*���߷�") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Attack_Rating = atoi(strBuff);

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Defence = atoi(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*�����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Absorption = atoi(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Chance_Block = atoi(strBuff);

			NextFlag = TRUE;
		}


		if(!NextFlag && (lstrcmp(decode, "*�����") == 0 || lstrcmp(decode, "*������") == 0))
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Life[0] = atoi(strBuff);
			lpCharInfo->Life[1] = lpCharInfo->Life[0];

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*��ü") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_BIONIC] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_WATER] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_LIGHTING] = (short)atoi(strBuff);

			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*����") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_ICE] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*�ٶ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_WIND] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*������") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_EARTH] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_FIRE] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && lstrcmp(decode, "*��") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Resistance[sITEMINFO_POISON] = (short)atof(strBuff);
			NextFlag = TRUE;
		}








		if(!NextFlag && lstrcmp(decode, "*�þ�") == 0)
		{
			p = GetWord(strBuff, p);
			lpCharInfo->Sight = atoi(strBuff);
			if(lpMonInfo) lpMonInfo->Real_Sight = lpCharInfo->Sight;

			lpCharInfo->Sight *= lpCharInfo->Sight;
			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmp(decode, "*ȭ�麸��") == 0)
		{
			p = GetWord(strBuff, p);
			if(strBuff[0])
				lpCharInfo->ArrowPosi[0] = atoi(strBuff);

			p = GetWord(strBuff, p);
			if(strBuff[0])
				lpCharInfo->ArrowPosi[1] = atoi(strBuff);

		}

		if(lpMonInfo && !NextFlag)
		{


			if(!NextFlag && lstrcmp(decode, "*�����") == 0)
			{
				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(lpCharInfo->szModelName2 + 1, sizeof(lpCharInfo->szModelName2) - 1, strBuff);
				lpMonInfo->UseEventModel = TRUE;
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*������ݷ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SkillDamage[0] = atoi(strBuff);
				p = GetWord(strBuff, p);
				lpMonInfo->SkillDamage[1] = atoi(strBuff);

				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*������ݰŸ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SkillDistance = atoi(strBuff);

				NextFlag = TRUE;
			}



			if(!NextFlag && lstrcmp(decode, "*������ݹ���") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SkillRange = atoi(strBuff);

				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*������ݷ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SkillRating = atoi(strBuff);

				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*���ֱ��") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SkillCurse = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�̵�Ÿ��") == 0)
			{
				p = GetWord(strBuff, p);

				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�̵�����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->MoveRange = (int)(atof(strBuff)*fONE);
				NextFlag = TRUE;
			}



			if(!NextFlag && lstrcmp(decode, "*Ȱ���ð�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->ActiveHour = 0;
				if(lstrcmpi(strBuff, "��") == 0)
					lpMonInfo->ActiveHour = 1;
				if(lstrcmpi(strBuff, "��") == 0)
					lpMonInfo->ActiveHour = -1;
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->GenerateGroup[0] = atoi(strBuff);
				p = GetWord(strBuff, p);
				lpMonInfo->GenerateGroup[1] = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->IQ = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�����ڵ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->ClassCode = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && (lstrcmp(decode, "*������") == 0 || lstrcmp(decode, "*���Ϸ�") == 0))
			{
				p = GetWord(strBuff, p);
				lpMonInfo->DamageStunPers = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*ǰ��") == 0)
			{
				lpMonInfo->Nature = smCHAR_MONSTER_NATURAL;


				p = GetWord(strBuff, p);
				if(lstrcmpi(strBuff, "good") == 0)
				{
					lpMonInfo->Nature = smCHAR_MONSTER_GOOD;

				}
				if(lstrcmpi(strBuff, "evil") == 0)
				{
					lpMonInfo->Nature = smCHAR_MONSTER_EVIL;

				}
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�̺�Ʈ�ڵ�") == 0)
			{
				p = GetWord(strBuff, p);

				lpMonInfo->EventCode = atoi(strBuff);
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�̺�Ʈ����") == 0)
			{
				p = GetWord(strBuff, p);

				lpMonInfo->EventInfo = atoi(strBuff);
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�̺�Ʈ������") == 0)
			{
				p = GetWord(strBuff, p);


				for(cnt = 0; cnt < MAX_ITEM; cnt++)
				{
					if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
					{
						lpMonInfo->dwEvnetItem = sItem[cnt].CODE;
						break;
					}
				}
				NextFlag = TRUE;
			}



			if(!NextFlag && lstrcmp(decode, "*Ư�����ݷ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->SpAttackPercetage = ConvPercent8(atoi(strBuff));
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*�𵥵�") == 0)
			{
				p = GetWord(strBuff, p);
				if(lstrcmp(strBuff, "��") == 0 || lstrcmp(strBuff, "����") == 0)
				{
					lpMonInfo->Undead = TRUE;
					lpCharInfo->Brood = smCHAR_MONSTER_UNDEAD;
				}
				else
				{
					lpMonInfo->Undead = FALSE;
					lpCharInfo->Brood = smCHAR_MONSTER_NORMAL;
				}

				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*��������") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
				{

					lpCharInfo->Brood = smCHAR_MONSTER_NORMAL;

					if(lstrcmp(strBuff, "�𵥵�") == 0)
					{
						lpCharInfo->Brood = smCHAR_MONSTER_UNDEAD;
					}
					else if(lstrcmp(strBuff, "����Ʈ") == 0)
					{
						lpCharInfo->Brood = smCHAR_MONSTER_MUTANT;
					}
					else if(lstrcmp(strBuff, "���") == 0)
					{
						lpCharInfo->Brood = smCHAR_MONSTER_DEMON;
					}
					else if(lstrcmp(strBuff, "��ī��") == 0)
					{
						lpCharInfo->Brood = smCHAR_MONSTER_MECHANIC;
					}
				}
			}


			//Exp Mob
			if(!NextFlag && lstrcmp(decode, "*����ġ") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->GetExp = atoi(strBuff);
				lpCharInfo->Exp = lpMonInfo->GetExp;
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*���ຸ����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->PotionCount = atoi(strBuff);
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*���ຸ����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->PotionPercent = atoi(strBuff);
				NextFlag = TRUE;
			}




			if(!NextFlag && lstrcmp(decode, "*�����۸��") == 0)
			{
				lpMonInfo->AllSeeItem = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*������ī����") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->FallItemMax = atoi(strBuff);
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*�߰�������") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->FallItems_Plus[lpMonInfo->FallItemPlusCount].Percentage = atoi(strBuff);

				p = GetWord(strBuff, p);
				if(strBuff[0] && lpMonInfo->FallItemPlusCount < FALLITEM2_MAX)
				{
					for(cnt = 0; cnt < MAX_ITEM; cnt++)
					{
						if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
						{
							lpMonInfo->FallItems_Plus[lpMonInfo->FallItemPlusCount].dwItemCode = sItem[cnt].CODE;
							lpMonInfo->FallItemPlusCount++;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*������") == 0)
			{
				p = GetWord(strBuff, p);
				percent = atoi(strBuff);

				lpMonInfo->FallItemPerMax += percent;

				p = GetWord(strBuff, p);
				if(lstrcmp(strBuff, "����") == 0)
				{

					if(rsServerConfig.TestSeverMode)
					{
						lpMonInfo->FallItemPerMax -= percent;
						percent /= 2;
						lpMonInfo->FallItemPerMax += percent;
					}


					lpMonInfo->FallItems[lpMonInfo->FallItemCount].dwItemCode = 0;
					lpMonInfo->FallItems[lpMonInfo->FallItemCount].Percentage = percent;
					lpMonInfo->FallItemCount++;
				}
				else
				{
					if(lstrcmp(strBuff, "��") == 0)
					{

						lpMonInfo->FallItems[lpMonInfo->FallItemCount].dwItemCode = sinGG1 | sin01;
						p = GetWord(strBuff, p);
						lpMonInfo->FallItems[lpMonInfo->FallItemCount].sPrice[0] = atoi(strBuff);
						p = GetWord(strBuff, p);
						lpMonInfo->FallItems[lpMonInfo->FallItemCount].sPrice[1] = atoi(strBuff);
						lpMonInfo->FallItems[lpMonInfo->FallItemCount].Percentage = percent;
						lpMonInfo->FallItemCount++;
					}
					else
					{

						ItemCodeCnt = 0;

						while(1)
						{
							if(strBuff[0])
							{

								for(cnt = 0; cnt < MAX_ITEM; cnt++)
								{
									if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
									{
										dwItemCode[ItemCodeCnt++] = sItem[cnt].CODE;
										break;
									}
								}
							}
							else
							{
								break;
							}

							strBuff[0] = 0;
							if(p[0] == 0) break;
							p = GetWord(strBuff, p);
						}

						if(ItemCodeCnt > 0)
						{

							percent = percent / ItemCodeCnt;
							for(cnt = 0; cnt < ItemCodeCnt; cnt++)
							{
								lpMonInfo->FallItems[lpMonInfo->FallItemCount].dwItemCode = dwItemCode[cnt];
								lpMonInfo->FallItems[lpMonInfo->FallItemCount].Percentage = percent;
								lpMonInfo->FallItemCount++;
							}
						}
					}
				}
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�����Ǹ�") == 0)
			{
				while(1)
				{
					pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
					if(strBuff[0] == 0) break;
					if(lpMonInfo->SellAttackItemCount >= 32) break;
					for(cnt = 0; cnt < MAX_ITEM; cnt++)
					{
						if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
						{
							lpMonInfo->SellAttackItem[lpMonInfo->SellAttackItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*���Ǹ�") == 0)
			{
				while(1)
				{
					pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
					if(strBuff[0] == 0) break;
					if(lpMonInfo->SellDefenceItemCount >= 32) break;
					for(cnt = 0; cnt < MAX_ITEM; cnt++)
					{
						if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
						{
							lpMonInfo->SellDefenceItem[lpMonInfo->SellDefenceItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*��ȭ�Ǹ�") == 0)
			{
				while(1)
				{
					pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
					if(strBuff[0] == 0) break;
					if(lpMonInfo->SellEtcItemCount >= 32) break;
					for(cnt = 0; cnt < MAX_ITEM; cnt++)
					{
						if(lstrcmpi(strBuff, sItem[cnt].LastCategory) == 0)
						{
							lpMonInfo->SellEtcItem[lpMonInfo->SellEtcItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*��ų����") == 0)
			{
				lpMonInfo->SkillMaster = TRUE;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*������ȯ") == 0)
			{
				lpMonInfo->SkillChangeJob = TRUE;

				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->SkillChangeJob = atoi(strBuff);

				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*�̺�Ʈ��ǥ��") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->EventNPC = atoi(strBuff);
				else
					lpMonInfo->EventNPC = 1;

				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�����ۺ���") == 0)
			{
				lpMonInfo->WareHouseMaster = TRUE;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*����������") == 0)
			{
				lpMonInfo->ItemMix = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*����������") == 0)
			{
				lpMonInfo->Smelting = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*����������") == 0)
			{
				lpMonInfo->Manufacture = TRUE;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�����ۿ���") == 0)
			{
				lpMonInfo->ItemMix = 200;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�����ۿ���¡") == 0)
			{
				lpMonInfo->ItemAging = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*�ͽ�ó����") == 0)
			{
				lpMonInfo->MixtureReset = TRUE;
				NextFlag = TRUE;
			}

			if (!NextFlag && lstrcmp(decode, "*Shop") == 0)
			{
				lpMonInfo->ItemShop = TRUE;
				NextFlag = TRUE;
			}

			if (!NextFlag && lstrcmp(decode, "*BATTLE_EVENT") == 0)
			{
				lpMonInfo->BattleEvent = TRUE;
				NextFlag = TRUE;
			}

			if (!NextFlag && lstrcmp(decode, "*RestaureItem") == 0)
			{
				lpMonInfo->RestaureItem = TRUE;
				NextFlag = TRUE;
			}

			if (!NextFlag && lstrcmp(decode, "*BattleArena") == 0)
			{
				lpMonInfo->BattleArena = TRUE;
				NextFlag = TRUE;
			}
			
			if (!NextFlag && lstrcmp(decode, "*QuestDiary") == 0)
			{
				lpMonInfo->QuestDiary = TRUE;
				NextFlag = TRUE;
			}

			if (!NextFlag && lstrcmp(decode, "*Ranking") == 0)
			{
				lpMonInfo->Ranking = TRUE;
				NextFlag = TRUE;
			}


			if(!NextFlag && lstrcmp(decode, "*�����") == 0)
			{
				lpMonInfo->CollectMoney = TRUE;
				NextFlag = TRUE;
			}
#ifdef _LANGUAGE_VEITNAM
			if(!NextFlag && lstrcmp(decode, "*��������") == 0)
			{
				lpMonInfo->WowEvent = TRUE;
				NextFlag = TRUE;
			}
#endif
			if(!NextFlag && lstrcmp(decode, "*��ǰ��÷") == 0)
			{
				lpMonInfo->EventGift = TRUE;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*Ŭ�����") == 0)
			{
				lpMonInfo->ClanNPC = TRUE;
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*��ǰ���") == 0)
			{
				lpMonInfo->GiftExpress = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*������Ʈ") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->WingQuestNpc = atoi(strBuff);
				else
					lpMonInfo->WingQuestNpc = 1;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*����Ʈ�̺�Ʈ") == 0)
			{

				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->WingQuestNpc = atoi(strBuff);
				else
					lpMonInfo->WingQuestNpc = 2;

				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*������Ʈ����") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->StarPointNpc = atoi(strBuff);
				else
					lpMonInfo->StarPointNpc = 20;

				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*�����") == 0)
			{
				lpMonInfo->GiveMoneyNpc = TRUE;
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*�ڷ���Ʈ") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->TelePortNpc = atoi(strBuff);
				else
					lpMonInfo->TelePortNpc = 1;

				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*����ĳ��") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->BlessCastleNPC = atoi(strBuff);
				else
					lpMonInfo->BlessCastleNPC = 1;

				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*��������") == 0)
			{
				p = GetWord(strBuff, p);
				if(strBuff[0])
					lpMonInfo->PollingNpc = atoi(strBuff);
				else
					lpMonInfo->PollingNpc = 1;

				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*����������") == 0)
			{
				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				if(strBuff[0])
				{
					lpMonInfo->szMediaPlayNPC_Title = SetNPCMsg(strBuff);
				}
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*��������") == 0)
			{
				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				if(strBuff[0])
				{
					lpMonInfo->szMediaPlayNPC_Path = SetNPCMsg(strBuff);
				}
				NextFlag = TRUE;
			}

			if(!NextFlag && lstrcmp(decode, "*��������") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->OpenCount[0] = atoi(strBuff);
				p = GetWord(strBuff, p);
				lpMonInfo->OpenCount[1] = atoi(strBuff);
				NextFlag = TRUE;
			}
			if(!NextFlag && lstrcmp(decode, "*����Ʈ�ڵ�") == 0)
			{
				p = GetWord(strBuff, p);
				lpMonInfo->QuestCode = atoi(strBuff);
				p = GetWord(strBuff, p);
				lpMonInfo->QuestParam = atoi(strBuff);
				NextFlag = TRUE;
			}
		}


		if(!NextFlag && lstrcmp(decode, "*��������") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);

			char szNextFile[128];
			GetDirectoryFromFile(szFile, szNextFile, sizeof(szNextFile));
			lstrcat(szNextFile, strBuff);
			NextFlag = TRUE;
			fclose(fp);

			fp = fopen(szNextFile, "rb");
			if(fp == NULL) break;
		}

	}


	if(lpMonInfo)
		lpCharInfo->lpMonInfo = lpMonInfo;
	else
		lpCharInfo->lpMonInfo = 0;


	if(fp) fclose(fp);

	return TRUE;
}


int DecodeOpenMonster(char *szCharFile, rsSTG_MONSTER_LIST *lpStgMonList, smCHAR_INFO *lpCharInfoList, int ListCnt)
{

	FILE	*fp;
	char strBuff[64];
	char *p;
	char *pb;
	int NextFlag;
	int cnt, MonCnt, PercentCnt;
	sBOSS_MONSTER *lpBossMonster;

	ZeroMemory(lpStgMonList, sizeof(rsSTG_MONSTER) * rsSTG_MONSTER_MAX);


	lpStgMonList->OpenInterval = 0x7F;
	lpStgMonList->OpenLimit = 3;

	fp = fopen(szCharFile, "rb");
	if(fp == NULL) return FALSE;

	MonCnt = 0;
	PercentCnt = 0;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)	break;

		p = GetWord(decode, line);

		NextFlag = 0;


		if(lstrcmp(decode, "*�⿬��") == 0 || lstrcmpi(decode, "*ACTOR") == 0)
		{
			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			strcpy_s(lpStgMonList->rsMonster[MonCnt].szMonsterName, strBuff);
			for(cnt = 0; cnt < ListCnt; cnt++)
			{
				if(lstrcmp(strBuff, lpCharInfoList[cnt].szName) == 0)
				{
					lpStgMonList->rsMonster[MonCnt].lpCharInfo = &lpCharInfoList[cnt];

					p = GetWord(strBuff, p);
					cnt = atoi(strBuff);
					lpStgMonList->rsMonster[MonCnt].NumOpenStart = PercentCnt;
					lpStgMonList->rsMonster[MonCnt].OpenPercentage = cnt;
					PercentCnt += cnt;
					MonCnt++;
					break;
				}
			}

			NextFlag = TRUE;
		}

		if(lstrcmp(decode, "*�⿬�ڵθ�") == 0 || lstrcmpi(decode, "*BOSS_ACTOR") == 0)
		{

			lpBossMonster = &lpStgMonList->sBossMonsters[lpStgMonList->BossMonsterCount];

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			for(cnt = 0; cnt < ListCnt; cnt++)
			{
				if(lstrcmp(strBuff, lpCharInfoList[cnt].szName) == 0)
				{
					lpBossMonster->MasterMonster = &lpCharInfoList[cnt];
					break;
				}
			}

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			for(cnt = 0; cnt < ListCnt; cnt++)
			{
				if(lstrcmp(strBuff, lpCharInfoList[cnt].szName) == 0)
				{
					lpBossMonster->SlaveMonster = &lpCharInfoList[cnt];
					break;
				}
			}

			p = GetWord(strBuff, p);
			lpBossMonster->SlaveCount = atoi(strBuff);


			for(cnt = 0; cnt < 32; cnt++)
			{
				p = GetWord(strBuff, p);
				if(!strBuff[0]) break;
				lpBossMonster->bOpenTime[lpBossMonster->OpenTimeCount++] = atoi(strBuff);
			}

			lpStgMonList->BossMonsterCount++;
			NextFlag = TRUE;
		}


		if(!NextFlag && (lstrcmp(decode, "*�ִ뵿��������") == 0 || lstrcmp(decode, "*MAX_ACTOR_POS") == 0))
		{
			p = GetWord(strBuff, p);
			lpStgMonList->LimitMax = atoi(strBuff);
			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*��������") == 0 || lstrcmp(decode, "*DELAY") == 0))
		{
			p = GetWord(strBuff, p);
			lpStgMonList->OpenInterval = (1 << atoi(strBuff));
			if(lpStgMonList->OpenInterval > 1) lpStgMonList->OpenInterval--;

			p = GetWord(strBuff, p);
			if(strBuff[0])
				lpStgMonList->dwIntervalTime = atoi(strBuff) * 1000;

			NextFlag = TRUE;
		}

		if(!NextFlag && (lstrcmp(decode, "*������") == 0 || lstrcmp(decode, "*MAX_ACTOR") == 0))
		{
			p = GetWord(strBuff, p);
			lpStgMonList->OpenLimit = atoi(strBuff);
			NextFlag = TRUE;
		}


	}
	lpStgMonList->Counter = MonCnt;
	lpStgMonList->PecetageCount = PercentCnt;


	fclose(fp);

	return TRUE;
}



int GetRandomPos(int Min, int Max)
{
	int smaller = 0;
	int bigger = 0;

	if(Min <= Max)
	{
		smaller = Min;
		bigger = Max;
	}
	else
	{
		smaller = Max;
		bigger = Min;
	}

	int sb = (Max + 1) - Min;

	if(sb == 0)
		return Max;
	else
	{
		int rnd = rand() % sb;
		return Min + rnd;
	}
}


float GetRandomFloatPos(float Min, float Max)
{
	float smaller = 0.0f;
	float bigger = 0.0f;

	if(Min <= Max)
	{
		smaller = Min;
		bigger = Max;
	}
	else
	{
		smaller = Max;
		bigger = Min;
	}


	int sb = (int)((bigger - smaller) * 100.0f);

	if(sb == 0)
		return Max;
	else
	{
		int rnd = rand() % (sb + 1);
		return Min + ((float)((float)rnd / 100.0f));
	}
}


float GetRandomFloatPos2(float Min, float Max)
{
	float smaller = 0.0f;
	float bigger = 0.0f;

	if(Min <= Max)
	{
		smaller = Min;
		bigger = Max;
	}
	else
	{
		smaller = Max;
		bigger = Min;
	}

	int sb = (int)((bigger - smaller) * 10.0f);

	if(sb == 0)
		return Max;
	else
	{
		int rnd = rand() % (sb + 1);

		return Min + ((float)((float)rnd / 10.0f));
	}
}


int GetMiddlePos(int Min, int Max)
{
	int sb;

	sb = (Max - Min) / 2;

	return Min + sb;
}



static int	Random_NormalMode = 0;


int GetRandomPos_Normal(int inMin, int inMax)
{
	int sb, sc;
	int rnd;
	int	Min, Max;

	if(!Random_NormalMode)
		return GetRandomPos(inMin, inMax);

	sc = inMax - inMin;
	sb = sc / 4;

	if(sb == 0 && sc >= 2) sb = 1;

	Min = inMin + sb;
	Max = inMax - sb;

	sb = (Max + 1) - Min;

	if(sb == 0) return Max;

	rnd = rand() % sb;
	return Min + rnd;
}

struct sSPECIAL_REVISION
{
	DWORD	dwJobCode;
	short	sLevel[2];
	short	sStrength[2];
	short	sSpirit[2];
	short	sTalent[2];
	short	sDexterity[2];
	short	sHealth[2];
};

#define	sSPECIAL_REVISION_MAX		10


sSPECIAL_REVISION	sSpecialRevision[sSPECIAL_REVISION_MAX] = {

	{ JOB_CODE_MECHANICIAN,		0,0,	5,15,		-20,-10,	0,0,		-25,-15,	0,0		},
	{ JOB_CODE_FIGHTER,			0,0,	10,15,		-20,-15,	0,0,		-20,-15,	0,0		},
	{ JOB_CODE_PIKEMAN,			0,0,	10,15,		-20,-15,	0,0,		-25,-15,	0,0		},
	{ JOB_CODE_ARCHER,			0,0,	-25,-15,	-20,-10,	0,0,		15,25,		0,0		},
	{ JOB_CODE_KNIGHT,			0,0,	5,15,		-15,-10,	5,10,		-25,-15,	0,0		},
	{ JOB_CODE_ATALANTA,		0,0,	-20,-15,	-20,-10,	0,0,		15,25,		0,0		},
	{ JOB_CODE_PRIEST,			0,0,	-25,-20,	15,20,		-15,-10,	-20,-15,	0,0		},
	{ JOB_CODE_MAGICIAN,		0,0,	-25,-20,	15,25,		-15,-10,	-20,-15,	0,0		},
	{ JOB_CODE_ASSASSIN,		0,0,	-25,-15,	-20,-10,	0,0,		15,25,		0,0		},
	{ JOB_CODE_SHAMAN,			0,0,	-25,-20,	15,25,		-15,-10,	-20,-15,	0,0		},
};


int CreateDefItem(sITEMINFO *lpItem,		sDEF_ITEMINFO *lpDefItem, int SpJobCode, int ItemNormam)
{
	int is, ie;
	int cnt;
	JOB_DATA_CODE	*lpJobDataCode = 0;

	Random_NormalMode = ItemNormam;




	memcpy(lpItem, &lpDefItem->Item, sizeof(sITEMINFO));


	if(lpDefItem->sDurability[0])
	{

		if(lpDefItem->sDurability[1])
			lpItem->Durability[1] = GetRandomPos_Normal(lpDefItem->sDurability[0], lpDefItem->sDurability[1]);
		else
			lpItem->Durability[1] = lpDefItem->sDurability[0];

		ie = lpItem->Durability[1];
		is = ie / 2;
		lpItem->Durability[0] = GetRandomPos_Normal(is, ie);
	}


	for(cnt = 0; cnt < 8; cnt++)
	{
		if(lpDefItem->sResistance[cnt][1])
		{
			lpItem->Resistance[cnt] =
				GetRandomPos_Normal(lpDefItem->sResistance[cnt][0], lpDefItem->sResistance[cnt][1]);
		}
		else
			lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
	}


	if(lpDefItem->sDamage[1] || lpDefItem->sDamage[3])
	{
		lpItem->Damage[0] = GetRandomPos_Normal(lpDefItem->sDamage[0], lpDefItem->sDamage[1]);
		lpItem->Damage[1] = GetRandomPos_Normal(lpDefItem->sDamage[2], lpDefItem->sDamage[3]);
	}


	if(lpDefItem->sAttack_Rating[1])
		lpItem->Attack_Rating = GetRandomPos_Normal(lpDefItem->sAttack_Rating[0], lpDefItem->sAttack_Rating[1]);
	else
		lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];


	if(lpDefItem->fAbsorb[1] != 0)
		lpItem->fAbsorb = GetRandomFloatPos2(lpDefItem->fAbsorb[0], lpDefItem->fAbsorb[1]);
	else
		lpItem->fAbsorb = lpDefItem->fAbsorb[0];


	if(lpDefItem->sDefence[1])
		lpItem->Defence = GetRandomPos_Normal(lpDefItem->sDefence[0], lpDefItem->sDefence[1]);
	else
		lpItem->Defence = lpDefItem->sDefence[0];


	if(lpDefItem->fBlock_Rating[1] != 0)
		lpItem->fBlock_Rating = GetRandomFloatPos(lpDefItem->fBlock_Rating[0], lpDefItem->fBlock_Rating[1]);
	else
		lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];



	if(lpDefItem->fSpeed[1] != 0)
		lpItem->fSpeed = GetRandomFloatPos2(lpDefItem->fSpeed[0], lpDefItem->fSpeed[1]);
	else
		lpItem->fSpeed = lpDefItem->fSpeed[0];



	if(lpDefItem->fMana_Regen[1] != 0)
		lpItem->fMana_Regen = GetRandomFloatPos2(lpDefItem->fMana_Regen[0], lpDefItem->fMana_Regen[1]);
	else
		lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];


	if(lpDefItem->fLife_Regen[1] != 0)
		lpItem->fLife_Regen = GetRandomFloatPos2(lpDefItem->fLife_Regen[0], lpDefItem->fLife_Regen[1]);
	else
		lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];


	if(lpDefItem->fStamina_Regen[1] != 0)
		lpItem->fStamina_Regen = GetRandomFloatPos2(lpDefItem->fStamina_Regen[0], lpDefItem->fStamina_Regen[1]);
	else
		lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];



	if(lpDefItem->Increase_Life[1])
		lpItem->fIncrease_Life = (float)GetRandomPos_Normal(lpDefItem->Increase_Life[0], lpDefItem->Increase_Life[1]);
	else
		lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];


	if(lpDefItem->Increase_Mana[1])
		lpItem->fIncrease_Mana = (float)GetRandomPos_Normal(lpDefItem->Increase_Mana[0], lpDefItem->Increase_Mana[1]);
	else
		lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];


	if(lpDefItem->Increase_Stamina[1])
		lpItem->fIncrease_Stamina = (float)GetRandomPos_Normal(lpDefItem->Increase_Stamina[0], lpDefItem->Increase_Stamina[1]);
	else
		lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];


	lpItem->ItemLocked = 0;

	DWORD	dwSpecialJob;
	int		RndPos;
	int		Revision;
	int		tempJobCode = 0;


	if(SpJobCode >= 100)
	{
		tempJobCode = SpJobCode - 100;
		SpJobCode = 0;
	}

	if(SpJobCode > 0)
	{
		lpJobDataCode = GetJobDataCode(SpJobCode, 0);

		if(lpJobDataCode)
		{
			dwSpecialJob = lpJobDataCode->JobBitCode;

			for(cnt = 0; cnt < lpDefItem->JobBitCodeRandomCount; cnt++)
			{
				if(lpDefItem->dwJobBitCode_Random[cnt] == dwSpecialJob) break;
			}
			if(cnt >= lpDefItem->JobBitCodeRandomCount)
			{
				if(dwSpecialJob != lpItem->JobCodeMask) SpJobCode = 0;
			}
		}
	}


	if(lpItem->JobCodeMask || lpDefItem->JobBitCodeRandomCount || SpJobCode)
	{



		cnt = rand() % 10;


		if(NotItemSpecial)
		{
			cnt = 100;
			NotItemSpecial = 0;
		}

		if(cnt <= 3 || SpJobCode)
		{


			cnt = rand() % 10;

			dwSpecialJob = lpItem->JobCodeMask;

			if(cnt < 3 && lpDefItem->JobBitCodeRandomCount)
			{
				lpItem->JobCodeMask = 0;
			}

			if(!lpItem->JobCodeMask && lpDefItem->JobBitCodeRandomCount)
			{
				if(tempJobCode > 0)
				{
					lpJobDataCode = GetJobDataCode(tempJobCode, 0);
					if(lpJobDataCode)
					{
						cnt = rand() % lpDefItem->JobBitCodeRandomCount;
						while(lpDefItem->dwJobBitCode_Random[cnt] == lpJobDataCode->JobBitCode)
						{
							cnt = rand() % lpDefItem->JobBitCodeRandomCount;
							if(lpDefItem->dwJobBitCode_Random[cnt] != lpJobDataCode->JobBitCode)
							{
								dwSpecialJob = lpDefItem->dwJobBitCode_Random[cnt];
								lpItem->JobCodeMask = dwSpecialJob;
								break;
							}
						}
					}
				}
				else
				{
					cnt = rand() % lpDefItem->JobBitCodeRandomCount;
					dwSpecialJob = lpDefItem->dwJobBitCode_Random[cnt];
					lpItem->JobCodeMask = dwSpecialJob;
				}
			}

			if(SpJobCode > 0)
			{

				lpJobDataCode = GetJobDataCode(SpJobCode, 0);
				if(lpJobDataCode)
				{
					dwSpecialJob = lpJobDataCode->JobBitCode;
					lpItem->JobCodeMask = dwSpecialJob;
				}
			}


			if(lpItem->JobCodeMask) lpItem->Price += (lpItem->Price * 2) / 10;




			for(cnt = 0; cnt < sSPECIAL_REVISION_MAX; cnt++)
			{
				if(sSpecialRevision[cnt].dwJobCode == dwSpecialJob)
				{

					if(lpItem->Level && sSpecialRevision[cnt].sLevel[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sLevel[0], sSpecialRevision[cnt].sLevel[1]);
						Revision = (lpItem->Level*RndPos) / 100;
						lpItem->Level += Revision;
					}

					if(lpItem->Strength && sSpecialRevision[cnt].sStrength[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sStrength[0], sSpecialRevision[cnt].sStrength[1]);
						Revision = (lpItem->Strength*RndPos) / 100;
						lpItem->Strength += Revision;
					}

					if(lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sSpirit[0], sSpecialRevision[cnt].sSpirit[1]);
						Revision = (lpItem->Spirit*RndPos) / 100;
						lpItem->Spirit += Revision;
					}

					if(lpItem->Talent && sSpecialRevision[cnt].sTalent[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sTalent[0], sSpecialRevision[cnt].sTalent[1]);
						Revision = (lpItem->Talent*RndPos) / 100;
						lpItem->Talent += Revision;
					}

					if(lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sDexterity[0], sSpecialRevision[cnt].sDexterity[1]);
						Revision = (lpItem->Dexterity*RndPos) / 100;
						lpItem->Dexterity += Revision;
					}

					if(lpItem->Health && sSpecialRevision[cnt].sHealth[0])
					{
						RndPos = GetRandomPos_Normal(sSpecialRevision[cnt].sHealth[0], sSpecialRevision[cnt].sHealth[1]);
						Revision = (lpItem->Health*RndPos) / 100;
						lpItem->Health += Revision;
					}
				}
			}


			if(lpDefItem->fSpecial_Absorb[1] != 0)
			{
				lpItem->JobItem.Add_fAbsorb = GetRandomFloatPos(lpDefItem->fSpecial_Absorb[0], lpDefItem->fSpecial_Absorb[1]);
			}
			else
			{
				lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];
			}


			if(lpDefItem->sSpecial_Defence[1])
			{
				lpItem->JobItem.Add_Defence = GetRandomPos_Normal(lpDefItem->sSpecial_Defence[0], lpDefItem->sSpecial_Defence[1]);
			}
			else
			{
				lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];
			}


			if(lpDefItem->fSpecial_fSpeed[1] != 0)
			{
				lpItem->JobItem.Add_fSpeed = GetRandomFloatPos(lpDefItem->fSpecial_fSpeed[0], lpDefItem->fSpecial_fSpeed[1]);
			}
			else
			{
				lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];
			}


			if(lpDefItem->fSpecial_Magic_Mastery[1] != 0)
			{
				lpItem->JobItem.Add_fMagic_Mastery = GetRandomFloatPos(lpDefItem->fSpecial_Magic_Mastery[0], lpDefItem->fSpecial_Magic_Mastery[1]);
			}
			else
			{
				lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];
			}


			if(lpDefItem->fSpecial_Mana_Regen[1] != 0)
			{
				lpItem->JobItem.Per_Mana_Regen = GetRandomFloatPos(lpDefItem->fSpecial_Mana_Regen[0], lpDefItem->fSpecial_Mana_Regen[1]);
			}
			else
			{
				lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];
			}



			if(lpDefItem->Lev_Attack_Rating[1])
			{
				lpItem->JobItem.Lev_Attack_Rating = GetRandomPos_Normal(lpDefItem->Lev_Attack_Rating[0], lpDefItem->Lev_Attack_Rating[1]);
			}
			else
			{
				lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];
			}


		}
		else
		{

			lpItem->JobCodeMask = 0;
		}
	}

	if(!lpItem->JobCodeMask)
	{
		ZeroMemory(&lpItem->JobItem, sizeof(sITEM_SPECIAL));
	}





	ReformItem(lpItem);

	return	TRUE;
}


int CreateItemPerf(sITEMINFO* lpItem, sDEF_ITEMINFO* lpDefItem, int SpJobCode)
{
int cnt;
JOB_DATA_CODE* lpJobDataCode = 0;


memcpy(lpItem, &lpDefItem->Item, sizeof(sITEMINFO));

if (lpDefItem->sDurability[0])
{
	if (lpDefItem->sDurability[1])
	{
		lpItem->Durability[0] = lpDefItem->sDurability[1];
		lpItem->Durability[1] = lpDefItem->sDurability[1];
	}
	else
	{
		lpItem->Durability[0] = lpDefItem->sDurability[0];
		lpItem->Durability[1] = lpDefItem->sDurability[0];
	}
}

for (cnt = 0; cnt < 8; cnt++)
{
	if (lpDefItem->sResistance[cnt][1])
		lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][1];
	else
		lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
}

if (lpDefItem->sDamage[1] || lpDefItem->sDamage[3])
{
	lpItem->Damage[0] = lpDefItem->sDamage[1];
	lpItem->Damage[1] = lpDefItem->sDamage[3];
}

if (lpDefItem->sAttack_Rating[1])
lpItem->Attack_Rating = lpDefItem->sAttack_Rating[1];
else
lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];

if (lpDefItem->fAbsorb[1] != 0)
lpItem->fAbsorb = lpDefItem->fAbsorb[1];
else
lpItem->fAbsorb = lpDefItem->fAbsorb[0];

if (lpDefItem->sDefence[1])
lpItem->Defence = lpDefItem->sDefence[1];
else
lpItem->Defence = lpDefItem->sDefence[0];

if (lpDefItem->fBlock_Rating[1] != 0)
lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[1];
else
lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];

if (lpDefItem->fSpeed[1] != 0)
lpItem->fSpeed = lpDefItem->fSpeed[1];
else
lpItem->fSpeed = lpDefItem->fSpeed[0];


if (lpDefItem->fMana_Regen[1] != 0)
lpItem->fMana_Regen = lpDefItem->fMana_Regen[1];
else
lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];

if (lpDefItem->fLife_Regen[1] != 0)
lpItem->fLife_Regen = lpDefItem->fLife_Regen[1];
else
lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];

if (lpDefItem->fStamina_Regen[1] != 0)
lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[1];
else
lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];


if (lpDefItem->Increase_Life[1])
lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[1];
else
lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];

if (lpDefItem->Increase_Mana[1])
lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[1];
else
lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];

if (lpDefItem->Increase_Stamina[1])
lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[1];
else
lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];

lpItem->ItemLocked = 0;

DWORD	dwSpecialJob;
int		RndPos;
int		Revision;

if (SpJobCode > 0)
{
	lpJobDataCode = GetJobDataCode(SpJobCode, 0);

	if (lpJobDataCode)
	{
		dwSpecialJob = lpJobDataCode->JobBitCode;

		for (cnt = 0; cnt < lpDefItem->JobBitCodeRandomCount; cnt++)
		{
			if (lpDefItem->dwJobBitCode_Random[cnt] == dwSpecialJob) break;
		}
		if (cnt >= lpDefItem->JobBitCodeRandomCount)
		{
			if (dwSpecialJob != lpItem->JobCodeMask) SpJobCode = 0;
		}
	}
}

if (SpJobCode > 0)
{
	lpJobDataCode = GetJobDataCode(SpJobCode, 0);
	if (lpJobDataCode)
	{
		dwSpecialJob = lpJobDataCode->JobBitCode;
		lpItem->JobCodeMask = dwSpecialJob;
	}

	if (lpItem->JobCodeMask) lpItem->Price += (lpItem->Price * 2) / 10;

	for (cnt = 0; cnt < sSPECIAL_REVISION_MAX; cnt++)
	{
		if (sSpecialRevision[cnt].dwJobCode == dwSpecialJob)
		{
			if (lpItem->Level && sSpecialRevision[cnt].sLevel[0])
			{
				RndPos = sSpecialRevision[cnt].sLevel[0];
				Revision = (lpItem->Level * RndPos) / 100;
				lpItem->Level += Revision;
			}

			if (lpItem->Strength && sSpecialRevision[cnt].sStrength[0])
			{
				RndPos = sSpecialRevision[cnt].sStrength[0];
				Revision = (lpItem->Strength * RndPos) / 100;
				lpItem->Strength += Revision;
			}

			if (lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0])
			{
				RndPos = sSpecialRevision[cnt].sSpirit[0];
				Revision = (lpItem->Spirit * RndPos) / 100;
				lpItem->Spirit += Revision;
			}

			if (lpItem->Talent && sSpecialRevision[cnt].sTalent[0])
			{
				RndPos = sSpecialRevision[cnt].sTalent[0];
				Revision = (lpItem->Talent * RndPos) / 100;
				lpItem->Talent += Revision;
			}

			if (lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0])
			{
				RndPos = sSpecialRevision[cnt].sDexterity[0];
				Revision = (lpItem->Dexterity * RndPos) / 100;
				lpItem->Dexterity += Revision;
			}

			if (lpItem->Health && sSpecialRevision[cnt].sHealth[0])
			{
				RndPos = sSpecialRevision[cnt].sHealth[0];
				Revision = (lpItem->Health * RndPos) / 100;
				lpItem->Health += Revision;
			}
		}
	}

	if (lpDefItem->fSpecial_Absorb[1] != 0)
		lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[1];
	else
		lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];

	if (lpDefItem->sSpecial_Defence[1])
		lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[1];
	else
		lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];

	if (lpDefItem->fSpecial_fSpeed[1] != 0)
		lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[1];
	else
		lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];

	if (lpDefItem->fSpecial_Magic_Mastery[1] != 0)
		lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[1];
	else
		lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];

	if (lpDefItem->fSpecial_Mana_Regen[1] != 0)
		lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[1];
	else
		lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];

	/*if (lpDefItem->Lev_Attack_Rating[1])
		lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[1];
	else
		lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];*/

	if (!lpDefItem->Lev_Attack_Rating[0] && lpDefItem->Lev_Attack_Rating[1])
		lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[1];
	else if (lpDefItem->Lev_Attack_Rating[0])
		lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];

	lpItem->SpecialItemFlag[1] = ITEM_KIND_PERFECT;
}
else
{
	lpItem->JobCodeMask = 0;
}

if (!lpItem->JobCodeMask)
{
	ZeroMemory(&lpItem->JobItem, sizeof(sITEM_SPECIAL));
}

ReformItem(lpItem);

return	TRUE;
}

int CreateDefItem(sITEMINFO *lpItem, sDEF_ITEMINFO *lpDefItem, int SpJobCode)
{
	return CreateDefItem(lpItem, lpDefItem, SpJobCode, 0);
}

int CreateDefItemPerf(sITEMINFO *lpItem, sDEF_ITEMINFO *lpDefItem, int SpJobCode)
{
	int cnt;
	JOB_DATA_CODE	*lpJobDataCode = 0;


	memcpy(lpItem, &lpDefItem->Item, sizeof(sITEMINFO));

	if (lpDefItem->sDurability[0])
	{
		if (lpDefItem->sDurability[1])
		{
			lpItem->Durability[0] = lpDefItem->sDurability[1];
			lpItem->Durability[1] = lpDefItem->sDurability[1];
		}
		else
		{
			lpItem->Durability[0] = lpDefItem->sDurability[0];
			lpItem->Durability[1] = lpDefItem->sDurability[0];
		}
	}

	for (cnt = 0; cnt < 8; cnt++)
	{
		if (lpDefItem->sResistance[cnt][1])
			lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][1];
		else
			lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
	}

	if (lpDefItem->sDamage[1] || lpDefItem->sDamage[3])
	{
		lpItem->Damage[0] = lpDefItem->sDamage[1];
		lpItem->Damage[1] = lpDefItem->sDamage[3];
	}

	if (lpDefItem->sAttack_Rating[1])
		lpItem->Attack_Rating = lpDefItem->sAttack_Rating[1];
	else
		lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];

	if (lpDefItem->fAbsorb[1] != 0)
		lpItem->fAbsorb = lpDefItem->fAbsorb[1];
	else
		lpItem->fAbsorb = lpDefItem->fAbsorb[0];

	if (lpDefItem->sDefence[1])
		lpItem->Defence = lpDefItem->sDefence[1];
	else
		lpItem->Defence = lpDefItem->sDefence[0];

	if (lpDefItem->fBlock_Rating[1] != 0)
		lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[1];
	else
		lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];

	if (lpDefItem->fSpeed[1] != 0)
		lpItem->fSpeed = lpDefItem->fSpeed[1];
	else
		lpItem->fSpeed = lpDefItem->fSpeed[0];


	if (lpDefItem->fMana_Regen[1] != 0)
		lpItem->fMana_Regen = lpDefItem->fMana_Regen[1];
	else
		lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];

	if (lpDefItem->fLife_Regen[1] != 0)
		lpItem->fLife_Regen = lpDefItem->fLife_Regen[1];
	else
		lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];

	if (lpDefItem->fStamina_Regen[1] != 0)
		lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[1];
	else
		lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];


	if (lpDefItem->Increase_Life[1])
		lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[1];
	else
		lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];

	if (lpDefItem->Increase_Mana[1])
		lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[1];
	else
		lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];

	if (lpDefItem->Increase_Stamina[1])
		lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[1];
	else
		lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];

	lpItem->ItemLocked = 0;

	DWORD	dwSpecialJob;
	int		RndPos;
	int		Revision;

	if (SpJobCode > 0)
	{
		lpJobDataCode = GetJobDataCode(SpJobCode, 0);

		if (lpJobDataCode)
		{
			dwSpecialJob = lpJobDataCode->JobBitCode;

			for (cnt = 0; cnt < lpDefItem->JobBitCodeRandomCount; cnt++)
			{
				if (lpDefItem->dwJobBitCode_Random[cnt] == dwSpecialJob) break;
			}
			if (cnt >= lpDefItem->JobBitCodeRandomCount)
			{
				if (dwSpecialJob != lpItem->JobCodeMask) SpJobCode = 0;
			}
		}
	}

	if (SpJobCode > 0)
	{
		lpJobDataCode = GetJobDataCode(SpJobCode, 0);
		if (lpJobDataCode)
		{
			dwSpecialJob = lpJobDataCode->JobBitCode;
			lpItem->JobCodeMask = dwSpecialJob;
		}

		if (lpItem->JobCodeMask) lpItem->Price += (lpItem->Price * 2) / 10;

		for (cnt = 0; cnt < sSPECIAL_REVISION_MAX; cnt++)
		{
			if (sSpecialRevision[cnt].dwJobCode == dwSpecialJob)
			{
				if (lpItem->Level && sSpecialRevision[cnt].sLevel[0])
				{
					RndPos = sSpecialRevision[cnt].sLevel[0];
					Revision = (lpItem->Level*RndPos) / 100;
					lpItem->Level += Revision;
				}

				if (lpItem->Strength && sSpecialRevision[cnt].sStrength[0])
				{
					RndPos = sSpecialRevision[cnt].sStrength[0];
					Revision = (lpItem->Strength*RndPos) / 100;
					lpItem->Strength += Revision;
				}

				if (lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0])
				{
					RndPos = sSpecialRevision[cnt].sSpirit[0];
					Revision = (lpItem->Spirit*RndPos) / 100;
					lpItem->Spirit += Revision;
				}

				if (lpItem->Talent && sSpecialRevision[cnt].sTalent[0])
				{
					RndPos = sSpecialRevision[cnt].sTalent[0];
					Revision = (lpItem->Talent*RndPos) / 100;
					lpItem->Talent += Revision;
				}

				if (lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0])
				{
					RndPos = sSpecialRevision[cnt].sDexterity[0];
					Revision = (lpItem->Dexterity*RndPos) / 100;
					lpItem->Dexterity += Revision;
				}

				if (lpItem->Health && sSpecialRevision[cnt].sHealth[0])
				{
					RndPos = sSpecialRevision[cnt].sHealth[0];
					Revision = (lpItem->Health*RndPos) / 100;
					lpItem->Health += Revision;
				}
			}
		}

		if (lpDefItem->fSpecial_Absorb[1] != 0)
			lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[1];
		else
			lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];

		if (lpDefItem->sSpecial_Defence[1])
			lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[1];
		else
			lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];

		if (lpDefItem->fSpecial_fSpeed[1] != 0)
			lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[1];
		else
			lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];

		if (lpDefItem->fSpecial_Magic_Mastery[1] != 0)
			lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[1];
		else
			lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];

		if (lpDefItem->fSpecial_Mana_Regen[1] != 0)
			lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[1];
		else
			lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];

		/*if (lpDefItem->Lev_Attack_Rating[1])
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[1];
		else
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];*/

		if (!lpDefItem->Lev_Attack_Rating[0] && lpDefItem->Lev_Attack_Rating[1])
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[1];
		else if (lpDefItem->Lev_Attack_Rating[0])
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];

		lpItem->SpecialItemFlag[1] = ITEM_KIND_PERFECT;
	}
	else
	{
		lpItem->JobCodeMask = 0;
	}

	if (!lpItem->JobCodeMask)
	{
		ZeroMemory(&lpItem->JobItem, sizeof(sITEM_SPECIAL));
	}

	ReformItem(lpItem);

	return	TRUE;
}

int SetLowerItem(sDEF_ITEMINFO *lpDefItem)
{
	int ie;
	int cnt;

	sITEMINFO *lpItem;
	lpItem = &lpDefItem->Item;


	if(lpDefItem->sDurability[0])
	{
		ie = lpDefItem->sDurability[0];
		lpItem->Durability[0] = ie;
		lpItem->Durability[1] = ie;
	}


	for(cnt = 0; cnt < 8; cnt++)
	{
		lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
	}


	if(lpDefItem->sDamage[1] || lpDefItem->sDamage[3])
	{
		lpItem->Damage[0] = lpDefItem->sDamage[0];
		lpItem->Damage[1] = lpDefItem->sDamage[2];
	}

	lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];
	lpItem->fAbsorb = lpDefItem->fAbsorb[0];
	lpItem->Defence = lpDefItem->sDefence[0];
	lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];
	lpItem->fSpeed = lpDefItem->fSpeed[0];

	lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];
	lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];
	lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];

	lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];
	lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];
	lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];

	lpItem->ItemLocked = 0;

	DWORD	dwSpecialJob;
	int		RndPos;
	int		Revision;


	if(lpItem->JobCodeMask)
	{


		dwSpecialJob = lpItem->JobCodeMask;


		for(cnt = 0; cnt < sSPECIAL_REVISION_MAX; cnt++)
		{
			if(sSpecialRevision[cnt].dwJobCode == dwSpecialJob)
			{

				if(lpItem->Level && sSpecialRevision[cnt].sLevel[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sLevel[0], sSpecialRevision[cnt].sLevel[1]);
					Revision = (lpItem->Level*RndPos) / 100;
					lpItem->Level += Revision;
				}

				if(lpItem->Strength && sSpecialRevision[cnt].sStrength[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sStrength[0], sSpecialRevision[cnt].sStrength[1]);
					Revision = (lpItem->Strength*RndPos) / 100;
					lpItem->Strength += Revision;
				}

				if(lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sSpirit[0], sSpecialRevision[cnt].sSpirit[1]);
					Revision = (lpItem->Spirit*RndPos) / 100;
					lpItem->Spirit += Revision;
				}

				if(lpItem->Talent && sSpecialRevision[cnt].sTalent[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sTalent[0], sSpecialRevision[cnt].sTalent[1]);
					Revision = (lpItem->Talent*RndPos) / 100;
					lpItem->Talent += Revision;
				}

				if(lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sDexterity[0], sSpecialRevision[cnt].sDexterity[1]);
					Revision = (lpItem->Dexterity*RndPos) / 100;
					lpItem->Dexterity += Revision;
				}

				if(lpItem->Health && sSpecialRevision[cnt].sHealth[0])
				{
					RndPos = GetMiddlePos(sSpecialRevision[cnt].sHealth[0], sSpecialRevision[cnt].sHealth[1]);
					Revision = (lpItem->Health*RndPos) / 100;
					lpItem->Health += Revision;
				}
			}
		}


		lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];


		lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];


		lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];


		lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];


		lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];


		if(lpDefItem->Lev_Attack_Rating[1])
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0] + (lpDefItem->Lev_Attack_Rating[1] - lpDefItem->Lev_Attack_Rating[0]) / 2;
		else
			lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];

	}
	else
	{
		ZeroMemory(&lpItem->JobItem, sizeof(sITEM_SPECIAL));
	}


	ReformItem(lpItem);

	return	TRUE;
}


JOB_DATA_CODE *GetJobDataCode(DWORD BaseJob, int JobCnt)
{
	int	JobCount = 0;
	int	JobCount2 = JobCnt & 3;
	int	bJob = BaseJob & 0xFFFF;

	if(!JobCnt)
	{
		JobCount2 = BaseJob >> 24;
	}

	int cnt = 0;
	while(1)
	{
		if(!JobDataBase[cnt].szName[0])
			break;
		if(bJob == JobDataBase[cnt].JobCode)
		{
			if(JobCount2 == JobCount)
				return &JobDataBase[cnt];
			JobCount++;
		}
		cnt++;
	}

	//LOG(LOG_DEBUG, "error.....");
	return NULL;
}


#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_JobCode.h"
#endif



SKILL_DATA_CODE	SkillDataCode[] = {
	{	"xxxxxxxxxxxxx"			,	0								},

	{	"ExtremeShield"			,	SKILL_PLAY_EXTREME_SHIELD		},
	{	"MechanicBomb"			,	SKILL_PLAY_MECHANIC_BOMB		},
	{	"PhysicalAbsorption"	,	SKILL_PLAY_PHYSICAL_ABSORB		},
	{	"PoisonAttribute"		,	0								},

	{	"roundimpact"			,	SKILL_PLAY_GREAT_SMASH			},
	{	"Maximize"				,	SKILL_PLAY_MAXIMIZE				},
	{	"Automation"			,	SKILL_PLAY_AUTOMATION			},
	{	"Spark"					,	SKILL_PLAY_SPARK				},

	{	"MetalArmor"			,	SKILL_PLAY_METAL_ARMOR			},
	{	"GrandSmash"			,	SKILL_PLAY_GRAND_SMASH			},
	{	"SparkShield"			,	SKILL_PLAY_SPARK_SHIELD			},

	{	"IMPULSION"				,	SKILL_PLAY_IMPULSION			},
	{	"COMPULSION"			,	SKILL_PLAY_COMPULSION			},
	{	"MAGNETICSPHERE"		,	SKILL_PLAY_MAGNETIC_SPHERE		},
	{	"METALGOLEM"			,	SKILL_PLAY_METAL_GOLEM			},



	{	"MeleeMastery"			,	0								},
	{	"FireAttribute"			,	0								},
	{	"Raving"				,	SKILL_PLAY_RAVING				},
	{	"Impact"				,	SKILL_PLAY_IMPACT				},

	{	"TripleImpact"			,	SKILL_PLAY_TRIPLE_IMPACT		},
	{	"BrutalSwing"			,	SKILL_PLAY_BRUTAL_SWING			},
	{	"Roar"					,	SKILL_PLAY_ROAR					},
	{	"RageofZecram"			,	SKILL_PLAY_RAGEOF_ZECRAM		},

	{	"Concentration"			,	SKILL_PLAY_CONCENTRATION		},
	{	"AvangingCrash"			,	SKILL_PLAY_AVANGING_CRASH		},
	{	"SwiftAxe"				,	SKILL_PLAY_SWIFT_AXE			},
	{	"BoneSmash"				,	SKILL_PLAY_BONE_SMASH			},

	{	"DESTROYER"				,	SKILL_PLAY_DESTROYER			},
	{	"BERSERKER"				,	SKILL_PLAY_BERSERKER			},
	{	"CYCLONESTRIKE"			,	SKILL_PLAY_CYCLONE_STRIKE		},



	{	"PikeWind"				,	SKILL_PLAY_PIKEWIND				},
	{	"IceAttribute"			,	0								},
	{	"CriticalHit"			,	SKILL_PLAY_CRITICAL_HIT			},
	{	"JumpingCrash"			,	SKILL_PLAY_JUMPING_CRASH		},

	{	"GroundPike"			,	SKILL_PLAY_GROUND_PIKE			},
	{	"Tornado"				,	SKILL_PLAY_TORNADO				},
	{	"WeaponDefenceMastery"	,	0								},
	{	"Expansion"				,	SKILL_PLAY_EXPANSION			},

	{	"VenomSpear"			,	SKILL_PLAY_VENOM_SPEAR			},

	{	"BladeOfBlaze"			,	SKILL_PLAY_BLADE_OF_BLAZE		},
	{	"ChainLance"			,	SKILL_PLAY_CHAIN_LANCE			},

	{	"ASSASSINEYE"			,	SKILL_PLAY_ASSASSIN_EYE			},
	{	"CHARGINGSTRIKE"		,	SKILL_PLAY_CHARGING_STRIKE		},
	{	"VAGUE"					,	SKILL_PLAY_VAGUE				},
	{	"SHADOWMASTER"			,	SKILL_PLAY_SHADOW_MASTER		},




	{	"ScoutHawk"				,	SKILL_PLAY_SCOUT_HAWK			},
	{	"ShootingMastery"		,	0								},
	{	"WindArrow"				,	SKILL_PLAY_WIND_ARROW			},
	{	"PerfectAim"			,	SKILL_PLAY_PERFECT_AIM			},

	{	"DionsEye"				,	0								},
	{	"Falcon"				,	SKILL_PLAY_FALCON				},
	{	"ArrowofRage"			,	SKILL_PLAY_ARROWOF_RAGE			},
	{	"Avalanche"				,	SKILL_PLAY_AVALANCHE			},

	{	"ElementalShot"			,	SKILL_PLAY_ELEMENTAL_SHOT		},
	{	"GoldenFalcon"			,	SKILL_PLAY_GOLDEN_FALCON		},
	{	"BombShot"				,	SKILL_PLAY_BOMB_SHOT			},
	{	"Perforation"			,	SKILL_PLAY_PERFORATION			},

	{	"RECALLWOLVERIN"		,	SKILL_PLAY_RECALL_WOLVERIN		},
	{	"PHOENIXSHOT"			,	SKILL_PLAY_PHOENIX_SHOT			},
	{	"FORCEOFNATURE"			,	SKILL_PLAY_FORCE_OF_NATURE		},





	{	"SwordBlast"			,	SKILL_PLAY_SWORD_BLAST			},
	{	"HolyBody"				,	SKILL_PLAY_HOLY_BODY			},
	{	"PhysicalTraning"		,	0								},
	{	"DoubleCrash"			,	SKILL_PLAY_DOUBLE_CRASH			},

	{	"holyteam"				,	SKILL_PLAY_HOLY_VALOR			},
	{	"Brandish"				,	SKILL_PLAY_BRANDISH				},
	{	"Piercing"				,	SKILL_PLAY_PIERCING				},
	{	"DrasticSpirit"			,	SKILL_PLAY_DRASTIC_SPIRIT		},

	{	"FlameBrandish"			,	SKILL_PLAY_FLAME_BRANDISH		},
	{	"Divineinhalation"		,	SKILL_PLAY_DIVINE_INHALATION	},
	{	"HolyIncantation"		,	SKILL_PLAY_HOLY_INCANTATION		},
	{	"GrandCross"			,	SKILL_PLAY_GRAND_CROSS			},

	{	"DIVINEPIERCING"		,	SKILL_PLAY_DIVINE_PIERCING		},
	{	"DIVINEPIERCING2"		,	SKILL_PLAY_DIVINE_PIERCING2		},
	{	"DIVINEPIERCING3"		,	SKILL_PLAY_DIVINE_PIERCING3		},
	{	"GODLYSHIELD"			,	SKILL_PLAY_GODLY_SHIELD			},
	{	"GODSBLESS"				,	SKILL_PLAY_GODS_BLESS			},
	{	"SWORDOFJUSTICE"		,	SKILL_PLAY_SWORD_OF_JUSTICE		},



	{	"ShieldStrike"			,	SKILL_PLAY_SHIELD_STRIKE		},
	{	"Farina"				,	SKILL_PLAY_FARINA				},
	{	"ThrowingMastery"		,	0								},
	{	"VigorSpear"			,	SKILL_PLAY_VIGOR_SPEAR			},

	{	"Windy"					,	SKILL_PLAY_WINDY				},
	{	"TwistJavelin"			,	SKILL_PLAY_TWIST_JAVELIN		},
	{	"SoulSucker"			,	SKILL_PLAY_SOUL_SUCKER			},
	{	"FireJavelin"			,	SKILL_PLAY_FIRE_JAVELIN			},

	{	"SplitJavelin"			,	SKILL_PLAY_SPLIT_JAVELIN		},
	{	"TriumphOfValhalla"		,	SKILL_PLAY_TRIUMPH_OF_VALHALLA	},
	{	"LightningJavelin"		,	SKILL_PLAY_LIGHTNING_JAVELIN	},
	{	"StormJavelin"			,	SKILL_PLAY_STORM_JAVELIN		},

	{	"HALLOFVALHALLA"		,	SKILL_PLAY_HALL_OF_VALHALLA		},
	{	"XRAGE"					,	SKILL_PLAY_X_RAGE				},
	{	"FROSTJAVELIN"			,	SKILL_PLAY_FROST_JAVELIN		},
	{	"VENGEANCE"				,	SKILL_PLAY_VENGEANCE			},



	{	"Healing"				,	SKILL_PLAY_HEALING				},
	{	"HolyBolt"				,	SKILL_PLAY_HOLY_BOLT			},
	{	"MultiSpark"			,	SKILL_PLAY_MULTI_SPARK			},
	{	"HolyMind"				,	SKILL_PLAY_HOLY_MIND			},

	{	"Meditation"			,	0								},
	{	"DivineLightning"		,	SKILL_PLAY_DIVINE_LIGHTNING		},
	{	"HolyReflection"		,	SKILL_PLAY_HOLY_REFLECTION		},
	{	"GrandHealing"			,	SKILL_PLAY_GREAT_HEALING		},

	{	"VigorBall"				,	SKILL_PLAY_VIGOR_BALL			},
	{	"Resurrection"			,	SKILL_PLAY_RESURRECTION			},
	{	"Extinction"			,	SKILL_PLAY_EXTINCTION			},
	{	"VirtualLife"			,	SKILL_PLAY_VIRTUAL_LIFE			},

	{	"GLACIALSPIKE"			,	SKILL_PLAY_GLACIAL_SPIKE		},
	{	"REGENERATIONFIELD"		,	SKILL_PLAY_REGENERATION_FIELD	},
	{	"CHAINLIGHTNING"		,	SKILL_PLAY_CHAIN_LIGHTNING		},
	{	"SUMMONMUSPELL"			,	SKILL_PLAY_SUMMON_MUSPELL		},



	{	"Agony"					,	SKILL_PLAY_AGONY				},
	{	"FireBolt"				,	SKILL_PLAY_FIRE_BOLT			},
	{	"Zenith"				,	SKILL_PLAY_ZENITH				},
	{	"FireBall"				,	SKILL_PLAY_FIRE_BALL			},

	{	"MentalMastery"			,	0								},
	{	"ColumnOfWater"			,	SKILL_PLAY_COLUMN_OF_WATER		},
	{	"EnchantWeapon"			,	SKILL_PLAY_ENCHANT_WEAPON		},
	{	"DeadRay"				,	SKILL_PLAY_DEAD_RAY				},

	{	"EnergyShield"			,	SKILL_PLAY_ENERGY_SHIELD		},
	{	"Diastrophism"			,	SKILL_PLAY_DIASTROPHISM			},
	{	"SpiritElemental"		,	SKILL_PLAY_SPIRIT_ELEMENTAL		},
	{	"DancingSword"			,	SKILL_PLAY_DANCING_SWORD		},

	{	"FIREELEMENTAL"			,	SKILL_PLAY_FIRE_ELEMENTAL		},
	{	"FLAMEWAVE"				,	SKILL_PLAY_FLAME_WAVE			},
	{	"DISTORTION"			,	SKILL_PLAY_DISTORTION			},
	{	"METEO"					,	SKILL_PLAY_METEO				},

	{	"",0 }
};







void ModelKeyWordEncode(DWORD dwFileCode, smMODELINFO *lpMODELINFO)
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if(lpMODELINFO->szLinkFile[0])
	{
		szFile = ChangeFileExt(lpMODELINFO->szLinkFile, szFileExt);
		DWORD dwLinkCode = GetSpeedSum(szFile);

		dwCode_1 = ((dwFileCode & 0x00ff0000) << 8);
		dwCode_2 = ((dwLinkCode & 0x000000ff) << 16);
		dwCode_3 = ((dwFileCode & 0x000000ff) << 8);
		dwCode_4 = ((dwLinkCode & 0xff000000) >> 24);
		lpMODELINFO->FileTypeKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4);

		dwCode_1 = ((dwFileCode & 0xff000000));
		dwCode_2 = ((dwLinkCode & 0x0000ff00) << 8);
		dwCode_3 = ((dwFileCode & 0x0000ff00));
		dwCode_4 = ((dwLinkCode & 0x00ff0000) >> 16);
		lpMODELINFO->LinkFileKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4);
	}
	else
	{
		dwCode_1 = ((dwFileCode & 0x0000ff00) << 16);
		dwCode_2 = ((dwFileCode & 0xff000000) >> 8);
		dwCode_3 = ((dwFileCode & 0x000000ff) << 8);
		dwCode_4 = ((dwFileCode & 0x00ff0000) >> 16);
		lpMODELINFO->FileTypeKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4);
	}
}


int ModelKeyWordDecode(DWORD dwFileCode, smMODELINFO *lpMODELINFO)
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if(lpMODELINFO->szLinkFile[0])
	{
		szFile = ChangeFileExt(lpMODELINFO->szLinkFile, szFileExt);
		DWORD dwLinkCode = GetSpeedSum(szFile);

		dwCode_1 = ((lpMODELINFO->LinkFileKeyWord & 0xff000000));
		dwCode_2 = ((lpMODELINFO->FileTypeKeyWord & 0xff000000) >> 8);
		dwCode_3 = ((lpMODELINFO->LinkFileKeyWord & 0x0000ff00));
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x0000ff00) >> 8);
		if(dwFileCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4))
			return FALSE;

		dwCode_1 = ((lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 24);
		dwCode_2 = ((lpMODELINFO->LinkFileKeyWord & 0x000000ff) << 16);
		dwCode_3 = ((lpMODELINFO->LinkFileKeyWord & 0x00ff0000) >> 8);
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x00ff0000) >> 16);
		if(dwLinkCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4))
			return FALSE;
	}
	else
	{
		dwCode_1 = ((lpMODELINFO->FileTypeKeyWord & 0xff000000) >> 16);
		dwCode_2 = ((lpMODELINFO->FileTypeKeyWord & 0x00ff0000) << 8);
		dwCode_3 = ((lpMODELINFO->FileTypeKeyWord & 0x0000ff00) >> 8);
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 16);
		if(dwFileCode != (dwCode_2 | dwCode_4 | dwCode_1 | dwCode_3))
			return FALSE;
	}

	return TRUE;
}


void MotionKeyWordEncode(DWORD dwCode, smMODELINFO *lpMODELINFO)
{
	int cnt, i, stFrm, endFrm;
	smMOTIONINFO *lpMotionInfo;


	cnt = lpMODELINFO->MotionCount;
	for(i = CHRMOTION_EXT; i < cnt; i++)
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if(lpMotionInfo)
		{
			stFrm = lpMotionInfo->StartFrame;
			endFrm = lpMotionInfo->EndFrame;


			if(stFrm)
			{
				lpMotionInfo->MotionKeyWord_1 = (dwCode & 0xff000000) | ((stFrm & 0x0000ff00) << 8) |
					((dwCode & 0x00ff0000) >> 8) | (stFrm & 0x000000ff);

				lpMotionInfo->StartFrame = ((dwCode & 0x000000ff) << 24) | (stFrm & 0x00ff0000) |
					(dwCode & 0x0000ff00) | ((stFrm & 0xff000000) >> 24);
			}


			if(endFrm)
			{
				lpMotionInfo->MotionKeyWord_2 = ((dwCode & 0x000000ff) << 24) | ((endFrm & 0xff000000) >> 8) |
					(dwCode & 0x0000ff00) | ((endFrm & 0x00ff0000) >> 16);

				lpMotionInfo->EndFrame = ((dwCode & 0x00ff0000) << 8) | ((endFrm & 0x0000ff00) << 8) |
					((dwCode & 0xff000000) >> 16) | (endFrm & 0x000000ff);
			}
		}
	}
}


int MotionKeyWordDecode(DWORD dwCode, smMODELINFO *lpMODELINFO)
{
	int cnt, i, KeyWord, Frame;
	smMOTIONINFO *lpMotionInfo;


	cnt = lpMODELINFO->MotionCount;
	for(i = CHRMOTION_EXT; i < cnt; i++)
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if(lpMotionInfo)
		{

			if(lpMotionInfo->MotionKeyWord_1 || lpMotionInfo->StartFrame)
			{
				KeyWord = (lpMotionInfo->MotionKeyWord_1 & 0xff000000) | ((lpMotionInfo->MotionKeyWord_1 & 0x0000ff00) << 8) |
					(lpMotionInfo->StartFrame & 0x0000ff00) | ((lpMotionInfo->StartFrame & 0xff000000) >> 24);

				Frame = ((lpMotionInfo->StartFrame & 0x000000ff) << 24) | (lpMotionInfo->StartFrame & 0x00ff0000) |
					((lpMotionInfo->MotionKeyWord_1 & 0x00ff0000) >> 8) | (lpMotionInfo->MotionKeyWord_1 & 0x000000ff);

				if(dwCode != KeyWord)
					return FALSE;

				lpMotionInfo->MotionKeyWord_1 = 0;
				lpMotionInfo->StartFrame = Frame;
			}


			if(lpMotionInfo->MotionKeyWord_2 || lpMotionInfo->EndFrame)
			{
				KeyWord = ((lpMotionInfo->EndFrame & 0x0000ff00) << 16) | ((lpMotionInfo->EndFrame & 0xff000000) >> 8) |
					(lpMotionInfo->MotionKeyWord_2 & 0x0000ff00) | ((lpMotionInfo->MotionKeyWord_2 & 0xff000000) >> 24);

				Frame = ((lpMotionInfo->MotionKeyWord_2 & 0x00ff0000) << 8) | ((lpMotionInfo->MotionKeyWord_2 & 0x000000ff) << 16) |
					((lpMotionInfo->EndFrame & 0x00ff0000) >> 8) | (lpMotionInfo->EndFrame & 0x000000ff);

				if(dwCode != KeyWord)
					return FALSE;

				lpMotionInfo->MotionKeyWord_2 = 0;
				lpMotionInfo->EndFrame = Frame;
			}
		}
	}

	return TRUE;
}



int	Open_SODConfig(char *szFileName, void *lphCoreMonster, int *SodTax, char *szSodText, size_t szSodTextSize, int *SodScoreDiv)
{

	FILE	*fp;
	char strBuff[256];
	char *p;
	char *pb;
	int NextFlag;
	int cnt;
	int hcRoundCount = 0;

	int	m_SodTax = 0;
	int m_SodScoreDiv = 0;
	char m_szSodText[256];
	sHCORE_MONSTER	hcMonster[hCORE_ROUND_MAX];
	sHCORE_MONSTER	*lpSod_Monster = (sHCORE_MONSTER *)lphCoreMonster;

	m_szSodText[0] = 0;
	memcpy(hcMonster, lpSod_Monster, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	for(cnt = 0; cnt < rsHARDCORE_COUNT_END; cnt++)
	{

		hcMonster[cnt].hCoreMonster1.szName[0] = 0;
		hcMonster[cnt].hCoreMonster1.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster1.perCount = 0;

		hcMonster[cnt].hCoreMonster2.szName[0] = 0;
		hcMonster[cnt].hCoreMonster2.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster2.perCount = 0;

		hcMonster[cnt].hCoreMonster3.szName[0] = 0;
		hcMonster[cnt].hCoreMonster3.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster3.perCount = 0;

		hcMonster[cnt].hCoreMonster4.szName[0] = 0;
		hcMonster[cnt].hCoreMonster4.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster4.perCount = 0;

		hcMonster[cnt].hCoreMonsterBoss.szName[0] = 0;
		hcMonster[cnt].hCoreMonsterBoss.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonsterBoss.perCount = 0;

		hcMonster[cnt].MaxMonster = 0;
	}


	fp = fopen(szFileName, "rb");
	if(fp == NULL) return FALSE;


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)	break;

		p = GetWord(decode, line);

		NextFlag = 0;


		if(lstrcmpi(decode, "*BELATRA_TAX") == 0)
		{

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			if(strBuff[0]) m_SodTax = atoi(strBuff);

			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmpi(decode, "*BELATRA_TEXT") == 0)
		{

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			strcpy_s(m_szSodText, strBuff);

			NextFlag = TRUE;
		}


		if(!NextFlag && lstrcmpi(decode, "*BELATRA_DIVSCORE") == 0)
		{

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			if(strBuff[0]) m_SodScoreDiv = atoi(strBuff);

			NextFlag = TRUE;
		}



		if(!NextFlag && lstrcmpi(decode, "*BELATRA_MONSTER") == 0)
		{
			if(hcRoundCount < rsHARDCORE_COUNT_END)
			{
				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(hcMonster[hcRoundCount].hCoreMonster1.szName, strBuff);
				p = GetWord(strBuff, p);
				hcMonster[hcRoundCount].hCoreMonster1.perCount = atoi(strBuff);

				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(hcMonster[hcRoundCount].hCoreMonster2.szName, strBuff);
				p = GetWord(strBuff, p);
				hcMonster[hcRoundCount].hCoreMonster2.perCount = atoi(strBuff);

				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(hcMonster[hcRoundCount].hCoreMonster3.szName, strBuff);
				p = GetWord(strBuff, p);
				hcMonster[hcRoundCount].hCoreMonster3.perCount = atoi(strBuff);

				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(hcMonster[hcRoundCount].hCoreMonster4.szName, strBuff);
				p = GetWord(strBuff, p);
				hcMonster[hcRoundCount].hCoreMonster4.perCount = atoi(strBuff);

				pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
				strcpy_s(hcMonster[hcRoundCount].hCoreMonsterBoss.szName, strBuff);
				hcMonster[hcRoundCount].hCoreMonsterBoss.perCount = 0;

				p = GetWord(strBuff, p);
				hcMonster[hcRoundCount].MaxMonster = atoi(strBuff);

				hcRoundCount++;
			}
			NextFlag = TRUE;
		}
	}
	fclose(fp);

	if(hcRoundCount < rsHARDCORE_COUNT_END)
	{
		return 0;
	}

	if(m_SodTax >= 0 && m_SodTax < 100)
	{
		*SodTax = m_SodTax;
	}

	if(m_szSodText[0])
	{
		strcpy_s(szSodText, szSodTextSize, m_szSodText);
	}

	if(m_SodScoreDiv > 0)
	{
		*SodScoreDiv = m_SodScoreDiv;
	}

	memcpy(lpSod_Monster, hcMonster, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	return 1;
}





int ReadCustomCracker(char *szCrackFile, TRANS_FIND_CRACKER *lpTransFindCrack)
{
	FILE	*fp;
	char strBuff[64];
	char *p, *pb;
	int cnt;


	fp = fopen(szCrackFile, "rb");
	if(fp == NULL)
	{
		return FALSE;
	}

	cnt = 0;

	while(!feof(fp))
	{

		if(fgets(line, 255, fp) == NULL)	break;

		p = GetWord(decode, line);


		if(lstrcmpi(decode, "*CRACK") == 0)
		{


			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			strcpy_s(lpTransFindCrack->CrackName[cnt].szName1, strBuff);

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			strcpy_s(lpTransFindCrack->CrackName[cnt].szName2, strBuff);

			pb = p; p = GetWord(strBuff, p); if(strBuff[0] == 34)p = GetString(strBuff, pb);
			strcpy_s(lpTransFindCrack->CrackName[cnt].szClass, strBuff);

			cnt++;
		}
		if(cnt >= FIND_CRACK_LIST_MAX) break;

	}

	lpTransFindCrack->code = OpCode::OPCODE_FINDCRACK;
	lpTransFindCrack->size = sizeof(_CRACK_NAME)*cnt + 16;
	lpTransFindCrack->FindCounter = cnt;

	fclose(fp);

	return cnt;
}



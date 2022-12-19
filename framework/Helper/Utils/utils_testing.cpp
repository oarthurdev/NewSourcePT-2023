#include "utils_testing.h"



#define	smTRANSCODE_SYSTEM			0x48400000

#define	smTRANSCODE_CLOSE			0x72470011

#define	smTRANSCODE_CONNECTED		0x48470080
#define smTRANSCODE_RECORDDATA		0x48470081
#define smTRANSCODE_GETRECORDDATA	0x48470082
#define smTRANSCODE_FAILRECORDDATA	0x48470083
#define smTRANSCODE_RECORDRESULT	0x48470084


#define smTRANSCODE_ID_GETUSERINFO	0x48470085
#define smTRANSCODE_ID_SETUSERINFO	0x48470086
#define smTRANSCODE_DELRECORDDATA	0x48470087
#define smTRANSCODE_INSRECORDDATA	0x48470088
#define smTRANSCODE_ISRECORDDATA	0x48470089


#define smTRANSCODE_VERSION			0x4847008A

#define smTRANSCODE_CHECK_NETSTATE	0x4847008B

#define smTRANSCODE_ADMINMODE		0x4847008C

#define smTRANSCODE_SET_OBJSERIAL	0x4847008D

#define smTRANSCODE_CHECK_NETSTATE2	0x4847008E
#define smTRANSCODE_CHECK_NETSTATE3	0x4847008F
#define smTRANSCODE_CHECK_NETSTATE4	0x48470090
#define smTRANSCODE_CHECK_NETSTATE5	0x48470091

#define smTRANSCODE_IPLIST			0x48471000
#define smTRANSCODE_CHATMESSAGE		0x48471001
#define smTRANSCODE_POSITION		0x48471002
#define smTRANSCODE_PLAYLIST		0x48471003
#define smTRANSCODE_CONTINUEDATA	0x48471004
#define smTRANSCODE_WHISPERMESSAGE	0x48471005
#define smTRANSCODE_COUPLERING		0x48471006			

#define smTRANSCODE_PLAYDATA1		0x48470010
#define smTRANSCODE_PLAYDATA2		0x48470011
#define smTRANSCODE_PLAYDATA3		0x48470012
#define smTRANSCODE_TRANSPLAYDATA	0x48470013
#define smTRANSCODE_PLAYDATAGROUP	0x48470014
#define smTRANSCODE_PLAY_COMMAND	0x48470018

#define smTRANSCODE_PARTY_CHATMSG	0x48471015

#define smTRANSCODE_ADDEXP_PARTY	0x48470029
#define smTRANSCODE_ATTACKDATA		0x48470030
#define smTRANSCODE_ADDEXP			0x48470031
#define smTRANSCODE_PLAYERINFO2		0x48470032
#define smTRANSCODE_SET_BLACKLIST	0x48470033
#define smTRANSCODE_SET_ITEMCOPYLIST 0x48470034
#define smTRANSCODE_SKIL_ATTACKDATA	0x48470035
#define smTRANSCODE_FINDCRACK		0x48470036
#define smTRANSCODE_MODULE_WARNIG	0x48470037
#define smTRANSCODE_UPDATE_CINFO	0x48470038
#define smTRANSCODE_OPENMONSTER		0x48470039
#define smTRANSCODE_WARPFIELD		0x48470040
#define smTRANSCODE_TRADEITEMS		0x48470041
#define smTRANSCODE_TRADE_REQUST	0x48470042
#define smTRANSCODE_TRADE_ITEMKEY	0x48470043
#define smTRANSCODE_TRADE_READYITEM	0x48470044
#define smTRANSCODE_SKILL_MENU		0x48470045
#define smTRANSCODE_WAREHOUSE		0x48470047

#define smTRANSCODE_OPEN_WAREHOUSE	0x48470048
#define smTRANSCODE_OPEN_MIXITEM	0x48470049
#define smTRANSCODE_OPEN_COLLECT	0x4847004A
#define smTRANSCODE_COLLECTMONEY	0x4847004B
#define	smTRANSCODE_PLAYERINFO_Q	0x4847004C
#define smTRANSCODE_OPEN_AGING		0x4847004D

#define smTRANSCODE_SKIL_ATTACKUSER	0x4847004E

#define smTRANSCODE_OPEN_EVENTGIFT	0x4847004F

#define smTRANSCODE_PLAYERINFO		0x48470020
#define smTRANSCODE_GETPLAYERINFO	0x48470021
#define smTRANSCODE_FAILCONNECT		0x48470023


#define smTRANSCODE_PLAYITEM		0x48470050
#define smTRANSCODE_DELITEM			0x48470051
#define smTRANSCODE_PUTITEM			0x48470052
#define smTRANSCODE_THROWITEM		0x48470053
#define smTRANSCODE_SHOP_ITEMLIST	0x48470054
#define smTRANSCODE_SAVETHROWITEM	0x48470055
#define smTRANSCODE_SAVETHROWMONEY	0x48470056
#define smTRANSCODE_SAVETHROWITEM2	0x48470057
#define smTRANSCODE_PLAYERKILLING	0x48470059
#define smTRANSCODE_GETITEM			0x4847005A
#define smTRANSCODE_USEITEM_CODE	0x4847005B
#define smTRANSCODE_COMMAND_USER	0x4847005C
#define smTRANSCODE_WING_NPC		0x4847005D
#define smTRANSCODE_PAYMENT_MONEY	0x4847005E
#define smTRANSCODE_MEDIA_NPC		0x4847005F

#define smTRANSCODE_ADD_STARTPOSI	0x48470060
#define smTRANSCODE_DEL_STARTPOSI	0x48470061
#define smTRANSCODE_ADD_NPC			0x48470070
#define smTRANSCODE_DEL_NPC			0x48470071
#define smTRANSCODE_ADMIN_COPYCHAR	0x48470062

#define	smTRANSCODE_PARTY_UPDATE		0x484700A0
#define	smTRANSCODE_PARTY_REQUEST		0x484700A1
#define	smTRANSCODE_PARTY_JOIN			0x484700A2
#define	smTRANSCODE_PARTY_PLAYUPDATE	0x484700A3
#define	smTRANSCODE_PARTY_RELEASE		0x484700A4
#define	smTRANSCODE_PARTY_COMMAND		0x484700A5
#define smTRANSCODE_OPEN_MIXTURE_RESET	0x484700A6	

#define smTRANSCODE_PCBANG_PET			0x484700B0
#define smTRANSCODE_PHENIX_PET			0x484700B1	
#define smTRANSCODE_HELP_PET			0x484700B2	

#define	smTRANSCODE_SERVER_INFO			0x484700C0

#define	smTRANSCODE_PARTY_POTION		0x484700D0

#define	smTRANSCODE_HEALING				0x484700D2
#define	smTRANSCODE_HOLYMIND			0x484700D3
#define	smTRANSCODE_GRAND_HEALING		0x484700D4

#define	smTRANSCODE_VAMPRIC_CUSPID		0x484700D6
#define	smTRANSCODE_VAMPRIC_CUSPID_EX		0x484700D7		
#define	smTRANSCODE_MANA_RECHARGING		0x484700D8


#define	smTRANSCODE_RECORD_TRADE		0x48480010



#define smTRANSCODE_NETWORK_QUALITY	0x484700E0
#define smTRANSCODE_PROCESSINFO		0x484700E4
#define	smTRANSCODE_CLOSECLIENT		0x484700E6
#define smTRANSCODE_CHECKIP			0x484700E7


#define	smTRANSCODE_SAVECLIENT		0x484700E8


#define smTRANSCODE_EFFECT_ITEM		0x48478000
#define smTRANSCODE_EFFECT_WEAPON	0x48478002
#define smTRANSCODE_EFFECT_STUN		0x48478004
#define smTRANSCODE_EFFECT_CURSE	0x48478006
#define smTRANSCODE_EFFECT_ICE		0x48478008
#define smTRANSCODE_EFFECT_POISION	0x4847800A
#define smTRANSCODE_EFFECT_VANISH	0x4847800C
#define smTRANSCODE_EFFECT_PERSHOP	0x4847800E
#define smTRANSCODE_EFFECT_LOWPET	0x4847800F
#define smTRANSCODE_EFFECT_CLANMGR	0x48479000
#define smTRANSCODE_EFFECT_FORCEORB	0x48479010
#define smTRANSCODE_EFFECT_CURSE_QUEST	0x48479011
#define smTRANSCODE_EFFECT_BLESS_SCORE	0x48479012
#define smTRANSCODE_EFFECT_KEEPSKILL	0x48479020



#define smTRANSCODE_CONT_OBJSERIAL	0x48478010


#define smTRANSCODE_MESSAGEBOX		0x48478100


#define	smTRANSCODE_FUNCERROR		0x48478200


#define smTRANSCODE_FUNCTION_MEM2	0x48478300


#define	smTRANSCODE_SET_BLACKLIST2	0x48478400

#define smTRANSCODE_SET_BLACKLIST3	0x48478500


#define	smTRANSCODE_BAD_PLAYER		0x48478600


#define	smTRANSCODE_FIX_ATTACK		0x48478700

#define	smTRANSCODE_DEAD_PLAYER		0x48478800


#define smTRANSCODE_CLIENT_ERROR	0x48478900


#define	smTRANSCODE_INVEN_ERR_ITEM	0x48478910

#define	smTRANSCODE_INVEN_ERR_MONEY	0x48478920


#define	smTRANSCODE_INVEN_POSITION	0x48478930
#define	smTRANSCODE_INVEN_POSITION2	0x48478931



#define smTRANSCODE_ENCODE_PACKET	0x80010000
#define smTRANSCODE_ENCODE_PACKET2	0x90010000


#define smTRANSCODE_OPEN_CLANMENU	0x48478A00

#define smTRANSCODE_OPEN_STARPOINT	0x48478A10
#define smTRANSCODE_STARPOINT		0x48478A12

#define smTRANSCODE_OPEN_GIVEMONEY	0x48478A14
#define smTRANSCODE_GIVEMONEY		0x48478A16

#define smTRANSCODE_CLANMONEY		0x48478A18



#define smTRANSCODE_ITEM_EXPRESS	0x48478A80


#define smTRANSCODE_OPEN_MYSHOP		0x48478A90

#define smTRANSCODE_CALL_MYSHOP		0x48478AA0

#define	smTRANSCODE_MYSHOP_ITEM		0x48478AB0

#define	smTRANSCODE_MYSHOP_MESSAGE	0x48478AC0

#define	smTRANSCODE_MYSHOP_TRADE	0x48478AD0



#define smTRANSCODE_EFFECT_PCBANGPET	0x48478AE0



#define smTRANSCODE_ADMINMODE2			0x5047108C

#define smTRANSCODE_CHECK_NETSTATE20	0x5047008E


#define smTRANSCODE_CHECK_EXPMONEY		0x50320010

#define smTRANSCODE_CHECK_EXPDATA		0x50320020

#define smTRANSCODE_FORCEORB_DATA		0x50320030

#define smTRANSCODE_PRIMEITEM_DATA		0x50320031



#define smTRANSCODE_PRIMEITEM_DATA2	0x50320032


#define smTRANSCODE_PRIMEITEM_DATA3	0x50320033






#define smTRANSCODE_BOOSTER_DATA		0x50320034


#define smTRANSCODE_AGING_DATA			0x50320035


#define smTRANSCODE_SKILLDELAY_DATA			0x50320036


#define smTRANSCODE_SEND_DATASERVER		0x50320100

#define smTRANSCODE_SEND_GAMESERVER		0x50320110

#define smTRANSCODE_SEND_AREASERVER		0x50320120

#define smTRANSCODE_SEND_AGAME_SERVER	0x50320130



#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2	0x50320140



#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3	0x50320150


#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4	0x50320160



#define smTRANSCODE_CRAFTITEM			0x50320200

#define smTRANSCODE_AGINGITEM			0x50320202

#define	smTRANSCODE_AGING_UPGRADE		0x50320204

#define	smTRANSCODE_MAKE_LINKCORE		0x50320205

#define	smTRANSCODE_USE_LINKCORE		0x50320206

#define smTRANSCODE_WINGITEM			0x50320208


#define smTRANSCODE_SHOPTITEM			0x50320210

#define smTRANSCODE_SHOP_SELLITEM		0x50320212


#define	smTRANSCODE_ITEM_FORCEORB		0x50320214


#define	smTRANSCODE_QUEST_COMMAND		0x50320220

#define	smTRANSCODE_EXITINFO_URL		0x50320230



#define smTRANSCODE_CHECKITEM			0x50320300

#define smTRANSCODE_ERRORITEM			0x50320310

#define smTRANSCODE_CLEARPOTION			0x50320320

#define smTRANSCODE_CHECK_ITEMMESH		0x50320330


#define smTRANSCODE_CLIENT_FUNCPOS		0x50320400

#define smTRANSCODE_GETCLIENT_FUNCPOS	0x50320410


#define smTRANSCODE_FUNCTION_MEM		0x50320420

#define smTRANSCODE_FUNCTON_RESULT		0x50320430


#define smTRANSCODE_PROCESS_TIMEMAX		0x50320500


#define smTRANSCODE_NSPRITE				0x50320600

#define smTRANSCODE_NPROTECT			0x50320700
#define smTRANSCODE_GAMEGUARD_AUTH		0x50320710



#define	smTRANSCODE_REC_DAMAGEDATA		0x50320800


#define	smTRANSCODE_SOD_RESULT			0x50320900
#define	smTRANSCODE_SOD_RESULT2			0x50320901


#define	smTRANSCODE_PARTY_SKILL			0x50320A00



#define	smTRANSCODE_CANCEL_SKILL		0x50320A10

#define	smTRANSCODE_PROCESS_SKILL		0x50320A20
#define smTRANSCODE_PROCESS_SKILL2		0x50320A30
#define smTRANSCODE_PROCESS_CLAN_SKILL	0x50320A35

#define	smTRANSCODE_UPDATEL_SKILL		0x50320A40

#define	smTRANSCODE_SUCCESS_EVATION		0x50320A50

#define	smTRANSCODE_RESISTANCE			0x50320A60


#define	smTRANSCODE_PUBLIC_POLLING		0x50320A70

#define	smTRANSCODE_NOTICE_BOX			0x50320A80

#define	smTRANSCODE_HACKTRAP			0x50320A90



#define	smTRANSCODE_VIRTURAL_POTION		0x50320B00


#define	smTRANSCODE_CLAN_SERVICE		0x50320C00

#define	smTRANSCODE_CLAN_UPDATE			0x50320C10


#define	smTRANSCODE_QUEST_MESSAGE		0x50320D00


#define	smTRANSCODE_DEAD_USER			0x50320E00

#define	smTRANSCODE_YAHOO_MOTION		0x50320E10

#define	smTRANSCODE_CHANGE_EVENT		0x50320F00


#define	smTRANSCODE_CLIENTINFO			0x50321000


#define	smTRANSCODE_WARNING_BLINK_ATT	0x50321010



#define smTRANSCODE_ATTACK_DAMAGE		0x50322000
#define smTRANSCODE_RANGE_DAMAGE		0x50322010
#define smTRANSCODE_ATTACK_RESULT		0x50322020
#define smTRANSCODE_DISP_DAMAGE			0x50322030
#define smTRANSCODE_ATTACKDATA2			0x50322040

#define smTRANSCODE_LIMIT_DAMAGE		0x50322050


#define smTRANSCODE_WARNING_CLIENT		0x50322060
#define smTRANSCODE_WARNING_SKILL		0x50322080

#define smTRANSCODE_COMIC_SKIN			0x50322070

#define	smTRANSCODE_REC_ADMIN_COMMAND	0x50322090


#define smTRANSCODE_CHECK_ADMINMODE		0x503220A0


#define smTRANSCODE_SOD_INFOMATION		0x503220B0


#define smTRANSCODE_BLESSCASTLE_INFO	0x503220C0
#define smTRANSCODE_BLESSCASTLE_TAX		0x503220D0


#define smTRANSCODE_ATTACK_SLASH_LIST	0x503220E0


#define smTRANSCODE_UPDATE_SERVER_PARAM	0x503220F0
#define smUPDATE_PARAM_LOWUSER_PRESENT	0x100


#define smTRANSCODE_USER_ID				0x50322100




#define smTRANSCODE_DAMAGE_ENCODE_MEM	0x50322F00
#define smTRANSCODE_DAMAGE_ENCODE_MEM2	0x50322EC0


#define	smTRANSCODE_PACKET_DYNFUNC		0x50323000



#define	smTRANSCODE_AREA_SERVER_MAP		0x50324000

#define smTRANSCODE_OPEN_SMELTING		0x50325000
#define smTRANSCODE_SMELTINGITEM		0x50325001

#define smTRANSCODE_OPEN_MANUFACTURE	0x50326000
#define smTRANSCODE_MANUFACTURE			0x50326001

#define smTRANSCODE_MANUFACTURE_WEIGHT_PRICE 0x50326002


#define smTRANSCODE_GIFTBOX_MONEY		0x50326003


#define smTRANSCODE_PREMIUMITEM_INIT	0x50326004


#define smTRANSCODE_MIXTURE_RESET_ITEM	0x50326006


#define	rsHARDCORE_EVENT_FLAG		0x100

#define smCODE_SOD_EFFECT		100			


#define smTRANSCODE_EVENT_GAME		0x50326007
#define smCODE_EVENT_STATE_INIT		100


#define smTRANSCODE_ITEMDOC			0x50326008


#define TRANS_BUFF_SIZE		4096

#define	smCHAR_STATE_NPC		0
#define	smCHAR_STATE_ENEMY		1
#define	smCHAR_STATE_USER		0x80

#define	smCHAR_MONSTER_NATURAL	0x80
#define	smCHAR_MONSTER_GOOD		0x81
#define	smCHAR_MONSTER_EVIL		0x82

#define	smCHAR_MONSTER_NORMAL	0x00
#define	smCHAR_MONSTER_UNDEAD	0x90
#define	smCHAR_MONSTER_MUTANT	0x91
#define	smCHAR_MONSTER_DEMON	0x92
#define	smCHAR_MONSTER_MECHANIC	0x93

#define	smCHAR_MONSTER_USER		0xA0

#define	smCOMMNAD_USER_WARP		0x100
#define	smCOMMNAD_USER_AGINGUP	0x110
#define	smCOMMNAD_USER_HOLY_INCANTATION	0x120
#define	smCOMMNAD_USER_RESURRECTION	0x130
#define	smCOMMNAD_USER_FORCEORB	0x140
#define	smCOMMNAD_USER_VALENTO	0x150
#define	smCOMMNAD_USER_FIREFLOWER	0x160

#define	smCOMMAND_PLAY_BABEL		0x200
#define	smCOMMAND_PLAY_BELSS_CASTLE	0x210
#define	smCOMMAND_PLAY_PK_FIELD		0x220
#define	smCOMMAND_PLAY_KELVEZU		0x230

char* GetTranscodeNameByOpcode(int opcode)
{
	switch (opcode)
	{
	case smTRANSCODE_SYSTEM:	return "smTRANSCODE_SYSTEM"; break;
	case smTRANSCODE_CONNECTED:	return "smTRANSCODE_CONNECTED"; break;
	case smTRANSCODE_RECORDDATA:	return "smTRANSCODE_RECORDDATA"; break;
	case smTRANSCODE_GETRECORDDATA:	return "smTRANSCODE_GETRECORDDATA"; break;
	case smTRANSCODE_FAILRECORDDATA:	return "smTRANSCODE_FAILRECORDDATA"; break;
	case smTRANSCODE_RECORDRESULT:	return "smTRANSCODE_RECORDRESULT"; break;
	case smTRANSCODE_ID_GETUSERINFO:	return "smTRANSCODE_ID_GETUSERINFO"; break;
	case smTRANSCODE_ID_SETUSERINFO:	return "smTRANSCODE_ID_SETUSERINFO"; break;
	case smTRANSCODE_DELRECORDDATA:	return "smTRANSCODE_DELRECORDDATA"; break;
	case smTRANSCODE_INSRECORDDATA:	return "smTRANSCODE_INSRECORDDATA"; break;
	case smTRANSCODE_ISRECORDDATA:	return "smTRANSCODE_ISRECORDDATA"; break;
	case smTRANSCODE_VERSION:	return "smTRANSCODE_VERSION"; break;
	case smTRANSCODE_CHECK_NETSTATE:	return "smTRANSCODE_CHECK_NETSTATE"; break;
	case smTRANSCODE_ADMINMODE:	return "smTRANSCODE_ADMINMODE"; break;
	case smTRANSCODE_SET_OBJSERIAL:	return "smTRANSCODE_SET_OBJSERIAL"; break;
	case smTRANSCODE_CHECK_NETSTATE2:	return "smTRANSCODE_CHECK_NETSTATE2"; break;
	case smTRANSCODE_CHECK_NETSTATE3:	return "smTRANSCODE_CHECK_NETSTATE3"; break;
	case smTRANSCODE_CHECK_NETSTATE4:	return "smTRANSCODE_CHECK_NETSTATE4"; break;
	case smTRANSCODE_CHECK_NETSTATE5:	return "smTRANSCODE_CHECK_NETSTATE5"; break;
	case smTRANSCODE_IPLIST:	return "smTRANSCODE_IPLIST"; break;
	case smTRANSCODE_CHATMESSAGE:	return "smTRANSCODE_CHATMESSAGE"; break;
	case smTRANSCODE_POSITION:	return "smTRANSCODE_POSITION"; break;
	case smTRANSCODE_PLAYLIST:	return "smTRANSCODE_PLAYLIST"; break;
	case smTRANSCODE_CONTINUEDATA:	return "smTRANSCODE_CONTINUEDATA"; break;
	case smTRANSCODE_WHISPERMESSAGE:	return "smTRANSCODE_WHISPERMESSAGE"; break;
	case smTRANSCODE_COUPLERING:	return "smTRANSCODE_COUPLERING"; break;
	case smTRANSCODE_PLAYDATA1:	return "smTRANSCODE_PLAYDATA1"; break;
	case smTRANSCODE_PLAYDATA2:	return "smTRANSCODE_PLAYDATA2"; break;
	case smTRANSCODE_PLAYDATA3:	return "smTRANSCODE_PLAYDATA3"; break;
	case smTRANSCODE_TRANSPLAYDATA:	return "smTRANSCODE_TRANSPLAYDATA"; break;
	case smTRANSCODE_PLAYDATAGROUP:	return "smTRANSCODE_PLAYDATAGROUP"; break;
	case smTRANSCODE_PLAY_COMMAND:	return "smTRANSCODE_PLAY_COMMAND"; break;
	case smTRANSCODE_PARTY_CHATMSG:	return "smTRANSCODE_PARTY_CHATMSG"; break;
	case smTRANSCODE_ADDEXP_PARTY:	return "smTRANSCODE_ADDEXP_PARTY"; break;
	case smTRANSCODE_ATTACKDATA:	return "smTRANSCODE_ATTACKDATA"; break;
	case smTRANSCODE_ADDEXP:	return "smTRANSCODE_ADDEXP"; break;
	case smTRANSCODE_PLAYERINFO2:	return "smTRANSCODE_PLAYERINFO2"; break;
	case smTRANSCODE_SET_BLACKLIST:	return "smTRANSCODE_SET_BLACKLIST"; break;
	case smTRANSCODE_SET_ITEMCOPYLIST:	return "smTRANSCODE_SET_ITEMCOPYLIST"; break;
	case smTRANSCODE_SKIL_ATTACKDATA:	return "smTRANSCODE_SKIL_ATTACKDATA"; break;
	case smTRANSCODE_FINDCRACK:	return "smTRANSCODE_FINDCRACK"; break;
	case smTRANSCODE_MODULE_WARNIG:	return "smTRANSCODE_MODULE_WARNIG"; break;
	case smTRANSCODE_UPDATE_CINFO:	return "smTRANSCODE_UPDATE_CINFO"; break;
	case smTRANSCODE_OPENMONSTER:	return "smTRANSCODE_OPENMONSTER"; break;
	case smTRANSCODE_WARPFIELD:	return "smTRANSCODE_WARPFIELD"; break;
	case smTRANSCODE_TRADEITEMS:	return "smTRANSCODE_TRADEITEMS"; break;
	case smTRANSCODE_TRADE_REQUST:	return "smTRANSCODE_TRADE_REQUST"; break;
	case smTRANSCODE_TRADE_ITEMKEY:	return "smTRANSCODE_TRADE_ITEMKEY"; break;
	case smTRANSCODE_TRADE_READYITEM:	return "smTRANSCODE_TRADE_READYITEM"; break;
	case smTRANSCODE_SKILL_MENU:	return "smTRANSCODE_SKILL_MENU"; break;
	case smTRANSCODE_WAREHOUSE:	return "smTRANSCODE_WAREHOUSE"; break;
	case smTRANSCODE_OPEN_WAREHOUSE:	return "smTRANSCODE_OPEN_WAREHOUSE"; break;
	case smTRANSCODE_OPEN_MIXITEM:	return "smTRANSCODE_OPEN_MIXITEM"; break;
	case smTRANSCODE_OPEN_COLLECT:	return "smTRANSCODE_OPEN_COLLECT"; break;
	case smTRANSCODE_COLLECTMONEY:	return "smTRANSCODE_COLLECTMONEY"; break;
	case smTRANSCODE_PLAYERINFO_Q:	return "smTRANSCODE_PLAYERINFO_Q"; break;
	case smTRANSCODE_OPEN_AGING:	return "smTRANSCODE_OPEN_AGING"; break;
	case smTRANSCODE_SKIL_ATTACKUSER:	return "smTRANSCODE_SKIL_ATTACKUSER"; break;
	case smTRANSCODE_OPEN_EVENTGIFT:	return "smTRANSCODE_OPEN_EVENTGIFT"; break;
	case smTRANSCODE_PLAYERINFO:	return "smTRANSCODE_PLAYERINFO"; break;
	case smTRANSCODE_GETPLAYERINFO:	return "smTRANSCODE_GETPLAYERINFO"; break;
	case smTRANSCODE_FAILCONNECT:	return "smTRANSCODE_FAILCONNECT"; break;
	case smTRANSCODE_PLAYITEM:	return "smTRANSCODE_PLAYITEM"; break;
	case smTRANSCODE_DELITEM:	return "smTRANSCODE_DELITEM"; break;
	case smTRANSCODE_PUTITEM:	return "smTRANSCODE_PUTITEM"; break;
	case smTRANSCODE_THROWITEM:	return "smTRANSCODE_THROWITEM"; break;
	case smTRANSCODE_SHOP_ITEMLIST:	return "smTRANSCODE_SHOP_ITEMLIST"; break;
	case smTRANSCODE_SAVETHROWITEM:	return "smTRANSCODE_SAVETHROWITEM"; break;
	case smTRANSCODE_SAVETHROWMONEY:	return "smTRANSCODE_SAVETHROWMONEY"; break;
	case smTRANSCODE_SAVETHROWITEM2:	return "smTRANSCODE_SAVETHROWITEM2"; break;
	case smTRANSCODE_PLAYERKILLING:	return "smTRANSCODE_PLAYERKILLING"; break;
	case smTRANSCODE_GETITEM:	return "smTRANSCODE_GETITEM"; break;
	case smTRANSCODE_USEITEM_CODE:	return "smTRANSCODE_USEITEM_CODE"; break;
	case smTRANSCODE_COMMAND_USER:	return "smTRANSCODE_COMMAND_USER"; break;
	case smTRANSCODE_WING_NPC:	return "smTRANSCODE_WING_NPC"; break;
	case smTRANSCODE_PAYMENT_MONEY:	return "smTRANSCODE_PAYMENT_MONEY"; break;
	case smTRANSCODE_MEDIA_NPC:	return "smTRANSCODE_MEDIA_NPC"; break;
	case smTRANSCODE_ADD_STARTPOSI:	return "smTRANSCODE_ADD_STARTPOSI"; break;
	case smTRANSCODE_DEL_STARTPOSI:	return "smTRANSCODE_DEL_STARTPOSI"; break;
	case smTRANSCODE_ADD_NPC:	return "smTRANSCODE_ADD_NPC"; break;
	case smTRANSCODE_DEL_NPC:	return "smTRANSCODE_DEL_NPC"; break;
	case smTRANSCODE_ADMIN_COPYCHAR:	return "smTRANSCODE_ADMIN_COPYCHAR"; break;
	case smTRANSCODE_PARTY_UPDATE:	return "smTRANSCODE_PARTY_UPDATE"; break;
	case smTRANSCODE_PARTY_REQUEST:	return "smTRANSCODE_PARTY_REQUEST"; break;
	case smTRANSCODE_PARTY_JOIN:	return "smTRANSCODE_PARTY_JOIN"; break;
	case smTRANSCODE_PARTY_PLAYUPDATE:	return "smTRANSCODE_PARTY_PLAYUPDATE"; break;
	case smTRANSCODE_PARTY_RELEASE:	return "smTRANSCODE_PARTY_RELEASE"; break;
	case smTRANSCODE_PARTY_COMMAND:	return "smTRANSCODE_PARTY_COMMAND"; break;
	case smTRANSCODE_OPEN_MIXTURE_RESET:	return "smTRANSCODE_OPEN_MIXTURE_RESET"; break;
	case smTRANSCODE_PCBANG_PET:	return "smTRANSCODE_PCBANG_PET"; break;
	case smTRANSCODE_PHENIX_PET:	return "smTRANSCODE_PHENIX_PET"; break;
	case smTRANSCODE_HELP_PET:	return "smTRANSCODE_HELP_PET"; break;
	case smTRANSCODE_SERVER_INFO:	return "smTRANSCODE_SERVER_INFO"; break;
	case smTRANSCODE_PARTY_POTION:	return "smTRANSCODE_PARTY_POTION"; break;
	case smTRANSCODE_HEALING:	return "smTRANSCODE_HEALING"; break;
	case smTRANSCODE_HOLYMIND:	return "smTRANSCODE_HOLYMIND"; break;
	case smTRANSCODE_GRAND_HEALING:	return "smTRANSCODE_GRAND_HEALING"; break;
	case smTRANSCODE_VAMPRIC_CUSPID:	return "smTRANSCODE_VAMPRIC_CUSPID"; break;
	case smTRANSCODE_VAMPRIC_CUSPID_EX:	return "smTRANSCODE_VAMPRIC_CUSPID_EX"; break;
	case smTRANSCODE_MANA_RECHARGING:	return "smTRANSCODE_MANA_RECHARGING"; break;
	case smTRANSCODE_RECORD_TRADE:	return "smTRANSCODE_RECORD_TRADE"; break;
	case smTRANSCODE_NETWORK_QUALITY:	return "smTRANSCODE_NETWORK_QUALITY"; break;
	case smTRANSCODE_PROCESSINFO:	return "smTRANSCODE_PROCESSINFO"; break;
	case smTRANSCODE_CLOSECLIENT:	return "smTRANSCODE_CLOSECLIENT"; break;
	case smTRANSCODE_CHECKIP:	return "smTRANSCODE_CHECKIP"; break;
	case smTRANSCODE_SAVECLIENT:	return "smTRANSCODE_SAVECLIENT"; break;
	case smTRANSCODE_EFFECT_ITEM:	return "smTRANSCODE_EFFECT_ITEM"; break;
	case smTRANSCODE_EFFECT_WEAPON:	return "smTRANSCODE_EFFECT_WEAPON"; break;
	case smTRANSCODE_EFFECT_STUN:	return "smTRANSCODE_EFFECT_STUN"; break;
	case smTRANSCODE_EFFECT_CURSE:	return "smTRANSCODE_EFFECT_CURSE"; break;
	case smTRANSCODE_EFFECT_ICE:	return "smTRANSCODE_EFFECT_ICE"; break;
	case smTRANSCODE_EFFECT_POISION:	return "smTRANSCODE_EFFECT_POISION"; break;
	case smTRANSCODE_EFFECT_VANISH:	return "smTRANSCODE_EFFECT_VANISH"; break;
	case smTRANSCODE_EFFECT_PERSHOP:	return "smTRANSCODE_EFFECT_PERSHOP"; break;
	case smTRANSCODE_EFFECT_LOWPET:	return "smTRANSCODE_EFFECT_LOWPET"; break;
	case smTRANSCODE_EFFECT_CLANMGR:	return "smTRANSCODE_EFFECT_CLANMGR"; break;
	case smTRANSCODE_EFFECT_FORCEORB:	return "smTRANSCODE_EFFECT_FORCEORB"; break;
	case smTRANSCODE_EFFECT_CURSE_QUEST:	return "smTRANSCODE_EFFECT_CURSE_QUEST"; break;
	case smTRANSCODE_EFFECT_BLESS_SCORE:	return "smTRANSCODE_EFFECT_BLESS_SCORE"; break;
	case smTRANSCODE_EFFECT_KEEPSKILL:	return "smTRANSCODE_EFFECT_KEEPSKILL"; break;
	case smTRANSCODE_CONT_OBJSERIAL:	return "smTRANSCODE_CONT_OBJSERIAL"; break;
	case smTRANSCODE_MESSAGEBOX:	return "smTRANSCODE_MESSAGEBOX"; break;
	case smTRANSCODE_FUNCERROR:	return "smTRANSCODE_FUNCERROR"; break;
	case smTRANSCODE_FUNCTION_MEM2:	return "smTRANSCODE_FUNCTION_MEM2"; break;
	case smTRANSCODE_SET_BLACKLIST2:	return "smTRANSCODE_SET_BLACKLIST2"; break;
	case smTRANSCODE_SET_BLACKLIST3:	return "smTRANSCODE_SET_BLACKLIST3"; break;
	case smTRANSCODE_BAD_PLAYER:	return "smTRANSCODE_BAD_PLAYER"; break;
	case smTRANSCODE_FIX_ATTACK:	return "smTRANSCODE_FIX_ATTACK"; break;
	case smTRANSCODE_DEAD_PLAYER:	return "smTRANSCODE_DEAD_PLAYER"; break;
	case smTRANSCODE_CLIENT_ERROR:	return "smTRANSCODE_CLIENT_ERROR"; break;
	case smTRANSCODE_INVEN_ERR_ITEM:	return "smTRANSCODE_INVEN_ERR_ITEM"; break;
	case smTRANSCODE_INVEN_ERR_MONEY:	return "smTRANSCODE_INVEN_ERR_MONEY"; break;
	case smTRANSCODE_INVEN_POSITION:	return "smTRANSCODE_INVEN_POSITION"; break;
	case smTRANSCODE_INVEN_POSITION2:	return "smTRANSCODE_INVEN_POSITION2"; break;
	case smTRANSCODE_ENCODE_PACKET:	return "smTRANSCODE_ENCODE_PACKET"; break;
	case smTRANSCODE_ENCODE_PACKET2:	return "smTRANSCODE_ENCODE_PACKET2"; break;
	case smTRANSCODE_OPEN_CLANMENU:	return "smTRANSCODE_OPEN_CLANMENU"; break;
	case smTRANSCODE_OPEN_STARPOINT:	return "smTRANSCODE_OPEN_STARPOINT"; break;
	case smTRANSCODE_STARPOINT:	return "smTRANSCODE_STARPOINT"; break;
	case smTRANSCODE_OPEN_GIVEMONEY:	return "smTRANSCODE_OPEN_GIVEMONEY"; break;
	case smTRANSCODE_GIVEMONEY:	return "smTRANSCODE_GIVEMONEY"; break;
	case smTRANSCODE_CLANMONEY:	return "smTRANSCODE_CLANMONEY"; break;
	case smTRANSCODE_ITEM_EXPRESS:	return "smTRANSCODE_ITEM_EXPRESS"; break;
	case smTRANSCODE_OPEN_MYSHOP:	return "smTRANSCODE_OPEN_MYSHOP"; break;
	case smTRANSCODE_CALL_MYSHOP:	return "smTRANSCODE_CALL_MYSHOP"; break;
	case smTRANSCODE_MYSHOP_ITEM:	return "smTRANSCODE_MYSHOP_ITEM"; break;
	case smTRANSCODE_MYSHOP_MESSAGE:	return "smTRANSCODE_MYSHOP_MESSAGE"; break;
	case smTRANSCODE_MYSHOP_TRADE:	return "smTRANSCODE_MYSHOP_TRADE"; break;
	case smTRANSCODE_EFFECT_PCBANGPET:	return "smTRANSCODE_EFFECT_PCBANGPET"; break;
	case smTRANSCODE_ADMINMODE2:	return "smTRANSCODE_ADMINMODE2"; break;
	case smTRANSCODE_CHECK_NETSTATE20:	return "smTRANSCODE_CHECK_NETSTATE20"; break;
	case smTRANSCODE_CHECK_EXPMONEY:	return "smTRANSCODE_CHECK_EXPMONEY"; break;
	case smTRANSCODE_CHECK_EXPDATA:	return "smTRANSCODE_CHECK_EXPDATA"; break;
	case smTRANSCODE_FORCEORB_DATA:	return "smTRANSCODE_FORCEORB_DATA"; break;
	case smTRANSCODE_PRIMEITEM_DATA:	return "smTRANSCODE_PRIMEITEM_DATA"; break;
	case smTRANSCODE_PRIMEITEM_DATA2:	return "smTRANSCODE_PRIMEITEM_DATA2"; break;
	case smTRANSCODE_PRIMEITEM_DATA3:	return "smTRANSCODE_PRIMEITEM_DATA3"; break;
	case smTRANSCODE_BOOSTER_DATA:	return "smTRANSCODE_BOOSTER_DATA"; break;
	case smTRANSCODE_AGING_DATA:	return "smTRANSCODE_AGING_DATA"; break;
	case smTRANSCODE_SKILLDELAY_DATA:	return "smTRANSCODE_SKILLDELAY_DATA"; break;
	case smTRANSCODE_SEND_DATASERVER:	return "smTRANSCODE_SEND_DATASERVER"; break;
	case smTRANSCODE_SEND_GAMESERVER:	return "smTRANSCODE_SEND_GAMESERVER"; break;
	case smTRANSCODE_SEND_AREASERVER:	return "smTRANSCODE_SEND_AREASERVER"; break;
	case smTRANSCODE_SEND_AGAME_SERVER:	return "smTRANSCODE_SEND_AGAME_SERVER"; break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2:	return "smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2"; break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3:	return "smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3"; break;
	case smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4:	return "smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4"; break;
	case smTRANSCODE_CRAFTITEM:	return "smTRANSCODE_CRAFTITEM"; break;
	case smTRANSCODE_AGINGITEM:	return "smTRANSCODE_AGINGITEM"; break;
	case smTRANSCODE_AGING_UPGRADE:	return "smTRANSCODE_AGING_UPGRADE"; break;
	case smTRANSCODE_MAKE_LINKCORE:	return "smTRANSCODE_MAKE_LINKCORE"; break;
	case smTRANSCODE_USE_LINKCORE:	return "smTRANSCODE_USE_LINKCORE"; break;
	case smTRANSCODE_WINGITEM:	return "smTRANSCODE_WINGITEM"; break;
	case smTRANSCODE_SHOPTITEM:	return "smTRANSCODE_SHOPTITEM"; break;
	case smTRANSCODE_SHOP_SELLITEM:	return "smTRANSCODE_SHOP_SELLITEM"; break;
	case smTRANSCODE_ITEM_FORCEORB:	return "smTRANSCODE_ITEM_FORCEORB"; break;
	case smTRANSCODE_QUEST_COMMAND:	return "smTRANSCODE_QUEST_COMMAND"; break;
	case smTRANSCODE_EXITINFO_URL:	return "smTRANSCODE_EXITINFO_URL"; break;
	case smTRANSCODE_CHECKITEM:	return "smTRANSCODE_CHECKITEM"; break;
	case smTRANSCODE_ERRORITEM:	return "smTRANSCODE_ERRORITEM"; break;
	case smTRANSCODE_CLEARPOTION:	return "smTRANSCODE_CLEARPOTION"; break;
	case smTRANSCODE_CHECK_ITEMMESH:	return "smTRANSCODE_CHECK_ITEMMESH"; break;
	case smTRANSCODE_CLIENT_FUNCPOS:	return "smTRANSCODE_CLIENT_FUNCPOS"; break;
	case smTRANSCODE_GETCLIENT_FUNCPOS:	return "smTRANSCODE_GETCLIENT_FUNCPOS"; break;
	case smTRANSCODE_FUNCTION_MEM:	return "smTRANSCODE_FUNCTION_MEM"; break;
	case smTRANSCODE_FUNCTON_RESULT:	return "smTRANSCODE_FUNCTON_RESULT"; break;
	case smTRANSCODE_PROCESS_TIMEMAX:	return "smTRANSCODE_PROCESS_TIMEMAX"; break;
	case smTRANSCODE_NSPRITE:	return "smTRANSCODE_NSPRITE"; break;
	case smTRANSCODE_NPROTECT:	return "smTRANSCODE_NPROTECT"; break;
	case smTRANSCODE_GAMEGUARD_AUTH:	return "smTRANSCODE_GAMEGUARD_AUTH"; break;
	case smTRANSCODE_REC_DAMAGEDATA:	return "smTRANSCODE_REC_DAMAGEDATA"; break;
	case smTRANSCODE_SOD_RESULT:	return "smTRANSCODE_SOD_RESULT"; break;
	case smTRANSCODE_SOD_RESULT2:	return "smTRANSCODE_SOD_RESULT2"; break;
	case smTRANSCODE_PARTY_SKILL:	return "smTRANSCODE_PARTY_SKILL"; break;
	case smTRANSCODE_CANCEL_SKILL:	return "smTRANSCODE_CANCEL_SKILL"; break;
	case smTRANSCODE_PROCESS_SKILL:	return "smTRANSCODE_PROCESS_SKILL"; break;
	case smTRANSCODE_PROCESS_SKILL2:	return "smTRANSCODE_PROCESS_SKILL2"; break;
	case smTRANSCODE_PROCESS_CLAN_SKILL:	return "smTRANSCODE_PROCESS_CLAN_SKILL"; break;
	case smTRANSCODE_UPDATEL_SKILL:	return "smTRANSCODE_UPDATEL_SKILL"; break;
	case smTRANSCODE_SUCCESS_EVATION:	return "smTRANSCODE_SUCCESS_EVATION"; break;
	case smTRANSCODE_RESISTANCE:	return "smTRANSCODE_RESISTANCE"; break;
	case smTRANSCODE_PUBLIC_POLLING:	return "smTRANSCODE_PUBLIC_POLLING"; break;
	case smTRANSCODE_NOTICE_BOX:	return "smTRANSCODE_NOTICE_BOX"; break;
	case smTRANSCODE_HACKTRAP:	return "smTRANSCODE_HACKTRAP"; break;
	case smTRANSCODE_VIRTURAL_POTION:	return "smTRANSCODE_VIRTURAL_POTION"; break;
	case smTRANSCODE_CLAN_SERVICE:	return "smTRANSCODE_CLAN_SERVICE"; break;
	case smTRANSCODE_CLAN_UPDATE:	return "smTRANSCODE_CLAN_SERVICE"; break;
	case smTRANSCODE_QUEST_MESSAGE:	return "smTRANSCODE_QUEST_MESSAGE"; break;
	case smTRANSCODE_DEAD_USER:	return "smTRANSCODE_DEAD_USER"; break;
	case smTRANSCODE_YAHOO_MOTION:	return "smTRANSCODE_YAHOO_MOTION"; break;
	case smTRANSCODE_CHANGE_EVENT:	return "smTRANSCODE_CHANGE_EVENT"; break;
	case smTRANSCODE_CLIENTINFO:	return "smTRANSCODE_CLIENTINFO"; break;
	case smTRANSCODE_WARNING_BLINK_ATT:	return "smTRANSCODE_WARNING_BLINK_ATT"; break;
	case smTRANSCODE_ATTACK_DAMAGE:	return "smTRANSCODE_ATTACK_DAMAGE"; break;
	case smTRANSCODE_RANGE_DAMAGE:	return "smTRANSCODE_RANGE_DAMAGE"; break;
	case smTRANSCODE_ATTACK_RESULT:	return "smTRANSCODE_ATTACK_RESULT"; break;
	case smTRANSCODE_DISP_DAMAGE:	return "smTRANSCODE_DISP_DAMAGE"; break;
	case smTRANSCODE_ATTACKDATA2:	return "smTRANSCODE_ATTACKDATA2"; break;
	case smTRANSCODE_LIMIT_DAMAGE:	return "smTRANSCODE_LIMIT_DAMAGE"; break;
	case smTRANSCODE_WARNING_CLIENT:	return "smTRANSCODE_WARNING_CLIENT"; break;
	case smTRANSCODE_WARNING_SKILL:	return "smTRANSCODE_WARNING_SKILL"; break;
	case smTRANSCODE_COMIC_SKIN:	return "smTRANSCODE_COMIC_SKIN"; break;
	case smTRANSCODE_REC_ADMIN_COMMAND:	return "smTRANSCODE_REC_ADMIN_COMMAND"; break;
	case smTRANSCODE_CHECK_ADMINMODE:	return "smTRANSCODE_CHECK_ADMINMODE"; break;
	case smTRANSCODE_SOD_INFOMATION:	return "smTRANSCODE_SOD_INFOMATION"; break;
	case smTRANSCODE_BLESSCASTLE_INFO:	return "smTRANSCODE_BLESSCASTLE_INFO"; break;
	case smTRANSCODE_BLESSCASTLE_TAX:	return "smTRANSCODE_BLESSCASTLE_TAX"; break;
	case smTRANSCODE_ATTACK_SLASH_LIST:	return "smTRANSCODE_ATTACK_SLASH_LIST"; break;
	case smTRANSCODE_UPDATE_SERVER_PARAM:	return "smTRANSCODE_UPDATE_SERVER_PARAM"; break;
	case smUPDATE_PARAM_LOWUSER_PRESENT:	return "smUPDATE_PARAM_LOWUSER_PRESENT"; break;
	case smTRANSCODE_USER_ID:	return "smTRANSCODE_USER_ID"; break;
	case smTRANSCODE_DAMAGE_ENCODE_MEM:	return "smTRANSCODE_DAMAGE_ENCODE_MEM"; break;
	case smTRANSCODE_DAMAGE_ENCODE_MEM2:	return "smTRANSCODE_DAMAGE_ENCODE_MEM2"; break;
	case smTRANSCODE_PACKET_DYNFUNC:	return "smTRANSCODE_PACKET_DYNFUNC"; break;
	case smTRANSCODE_AREA_SERVER_MAP:	return "smTRANSCODE_AREA_SERVER_MAP"; break;
	case smTRANSCODE_OPEN_SMELTING:	return "smTRANSCODE_OPEN_SMELTING"; break;
	case smTRANSCODE_SMELTINGITEM:	return "smTRANSCODE_SMELTINGITEM"; break;
	case smTRANSCODE_OPEN_MANUFACTURE:	return "smTRANSCODE_OPEN_MANUFACTURE"; break;
	case smTRANSCODE_MANUFACTURE:	return "smTRANSCODE_MANUFACTURE"; break;
	case smTRANSCODE_MANUFACTURE_WEIGHT_PRICE:	return "smTRANSCODE_MANUFACTURE_WEIGHT_PRICE"; break;
	case smTRANSCODE_GIFTBOX_MONEY:	return "smTRANSCODE_GIFTBOX_MONEY"; break;
	case smTRANSCODE_PREMIUMITEM_INIT:	return "smTRANSCODE_PREMIUMITEM_INIT"; break;
	case smTRANSCODE_MIXTURE_RESET_ITEM:	return "smTRANSCODE_MIXTURE_RESET_ITEM"; break;
		
	}

	return "UNKNOW_TRANSCODE";
}
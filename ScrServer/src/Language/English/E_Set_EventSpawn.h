





#define		EVENTSPAWN_PLAYING_TIME		15			

#define		EVENTSPAWN_OPEN_TIME		60			




static POINT EventSpawn_42_Posi = { -3647, -46307 };			
static int  EventSpawn_42_Range = 350;					


static char *szEventSpawn_Order42[][3] = {
	{ "イビエドクビラ", "?殿秘書 : 主はただ今外出しております。また後程いらしていただけますか？" , "?殿?ス : 我と戦いたいなら、まず我の部下を?してみろ！そうしたら相手をしてやる！" },
	{ "イクワクブラ", "?殿秘書 : 主はただ今外出しております。また後程いらしていただけますか？" , "?殿?ス : 我と戦いたいなら、まず我の部下を?してみろ！そうしたら相手をしてやる！" },
	{ "クベルティグヒ", "?殿秘書 : 主はただ今外出しております。また後程いらしていただけますか？" , "?殿?ス : 我と戦いたいなら、まず我の部下を?してみろ！そうしたら相手をしてやる！" },
	{ 0,0 }
};


sHCORE_MONSTER	sHCore_EventSpawn42 =

	{ { "呪われた???" , 0, 45 },		{ "呪われたオ??", 0, 30 },		{ "呪われたキングホピ?", 0, 20 },		{ "呪われたメトロン", 0, 5 },		{ "", 0, 0 },	100,					10,						0,			3,			10 };   
	





sHCORE_MONSTER	sHCore_EventSpawn42_Boss[] = {
	{ { "呪われたウイッ?", 0, 25 }		, { "呪われた インキュバス" , 0, 25 }	, { "呪われたウイッ?", 0, 25 }		, { "呪われたインキュバス" , 0, 25 }	, { "", 0, 0 }	, 100 , 0 , 80   , 1 , 0},
	{ { "呪われたサキュバス", 0, 25 }	, { "呪われたｲﾝｷｭﾊﾞｽｻﾏﾅ?"   , 0, 25 }	, { "呪われたサキュバス", 0, 25 }	, { "呪われたｲﾝｷｭﾊﾞｽｻﾏﾅ?"   , 0, 25 }	, { "", 0, 0 }	, 100 , 0 , 179   , 1 , 0},
	{ { "呪われたスティジアン", 0, 25 }	, { "呪われたカオスカラ"     , 0, 25 }	, { "呪われたスティジアン", 0, 25 }	, { "呪われたカオスカラ"     , 0, 25 }	, { "", 0, 0 }	, 100 , 0 , 1000 , 1 , 0},
	{ { "", 0, 20 }						, { "", 0, 20 }			      		, { "", 0, 40 }						, { "" , 0, 20 }					, { "", 0, 0 }	, 100 , 0 , 50   , 1 , 0},										
	{ { "" , 0, 0 } 					, { "", 0, 0 } 						, { "", 0, 0 } 						, { "", 0, 0 } 						, { "", 0, 0 }	, 0	  , 0 , 0    , 0 , 0}
};

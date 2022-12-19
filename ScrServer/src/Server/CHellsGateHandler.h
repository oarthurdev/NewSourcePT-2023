#pragma once

#define MAX_EVENT_INFO 10
#define MAX_MONSTER_INFO 20

enum HGState
{
	STATE_STOP,
	STATE_HG_INIT,
	STATE_HG_START,
	STATE_HG_END
};

struct sEventInfo
{
	int nHora;
	int nTempo;
	int nPLimite;
	int nMLimite;
	char szItemID[32];
};

struct sMonsterInfo
{
	char sBoss[32];
	char sMob[4][32];
};

struct sPlayerInfo
{
	char PlayerID[32];
	char PlayerIP[32] = { 0 };
	char PlayerName[32];
	DWORD dwObjectSerial;
};

class CHellsGate
{
private:
	bool							m_bEventFlag;		//Flag //true quando abre arena, false quando finaliza
	int								m_nState;			//HGState
	int								m_nEventIndex;		//Index do evento atual no vector m_vHellsGateInfo
	int								m_nEventStage;		//Estagio de Boss
	DWORD							m_dwEventTime;		//Tempo do Evento
	DWORD							m_dwDelayTime;		//Tempo de Espera

	std::vector<sEventInfo>			m_vHellsGateInfo;	//Informações do evento //SQL
	std::vector<sMonsterInfo>       m_vMonsterInfo;		//Informações do evento //SQL
	std::vector<sPlayerInfo*>		m_vPlayersInfo;		//Players participando do evento

	bool							m_bNpcFlag;			//NPC
	smCHAR*							m_lpCharEventNpc;	//NPC
	smTRNAS_PLAYERINFO				m_smTransNpcInfo;	//NPC

	smCHAR*							m_lpCharBoss;		//Boss ativo
	std::vector<smCHAR*>			m_vlpCharMonster;	//Monstros ativos
	
	//Adiciona NPC na cidade
	void AddNpc();

	//Remove o NPC
	void DelNpc();

	//Summona Boss e Mobs
	void AddMonster(int nStageIndex);

	//Elimina o Boss vivo, se ouver
	void KillBoss();

	//Elimina todos monstros vivos
	void KillMonster();

	//Envia informações do estágio
	void SendNextStage(rsPLAYINFO* lpPlayInfo);

public:
	CHellsGate();
	~CHellsGate();

	static CHellsGate* GetInstance() { static CHellsGate instance; return &instance; };

	void SetEventFlag(bool bflag) { m_bEventFlag = bflag; };
	bool GetEventFlag() { return m_bEventFlag; };

	//Carrega informações do SQL
	void Init();

	//Main
	void Main();

	//Adiciona Player, e teleporta pro evento
	void Accept(rsPLAYINFO* lpPlayInfo);

	//Eviar Premiação 
	void Reward();

	//Teleporta Player pra arena
	void Teleport(rsPLAYINFO* lpPlayInfo);
};

#define CHellsGateHandler CHellsGate::GetInstance()
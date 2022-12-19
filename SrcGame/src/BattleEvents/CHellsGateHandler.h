#pragma once

using TextureID = int;

class CHellsGate
{
public:
	CHellsGate();
	~CHellsGate();

	static CHellsGate* GetInstance() { static CHellsGate inst; return &inst; };

	void Init();
	void Main();
	void Draw();

	void RecvNextStage(smTRANS_HGINFO* lpTransHgInfo);

private:
	bool		m_bEventFlag;
	int			m_nStage;
	DWORD		m_dwBossSerial;
	DWORD		m_dwEventTime;
	DWORD		m_dwDelayTime;
	TextureID	m_LifeBar[2];

	char m_szBossName[32];
};

#define CHellsGateHandler CHellsGate::GetInstance()
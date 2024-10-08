

#define   SIN_ADD_FIRE			0x00000001	
#define   SIN_ADD_ICE			0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO			0x00000010	
#define   SIN_ADD_Critico			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE			0x00004000	
#define   SIN_ADD_MANA			0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000 	
#define   SIN_ADD_MANAREGEN		0x00040000  	
#define   SIN_ADD_STAMINAREGEN		0x00080000  	

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2



//____________________________________ MIX DEVINE BOTAS ____________________________________

{ {sinDB1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 40,1.5f,1.0f,30,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0 }, // Quantidade de atributos
"Defesa+40\rAbsor��o+1.5\rVelocidade+1.0\r30+HP\r" }, // Texto dos mix finalizado

//____________________________________ MIX CELESTO BOTAS ____________________________________

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 60,2.5f,2.0f,60,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0 }, // Quantidade de atributos
"Defesa+60\rAbsor��o+2.5\rVelocidade+2.0\r60+HP\r" }, // Texto dos mix finalizado

//____________________________________ MIX DEVINE LUVAS ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 40,1.5f,30,0,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa+40\rAbsor��o+1.5\rHP+30\r" }, // Texto dos mix finalizado

//____________________________________ MIX CELESTO LUVAS ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 60,2.5f,60,0,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa+60\rAbsor��o+2.5\rHP+60\r" }, // Texto dos mix finalizado

//____________________________________ MIX DEVINE BRACELETE ____________________________________

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ATTACK_RATE, SIN_ADD_DEFENCE, SIN_ADD_LIFE, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 50,60,40,0,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Taxa de Ataque+50\rDefesa+60\rHP+40\r" }, // Texto dos mix finalizado

//____________________________________ MIX (Celesto) BRACELETE ____________________________________
{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ATTACK_RATE, SIN_ADD_DEFENCE, SIN_ADD_LIFE, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 80,90,60,0,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Taxa de Ataque+80\rDefesa+90\rHP+60\r" }, // Texto dos mix finalizado

////____________________________________ MIX DEVINE Amuletos ____________________________________
//{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
//{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
//{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, SIN_ADD_LIFEREGEN, SIN_ADD_MANAREGEN, 0, 0, 0 }, // Define dos Atributos do Mix
//{ 20,20,20,1.0f,1.0f,0,0,0 }, // N�meros dos Atributos do Mix
//{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
//"HP+20\rMP+20\rST+20\rHP+1.0REG\rMP+1.0REG\r" }, // Texto dos mix finalizado
//
////____________________________________ MIX Celesto Amuletos ____________________________________
//
//{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
//{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
//{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, SIN_ADD_LIFEREGEN, SIN_ADD_MANAREGEN, 0, 0, 0 }, // Define dos Atributos do Mix
//{ 40,40,40,2.0f,2.0f,0,0,0 }, // N�meros dos Atributos do Mix
//{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
//"HP+40\rMP+40\rST+40\rHP+2.0REG\rMP+2.0REG\r" }, // Texto dos mix finalizado
//
////____________________________________ MIX DEVINE RINGS ____________________________________
//{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
//{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
//{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, 0, 0, 0 }, // Define dos Atributos do Mix
//{ 20,20,20,1,1,0,0,0 }, // N�meros dos Atributos do Mix
//{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
//"HP+20\rMP+20\rST+20\rAtaque Min+1\rAtaque Max+1\r" }, // Texto dos mix finalizado//______________________________________________________________________________________
////____________________________________ MIX CELESTO RINGS ____________________________________
//{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compat�veis para o mix
//{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
//{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, 0, 0, 0 }, // Define dos Atributos do Mix
//{ 40,40,40,2,2,0,0,0 }, // N�meros dos Atributos do Mix
//{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
//"HP+40\rMP+40\rST+20\rAtaque Min+2\rAtaque Max+2\r" }, // Texto dos mix finalizado

//____________________________________ MIX ARMAS (Devine) ____________________________________

{ {sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1}, // Itens compat�veis para o mix
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_Critico,SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,0 }, // Define dos Atributos do Mix
{ 50,10,10,3,30,30,30,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0 }, // Quantidade de atributos
"Taxa de Ataque +50\rAtaque Min+10\rAtaque Max+10\rCritico +3%\rHP+30\rMP+30\rRS+30" }, // Texto dos mix finalizado

//____________________________________ MIX ARMAS (Celesto) ____________________________________
{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_Critico,SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,0 }, // Define dos Atributos do Mix
{ 70,12,12,5,50,50,50,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0 }, // Quantidade de atributos
"Taxa de Ataque +70\rAtaque Min+12\rAtaque Max+12\rCritico +5%\rHP+50\rMP+50\rRS+50" }, // Texto dos mix finalizado

//____________________________________ ARMADURAS E ROUBES (Devine)______________________________

{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_BLOCK_RATE, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 90,4.0f,50,3,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 }, // Quantidade de atributos
"Defesa+90\rAbsor��o+4.0\rHP+50\rBlock 3%\r" }, // Texto dos mix finalizado

//____________________________________ ARMADURAS E ROUBES (Celesto)______________________________


{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_BLOCK_RATE, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 150,6.0f,75,5,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 }, // Quantidade de atributos
"Defesa+150\rAbsor��o+6.0\rHP+75\rBlock 5%\r" }, // Texto dos mix finalizado	

//____________________________________ MIX ESCUDOS/ORBITAIS (Devine) ____________________________________
{ { sinDS1,sinOM1,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,1,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, SIN_ADD_ABSORB, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 50,3,30,2.0f,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0 }, // Quantidade de atributos
"Defesa+50\rBlock+3%\rHP+30\rAbsor��o+2.0\r" }, // Texto dos mix finalizado

//____________________________________MIX ESCUDOS/ORBITAIS (celesto)____________________________________

{ { sinDS1,sinOM1,0,0,0,0,0,0 }, // Itens compat�veis para o mix
{ 0,0,0,0,0,1,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, SIN_ADD_ABSORB, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 90,5,50,4.0f,0,0,0,0 }, // N�meros dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0 }, // Quantidade de atributos
"Defesa+90\rBlock+5%\rHP+50\rAbsor��o+4.0\r" }, // Texto dos mix finalizado
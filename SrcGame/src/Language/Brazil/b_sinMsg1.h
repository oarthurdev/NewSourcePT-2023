

#include "sinLinkHeader.h"

sMESSAGEBOX	sMessageBox[100] = {
	{" No hay suficiente espacio en el inventario "},
	{" Has excedido el l�mite de peso del inventario "},
	{" El objeto no puede ser utilizado todav�a "},
	{" No hay suficiente oro "},
	{" El objeto no se puede mezclar "},
	{" Excede el n�mero  m�ximo de objetos de transacci�n "},
	{" Transacci�n cancelada "},
	{" Las pociones no se pueden depositar "},
	{" La Mezcla de objetos ha fallado "},
	{" Gracias por su generosa donaci�n"},
	{" Demasiados objetos en el dep�sito "},
	{" El objeto no puede ser Madurado "},
	{" El objeto ha cambiado. Por favor, controlar "},
	{" Excede el monto m�ximo de posesi�n de oro "},
	{" La Maduraci�n del objeto ha fallado "},
	{" Las estad�sticas se han reseteado "},
	{" La imagen del objeto no est� preparada "},
	{" S�lo se puede resetear una vez "},
	{" S�lo los miembros del clan pueden utilizar este objeto "},
	{" Debes estar en un clan para utilizar este objeto "},
	{" Imposible transferir debido a restricci�n de nivel "},
	{" El nivel de Maduraci�n ha sido disminuido en -1 "},
	{" El nivel de Maduraci�n ha sido disminuido en -2 "},
	{" El nivel de Maduraci�n ha sido aumentado en +1 "},
	{" El nivel de Maduraci�n ha sido aumentado en +2 "},
	{" Velocidad de ATK del objeto en misi�n disminuida "},
	{"   Subir de nivel el objeto en misi�n    "},
	{"   HP incrementado +15 "},
	{"   El rompecabezas est� completado    "},
	{"   El rompecabezas est� equivocado    "},
	{"   No hay m�s objetos para vender  "},
	{" El objeto ya fue vendido "},
	{" La tienda privada del vendedor est� cerrada "},
	{"   No se encuentra al vendedor   "},
	{"    N�mero incorrecto de objetos     "},
	{"    El personaje masculino no puede usar    "},
	{"    El personaje femenino no puede usar    "},
	{" El personaje femenino no puede adquirir el objeto "},
	{" El personaje masculino no puede adquirir el objeto "},
	{"    El precio del objeto ha cambiado  "},
	{"    No hay dinero de premio del clan     "},
	{"  Tu nivel no puede usar el Orbe  "},
	{"     El Orbe est� en uso ahora   "},
	{"     La funci�n ATK POW est?siendo probada    "},
	{"    La Maduraci�n del Orbe de Fuerza ha sido completada    "},
	{"    Puntos stadisticas incrementados en 5    "},
	{"    Puntos de habilidad incrementados en 1    "},
	{"  Puntos de stat y habilidad incrementados en 5 y 1 "},
	{"  Puntos de stat y habilidad incrementados en 5 y 2 "},
	{"    Exp. de pena de muerte disminuido en 1  "},
	{"   Vitalidad incrementada en 40   " },
	{" Est� en una Misi�n " },
	{" Sobre nivel 80, obtendr� 7 puntos stat en cada nivel. " },
	{" Sobre nivel 90, obtendr� 10 puntos stat en cada nivel. " },
	{" Reconfigura tus n?eros para entrenamiento. " },
	{" La misi�n fall� por exceso en el tiempo. " },
	{" Demasiados soldados mercenarios. "},
	{" Est� usando un objeto-habilidad. "},
	{" No te puede transferir al Castillo Bless Castle, "},
	{" El objeto no se puede vender a la tienda personal. "},
	{" No hay suficiente monto de impuestos para ser retirado. "},
	{" Ya respondiste la preguntas. "},
	{" Gracias por responder las preguntas. "},
	{" El objeto-sello no corresponde a tu nivel. "},
	{" El objeto fue reconstruido. "},
	{" Gana en la confrontaci�n con Furia. "},
	{" Pierde en la confrontaci�n con Furia. "},
	{" Adquirir objetos en compensaci�n. "},
	{" Los objetos aliados no se pueden usar juntos. "},
	{" Se puede usar m�s tarde "},
	{" Imposible cancelar mientras se mezcla "},
	{" No se puede llevar arma mientras se mezcla "},
	{" Se us� el mismo tipo de Poci�n para Ten�r el Cabello. "},
	{" Se us� el mismo tipo de Poci�n para Ten�r el Cabello. "},
		{"Ha fallado la Fundici�n."},
	{"Ha fallado la Fabricaci�n del objeto."},
	{"En la combinaci�n no puedes mantener los Oros y Cristales."},
	{"En la combinaci�n no puedes mantener las recetas."},
	{" Estas no son del mismo tipo o de cristales o Oro "},
	{" Esta no es la forma correcta de Fabricaci�n."},
};



sMESSAGEBOX2 sMessageBox2[20] = {
	{" �Cu�ntos objetos "," quieres comprar? "},
	{" �Cu�ntos objetos "," quieres vender? "},
	{" �Cu�ntos objetos "," quieres tirar? "},
	{" �Cu�nto oro "," quieres tirar? "},
	{"  ","  "},
	{" �Cu�nto oro "," quieres intercambiar? "},
	{" �Cu�nto oro "," quieres mover? "},
	{" �Cu�nto oro "," quieres recuperar? "},
	{" �Cu�ntas estrellas "," quieres comprar? "},
	{" �Cu�nto oro "," quieres donar? "},
	{" �Quieres registrar"," tu dinero en objetos?  "},
	{" �Cu�ntos objetos "," quieres comprar? "},
	{" �Cu�nto oro "," quieres recuperar? "},
	{" �Quieres "," comprar el objeto? "},
	{" �Quieres "," comprar el objeto? "},
	{" �Cu�nto oro "," quieres retirar? "},
	{" �Cu�ntos mercenarios "," te gustar? comprar? "}

};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{" �Quieres "," adquirir las habilidades? "},
	{" �Quieres ", " hacer rank up? "},
	{" �Quieres ", " llevar a cabo la misi�n? "},
	{" �Quieres "," redistribuir? "},
	{" Cuesta oro "," para el evento "},
	{" �Quieres ","initializar las STATS? "},
	{" �Quieres ", " llevar a cabo la misi�n? "},
	{" �Quieres ", " recibir el objeto? "},
	{" �Quieres ", " registrar el N�cleo de Uni�n? "},
	{" �Quieres ", " recibir el objeto? "},
	{" �Quieres ", " ir a ? "},
	{" "," Por favor tipea el n�mero "},
	{" �Quieres "," comprar un objeto estrella? "},
	{" �Quieres ", " vender el objeto? "},
	{" �Quieres ", " la misi�n? "},
	{" �Quieres ", " pagar la donaci�n? "},
	{" Tienda Privada ", " fffffffffff "},
	{" �Quieres ", "intercambiar el objeto? "},
	{" �Quieres ", "comprar el art�culo?"},
	{" �Quieres ", " cancelar el Registro? "},
	{" �Quieres ", " intercambiar el objeto? "},
	{" �Quieres ", " intercambiar el objeto? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Ad�nde ", " quieres ser teletransportado? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " buscar la misi�n? "},
	{" �Quieres ", " hacer rank up? "},
	{" �Quieres ", " intercambiar el objeto? "},
	{" �Teletransportarse? a ", " alg�n lugar? "},
	{" �te gustar�a comprar "," una torre de  cristal? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " usar este objeto? "},
	{" �Quieres ", " obtener la misi�n? "},
	{" �Quieres ", " recibir el objeto? "},
	{" �Quieres "," ir a la Zona de Batalla? "},
	{" �Quieres ", " Teletransportarte? "},
};


char *SkillMaster[4] = {
	" Aprender Habilidad ",
	" Cambiar Clase ",
	" Salir del Juego "

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	" �Recomenzar desde el campo? ",
	" �Recomenzar desde el pueblo? ",
	" �Salir del Juego? ",
	" No tienes suficiente XP "

};
char *ReStartMsg2[4] = {
	" Pena(Oro/XP) 1% ",
	"",
	"",
	" para permanecer en el campo ",

};

char *SkillUseInfoText[10] = { "    Entrenar Habilidad/Magia     ","    Seleccionar una Habilidad o Magia     ","      Para aprender o entrenar       ","  No tienes suficientes puntos de Habilidad  ","   para aprender o practicar " };
char *sinMsgSkillPoint = "    Puntos de Habilidad : %d";
char *sinMsgEliteSkillPoint = "Puntos de Habilidad de Elite : %d ";
char *sinStateName[5] = { "H P : %d/%d  ","M P : %d/%d  ","STM : %d/%d  ","X P : %d/%d  ","X P : %dM/%dM  " };


char *TownName[3] = {"Llamada para Ricarten\r","Llamada para Navisko\r","Llamada para Pillai\r"};

char *sinAbilityName[50] = {
	"Poder de Ataque: \r",
	"Vel. de Arma: \r",
	"Alcance: \r",
	"Cr�tico: \r",
	"Tasa de Defesa: \r",
	"Tasa de Ataque: \r",
	"Absorci�n: \r",
	"Bloqueo: \r",
	"Velocidad: \r",
	"Integridad: \r",
	"Regen de MP: \r",
	"Regen de HP: \r",
	"Regen de STM: \r",
	"Res. Organica: \r",
	"Nature Type: \r",
	"Res. a Fuego: \r",
	"Res. a Hielo: \r",
	"Res. a Rayo: \r",
	"Res. a Veneno: \r",
	"Water Type: \r",
	"Wind Type: \r",
	"HP Regen: \r",
	"MP Regen: \r",
	"STM Regen: \r",
	"Add. HP: \r",
	"MP Adicional: \r",
	"STM Adicional: \r",
	"Limite de Pociones: \r",
	"N�vel Necesario: \r",
	"Fuerza Necesaria: \r",
	"Inteligencia Necesaria: \r",
	"Talento Necesario: \r",
	"Agilidad Necesaria: \r",
	"Vitalidad Necesaria: \r" 
	"N�vel de Batalla Necesario: \r",
};


char *sinSpecialName[50] = { "Spec. ATK SPD: \r", "Cr�tico Adicional: \r", "Def. Adicional: \r", "Abs Adicional: \r",
"Bloqueo Adicional: \r", "Bonus M�gico: \r", "Vel. Adicional: \r", "R.Org. Adicional: \r", "Spec. Nature: \r",
"R. Fuego Adicional: \r", "R. Hielo Adicional: \r", "R. Rayo Adicional: \r", "R. Veneno Adicional: \r", "R. Agua Adicional: \r", "R. Viento Adicional: \r",
"P. de ATQ Adicional: \r", "Taxa de ATQ ad.: \r", "Spec. RNG: \r", "ATQ Org. Adicional: \r", "Spec. Nature ATK: \r", "ATQ Fogo Adicional: \r", "ATQ Gelo Adicional: \r",
"ATQ Rayo Adicional: \r", "ATQ Veneno Adicional: \r", "ATQ Agua Adicional: \r", "ATQ Viento Adicional: \r", "Bonus HP Max.: \r", "Bonus MP Max.: \r",
"Regen de HP: \r", "Regen de MP: \r", "Regen de STM:\r", "Precio de venta: \r", "Precio: \r" };


char *SpecialName3 = "%s Especial. \r ";
char *MixResultTitle = " Resultado de la Mezcla de Objetos ";
char *NowLevelText = " Nivel Actual\r ";
char *NextLevelText = " Pr�ximo Nivel\r ";

char *NormalAttckName = " Ataque Est�ndar ";
char *RequirLevel = " %s (Nivel Req.:%d)\r ";
char *UseItemGroupName = " Grupo de Objetos Compatible \r ";

char *PoisonName = " Tipo de Veneno:\r ";
char *FireName = " Tipo de Llama:\r ";
char *AttackAreaName = " Rango de Ataque:\r ";
char *Attack_RateName = " Capacidad de Ataque:\r ";
char *Max_DamageIncre = " Aumento M�ximo de Da�o:\r ";
char *DamageAddName = " Aumento de Da�o:\r ";
char *Attack_SpeedAdd = " Aumento de Velocidad de Ataque:\r ";
char *IncreBlock = " Mejora de la Capacidad de Bloqueo:\r ";
char *CountinueTime = " Duraci�n:\r ";
char *UseManaName = " Uso de MP:\r ";
char *DamageName = " Poder de Ataque:\r ";
char *ShootingRangeName = " Rango:\r ";
char *IncreAsorb = " Mejora de la Capacidad de Absorci�n:\r ";
char *SecName = " seg ";
char *PlusDamageName = " Da�o Adicional:\r ";
char *HitNumName = " N�mero de Golpes:\r ";
char *DecreLifeName = " Vida Disminuye:\r ";
char *Attck_RateAdd = " Poder de Ataque Adicional:\r ";
char *Add_CriticalName = " Cr�tico Adicional:\r ";
char *Push_AreaName = " Largo de Distanciamiento:\r ";
char *FireAttackDamageAdd = " Ataque de Llama:\r ";
char *IceName = " Propiedad de Escarcha:\r ";
char *IceAttackDamageAdd = " Ataque de Escarcha:\r ";
char *StuneRate = " Probabilidad de Paralizar:\r ";
char *DefenseRateIncre = " Capacidad de Defensa Incrementa:\r ";
char *WeaponSizeName = " Tama�o del Arma:\r ";
char *HwakRotationNum = " Rotaciones de Halc�n:\r ";
char *WeaponSpeedAddName = " Velocidad Adicional del Arma:\r ";
char *IncreAttack_RateName = "Incremento en la Capacidad de Ataque:\r ";
char *ShootingNumName = " N�mero de Tiros:\r ";
char *SeriesShootingCount = " Fuego Continuo:\r ";
char *UseStaminaName = " Uso de Vigor:\r ";
char *MasterSkillMoneyName = " Costo de la Habilidad:\r ";

char *ItemAgingResult;

char *sinGold = " %dOro ";
char *sinGiveItem5 = " Objeto de Regalo\r ";
char *sinCopyItem5 = " Objeto Copiado\r ";
char *sinNum7 = " RND ";
char *sinSkillPointName = " Punto de Habilidad ";
char *sinG_Pike_Time3 = " Tiempo Congelado:\r ";
char *sinItemLimitTimeOverMsg = " El l�mite de tiempo ha expirado\r ";
char *sinDeadSongPyeunEat = " �Maldici�n! �Es una podrida torta de arroz! ";
char *SmeltingResultTitle = "Resultado de la Fundici�n";
char *ManufactureResultTitle = "Creando";
char *ManufacturingTitle = "al Azar";
char *Expired = "validaci�n vencida";


char *sinMaxDamageAdd = " Incremento el Da�o M�ximo+\r ";
char *sinDamagePiercing = " (Ataque Punzante)\r ";
char *sinAddStamina = " Vigor Agregado:\r ";
char *sinAddLife = " Recuperaci�n de Vida:\r ";

char *sinDamageUndead50 = "50% m�s da�o a unidades de muertos vivos:\r ";
char *sinNumCount2 = " n�mero:\r ";
char *sinNumCount3 = " cantidad\r ";
char *sinDecreDamage = " Disminuci�n de da�o:\r ";
char *sinConvert4 = " �ndice de conversi�n:\r ";
char *sinIncreElement = " Incremento en caracter�stica de elemento:\r ";
char *sinPartyIncreElement = " Miembro del grupo re�ee 50% del incremento del elemento\r ";
char *sinFireBallDamage2 = " (100% de da�o al enemigo objetivo)\r ";
char *sinFireBallDamage3 = " ( crea objetivo 60 (1/3 da�o))\r ";
char *sinAddDamage7 = " da�o agregado:\r ";
char *PlusDamageWeapon = " arma ";
char *SparkDamage = " da�o por unidad:\r ";
char *SparkNum7 = " # de chispa m�ximo:\r ";
char *StunRage = " Rango de Paralizaci�n:\r ";
char *RecvPotion7 = " Poci�n ";


char *PartyArea7 = " �rea del Grupo:\r ";
char *Area17 = " �rea:\r ";
char *AddAttack_Rate9 = " Capacidad de Ataque:\r ";
char *PiercingRange = " Rango de Incisi�n:\r ";
char *IncreDefense = "Increase Defense:\r";
char *AddShootingRange = " Rango Incrementado de SHT:\r ";
char *LifeAbsorb = " Absorci�n de Vida:\r ";
char *FireDamage = " Da�o por Fuego:\r ";
char *IceDamage = " Da�o por Hielo:\r ";
char *LightningDamage = " Da�o por Rayo:\r ";
char *AddManaRegen = " Man� Adicional Regen.:\r ";
char *LightNum = " # de Rayo:\r ";
char *ReturnDamage = " Retorno de Da�o:\r ";
char *Area18 = " Rango disponible:\r ";
char *IncreMana5 = " Incremento de Man�\r ";
char *Area19 = " �rea disponible:\r ";
char *HelpTitle8 = " A Y U D A ";
char *QuestTitle8 = " M I S I � N  ";
char *ResearchTitle8 = " INVESTIGACI�N ";
char *TeleportTitle8 = " TELETRANSPORTE ";

char *IncreWeaponAttack_RateName = " Capacidad de ATK incrementada:\r ";
char *AddMaxDamage = " Da�o m?imo incrementado:\r ";
char *LinkCoreName = " Teletransportar a un miembro del clan\r ";
char *DesLinkCore = " Nombre: ";
char *Itemul = " objeto ";
char *ItemRecvOk = " �Quieres esto? ";
char *Money5 = " oro ";
char *Exp5 = " EXP ";
char *WingItemName[6] = { " Ala de Metal "," Ala de Plata "," Ala de Oro "," Ala Diamante ", " Ala de Caos ", " Ala de Extremo " };
char *WarpGateName[10] = { " Puerta Warp "," Ricarten "," Pillai "," Tierra del Crep�sculo "," Bosque de Bamb�"," Villa de Ruinen "," Pueblo de Navisko "," Tierra Prohibida ", " Villa de Eura ", " Tierra del Caos " };
char *sinWarningName5 = " Atenci�n ";
char *ClanCristalName = " S�lo para miembros del clan\r ";
char *NowMyShopSell = " En venta\r ";
char *SecretNumName = " Ingresar n�meros de autenticaci�n ";
char *MyShopExpDoc7 = " Informaci�n de Tienda ";
char *NotAgingItem2 = " Imposible madurar el objeto ";
char *ExpPercent2 = " EXP : %d.%d%s ";
char *ExpPercent3 = " EXP : %d.0%d%s ";
char *Mutant7 = " Mutante ";
char *Mechanic7 = " Mec�nico ";
char *Demon7 = " Demonio ";
char *Nomal7 = " Normal ";
char *Undead7 = "Muerto Vivo ";
char *MonsterAddDamage2 = " agregar da�o extra)\r ";
char *MonsterAddDamageFire = " agregar da�o de elemento fuego)\r ";
char *HaWarpGateName[] = { " Castillo Bless ",0 };
char *FallGameName = " Bosque Torcido ";
char *EndlessGameName = " Torre Interminable ";
char *TeleportBattleArena1 = " Torre de Batalla ";
char *LookHelp = " m�s?";



char *HoldStarNumDoc = " El n�mero de tus estrellas ";
char *StarItemBuy7 = " Comprar las estrellas ";
char *ChangeMoney7 = "(El precio de una estrella: 100000) ";




char *LightningDamage2 = " Da�o por Rayo:\r ";
char *SheildDefense = " Incrementa Defensa:\r ";

char *DemonDamage4 = " Poder de ATK VS Demonio:\r ";
char *PoisonDamage3 = " Da�o por Veneno:\r ";
char *PikeNum4 = " N�mero de lanza:\r ";
char *poisoningTime = " Tiempo de envenenamiento:\r ";
char *PlusCriticalName = " Incrementa Cr�tico%:\r ";
char *SpiritFalconDamage2 = " Da�o por Esp�ritu Halc�n:\r ";
char *LifeGegenPlus = " Incrementa HP:\r ";
char *PlusDamage4 = " M�s da�o:\r ";
char *PiercingPercent = " Porcentaje de Incisi�n:\r ";
char *DamageToLife = " Da�o a Vida:\r ";
char *MyMonster7 = " Mi monstruo:\r ";
char *LifeIncre4 = " Incremento de vida:\r ";
char *UndeadDamage3 = " Da�o por muerto vivo:\r ";

char *AttackNum3 = " N�mero de ATK:\r ";
char *AttackRateMinus = " Disminuye capacidad de ATK:\r ";
char *MaxDamagePlus2 = " M�ximo Da�o M�s:\r ";
char *LightningAddDamage3 = " Da�o Adicional por Rayo:\r ";
char *ReLifePercent4 = " Re. Porcentaje de Vida:\r ";
char *GetExp3 = " Obtener Exp:\r ";
char *ResurrectionChar4 = " Resurrecci�n Pers. Nivel ";
char *ExtinctionPercent2 = " Porcentaje de Extinci�n:\r ";
char *ExtinctionAmount2 = " Monto de Extinci�n:\r ";
char *IncreLifePercent2 = " Incrementa Porcentaje de Vida:\r ";

char *ReduceDamage3 = " Reduce Da�o:\r ";
char *IncreMagicDamage = " Incrementa Da�o M�gico:\r ";
char *AttackDelay3 = " Retraso de Ataque:\r ";

char *FireDamage2 = " Da�o por Fuego:\r ";
char *IceDamage2 = " Da�o por Hielo:\r ";
char *AddDefense8 = " Defensa adicional:\r ";
char *SkillDamage5 = " Da�o de Habilidad:\r ";

char *FireDamage3 = " Da�o por Fuego:\r ";
char *AddSpeed7 = " Velocidad Agregada:\r ";
char *AfterDamage7 = " Da�o Residual:\r ";
char *MonsterSight7 = " Visi�n de monstruo:\r ";



char *LinghtingAddDamage4 = " Capacidad de ataque adicionas en rayo:\r ";
char *MaxBoltNum4 = " M�s voltaje:\r ";
char *AddAbsorb4 = " �ndice Adicional de absorci�n:\r ";
char *IncreArea4 = " Incrementar rango:\r ";
char *IncreAttack4 = " M�s poder de ataque:\r ";
char *GolemLife4 = " Vida+STR:\r ";


char *SubAbsorb4 = " Disminuye absorci�n:\r ";
char *AreaDamage4 = " Capacidad de ataque para el rango:\r ";
char *MaxAttackNum4 = " M�s. golpes:\r ";
char *LifeUp4 = " Vitalidad adicional:\r ";

char *CriticalAddDamage4 = " Incremento de cr�tico:\r ";
char *MonstervsSubCritical4 = " Debilitar cr�tico de monstruo:\r ";
char *ChargingAddPercentDamage4 = " Capacidad de ataque adicional en carga:\r ";

char *IncreEvasionPercent4 = " Porcentaje de evasi�n:\r ";
char *AddShadowNum4 = " Incrementa combinaci�n ocular:\r ";

char *WolverinLife4 = " Vitalidad:\r ";
char *WolverinRate4 = " Exactitud:\r ";
char *WolverinDefense4 = " �ndice de Defensa:\r ";
char *AddEvasion4 = " Incrementa habilidad de evasi�n:\r ";
char *AddDamage4 = " Incrementa �ndice de ataque(f�sico):\r ";
char *FalconAddDamage4 = " Incrementa �ndica de ataque de halc�n:\r ";


char *IncreAttackAbsorb4 = " Incrementa �ndice de absorci�n:\r ";

char *RectAngleArea4 = " Atacar en �ngulo recto:\r ";

char *MonsterSubSpeed4 = " Velocidad decreciente del monstruo atacado:\r ";


char *AddLifeRegen4 = " Regeneraci�n de vida adicional:\r ";
char *AddManaRegen4 = " Regeneraci�n de man?adicional:\r ";
char *MagicArea4 = " Rango afectado por magia:\r ";
char *ChainNum4 = " N�mero de monstruos afectados:\r ";
char *ChainRange4 = " Furia del monstruo afectado:\r ";
char *UndeadDamageAbsorb4 = " Absorci�n del ataque de muertos vivientes:\r ";
char *UserBlockPercent4 = " Capacidad de Bloqueo para el personaje:\r ";

char *SecondIncreMana4 = "Incremento de �ndice de mana por segundo:\r ";
char *FireDamage4 = " �ndice de ataque de Fuego:\r ";
char *DecreSpeed4 = " Velocidad en Disminuci�n:\r ";
char *DecreAttack4 = " �ndice de ataque disminuido:\r ";
char *AddPercentDamage4 = " �ndice de ataque agregado:\r ";



char *ChainDamage3 = " Da�o por Cadena)\r ";
char *BrandishDamage3 = " Da�o por Embiste ";
char *PhysicalAbsorb3 = " Absorci�n F�sica ";
char *SparkDamage3 = " Da�o por Chispa ";
char *BrutalSwingCritical3 = " Swing Brutal Cr�tico ";
char *Attck_RateAdd5 = " Attck_RateAdd:\r ";
char *Triumph4 = " Triunfo ";
char *Use4 = " t�";
char *DivineShield4 = " Bloqueando �ndice de escudo divino ";


char *QuestMonsterName[] = { " Bargon "," Guerrero Skeleton "," Cortacabezas "," Escarabajo Armado "," Soldado Skeleton "," Tit�n " ,
						 " Monstruo de la Tierra Prohibida "," Monstruo del Oasis "," Monstruo del 1er piso de la Prisi�n Antigua " };



char *VampOption[10] = { "Incremento de maduraci�n%: \r "," Vampiro: \r "," RefDa�o: \r "," DisminuirHP: \r "," Afortunado: \r " };


char *Quest3ItemName[] = { " Cazador de Demonios "," Venganza Antigua "," Niebla "," Lado Demon?co "," Anaconda "," Espada Laminada "," Fantasma " };

char *Quset3ItemDoc15 = " El objeto de misi�n ";
char *Quset3ItemDoc16 = " no est�";

char *SparkDamage10 = " Da�o por Chispa:\r ";

char *RequirLevel3 = " (Nivel Requerido:%d)\r ";

char *RecvItemTT = " Recibo el objeto ";
char *PuzzleEvent5 = " Rompecabezas Completado ";
char *BabelHorn = " El Cuerno de Babel ";
char *NineTailFoxItem = " Amuleto Nine Tail ";
char *MyShopItemSell5 = " El Precio: \r ";
char *CristalItem = " los 7 Cristales ";
char *StarDust = " Polvo Destelleante ";
char *ChristMas = " Polvo Brillante ";


char *sinDeadCandyEat = " �Tiene un gusto horrible! ";

char *PotionCntDoc2 = " Precio por unidad ";
char *ItemPrice7 = " Precio del Objeto ";

char *BuyMyShopItem7 = " %s jugador ha tra�do %d n�mero de %s por %dOro ";
char *BuyMyShopItem8 = " %s jugador ha tra�do %d n�mero de %s por %dOro ";
char *ItemName87 = " objeto ";

char *sinEvent87 = " Pedido del coleccionista de peligros ";
char *sinAddDamageItem = " ATKPOWER agregado: \r ";
char *sinContinueTimeItem = " Duraci�n: \r ";
char *BuyPotionMoney = " Dinero: ";
char *BuyPotionKind = " N�mero: ";
char *SheltomName2[] = { " Lucidy "," Sereneo "," Fadeo "," Sparky "," Raident "," Transparo "," Murky "," Devine "," Celesto "," Mirage " ,"Inferna " ," Enigma "," Bellum "," Ordo " };

char *AddPercentDamage3 = "AddATKPOWER%: \r";

char *sinLuckyBox = " Bolsa de la Suerte ";
char *SodMessage_Etc[] = {
			" El ingreso del clan que maneja Bellatra es ",
			" S�lo el jefe del clan lo toma. ",
			" Ahora, el impuesto es %d%s. ",
};

char *SodMessage_Clan[] = {
			" El ingreso total es como sigue ",
			" Bellatra provey� el premio ayer. ",
};

char *SodMessage_Master[] = {
			" El ingreso total es como sigue ",
			" Bellatra provey� el premio ayer. ",
			" Lo quieres recibir? ",
};

char *OtherClanMaster[] = {
			" El clan todav�a obtiene el premio ",
			" escriba el oro a recibir. ",
};

char *SiegeMessage_Taxrates[] = {
	" El �ndice de impuesto ha cambiado a %d%s. ",
	" El Total de impuesto se ha estado acumulando ",
	" Oro. ",
	" �Te gustar�a retirar el impuesto?. ",
	" El �ndice de impuesto es ahora %d%s. ",
};
char *SiegeMessage_MercenrayA[] = {
	" Milicia de Ricarten ",
	" Consiste en la milicia ",
	" Tiene habilidad de lucha d?il, a cambio de su bajo precio. ",
	" Monto m�ximo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayB[] = {
	" Guardia de Ricarten ",
	" El precio y la habilidad est? en equilibrio paa convertirse en Mercenario ",
	" Tiene habilidad de lucha intermedia. ",
	" Monto m�ximo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayC[] = {
	" Guardia Real de Bless ",
	" El nivel m�s alto de Mercenario ",
	" habilidad de luchala mayor habilidad de lucha. ",
	" Monto m�ximo de Mercenario:20 / %d ",
};
char *SiegeMessage_TowerIce[] = {
	" Torre de Cristal de Hielo ",
	" El Atributo de Hielo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuraci�n del Cristal de Hielo est� completa ",
};
char *SiegeMessage_TowerFire[] = {
	" Torre de Cristal de Fuego ",
	" El Atributo de Fuego otorga un granpoder de ATK ",
	" No tiene habilidades especiales. ",
	" La configuraci�n del Cristal de Fuego est� completa ",
};
char *SiegeMessage_TowerLighting[] = {
	"  Torre de Cristal Rayo ",
	" El Rayo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuraci�n del Cristal de Rayo est� completa ",
};
char *SiegeMessage_MerMoney = " Dinero de Mercenario: ";
char *SiegeMessage_TowerMoney = " Dinero de la Torre: ";

char *sinClanMaster7 = " Jefe del Clan ";
char *sinPrize7 = " Premio ";

char *sinLevelQuestMonster[] = { " Bargon "," Muffin "," Abeja Terrible "," Tif�n "," Rat�"," Grotesco "," Pu�o de Hierro " };
char *sinLevelQusetDoc = "Misi�n> %s %d n�mero de monstruos necesario ";

char *sinTeleportDoc[] = { " Cueva Hongo "," Cueva Enjambre "," Tierra Maldita "," Tierra Prohibida " };
char *sinLevelQuest90_2Mon[] = { " Omega "," D-M�quina "," Monta�a " };
char *sinLevelQusetDoc2 = " <Misi�n> Caza %d de %s ";
char *sinLevelQusetDoc3 = " <Misi�n> Obt�n el objeto de %s ";
char *sinLimitTiem2 = " Tiempo L�mite: \r ";
char *sinMinute2 = " minuto ";
char *sinDay4 = " d�a ";
char *sinHour4 = " hora ";
char *sinLevelQusetDoc4 = "<Misi�n>  Finaliz� la caza %d de %s ";

sinSTRING sinTestMsg7(" Hurra, Neh Neh Neh Boo Boo, son perdedores! ");

char *sinMonCodeName[]={
	0,
	" Bargon ",
	" Guerrero Skeleton ",
	" cortacabezas ",
	" Escarabajo Armado ",
	" Soldado Skeleton ",
	" Tit�n ",
	" Muffin ",
	" Abeja Terrible ",
	" Tif�n ",
	" Rat�",
	" Grotesco ",
	" Pu� de Hierro ",
	" Omega ",
	" D-M�quina ",
	" Monta�a ",
	" Caballero Skeleton ",
	" Caracol S?ido ",
	" Arrastraespina ",
	" Momia ",
	" Guardia de la Perdici�n ",
	" Figon ",
	" Gigante de Piedra",
	" Golem de Piedra ",
	" Guardia de Hierro ",
	" Avelin ",
	" Avelisk-L ",
	" BeEvil ",
	" Caballero de la Ilusi�n ",
	" Pesadilla ",
	" Bruja ",
	" Goblin Pesado ",
	" Dawlin ",
	" Estigio ",
	" �ncubo ",
	" Golem Cadena ",
	" Espectro Oscuro ",
	" Metron ",
	" Lord Avelisk ",
	" Crep�sculo ",
	" Sadnesst ",
	0,
};

char *ChargingTime4 = " Elevar velocidad para cargar:\r ";
char *AddIceDamage4 = " Da�o Agregado de Elemental de Escarcha:\r ";
char *IceTime4 = " Tiempo Congelado:\r ";
char *sinAttackType = " Tipo de Ataque:\r ";
char *sinAttackType2[2] = { " Manual\r "," Aut�matico\r " };

char *Won="Oro";


char *CastlItemInfo[] ={
	{" Con Modo Dios instant�neo pero\r "},
	{" Porcentaje Cr�tico\r "},
	{" Agregando porcentaje de evasi�n\r "},
	{" STM,HP,MP de los jugadores del grupo\r "},
	{" resurreci�n inmediatamente.\r "},
	{" ATK de torre de Cristal\r "},
	{" poder de ATK est� 20% en el objetivo\r "},
	0,
};
char *CastlItemInfo2[] ={
	{"poder de ATK disminuye en 1/2.\r"},
	{"aumento de 5%\r"},
	{"aumento de 5%\r"},
	{"dos membros do grupo\r"},
	{"\r"},
	{"reduzido em 50%\r"},
	{"contra o alvo\r"},
	0,
};


char *CharClassTarget[10]={
	"Objetivo(Luchador)\r",
	"Objetivo(Mecanico)\r",
	"Objetivo(Pikero)\r",
	"Objetivo(Arquera)\r",
	"Objetivo(Caballero)\r",
	"Objetivo(Atalanta)\r",
	"Objetivo(Mago)\r",
	"Objetivo(Sacerdotisa)\r",
	"Objetivo(Asesina)\r",
	"Objetivo(Shaman)\r",
};
char *AttributeTower[4]={
	"Atributo(Fuego)\r",
	"Atributo(Hielo)\r",
	"Atributo(Rayo)\r",
	"Duraci�n: %d Segundos\r",
};

char *SiegeMessage_MerComplete ="Posicionamiento completo de mercenario";


char *haQuestMonsterName[]={
	"Hopi",
	"Conejo",
	"Duende Macabro",
	"Duende Salvaje",
	"Esqueleto",
	"Esqueleto del Mal",
	"Ciclope",
	"Bargon",
	0,
};
char *ha100LVQuestItemName[]={
	"Hacha Minotauro",
	"Garra Extrema",
	"Martillo Dragon",
	"Guada�a Infernal",
	"Arco de Venganza",
	"Espada Inmortal",
	"Lanza Salamandra",
	"Cayado G�tico",
	"Adaga",
	"Fanstama",
	0,
};

char *ha100LVQuestMonterName[]={
	"Monstruos de Peru",
	"Monstruos de Gallubia", 
	0,
};
char *ha100LVQuestName = "Fantasma de F�ria";


char *PremiumItemDoc[][2]={
	{"Redistribuir\r"     ,"pontos de Status\r"},     
	{"Redistribuir\r"     ,"pontos de Habilidade\r"},    
	{"Redistribuir\r"," pontos de St e Hab\r"},     
	{"Resuscitar\r"    ,"personagens mortos\r"},        
	{"Invencibilidad temporal\r","reduce el Ataque en 50%\r"},

	{"Aumento de 5% \r"    ,"en cr�tico\r"},		
	{"Aumento de 5% \r"         ,"en evadir\r"},		
};

char *UpKeepItemDoc[] = {
	"Tiempo restante : %d minutos",
	"Tasa de Drop %d%s adicional",
	"Exp. %d%s adicional",
	"Ataque %d%s adicional",
	"Convierte %% do da�o en HP",
	"Convierte %% do da�o en MP",
	"Aumenta la capacidad en d%",
	"Reduzce el uso de MP en %d%s",
	"^_^",
	"^_^",
	"^_^",
	"^_^",
	"^_^",
	"Reduce el uso de STM en %d%s",
};
char *UpKeepItemName[] = {
	"Ojo M�gico",
	"Poci�n de Experiencia",
	"Presa de Vampiro",
	"Drena de Almas",
	"Poder de Awell",
	"Poci�n de reduci�n de Mana",
	"Fenix",
	"Terry",
	"Nepsys",
	"Eor",
	"Mute",
	"",
	"Poci�n de reduci�n de STM",
	"Poci�n de Humor",
	"Poci�n de 2",
	"Poci�n de 3",
	"Poci�n de 4",
	"Poci�n Carneiro",
};


char *BoosterItemInfo[] = {
	{ "�����ð����� �������\r" },
	{ "�����ð����� �����\r" },
	{ "�����ð����� �ٷ���\r" },
	0,
};
char *BoosterItemInfo2[] = {
	{ "15% ��½�Ų��.\r" },
	{ "15% ��½�Ų��.\r" },
	{ "15% ��½�Ų��.\r" },
	0,
};

char *BillingMagicForceName = "���� ����";

char *CandydaysItem = "7���� ĵ��"; 

char *ExpireItem = "Item Expirado";

char *FindinvestigatorItem = "���ξƹķ���";
char *FindinvestigatorNineItem = "���ξƹķ���";
char *FindinvestigatorTaleItem = "���Ͼƹķ���";



char *InventoryFull = "�κ��丮 ��������";
char *InvenSpaceSecure = "������ Ȯ���� �ּ���";

char *MagicalGreenEmeraldItem = "7���� ���޶��带";

char *MagicalGreenJadeItem = "7���� ���븦";

char *TearOfKaraItem = "7���� ī���� ������";

char *MagicForceName = "";

char *StarItem = "7���� ��������"; 
								   
char *ValentineItem = "7���� ���ݸ���"; 
										
char *PristonAlphabetItem = "7���� ���ĺ�����";



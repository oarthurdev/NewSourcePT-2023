#include "CLI.h"
#include <iostream>
#include <Windows.h>
#include "SocketServer/smwsock.h"
#include "Server\onserver.h"
#include "smPacket.h"
#include "GameMasters\GameMasters.h"
#include <chrono>
#include <ctime>
#include <ratio>
#include "global_def.h"

using namespace std;

using std::chrono::system_clock;
extern int rsRefreshConfig();
CLI commandLine;

CLI::CLI()
{
	done = nullptr;

}

CLI::~CLI()
{
}

bool CLI::run(bool *done)
{
	this->done = done;

	std::string input;

	system_clock::time_point today = system_clock::now();

	std::time_t tt = system_clock::to_time_t(today);

	extern TRANS_SERVER_LIST TransServerList;

	cout << "Servidor Aberto!" << endl;
	cout << "Developer: Guilherme" << endl;
	cout << "Data: " << ctime(&tt) << endl;
	cout << "Seja bem vindo ao Servidor de Testes!" << endl;
	cout << "Servidor rodando na chave 0xLD e na porta " << SERVER_TCP_PORT << endl;
	cout << "Versao: 1.0.0." << endl;
	cout << "Digite: 'help;' para ajuda. Digite 'exit;' para desligar o servidor" << endl << endl;

	while(!(*this->done))
	{
		cout << "server> ";
		cin >> input;

		if(input.back() != ';')
		{
			cout << "Comandos precisam terminar com ;" << endl;
		}
		else
		{
			process(input);
		}
	}


	return true;
}

bool CLI::process(const std::string &cmd)
{
	
	if(cmd.compare("help;") == 0)
		handleHelpCommand();
	else if(cmd.compare("exit;") == 0)
		handleExitCommand();
	else if(cmd.compare("shutdown;") == 0)
		handleShutdownCommand();
	else if(cmd.compare("clear;") == 0)
		system("cls");
	else if(cmd.compare("connected;") == 0)
		handleConnectedCommand();
	else if(cmd.compare(0, 4, "kick") == 0)
		handleKickCommand(cmd);
	else if(cmd.compare("reloadGMS;") == 0)
		handleReloadGMSCommand();
	else if(cmd.compare("showGMS;") == 0)
		handlePrintGMSCommand();
	else if (cmd.compare("reloadConfig;") == 0)
	{
		rsRefreshConfig();
		cout << endl;
		cout << "Configs recarregadas." << endl;
	}
	else
		cout << "Comando invalido. Digite help; para ajuda" << endl;




	return false;
}

void CLI::handleHelpCommand()
{
	cout << "Comandos terminam em ;" << endl;
	cout << "Comando: help; <Exibe mensagens para auxiliar o administrador>" << endl;
	cout << "Comando: exit; <Fecha o servidor>" << endl;
	cout << "Comando: shutdown; <Fecha o servidor em 3 minutos>" << endl;
	cout << "Comando: clear; <Limpa a tela de comandos>" << endl;
	cout << "Comando: connected; <Exibe todos os usu�rios conectados ao servidor>" << endl;
	cout << "Comando: kick(player name); <Expulsa um jogador do servidor>" << endl;
	cout << "Comando: reloadGMS; <Recarrega os Game Masters do servidor>" << endl;
	cout << "Comando: showGMS; <Exibe todos os Game Masters ativados>" << endl;
	cout << "Command: reloadConfig; <Reload the server settings>" << endl;
}

void CLI::handleExitCommand()
{
	*this->done = true;
}

void CLI::handleShutdownCommand()
{
	rsShutDown();
	cout << "Servidor sera desligado em 3 minutos" << endl;
}

void CLI::handleConnectedCommand()
{
	int count = 0;

	for(int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock)
		{
			rsPLAYINFO& player = rsPlayInfo[cnt];

			cout << "Id: " << player.getAccount() << " - Name: " << player.getName() << " - IP: " << player.lpsmSock->szIP << " - Stage: " << player.Position.Area << endl;
			count++;
		}
	}

	cout << "Usuarios conectados: " << count << endl;
}

void CLI::handleKickCommand(const std::string & cmd)
{
	if(cmd.length() < 6)
		return;

	std::string name;
	bool flag = false;

	for(auto it = cmd.begin() + 5; it != cmd.end(); ++it)
	{
		if(*it == ')')
		{
			flag = true;
			break;
		}

		name += *it;
		
	}

	if(!flag) return;

	rsPLAYINFO* player = FindUserFromName(const_cast<char*>(name.c_str()));

	if(!player)
	{
		player = FindUserFromName2(const_cast<char*>(name.c_str()));
	}

	if(player)
	{
		DisconnectUser(player->lpsmSock);
	}
}

void CLI::handlePrintGMSCommand()
{
	GameMasters::getInstance()->print();
}

void CLI::handleReloadGMSCommand()
{
	GameMasters::getInstance()->readFromDatabase();
	cout << "GMS Recarregados" << endl;
}

//void CLI::handleReloadConfigCommand()
//{
//	int rsRefreshConfig();
//
//	rsRefreshConfig();
//
//	cout << "Settings reloaded" << endl;
//}

CLI* CLI::getInstance()
{
	return &commandLine;
}

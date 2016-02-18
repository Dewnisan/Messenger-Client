#include <iostream>

#include "Listener.h"
#include "TCPMessengerProtocolExtentions.h"

using namespace std;

Listener::Listener(LoginManager* loginManager) :
		 _running(false), _loginManager(loginManager), _listenSock(new TCPSocket(MSNGR_PORT)) {
	start();
}

Listener::~Listener() {
	_running = false;
	_listenSock->cclose();
	waitForThread();
}

void Listener::run() {
	_running = true;

	while (_running) {
		TCPSocket* sock = _listenSock->listenAndAccept();
		if (sock == NULL) {
			break;
		}

		_loginManager->addPendingPeer(sock);
		cout << "New peer connected: " << sock->destIpAndPort() << endl;
	}

	cout << "Listener has stopped" << endl;
}


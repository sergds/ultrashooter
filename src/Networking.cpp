#include "globals.h"
#include "fix_winapi_conflicts.h"
#define ENET_IMPLEMENTATION
#include "Networking.h"
#include <iostream>
#include "HTTP.h"
#include <string>

int Networking::Init()
{
	logger.Log("Initialized Networking.");
	curl_global_init(CURL_GLOBAL_ALL); 
    logger.Log("http via cURL"); 
    //logger.Log("LIBCURL VERSION: " + std::to_string(LIBCURL_VERSION));
	HTTP http;
	logger.Log("External IP: " + http.GET("http://ifconfig.me/ip"));
	return enet_initialize();
}

void Networking::Host()
{
	net_ticrate = NET_TICRATE;
	logger.Log("Using Network TickRate of " + std::to_string(net_ticrate));
	ENetAddress addr;
	addr.host = ENET_HOST_ANY;
	addr.port = 1945;
	host = enet_host_create(&addr, 1, 1, 0, 0);
	if(host == NULL){
		logger.Log("FAILED TO CREATE HOST!!!");
		return;
	}
	authority = true;
	logger.Log("Created a Host, and became an authority.");
	return;
}

void Networking::DestroyHost() {
	if (host != nullptr) {
		enet_host_destroy(host);
		host = nullptr;
		authority = false;
		logger.Log("Destroyed host.");
		logger.Log("No longer an authority.");
		net_ticrate = 33;
		logger.Log("Using Network TickRate of " + std::to_string(net_ticrate));
	}
}

void Networking::Frame()
{
	ENetEvent evt;
	if (host == nullptr) {
		return;
	}
	while (enet_host_service(host, &evt, 1000) > 0) {
		switch (evt.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			logger.Log("Player connected!");
			break;
		default:
			break;
		}
	}
}

bool Networking::GetAuthority()
{
	return authority;
}

bool Networking::Connect(std::string hostname)
{
	net_ticrate = NET_TICRATE;
	logger.Log("Using Network TickRate of " + std::to_string(net_ticrate));
	host = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);
	ENetAddress addr;
	addr.port = 1945;
	enet_address_set_host_ip(&addr, hostname.c_str());
	otherPeer = enet_host_connect(host, &addr, 1, 1);
	ENetEvent evt;
	if (enet_host_service(host, &evt, 3000) > 0) {
		switch (evt.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			//std::cout << "Connected succesfully to " << evt.peer->address.host;
			enet_packet_destroy(evt.packet);
			return true;
			break;
		default:
			break;
		}
	}
	return false;
}

Networking::~Networking()
{
	if (host != nullptr) {
		enet_host_destroy(host);
		logger.Log("Destroyed host.");
	}
	enet_deinitialize();
	curl_global_cleanup();
	logger.Log("Destroyed Networking.");
}

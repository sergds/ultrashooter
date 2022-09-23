#pragma once
#include <cstdint>
#include <string>
#include "fix_winapi_conflicts.h"
#include <enet/enet.h>

// The UltraShooter Networking.
// Currently only up to 2 players are supported (including host).
class Networking
{
public:
   static Networking& getInstance()
    {
        static Networking instance;
        return instance;
    }
   int Init();
   void Host();
   void DestroyHost();
   void Frame();
   bool GetAuthority();
   bool Connect(std::string hostname); // Returns true on success.
   enum GameCommands : uint8_t {
       cmd_Plrinfo, // Player Info (nickname). sent by a connecting player.
       cmd_UpdateGMode, // Change GameMode (game mode is a shared game state: Lobbying, PlayingCOOP, PlayingVS, etc...). This cmd can only be broadcasted by an authority (host).
       cmd_PMove, // Player Move cmd, used to update player's position.
       cmd_SingleAction, // Single Gameplay-defined action fired by a player.
   };
private:
    bool authority = false; // Set to true if this machine is the host.
    ENetPeer* otherPeer;
    ENetHost* host;
    Networking() {};
    ~Networking();
public:
    Networking(Networking const&) = delete;
    void operator=(Networking const&) = delete;
};


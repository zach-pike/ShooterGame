#pragma once

#include <cstdint>

enum class PacketType : std::uint32_t {
    Heartbeat  = 0,   // Can be S -> C || C -> S
    PlayerMove = 1,   // Sent from C -> S to inform of new player position
};
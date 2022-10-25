#include "doors/doors.h"

void doors_normal()
{
    std::vector<Player> players(PLAYERS);
    std::vector<Door> doors(DOORS);
    std::vector<uint32_t> open(DOORS, 0);

    for (auto &player : players)
        player = {fast_rand(), fast_rand(), fast_rand(), fast_rand() % 5};

    for (auto &door : doors)
        door = Door{fast_rand(), fast_rand(), fast_rand(), fast_rand() % 512, fast_rand() % 5};

    CHECK_TIME(
        "NORMAL",
        int i = 0;
        for (auto &door
             : doors) {
            for (auto const &player : players)
            {
                if (player.team != door.team)
                    continue;

                auto xdiff = player.xpos - door.xpos;
                auto ydiff = player.ypos - door.ypos;
                auto zdiff = player.zpos - door.zpos;

                if ((xdiff * xdiff + ydiff * ydiff + zdiff * zdiff) < door.radiusSq)
                {
                    open[i] = 1;
                    break;
                }
            }
            ++i;
        });
}

void doors_simd()
{

    std::vector<Player> players(PLAYERS);
    simd::algo::soa_vector<DoorSimd> doors(DOORS);
    std::vector<uint32_t> open(DOORS, 0);

    for (auto &player : players)
        player = {fast_rand(), fast_rand(), fast_rand(), fast_rand() % 5};

    for (int i = 0; i < doors.size(); ++i)
        doors.set(i, DoorSimd{fast_rand(), fast_rand(), fast_rand(), fast_rand() % 512, fast_rand() % 5});

    CHECK_TIME("EVESMD",
               eve::algo::transform_to(doors, open, [&players](eve::like<DoorSimd> auto const &door)

                                       {
        auto dx = getXPos(door);
        auto dy = getYPos(door);
        auto dz = getZPos(door);
        auto dr = getRadiusSq(door);
        auto dt = getTeam(door);
        auto diff = eve::wide<float>{0};
        auto result = eve::wide<uint32_t>{0};

        for (auto const &player : players)
        {
            auto dist = eve::wide<float>{0};
            diff = dx - player.xpos;
            dist += diff*diff;
            diff = dy - player.ypos;
            dist += diff*diff;
            diff = dz - player.zpos;
            dist += diff*diff;
            result = eve::if_else((dist < dr) && (dt == player.team), 1, result);
        }
        return result; }););
}
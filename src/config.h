#pragma once

#include <linux/input-event-codes.h>
#include <string>

namespace Config {

    // This is the name of the process, as it shows in 'ps -e'. 
    // Sometimes the game name cuts off, but it works.
    const std::string processName = "SaintsRowTheThi";

    // Replace this with your keyboard event.
    const std::string keyboardEvent = "/dev/input/event5";

    namespace Keybinds{
        const int HACK_EXITKEY = KEY_F8;
    }
}
#include "lib.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main()
{
    auto logger = spdlog::stdout_color_mt("console");
    spdlog::get("logger")->info("version {} was started", version());

    return 0;
}
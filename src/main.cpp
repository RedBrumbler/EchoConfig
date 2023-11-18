#include "log.h"
#include "yodel/shared/loader.hpp"
#include <filesystem>

extern "C" void setup(CModInfo *info) {
  info->id = MOD_ID;
  info->version = VERSION;
  info->version_long = GIT_COMMIT;
}

extern "C" void load() {
  LOG_INFO("Replacing echovr config with echo-config from branch " GIT_BRANCH
           " (0x{:X})",
           GIT_COMMIT);

  auto application = modloader::get_application_id();

  std::filesystem::path source{
      fmt::format("/sdcard/ModData/{}/config.json", application)};

  if (std::filesystem::exists(source)) {
    std::filesystem::path destination{
        fmt::format("/data/user/0/{}/files/_local/config.json", application)};
    std::filesystem::copy_file(
        source, destination, std::filesystem::copy_options::overwrite_existing);
  } else {
    LOG_ERROR("Can't copy config from {}, file did not exist!", source.c_str());
  }
}

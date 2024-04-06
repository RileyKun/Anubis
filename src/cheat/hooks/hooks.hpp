#pragma once

class c_user_cmd;
namespace hooks {

namespace createmove {
void startup();
void shutdown();
bool __fastcall hooked_createmove(void* ecx, void* edx, float sample_time, c_user_cmd* cmd);
} // namespace createmove

} // namespace hooks
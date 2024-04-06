#pragma once

class c_user_cmd;
enum frame_stage;
namespace hooks {

namespace createmove {
void startup();
void shutdown();
bool __fastcall hooked_createmove(void* ecx, void* edx, float sample_time, c_user_cmd* cmd);
} // namespace createmove

namespace fs_notify {
void startup();
void shutdown();
void __fastcall hooked_fs_notify(void* ecx, void* edx, frame_stage stage);
}

} // namespace hooks
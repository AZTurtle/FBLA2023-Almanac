#include "core/time_manager.h"

milliseconds global_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
long long globalTime;
float delta_time = 0;

void update_time(){
    milliseconds new_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    delta_time = (new_time - global_time).count() / 1000.0f, 1.0f;
    delta_time = delta_time < 1.0f ? delta_time : 1.0f;
    global_time = new_time;
    globalTime = global_time.count();
}

long long getGlobal(){
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
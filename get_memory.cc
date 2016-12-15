#ifdef __APPLE__

#include <mach/mach.h>
int get_memory() {
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(),
                                  TASK_BASIC_INFO, (task_info_t)&t_info,
                                  &t_info_count)) {
        return -1;
    }
    // cout << "Used memory: " << (t_info.resident_size/(1 << 20)) << " MB" << endl;
    return 0;
}

#endif

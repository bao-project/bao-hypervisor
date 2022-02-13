#include <stdio.h>
#include <config.h>

int main() {
    size_t vcpu_num = 0;
    for (size_t i = 0; i < config.vmlist_size; i++) {
        vcpu_num += config.vmlist[i].platform.cpu_num;
    }

    printf("#define CONFIG_VM_NUM %ld\n", config.vmlist_size);
    printf("#define CONFIG_VCPU_NUM %ld\n", vcpu_num);

    return 0;
 }

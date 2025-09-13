#include <cpu.h>
#include <timer.h>
#include <spinlock.h>
#include "testf.h"

#define NUM_CPUS 4
#define CPU_BOOT_WAIT_TIME TIME_MS(1000)

volatile bool cpu_boot_status[NUM_CPUS] = {false};
spinlock_t boot_status_lock = SPINLOCK_INITVAL;

BAO_TEST(BOOT_CHECK, VM_BOOT)
{
    if(cpu_is_master()) {
        TESTF_PASS("System booted successfully!\n");
    }
}

BAO_TEST(BOOT_CHECK, CPU_BOOT) 
{
    int cpu_id = get_cpuid();
    spin_lock(&boot_status_lock);
    cpu_boot_status[cpu_id] = true;
    spin_unlock(&boot_status_lock);

    if(cpu_is_master()) {
        timer_wait(CPU_BOOT_WAIT_TIME);
        for(int i = 0; i < NUM_CPUS; i++) {
            if(!cpu_boot_status[i]) {
                TESTF_FAIL("CPUs did not boot successfully!\n");
                return;
            }
        }
        TESTF_PASS("All CPUs booted successfully!\n");
    }
}
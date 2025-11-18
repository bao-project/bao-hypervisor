
#include <sched.h>
#include <list.h>
#include <timer.h>
#include <objpool.h>
#include <config.h>
#include <vm.h>
#include <cpu.h>

static inline timer_value_t sched_next_event_time(void) 
{
    // hardcoded 10 ms time slice
    return timer_arch_get_count() + TIME_MS(10);
}

static void sched_timer_event_handler(struct timer_event *timer_event);

static void sched_set_next_timer_event(void)
{
    struct timer_event *timer_event = &cpu()->sched.timer_event;
    timer_value_t timer = sched_next_event_time();
    timer_event_set(timer_event, timer, sched_timer_event_handler);
    timer_event_add(timer_event);
}

static void sched_next(void) {
    node_t *next_node = list_pop(&cpu()->vcpu_list);
    list_push(&cpu()->vcpu_list, next_node);
    struct vcpu *vcpu = CONTAINER_OF(struct vcpu, cpu_vcpu_list_node, next_node);
    cpu()->next_vcpu = vcpu;
}


static void sched_timer_event_handler(struct timer_event *timer_event)
{
    (void)timer_event;
    sched_next();
    sched_set_next_timer_event();
}

void sched_start() {
    sched_next();
    if (list_size(&cpu()->vcpu_list) > 1) {
        sched_set_next_timer_event();
    }
}

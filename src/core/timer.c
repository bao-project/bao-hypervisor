
#include <timer.h>
#include <util.h>
#include <cpu.h>
#include <interrupts.h>

irqid_t timer_irq_id;

static inline struct list* timer_cpu_list(void) {
    return &cpu()->timer_event_list;
}

static int timer_event_compare(node_t *n1, node_t *n2) 
{
    struct timer_event *te1 = CONTAINER_OF(struct timer_event, node, n1);
    struct timer_event *te2 = CONTAINER_OF(struct timer_event, node, n2);
    return (te1->timer == te2->timer) ? 0 :
            (te1->timer > te2->timer) ? 1 : -1;
}

static void timer_set_next_event(void)
{
    node_t* next_node = list_peek(timer_cpu_list());
    if (next_node != NULL) {
        struct timer_event *next_event = CONTAINER_OF(struct timer_event, node, next_node);
        timer_arch_set(next_event->timer);
    } else {
        timer_disable();
    }
}

static void timer_irq_handler(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    node_t* next_node;

    while ((next_node = list_peek(timer_cpu_list())) !=  NULL) {
        struct timer_event *next_event = CONTAINER_OF(struct timer_event, node, next_node);
        if (next_event->timer <= timer_arch_get_count()) {
            (void)list_pop(timer_cpu_list());
            if (next_event->handler != NULL) {
                next_event->handler(next_event);
            }
        } else {
            break;
        }
    }

    timer_set_next_event();
}

void timer_event_add(struct timer_event *event) {
    list_insert_ordered(timer_cpu_list(), &event->node, timer_event_compare);
    timer_set_next_event();
}

void timer_event_remove(struct timer_event *event) {
    list_rm(timer_cpu_list(), &event->node);
    timer_set_next_event();
}

void timer_init()
{
    timer_arch_init();

    if (cpu_is_master()) {
        timer_irq_id = 
            interrupts_reserve(timer_arch_irq_id(), timer_irq_handler);
        list_init(timer_cpu_list());
    }

    cpu_sync_barrier(&cpu_glb_sync);

    interrupts_cpu_enable(timer_irq_id, true);
}

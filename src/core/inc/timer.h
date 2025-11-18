#ifndef TIMER_H
#define TIMER_H

#include <arch/timer.h>
#include <list.h>

#define TIME_US(us) (((TIMER_ARCH_FREQ())*(us))/(1000000ull))
#define TIME_MS(ms) (TIME_US((ms)*1000ull))
#define TIME_S(s)   (TIME_MS((s)*1000ull))

struct timer_event;

typedef void (*timer_event_handler_t)(struct timer_event *event);

struct timer_event {
    node_t node;
    timer_value_t timer;
    timer_event_handler_t handler;
};

void timer_init(void);
void timer_event_add(struct timer_event *event);
void timer_event_remove(struct timer_event *event);

static inline void timer_event_set(struct timer_event *event, timer_value_t timer,
    timer_event_handler_t handler)
{
        event->timer = timer;
        event->handler = handler;
}

static inline void timer_disable(void)
{
    timer_arch_disable();
}

extern irqid_t timer_irq_id;

#endif /* TIMER_H */

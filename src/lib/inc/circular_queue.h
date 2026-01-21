#ifndef BAO_CIRCULAR_QUEUE_H
#define BAO_CIRCULAR_QUEUE_H

#define cq_define(type, name, number_of_objects)    \
    struct {                                        \
        type objects [number_of_objects];           \
        signed int front, rear;                     \
        spinlock_t lock;                            \
    } name;

#define cq_max_size(cq) (sizeof(cq.objects) / sizeof(cq.objects[0]))

#define cq_is_full(cq) \
    ((cq.rear + 1) % cq_max_size(cq) == cq.front)

#define cq_is_empty(cq) \
    (cq.front == -1)

#define cq_init(cq)                     \
    do {                                \
        cq.lock = SPINLOCK_INITVAL;     \
        cq.front = cq.rear = -1;        \
    } while (0)

#define cq_add(cq, data)                                        \
    ({                                                          \
        bool _ok;                                               \
        spin_lock(&cq.lock);                                    \
        _ok = !cq_is_full(cq);                                  \
                                                                \
        if (_ok) {                                              \
            if ((cq.front) == -1) (cq.front) = 0;               \
            (cq.rear) = ((cq.rear) + 1) % (cq_max_size(cq));    \
            (cq.objects)[(cq.rear)] = (data);                   \
            _ok = true;                                         \
        }                                                       \
                                                                \
        spin_unlock(&cq.lock);                                  \
        _ok;                                                    \
    })

#define cq_pop(cq, data)                                        \
    ({                                                          \
        bool _ok;                                               \
        spin_lock(&cq.lock);                                    \
        _ok = !cq_is_empty(cq);                                 \
                                                                \
        if (_ok) {                                              \
            *data = cq.objects[cq.front];                       \
                                                                \
            if (cq.front == cq.rear)                            \
                cq.front = cq.rear = -1;                        \
            else                                                \
                cq.front = (cq.front + 1) % cq_max_size(cq);    \
        }                                                       \
        spin_unlock(&cq.lock);                                  \
                                                                \
        _ok;                                                    \
    })

#endif //BAO_CIRCULAR_QUEUE_H

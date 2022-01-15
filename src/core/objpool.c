#include <objpool.h>
#include <string.h>

void objpool_init(struct objpool *objpool) {
    memset(objpool->pool, 0, objpool->objsize*objpool->num);
    memset(objpool->bitmap, 0, BITMAP_SIZE(objpool->num));
}

void* objpool_alloc(struct objpool *objpool) {
    ssize_t n = bitmap_find_nth(objpool->bitmap, objpool->num, 1, 0, false);
    if(n < 0) {
        return NULL;
    } else {
        bitmap_set(objpool->bitmap, n);
        return objpool->pool + (objpool->objsize * n);
    }
}

void objpool_free(struct objpool *objpool, void* obj) {
    vaddr_t obj_addr = (vaddr_t)obj;
    vaddr_t pool_addr = (vaddr_t)objpool->pool;
    bool in_pool = 
        in_range(obj_addr, pool_addr, objpool->objsize * objpool->num);
    bool aligned = IS_ALIGNED(obj_addr-pool_addr, objpool->objsize);
    if (in_pool && aligned) {
        size_t n = (obj_addr-pool_addr)/objpool->objsize;
        bitmap_clear(objpool->bitmap, n);
    } else {
	WARNING("leaked while trying to free stray object");
    }
}

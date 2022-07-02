#include <mem.h>

#include <cpu.h>

void mem_prot_init() {

}

size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

vaddr_t mem_alloc_vpage(struct addr_space *as, enum AS_SEC section,
                            vaddr_t at, size_t n)
{
    return NULL_VA;
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t n, mem_flags_t flags)
{
    return false;
}

vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t n) {
    return vas;
}

void mem_unmap(struct addr_space *as, vaddr_t at, size_t n,
                    bool free_ppages)
{

}

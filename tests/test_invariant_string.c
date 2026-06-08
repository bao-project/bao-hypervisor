#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// Import the actual function from production code
extern char* strcpy(char* dest, char* src);

START_TEST(test_strcpy_buffer_overflow_protection)
{
    // Invariant: Buffer reads never exceed the declared length
    const char *payloads[] = {
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 64 bytes - exploit case
        "AAAAAAAAAA",  // 10 bytes - boundary case
        "ABC",  // 3 bytes - valid input
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        size_t src_len = strlen(payloads[i]);
        size_t dest_size = 8;  // Small fixed buffer to trigger overflow
        
        char *dest = calloc(dest_size + 16, 1);  // Extra canary space
        memset(dest + dest_size, 0xCC, 16);  // Canary pattern
        
        // Call the actual production function
        char *result = strcpy(dest, payloads[i]);
        
        // Check that canary was not overwritten (no buffer overflow)
        int canary_intact = 1;
        for (size_t j = 0; j < 16; j++) {
            if ((unsigned char)dest[dest_size + j] != 0xCC) {
                canary_intact = 0;
                break;
            }
        }
        
        ck_assert_msg(canary_intact || src_len < dest_size,
                      "Buffer overflow detected: strcpy wrote beyond declared buffer length");
        
        free(dest);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_strcpy_buffer_overflow_protection);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
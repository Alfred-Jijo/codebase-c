#include "../base/macros.h"

int
main(void) {
	print("=== test_macros ===\n");
	print_context_info();

	// Test ASSERT macro (should not trigger)
	ASSERT(1);

	// Uncomment to test assertion failure (should break in debug)
	// ASSERT(0);

	print("test_macros: OK\n");
	return 0;
}

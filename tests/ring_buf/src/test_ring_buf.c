/*
 * Ring Buffer Module - Homework Test Skeleton
 *
 * test_fresh_state is provided as a worked example. Fill in the remaining
 * 7 ZTEST bodies according to TEST_SPEC.md. Stubs call ztest_test_skip()
 * so the binary builds and runs cleanly before each test is implemented.
 *
 * Run:
 *   west twister -T tests/ring_buf -p native_sim
 */

#include <zephyr/ztest.h>
#include <errno.h>

#include "ring_buf.h"


/*
 * Windows:
 * west twister -T tests/ring_buf -p qemu_x86 -b    # simple view of errors
 * west twister -T tests/ring_buf -p qemu_x86 -v    # compile & execute
*/


/*
 * Shared before hook: every suite reinitialises the ring buffer with a
 * capacity of 4 so tests start from a clean, known state. Capacity 4 is
 * enough to exercise FIFO order (push 1, 2, 3) and overflow (full at 4).
 */
static void before(void *f)
{
	ARG_UNUSED(f);
	rb_init(4);
}

/*
 * ============================================================================
 * Test Suite: ring_buf_init
 *
 * Initial state and re-initialization behaviour.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_init, NULL, NULL, before, NULL, NULL);

/* PROVIDED — study this test before writing the rest. */
ZTEST(ring_buf_init, test_fresh_state)
{
	/*
	
	| #   | Scenario                 | Precondition       | Input                                 | Expected    |
	| --- | ------------------------ | ------------------ | ------------------------------------- | ----------- |
	| 1   | Fresh state *(provided)* | None (before hook) | `rb_is_empty()`, `rb_count()`         | `true`, `0` |
	
	SPEC COL         TEST
	-----------  |  ------------
	Precondition |    Arrange
	Input        |    Act
	Expected     |    Assert

	Parameters: 
	zassert_true(condition, message);
	zassert_equal(value, expected, message); // or zassert_equal(value, expected, message with format, printed_value);

	*/

	zassert_true(rb_is_empty(), "Fresh buffer must be empty");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0");
}

ZTEST(ring_buf_init, test_reinit_clears_state)
{
	/* TODO(l8-task1): Push a value, call rb_init(4) again, then
	 * verify the buffer is empty and count is 0.
	 * See TEST_SPEC.md "Suite ring_buf_init" #2.
	*/

	/*
	| #   | Scenario                 | Precondition       | Input                                 | Expected    |
	| 2   | Reinit clears state      | `push(99)`         | `rb_init(4)` then the same two checks | `true`, `0` |
	
	*/

	/* Arrange: buffer with element*/
	zassert_equal(rb_push(99), 0, "rb_push(99) must return 0");      // 99 is spec value 

	/* Act: reinitialization (re-init) */
	zassert_equal(rb_init(4), 0, "rb_init(0) must re-init buffer");

	/* Assert: discard previous element*/
	zassert_true(rb_is_empty(), "rb must be empty after reinitialization");
	zassert_equal(rb_count(), 0, "rb_count must be 0 after reinitialization");

	// Deleted: ztest_test_skip();
}

/*
 * ============================================================================
 * Test Suite: ring_buf_push_pop
 *
 * Single push/pop round-trip, FIFO order, full error path.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_push_pop, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_push_pop, test_single_push_pop)
{
	/* TODO(l8-task1): rb_push(42), rb_pop(&v) -> v == 42, buffer empty after.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #1.
	*/

	/*
	| #   | Scenario             | Precondition            | Input                                          | Expected                       |
	| --- | -------------------- | ----------------------- | ---------------------------------------------- | ------------------------------ |
	| 1   | Single push then pop | None (before hook)      | `push(42)`, `pop(&v)`                          | both return `0`; `v == 42`     |
	
	**Verify #1:** `push(42) == 0`; `pop(&v) == 0`; `v == 42`; after the pop
	`rb_is_empty() == true`.

	*/

	/*
	 Precondition = Arrange
	 Input        = Act
	 Expected     = Assert 
	*/

	/*Precondition = None, just v declaration*/
		int v = 0;
	/* Act */
	
	zassert_equal(rb_push(42),0,"rb_push(42) must return 0");
	zassert_equal(rb_pop(&v),0, "rb_pop(&v) must return 0");  // writes on v

	/* Assert */
	zassert_equal(v,42,"v value must be 42. Got this value: %d",v);
	zassert_true(rb_is_empty(), "rb must be empty after pop");



	// Deleted: ztest_test_skip();
}

ZTEST(ring_buf_push_pop, test_fifo_order)
{
	/* TODO(l8-task1): rb_push(1), rb_push(2), rb_push(3); pop three times
	 * and verify the values come out as 1, 2, 3 in that order.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #2.
	*/

	/*
		| #   | Scenario             | Precondition            | Input                                          | Expected                       |
		| --- | -------------------- | ----------------------- | ---------------------------------------------- | ------------------------------ |
		| 2   | FIFO order preserved | None (before hook)      | `push(1)`, `push(2)`, `push(3)`, `pop(&v)` × 3 | three pops yield `1`, `2`, `3` |
	
		**Verify #2:** all three `push(...)` calls return `0`; the three `pop(&v)`
		calls yield `1`, then `2`, then `3` (use `zassert_equal` per pop). After
		the third pop `rb_is_empty() == true`.

	*/

	/* Arrange: hook before used */
	int v = 0;

	/* Act */
	zassert_equal(rb_push(1), 0, "rb_push(1) must return 0");
	zassert_equal(rb_push(2), 0, "rb_push(2) must return 0");
	zassert_equal(rb_push(3), 0, "rb_push(3) must return 0");

	/* Asserts */
	zassert_equal(rb_pop(&v),0, "rb_pop(&v) must return 0");
	zassert_equal(v,1,"v value must be 1. Got this value: %d",v);

	zassert_equal(rb_pop(&v),0, "rb_pop(&v) must return 0");
	zassert_equal(v,2,"v value must be 2. Got this value: %d",v);

	zassert_equal(rb_pop(&v),0, "rb_pop(&v) must return 0");
	zassert_equal(v,3,"v value must be 3. Got this value: %d",v);

	zassert_true(rb_is_empty(), "rb must be empty after 3 pops");


	// Deleted: ztest_test_skip();
}

ZTEST(ring_buf_push_pop, test_push_full_returns_enospc)
{
	/* TODO(l8-task1): Fill the buffer to its capacity of 4, then push
	 * one more value -> -ENOSPC.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #3.
	*/

	/*
	| #   | Scenario             | Precondition            | Input                                          | Expected                       |
	| --- | -------------------- | ----------------------- | ---------------------------------------------- | ------------------------------ |
	| 3   | Push past capacity   | `push(1..4)` (buf full) | `push(99)`                                     | `-ENOSPC`                      |
	
	**Verify #3:** the four initial pushes all return `0`; `rb_is_full() == true`;
	the fifth `push(99)` returns exactly `-ENOSPC`; `rb_count() == 4`
	(rejected push did not consume a slot).
	*/

	/* Arrange: hook "before" used */

	zassert_equal(rb_push(1), 0, "rb_push(1) must return 0");
	zassert_equal(rb_push(2), 0, "rb_push(2) must return 0");
	zassert_equal(rb_push(3), 0, "rb_push(3) must return 0");
	zassert_equal(rb_push(4), 0, "rb_push(4) must return 0");

	zassert_true(rb_is_full(), "rb must be full");

	/* Act */

	zassert_equal(rb_push(99), -ENOSPC, "rb_push(99) must return -ENOSPC on full buffer");

	/*Assert*/
	zassert_equal(rb_count(), 4, "rb_count must be max capacity: 4. Got %u",rb_count()); //rb_count returns uint32_t


	// Deleted: ztest_test_skip();
}

/*
 * ============================================================================
 * Test Suite: ring_buf_boundaries
 *
 * Peek semantics and NULL-pointer boundary conditions.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_boundaries, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_boundaries, test_peek_does_not_consume)
{
	/* TODO(l8-task1): rb_push(7); rb_peek(&v) -> v == 7; rb_peek(&v) again
	 * -> v == 7; rb_count() still == 1.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #1.
	*/
	/*
		| #   | Scenario              | Precondition       | Input                  | Expected                            |
		| --- | --------------------- | ------------------ | ---------------------- | ----------------------------------- |
		| 1   | Peek does not consume | `push(7)`          | `peek(&v)`, `peek(&v)` | both return `0`; `v == 7` each time |

		**Verify #1:** the first and second `peek(&v)` both return `0` and write
		`7` into `v`. After the two peeks `rb_count() == 1` (peek must not
		consume).
	*/

	/* Arrange */
	int v = 0;
	zassert_equal(rb_push(7), 0, "rb_push(7) must return 0");

	/* Act */
	zassert_equal(rb_peek(&v), 0, "1st rb_peek(&v) must return 0");
	zassert_equal(v, 7, "v must be 7 with 1st rb_peek(&v). Value of v:%d",v);

	
	v = 0; // 2nd peek must write 
	zassert_equal(rb_peek(&v), 0, "2nd rb_peek(&v) must return 0");
	zassert_equal(v, 7, "v must be 7 with 2nd rb_peek(&v). Value of v:%d",v);

	/* Assert */
	zassert_equal(rb_count(), 1, "rb_count must be 1 (not consume). Value of rb_count():%u",rb_count());


	// Deleted: ztest_test_skip();
}

ZTEST(ring_buf_boundaries, test_pop_null_returns_einval)
{
	/* TODO(l8-task1): rb_pop(NULL) -> -EINVAL.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #2.
	*/

	/*
		| #   | Scenario              | Precondition       | Input                  | Expected                            |
		| --- | --------------------- | ------------------ | ---------------------- | ----------------------------------- |
		| 2   | `pop(NULL)`           | None (before hook) | `rb_pop(NULL)`         | `-EINVAL`                           |

		**Verify #2:** `rb_pop(NULL)` returns exactly `-EINVAL`.
	*/

	/* Arrange: None */
	/*Act + Assert*/
	zassert_equal(rb_pop(NULL), -EINVAL, "rb_pop(NULL) must return -EINVAL"); // -EINVAL: NULL Pointer

	// Deleted: ztest_test_skip();
}

ZTEST(ring_buf_boundaries, test_is_full_after_fill)
{
	/* TODO(l8-task1): push 4 values -> rb_is_full() == true, rb_count() == 4.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #3.
	 */
	/*

	| #   | Scenario              | Precondition       | Input                  | Expected                            |
	| --- | --------------------- | ------------------ | ---------------------- | ----------------------------------- |
	| 3   | `is_full` after fill  | `push(1..4)`       | `rb_is_full()`         | `true`                              |

	**Verify #3:** all four pushes return `0`; `rb_is_full() == true`;
	`rb_count() == 4`.

*/

	/*Arrange*/
	zassert_equal(rb_push(1), 0, "rb_push(1) must return 0");
	zassert_equal(rb_push(2), 0, "rb_push(2) must return 0");
	zassert_equal(rb_push(3), 0, "rb_push(3) must return 0");
	zassert_equal(rb_push(4), 0, "rb_push(4) must return 0");

	/* Act */

	zassert_true(rb_is_full(), "rb_is_full must be true after 4 rb_pushes");

	/* Assert */

	zassert_equal(rb_count(), 4, "rb_count must be 4. Got %u", rb_count());

	// Deleted: ztest_test_skip();
}

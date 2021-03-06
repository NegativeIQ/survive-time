#include <core>
#include <console>
#include <float>
#include <file>
#include <string>

native ExitProcess(status = 0);
// native CallLocalFunction(const function[], const format[], {Float,_}:...);

stock bool:test_false = false;
stock test_id = 0;
stock failed_test_count = 0;

#if __Pawn == 0x030A
	#define TEST_LINE __line
#else
	#define TEST_LINE 0
#endif

#define TEST_TRUE(%0) \
     do { \
          test_id++; \
          if (!(%0)) { \
               TestFailed(test_id, TEST_LINE, "Expression is false"); \
          } \
     } while (test_false)

#define TEST_FALSE(%0) \
     do { \
          test_id++; \
          if (%0) { \
               TestFailed(test_id, TEST_LINE, "Expression is true"); \
          } \
     } while (test_false)

stock TestExit() {
     if (failed_test_count == 0) {
          print("All tests passed");
     }
     ExitProcess();
}

stock TestFailed(id, line, const reason[]) {
     failed_test_count++;
     if (line > 0) {
          printf("Test #%d at line %d failed: %s", id, line, reason);
     } else {
          printf("Test #%d failed: %s", id, reason);
     }
     #emit halt 1
}
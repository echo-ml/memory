#include <echo/memory/copy.h>
#include <echo/test.h>

using namespace echo;
using namespace memory;

struct my_memory_backend_tag1 : memory_backend_tag {};
struct my_memory_backend_tag2 : memory_backend_tag {};
struct my_memory_backend_tag3 : memory_backend_tag {};

static bool was_called1 = false;

void memcpy(my_memory_backend_tag1, void*, const void*, std::size_t) {
  was_called1 = true;
}

TEST_CASE("copy") {
  double a[3] = {1, 2, 3};
  double b[4];
  b[3] = -1;

  SECTION("generic_copy1") {
    copy(memory_backend_tag(), std::begin(a), std::end(a), std::begin(b));
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
    REQUIRE(b[3] == -1);
  }

  SECTION("generic_copy2") {
    copy(my_memory_backend_tag2(), std::begin(a), std::end(a), std::begin(b));
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
    REQUIRE(b[3] == -1);
  }

  SECTION("generic_copy3") {
    copy(my_memory_backend_tag2(), std::begin(a), std::end(a),
         my_memory_backend_tag3(), std::begin(b));
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
    REQUIRE(b[3] == -1);
  }

  SECTION("overloaded_copy") {
    copy(my_memory_backend_tag1(), std::begin(a), std::end(a), std::begin(b));
    REQUIRE(was_called1);
    was_called1 = false;
  }
}

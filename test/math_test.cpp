// CATCH_CONFIG_MAIN : Let Catch provide main()
// So other test file should not define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "math.hpp"

TEST_CASE( "Math test", "[math]" ) {
    REQUIRE(glm::vec2(1.0f, 2.0f).x == 1.0f);
    REQUIRE(glm::vec3(1.0f, 2.0f, 3.0f).y == 2.0f);
    REQUIRE(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f).z == 3.0f);
}
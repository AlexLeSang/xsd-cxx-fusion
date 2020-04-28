#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_USE_ASYNC

#include <catch2/catch.hpp>

#include <shiporder.h>
#include <type-to-string.hpp>

#include <iostream>

// BOOST_FUSION_ADAPT_ADT(demo::employee, (obj.get_name(), obj.set_name(val))(obj.get_age(), obj.set_age(val)))

// clang-format off
BOOST_FUSION_ADAPT_ADT(Shiporder,
                       (obj.orderperson(),
                        obj.orderperson(val))
                       )
// clang-format on

// clang-format off
// BOOST_FUSION_ADAPT_ADT(shipto,
//                        (obj.name(), obj.name(val))
//                        )
// clang-format on

TEST_CASE("Test 2") {
  // shipto order_person;
  // std::cout << TypeToString(order_person) << std::endl;

  Shiporder shiporder;
  const auto eployee_string = TypeToString(shiporder);
  std::cout << eployee_string << std::endl;

  REQUIRE(2 == 2);
}

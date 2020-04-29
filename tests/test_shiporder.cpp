#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_USE_ASYNC

#include <catch2/catch.hpp>

#include <shiporder.h>
#include <type_to_string.hpp>

#include <iostream>

// clang-format off
BOOST_FUSION_ADAPT_ADT(Shipto,
                       (obj.name(), obj.name(val))
                       (obj.address(), obj.address(val))
                       (obj.city(), obj.city(val))
                       )
// clang-format on

std::ostream &operator<<(std::ostream &os, const Shipto &shipto) {
  os << TypeToString(shipto) << std::endl;
  return os;
}

// clang-format off
BOOST_FUSION_ADAPT_ADT(Item,
                       (obj.title(), obj.title(val))
                       (obj.note(),  obj.note(val))
                       (obj.quantity(),  obj.quantity(val))
                       (obj.price(),  obj.price(val))
                       )
// clang-format on

std::ostream &operator<<(std::ostream &os, const Item &item) {
  os << TypeToString(item) << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, const xsd::cxx::tree::sequence<Item> &items) {
  boost::range::for_each(items, [&os](const Item &item) { os << TypeToString(item) << std::endl; });
  return os;
}

// clang-format off
BOOST_FUSION_ADAPT_ADT(Shiporder,
                       (obj.Orderperson(), obj.Orderperson(val))
                       (obj.Shipto(),      obj.Shipto(val))
                       (obj.Item(),        obj.Item(val))
                       )
// clang-format on

TEST_CASE("Test 2") {
  const Shipto shipto{"Name", "Address", "City", "Country"};

  Shiporder shiporder{"Order Person", shipto, "Order"};
  shiporder.Item().push_back({"Item 1", 20, 12});
  shiporder.Item().push_back({"Item 2", 30, 22});

  std::cout << TypeToString(shiporder) << std::endl;

  REQUIRE(2 == 2);
}

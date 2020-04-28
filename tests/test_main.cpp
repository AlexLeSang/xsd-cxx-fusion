#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_USE_ASYNC

#include <type-to-string.hpp>

#include <catch2/catch.hpp>

#include <boost/bind.hpp>

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

#include <boost/fusion/include/adapt_adt.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/range/algorithm.hpp>

#include <iostream>

using namespace Catch::Matchers;

struct print_visitor {
  template <class Index, class C> void operator()(Index, C &c) {
    std::cout << boost::fusion::extension::struct_member_name<C, Index::value>::call() << "="
              << boost::fusion::at<Index>(c) << std::endl;
  }
};

template <class C> void print_fields(C &c) {
  typedef boost::mpl::range_c<int, 0, boost::fusion::result_of::size<C>::type::value> range;
  boost::mpl::for_each<range>(boost::bind<void>(print_visitor(), boost::ref(c), _1));
}

namespace demo {
struct employee {
private:
  std::string name;
  int age;

public:
  void set_name(std::string const &n) { name = n; }

  void set_age(int a) { age = a; }

  std::string const &get_name() const { return name; }

  int get_age() const { return age; }
};
} // namespace demo

BOOST_FUSION_ADAPT_ADT(demo::employee, (obj.get_name(), obj.set_name(val))(obj.get_age(), obj.set_age(val)))

TEST_CASE("Test 1") {

  demo::employee emploee;

  constexpr auto age = 41;

  boost::fusion::front(emploee) = "Edward Norton";
  boost::fusion::back(emploee) = age;

  // Prints 'Edward Norton is 41 years old'
  std::cout << emploee.get_name() << " is " << emploee.get_age() << " years old" << std::endl;

  namespace bfea = boost::fusion::extension;

  REQUIRE(emploee.get_age() == age);
  REQUIRE(bfea::access::adt_attribute_access<demo::employee, 1>::boost_fusion_adapt_adt_impl_get(emploee) == age);
  REQUIRE(typeid(bfea::access::struct_member<demo::employee, 1>::type).name() == std::string{"i"});

  std::cout << "Print" << std::endl;

  const auto eployee_string = TypeToString(emploee);

  std::cout << eployee_string << std::endl;
}

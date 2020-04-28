#ifndef PRINT_TYPE_H
#define PRINT_TYPE_H

#include <sstream>

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/sequence.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

#include <boost/bind.hpp>

#include <boost/range/algorithm.hpp>

auto TypeToString = [](const auto &object) {
  namespace bfea = boost::fusion::extension;
  using Object = typename std::decay<decltype(object)>::type;

  using range = boost::mpl::range_c<int, 0, boost::fusion::result_of::size<Object>::type::value>;

  std::ostringstream oss;
  boost::mpl::for_each<range>([&oss, &object](const auto index) {
    const auto field =
        bfea::access::adt_attribute_access<Object, decltype(index)::value>::boost_fusion_adapt_adt_impl_get(object);

    oss << typeid(field).name() << " : " << field << std::endl;
  });

  return oss.str();
};

#endif /* PRINT_TYPE_H */

//
// default_completion_token.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_HPP
#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T, typename = void>
struct default_completion_token_impl
{
  typedef void type;
};

template <typename T>
struct default_completion_token_impl<T,
    void_t<typename T::default_completion_token_type>
  >
{
  typedef typename T::default_completion_token_type type;
};

} // namespace detail

#if defined(GENERATING_DOCUMENTATION)

/// Traits type used to determine the default completion token type associated
/// with a type (such as an executor).
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type.
 *
 * Specialisations of this trait may provide a nested typedef @c type, which is
 * a default-constructible completion token type.
 *
 * If not otherwise specialised, the default completion token type is
 * boost::asio::deferred_t.
 */
template <typename T>
struct default_completion_token
{
  /// If @c T has a nested type @c default_completion_token_type,
  /// <tt>T::default_completion_token_type</tt>. Otherwise the typedef @c type
  /// is not defined.
  typedef see_below type;
};
#else
template <typename T>
struct default_completion_token
  : detail::default_completion_token_impl<T>
{
};
#endif

template <typename T>
using default_completion_token_t = typename default_completion_token<T>::type;

#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(e) \
  = typename ::boost::asio::default_completion_token<e>::type
#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(e) \
  = typename ::boost::asio::default_completion_token<e>::type()

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_HPP

/******************************************************************************
 *  File Name:
 *    version.hpp
 *
 *  Description:
 *    Version information for the test server application
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_VERSION_HPP
#define IRIS_VERSION_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <etl/string.h>

namespace Iris
{
  static constexpr etl::string_view VERSION = "0.0.1";
}  // namespace

#endif  /* !IRIS_VERSION_HPP */

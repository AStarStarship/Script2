// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_TEST_INLINE_CODE
#define SCRIPT2_TEST_INLINE_CODE 1
#include "Test.h"
namespace _ {

template<TestCase... N>
const CHA* TTestTree(const CHA* args) {
  static TestCase nodes[sizeof...(N)] = {N...};
  return TestTree(args, nodes, sizeof...(N));
}

template<TestCase... N>
ISN TTestTree(ISN arg_count, CHA** args) {
  static TestCase tests[sizeof...(N)] = {N...};
  return SeamTreeTest(arg_count, args, tests, sizeof...(N));
}

}  //< namespace _
#endif

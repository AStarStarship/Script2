// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_TEST_HPP
#define SCRIPT2_TEST_HPP 1
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

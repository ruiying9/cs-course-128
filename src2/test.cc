#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "sandwich.hpp"

using std::string;
using std::vector;

// A helper method for you to visualize what the contents of a vector are. You
// are welcome to modify this method or create additional helper methods.
//
// Example usage:
//  vector<string> my_vec;
//  my_vec.push_back("hello");
//  my_vec.push_back("world"):
//  PrintVector(my_vec);
// Prints:
//  [hello, world]
void PrintVector(const vector<string>& vec) {
  std::cout << "[";
  bool first = true;
  for (const auto& it : vec) {
    if (!first) {
      std::cout << ", ";
    } else {
      first = false;
    }

    std::cout << it;
  }

  std::cout << "]" << std::endl;
}

TEST_CASE("Sandwich::AddTopping test", "[AddTopping]") {
  Sandwich my_topping = Sandwich();
  vector<string> my_top = my_topping.GetToppings();
  SECTION("Only one cheese chould be included") {
    if (my_topping.AddTopping("cheese")) {
      REQUIRE_FALSE(my_topping.AddTopping("cheese"));
    }
  }
}

TEST_CASE("Sandwich::RemoveTopping test", "[RemoveTopping]") {
  SECTION("Only remove topping before dressing been added-non present") {
    Sandwich my_topping = Sandwich();
    vector<string> my_top = my_topping.GetToppings();
    vector<string> my_dress = my_topping.GetDressings();
    for (string w : my_topping.dressings) {
      my_topping.AddDressing(w);
      for (string s : my_topping.toppings) {
        REQUIRE_FALSE(my_topping.RemoveTopping(s));
      }
    }
  }
  SECTION("Only remove topping before dressing been added-present") {
    Sandwich my_topping = Sandwich();
    vector<string> my_top = my_topping.GetToppings();
    vector<string> my_dress = my_topping.GetDressings();
    my_topping.AddTopping("cheese");
    my_topping.AddDressing("mayo");
    REQUIRE_FALSE(my_topping.RemoveTopping("cheese"));
  }
}

TEST_CASE("Sandwich::AddDressing test", "[AddDressing]") {
  // your tests for Sandwich::AddDressing here
  SECTION("At least one topping before the dressing") {
    Sandwich my_topping = Sandwich();
    vector<string> my_top = my_topping.GetToppings();
    vector<string> my_dress = my_topping.GetDressings();
    for (string k : my_topping.dressings) {
      if (my_topping.AddDressing(k)) {
        REQUIRE_FALSE(my_top.empty());
      }
    }
  }
  SECTION("No duplicate of dressing") {
    Sandwich my_topping = Sandwich();
    vector<string> my_top = my_topping.GetToppings();
    vector<string> my_dress = my_topping.GetDressings();
    my_topping.AddTopping("cheese");
    for (string n : my_topping.dressings) {
      if (my_topping.AddDressing(n)) {
        REQUIRE_FALSE(my_topping.AddDressing(n));
      }
    }
  }
}

#pragma once

#include <iostream>
#include <string>
#include <vector>

#define rt_assert(C, M)      \
  ::naga::rt::test::_assert( \
    !!(C),                   \
    std::string(M) + std::string("\n|  " __FILE__ ":" TOSTRING(__LINE__)));

#define rt_check(C, M)      \
  ::naga::rt::test::_check( \
    !!(C),                  \
    std::string(M) + std::string("\n|  " __FILE__ ":" TOSTRING(__LINE__)));

#define rt_message(M)         \
  ::naga::rt::test::_message( \
    std::string(M) + std::string("\n| " __FILE__  ":" TOSTRING(__LINE__)));

#define TOSTRING(n) TOSTRING_(n)
#define TOSTRING_(n) #n

#if defined(_WIN32)
  #define RT_TERM_COLOR_RED
  #define RT_TERM_COLOR_GREEN
  #define RT_TERM_COLOR_YELLOW
  #define RT_TERM_COLOR_DEFAULT
#else
  #define RT_TERM_COLOR_RED "\e[31m"
  #define RT_TERM_COLOR_GREEN "\e[32m"
  #define RT_TERM_COLOR_YELLOW "\e[33m"
  #define RT_TERM_COLOR_DEFAULT "\e[0m"
#endif

namespace naga::rt {
  /// test
  struct test {
    /// test run
    static int test_run;
    /// test name
    static std::string test_name;
    /// stored messages
    static std::vector<std::string> messages;

    /// assert
    static void _assert(bool cond, const std::string& message);
    /// check
    static void _check(bool cond, const std::string& message);
    /// message
    static void _message(const std::string& message);
    /// summarize
    static void summarize();
  };

  int test::test_run = 0;
  std::string test::test_name = "Unknown";
  std::vector<std::string> test::messages = {};

  void test::_assert(bool cond, const std::string& message) {
    if (cond) {
      ++test_run;
    } else {
      messages.emplace_back(
        std::string(
          RT_TERM_COLOR_RED "[rt_assert failed]: " RT_TERM_COLOR_DEFAULT
        ) + message);
      std::cerr << messages.back() << std::endl;
      summarize();
      std::abort();
    }
  }

  void test::_check(bool cond, const std::string& message) {
    ++test_run;
    if (!cond) {
      messages.emplace_back(
        std::string(
          RT_TERM_COLOR_YELLOW "[rt_check failed]: " RT_TERM_COLOR_DEFAULT
        ) + message);
      std::cerr << messages.back() << std::endl;
    }
  }

  void test::_message(const std::string& message) {
    messages.emplace_back(
      std::string(
        RT_TERM_COLOR_GREEN "[rt_message]: " RT_TERM_COLOR_DEFAULT
      ) + message);
    std::cerr << messages.back() << std::endl;
  }

  void test::summarize() {
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "[Summary of tests]" << std::endl;
    std::cout << "  Test name: " << test::test_name << std::endl;
    std::cout << "  Total test run: " << test::test_run << std::endl;
    if (!test::messages.empty()) {
      std::cout << "  Messages:" << std::endl;
      for (auto m : test::messages) {
        std::cout << m << std::endl;
      }
    }
    std::cout << "------------------------------------------" << std::endl;
  }
}
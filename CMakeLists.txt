cmake_minimum_required(VERSION 3.0)

project("echo-memory")

enable_testing()

find_package(Echo)
include(Echo/Default)

ECHO_INSTALL_DEFAULT_HEADERS()
ECHO_ADD_DEFAULT_TEST()

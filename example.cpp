
// ------------------------------------------------

#include "pack_utils.hpp"

// ------------------------------------------------

using namespace kaixo;

static_assert(pack_size_v<pack<double, int, float>> == 3);
static_assert(pack_size_v<pack<double, int, int, int>> == 4);
static_assert(pack_size_v<pack<>> == 0);

static_assert(std::same_as<pack_element_t<0, pack<double, int, int, char>>, double>);
static_assert(std::same_as<pack_element_t<1, pack<double, int, int, int>>, int>);
static_assert(std::same_as<pack_element_t<3, pack<double, int, int, char>>, char>);
static_assert(std::same_as<pack_element_t<0, pack<double>>, double>);

static_assert(indices_element_v<0, std::index_sequence<0, 1, 2, 3>> == 0);
static_assert(indices_element_v<1, std::index_sequence<0, 1, 2, 3>> == 1);
static_assert(indices_element_v<3, std::index_sequence<0, 1, 2, 3>> == 3);
static_assert(indices_element_v<0, std::index_sequence<0>> == 0);

static_assert(pack_contains_v<int, pack<double, int, float>>);
static_assert(!pack_contains_v<char, pack<double, int, float>>);
static_assert(!pack_contains_v<char, pack<>>);

static_assert(pack_contains_all_v<pack<int, double>, pack<double, int, float>>);
static_assert(!pack_contains_all_v<pack<int, char>, pack<double, int, float>>);
static_assert(!pack_contains_all_v<pack<int, char>, pack<>>);
static_assert(pack_contains_all_v<pack<>, pack<>>);

static_assert(pack_contains_any_v<pack<int, char>, pack<double, int, float>>);
static_assert(!pack_contains_any_v<pack<long, char>, pack<double, int, float>>);
static_assert(!pack_contains_any_v<pack<long, char>, pack<>>);
static_assert(!pack_contains_any_v<pack<>, pack<>>);

static_assert(pack_find_v<std::is_integral, pack<long, char>>);
static_assert(pack_find_v<std::is_integral, pack<float, char>>);
static_assert(!pack_find_v<std::is_integral, pack<float, double>>);
static_assert(!pack_find_v<std::is_integral, pack<>>);

static_assert(pack_count_v<int, pack<double, int, float>> == 1);
static_assert(pack_count_v<char, pack<double, int, float>> == 0);
static_assert(pack_count_v<float, pack<float, int, float>> == 2);
static_assert(pack_count_v<float, pack<>> == 0);

static_assert(pack_count_all_v<pack<float>, pack<float, int, float>> == 2);
static_assert(pack_count_all_v<pack<float, int>, pack<float, int, float>> == 3);
static_assert(pack_count_all_v<pack<float, int>, pack<char, int, float>> == 2);
static_assert(pack_count_all_v<pack<float, int>, pack<>> == 0);

static_assert(pack_count_unique_v<pack<int, double>> == 2);
static_assert(pack_count_unique_v<pack<int, double, int>> == 2);
static_assert(pack_count_unique_v<pack<int, int, int>> == 1);
static_assert(pack_count_unique_v<pack<>> == 0);

static_assert(pack_count_filter_v<std::is_integral, pack<char, int, float>> == 2);
static_assert(pack_count_filter_v<std::is_integral, pack<double, float>> == 0);
static_assert(pack_count_filter_v<std::is_integral, pack<>> == 0);

static_assert(pack_nth_index_of_v<int, 0, pack<double, int, float, int, long>> == 1);
static_assert(pack_nth_index_of_v<int, 1, pack<double, int, float, int, long>> == 3);
static_assert(pack_nth_index_of_v<int, 2, pack<double, int, float, int, long>> == npos);
static_assert(pack_nth_index_of_v<int, 4, pack<int, int, int, int, int>> == 4);
static_assert(pack_nth_index_of_v<char, 0, pack<double, int, float>> == npos);
static_assert(pack_nth_index_of_v<char, 1, pack<double, int, float>> == npos);
static_assert(pack_nth_index_of_v<char, 1, pack<>> == npos);

static_assert(pack_nth_index_of_any_v<pack<int, float>, 0, pack<double, int, float, int, long>> == 1);
static_assert(pack_nth_index_of_any_v<pack<int, double>, 1, pack<double, int, float, int, long>> == 1);
static_assert(pack_nth_index_of_any_v<pack<int, float>, 2, pack<double, int, float, int, long>> == 3);
static_assert(pack_nth_index_of_any_v<pack<int, float>, 3, pack<double, int, float, int, long>> == npos);
static_assert(pack_nth_index_of_any_v<pack<int, float>, 4, pack<int, int, int, int, int>> == 4);
static_assert(pack_nth_index_of_any_v<pack<char, long>, 0, pack<double, int, float>> == npos);
static_assert(pack_nth_index_of_any_v<pack<char, long>, 1, pack<double, int, float>> == npos);
static_assert(pack_nth_index_of_any_v<pack<char, long>, 1, pack<>> == npos);
static_assert(pack_nth_index_of_any_v<pack<>, 0, pack<>> == npos);
static_assert(pack_nth_index_of_any_v<pack<>, 0, pack<int, long, float>> == npos);
static_assert(pack_nth_index_of_any_v<pack<>, 1, pack<int, long, float>> == npos);

static_assert(pack_nth_index_filter_v<std::is_integral, 0, pack<double, int, float, int, long>> == 1);
static_assert(pack_nth_index_filter_v<std::is_integral, 1, pack<double, int, float, int, long>> == 3);
static_assert(pack_nth_index_filter_v<std::is_integral, 2, pack<double, int, float, int, long>> == 4);
static_assert(pack_nth_index_filter_v<std::is_integral, 3, pack<double, int, float, int, long>> == npos);
static_assert(pack_nth_index_filter_v<std::is_integral, 4, pack<int, int, int, int, int>> == 4);
static_assert(pack_nth_index_filter_v<std::is_integral, 0, pack<double, int, float>> == 1);
static_assert(pack_nth_index_filter_v<std::is_integral, 1, pack<double, int, float>> == npos);
static_assert(pack_nth_index_filter_v<std::is_integral, 0, pack<>> == npos);
static_assert(pack_nth_index_filter_v<std::is_integral, 1, pack<>> == npos);

static_assert(pack_index_of_v<int, pack<double, int, float, int>> == 1);
static_assert(pack_index_of_v<char, pack<double, int, float>> == npos);
static_assert(pack_index_of_v<char, pack<>> == npos);

static_assert(pack_index_of_any_v<pack<int, float>, pack<double, int, float, int>> == 1);
static_assert(pack_index_of_any_v<pack<char, long>, pack<double, int, float>> == npos);
static_assert(pack_index_of_any_v<pack<char>, pack<>> == npos);
static_assert(pack_index_of_any_v<pack<>, pack<>> == npos);
static_assert(pack_index_of_any_v<pack<>, pack<int, long, char>> == npos);

static_assert(pack_index_filter_v<std::is_integral, pack<double, int, float, int>> == 1);
static_assert(pack_index_filter_v<std::is_integral, pack<double, float>> == npos);
static_assert(pack_index_filter_v<std::is_integral, pack<>> == npos);

static_assert(pack_first_index_of_v<int, pack<double, int, float, int>> == 1);
static_assert(pack_first_index_of_v<char, pack<double, int, float>> == npos);
static_assert(pack_first_index_of_v<char, pack<>> == npos);

static_assert(pack_first_index_of_any_v<pack<int, float>, pack<double, int, float, int>> == 1);
static_assert(pack_first_index_of_any_v<pack<char, long>, pack<double, int, float>> == npos);
static_assert(pack_first_index_of_any_v<pack<char>, pack<>> == npos);
static_assert(pack_first_index_of_any_v<pack<>, pack<>> == npos);
static_assert(pack_first_index_of_any_v<pack<>, pack<int, long, char>> == npos);

static_assert(pack_first_index_filter_v<std::is_integral, pack<double, int, float, int>> == 1);
static_assert(pack_first_index_filter_v<std::is_integral, pack<double, float>> == npos);
static_assert(pack_first_index_filter_v<std::is_integral, pack<>> == npos);

static_assert(pack_last_index_of_v<int, pack<double, int, float, int>> == 3);
static_assert(pack_last_index_of_v<int, pack<double, int, float, char>> == 1);
static_assert(pack_last_index_of_v<char, pack<double, int, float>> == npos);
static_assert(pack_last_index_of_v<char, pack<>> == npos);

static_assert(pack_last_index_of_any_v<pack<int, float>, pack<double, int, float, int>> == 3);
static_assert(pack_last_index_of_any_v<pack<int, float>, pack<double, int, int, char>> == 2);
static_assert(pack_last_index_of_any_v<pack<int, float>, pack<double, int, float, char>> == 2);
static_assert(pack_last_index_of_any_v<pack<char, long>, pack<double, int, float>> == npos);
static_assert(pack_last_index_of_any_v<pack<char>, pack<>> == npos);
static_assert(pack_last_index_of_any_v<pack<>, pack<>> == npos);
static_assert(pack_last_index_of_any_v<pack<>, pack<int, long, char>> == npos);

static_assert(pack_last_index_filter_v<std::is_integral, pack<double, int, float, int>> == 3);
static_assert(pack_last_index_filter_v<std::is_integral, pack<double, int, float, float>> == 1);
static_assert(pack_last_index_filter_v<std::is_integral, pack<double, float>> == npos);
static_assert(pack_last_index_filter_v<std::is_integral, pack<>> == npos);

static_assert(std::same_as<pack_indices_of_t<int, pack<double, float, int, long, int>>, std::index_sequence<2, 4>>);
static_assert(std::same_as<pack_indices_of_t<int, pack<int, long, int>>, std::index_sequence<0, 2>>);
static_assert(std::same_as<pack_indices_of_t<char, pack<int, long, int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_of_t<char, pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_indices_of_all_t<pack<int, long>, pack<double, float, int, long, int>>, std::index_sequence<2, 3, 4>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<int, long>, pack<int, long, int>>, std::index_sequence<0, 1, 2>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<char, float>, pack<int, long, int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<char, float>, pack<>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<>, pack<>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<>, pack<int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_of_all_t<pack<>, pack<int, double, float>>, std::index_sequence<>>);

static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<double, float, int, long, int>>, std::index_sequence<2, 3, 4>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<int>>, std::index_sequence<0>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<int, double, float>>, std::index_sequence<0>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<double, float, int>>, std::index_sequence<2>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<int, long, int>>, std::index_sequence<0, 1, 2>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<float, double>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_filter_t<std::is_integral, pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<double, float, int, long, int>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<int, double, float>>, std::index_sequence<1, 2>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<double, float, int>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<int, long, int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<float, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_filter_t<std::is_integral, pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_indices_not_of_t<int, pack<double, float, int, long, int>>, std::index_sequence<0, 1, 3>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<int, double, float>>, std::index_sequence<1, 2>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<double, float, int>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<int, long, int>>, std::index_sequence<1>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<float, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_of_t<int, pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<double, float, int, long, int>>, std::index_sequence<0, 1, 3>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<int>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<int, double, float>>, std::index_sequence<1, 2>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<double, float, int>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<int, long, int>>, std::index_sequence<1>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<float, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int>, pack<>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<>, pack<>>, std::index_sequence<>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<>, pack<int, float>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int, float>, pack<int, double, float>>, std::index_sequence<1>>);
static_assert(std::same_as<pack_indices_not_of_all_t<pack<int, float>, pack<char, double, long>>, std::index_sequence<0, 1, 2>>);

static_assert(std::same_as<pack_first_indices_t<pack<int, double, int, float>>, std::index_sequence<0, 1, 3>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, double, char, float>>, std::index_sequence<0, 1, 2, 3>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, double, int, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, int, double, double>>, std::index_sequence<0, 2>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, int, int, int>>, std::index_sequence<0>>);
static_assert(std::same_as<pack_first_indices_t<pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_last_indices_t<pack<int, double, int, float>>, std::index_sequence<1, 2, 3>>);
static_assert(std::same_as<pack_last_indices_t<pack<int, double, char, float>>, std::index_sequence<0, 1, 2, 3>>);
static_assert(std::same_as<pack_last_indices_t<pack<int, double, int, double>>, std::index_sequence<2, 3>>);
static_assert(std::same_as<pack_last_indices_t<pack<int, int, double, double>>, std::index_sequence<1, 3>>);
static_assert(std::same_as<pack_last_indices_t<pack<int, int, int, int>>, std::index_sequence<3>>);
static_assert(std::same_as<pack_last_indices_t<pack<>>, std::index_sequence<>>);

static_assert(std::same_as<pack_nth_indices_t<0, pack<int, double, int, float>>, std::index_sequence<0, 1, 3>>);
static_assert(std::same_as<pack_nth_indices_t<0, pack<int, double, char, float>>, std::index_sequence<0, 1, 2, 3>>);
static_assert(std::same_as<pack_nth_indices_t<0, pack<int, double, int, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_nth_indices_t<1, pack<int, double, int, double>>, std::index_sequence<2, 3>>);
static_assert(std::same_as<pack_nth_indices_t<0, pack<int, int, double, double>>, std::index_sequence<0, 2>>);
static_assert(std::same_as<pack_nth_indices_t<1, pack<int, int, double, double>>, std::index_sequence<1, 3>>);
static_assert(std::same_as<pack_nth_indices_t<0, pack<int, int, int, int>>, std::index_sequence<0>>);
static_assert(std::same_as<pack_nth_indices_t<1, pack<int, int, int, int>>, std::index_sequence<1>>);
static_assert(std::same_as<pack_nth_indices_t<2, pack<int, int, int, int>>, std::index_sequence<2>>);
static_assert(std::same_as<pack_nth_indices_t<3, pack<int, int, int, int>>, std::index_sequence<3>>);
static_assert(std::same_as<pack_nth_indices_t<0, pack<>>, std::index_sequence<>>);
static_assert(std::same_as<pack_nth_indices_t<1, pack<int, double, int, float>>, std::index_sequence<2>>);
static_assert(std::same_as<pack_nth_indices_t<2, pack<int, double, int, float>>, std::index_sequence<>>);

static_assert(std::same_as<pack_at_indices_t<std::index_sequence<0>, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<0>, pack<int, float>>, pack<int>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<1>, pack<int, float>>, pack<float>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<0, 1>, pack<int, float>>, pack<int, float>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<0, 3>, pack<int, float, char, long>>, pack<int, long>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<1, 3>, pack<int, float, char, long>>, pack<float, long>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<1, 3, 1>, pack<int, float, char, long>>, pack<float, long, float>>);
static_assert(std::same_as<pack_at_indices_t<std::index_sequence<>, pack<int, float, char, long>>, pack<>>);

static_assert(std::same_as<pack_unique_t<pack<int, float, char, long>>, pack<int, float, char, long>>);
static_assert(std::same_as<pack_unique_t<pack<int, float, int, long>>, pack<int, float, long>>);
static_assert(std::same_as<pack_unique_t<pack<int, int, int, long>>, pack<int, long>>);
static_assert(std::same_as<pack_unique_t<pack<long, int, int, long>>, pack<long, int>>);
static_assert(std::same_as<pack_unique_t<pack<int>>, pack<int>>);
static_assert(std::same_as<pack_unique_t<pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_t<0, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_drop_t<1, pack<int, double>>, pack<double>>);
static_assert(std::same_as<pack_drop_t<2, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_drop_t<1, pack<int>>, pack<>>);
static_assert(std::same_as<pack_drop_t<0, pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_while_t<std::is_integral, pack<int, double>>, pack<double>>);
static_assert(std::same_as<pack_drop_while_t<std::is_integral, pack<double, int>>, pack<double, int>>);
static_assert(std::same_as<pack_drop_while_t<std::is_integral, pack<int>>, pack<>>);
static_assert(std::same_as<pack_drop_while_t<std::is_integral, pack<double>>, pack<double>>);
static_assert(std::same_as<pack_drop_while_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_until_t<std::is_integral, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_drop_until_t<std::is_integral, pack<double, int>>, pack<int>>);
static_assert(std::same_as<pack_drop_until_t<std::is_integral, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_drop_until_t<std::is_integral, pack<double>>, pack<>>);
static_assert(std::same_as<pack_drop_until_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_t<0, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_take_t<1, pack<int, double>>, pack<int>>);
static_assert(std::same_as<pack_take_t<2, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_take_t<1, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_take_t<0, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_while_t<std::is_integral, pack<int, double>>, pack<int>>);
static_assert(std::same_as<pack_take_while_t<std::is_integral, pack<double, int>>, pack<>>);
static_assert(std::same_as<pack_take_while_t<std::is_integral, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_take_while_t<std::is_integral, pack<double>>, pack<>>);
static_assert(std::same_as<pack_take_while_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_until_t<std::is_integral, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_take_until_t<std::is_integral, pack<double, int>>, pack<double>>);
static_assert(std::same_as<pack_take_until_t<std::is_integral, pack<int>>, pack<>>);
static_assert(std::same_as<pack_take_until_t<std::is_integral, pack<double>>, pack<double>>);
static_assert(std::same_as<pack_take_until_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_last_t<0, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_drop_last_t<1, pack<int, double>>, pack<int>>);
static_assert(std::same_as<pack_drop_last_t<2, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_drop_last_t<1, pack<int>>, pack<>>);
static_assert(std::same_as<pack_drop_last_t<0, pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_last_while_t<std::is_integral, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_drop_last_while_t<std::is_integral, pack<double, int>>, pack<double>>);
static_assert(std::same_as<pack_drop_last_while_t<std::is_integral, pack<int>>, pack<>>);
static_assert(std::same_as<pack_drop_last_while_t<std::is_integral, pack<double>>, pack<double>>);
static_assert(std::same_as<pack_drop_last_while_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_drop_last_until_t<std::is_integral, pack<int, double>>, pack<int>>);
static_assert(std::same_as<pack_drop_last_until_t<std::is_integral, pack<double, int>>, pack<double, int>>);
static_assert(std::same_as<pack_drop_last_until_t<std::is_integral, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_drop_last_until_t<std::is_integral, pack<double>>, pack<>>);
static_assert(std::same_as<pack_drop_last_until_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_last_t<0, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_take_last_t<1, pack<int, double>>, pack<double>>);
static_assert(std::same_as<pack_take_last_t<2, pack<int, double>>, pack<int, double>>);
static_assert(std::same_as<pack_take_last_t<1, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_take_last_t<0, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_last_while_t<std::is_integral, pack<int, double>>, pack<>>);
static_assert(std::same_as<pack_take_last_while_t<std::is_integral, pack<double, int>>, pack<int>>);
static_assert(std::same_as<pack_take_last_while_t<std::is_integral, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_take_last_while_t<std::is_integral, pack<double>>, pack<>>);
static_assert(std::same_as<pack_take_last_while_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_take_last_until_t<std::is_integral, pack<int, double>>, pack<double>>);
static_assert(std::same_as<pack_take_last_until_t<std::is_integral, pack<double, int>>, pack<>>);
static_assert(std::same_as<pack_take_last_until_t<std::is_integral, pack<int>>, pack<>>);
static_assert(std::same_as<pack_take_last_until_t<std::is_integral, pack<double>>, pack<double>>);
static_assert(std::same_as<pack_take_last_until_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_concat_t<pack<>>, pack<>>);
static_assert(std::same_as<pack_concat_t<pack<>, pack<>>, pack<>>);
static_assert(std::same_as<pack_concat_t<pack<>, pack<>, pack<>>, pack<>>);
static_assert(std::same_as<pack_concat_t<pack<int>, pack<>, pack<>>, pack<int>>);
static_assert(std::same_as<pack_concat_t<pack<>, pack<int>, pack<>>, pack<int>>);
static_assert(std::same_as<pack_concat_t<pack<>, pack<>, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_concat_t<pack<int>, pack<char>, pack<>>, pack<int, char>>);
static_assert(std::same_as<pack_concat_t<pack<int>, pack<>, pack<char>>, pack<int, char>>);
static_assert(std::same_as<pack_concat_t<pack<>, pack<int>, pack<char>>, pack<int, char>>);
static_assert(std::same_as<pack_concat_t<pack<int>, pack<long>, pack<char>>, pack<int, long, char>>);
static_assert(std::same_as<pack_concat_t<pack<int, long>, pack<char>>, pack<int, long, char>>);
static_assert(std::same_as<pack_concat_t<pack<int>, pack<long, char>>, pack<int, long, char>>);

static_assert(std::same_as<pack_erase_t<0, pack<int, long, int>>, pack<long, int>>);
static_assert(std::same_as<pack_erase_t<1, pack<int, long, int>>, pack<int, int>>);
static_assert(std::same_as<pack_erase_t<2, pack<int, long, int>>, pack<int, long>>);

static_assert(std::same_as<pack_erase_all_t<std::index_sequence<0>, pack<int, long, int>>, pack<long, int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<1>, pack<int, long, int>>, pack<int, int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<2>, pack<int, long, int>>, pack<int, long>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<0, 2>, pack<int, long, int>>, pack<long>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<0, 1>, pack<int, long, int>>, pack<int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<1, 2>, pack<int, long, int>>, pack<int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<1, 1>, pack<int, long, int>>, pack<int, int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<>, pack<int, long, int>>, pack<int, long, int>>);
static_assert(std::same_as<pack_erase_all_t<std::index_sequence<>, pack<>>, pack<>>);

static_assert(std::same_as<pack_insert_t<int, 0, pack<float, long, double>>, pack<int, float, long, double>>);
static_assert(std::same_as<pack_insert_t<int, 1, pack<float, long, double>>, pack<float, int, long, double>>);
static_assert(std::same_as<pack_insert_t<int, 2, pack<float, long, double>>, pack<float, long, int, double>>);
static_assert(std::same_as<pack_insert_t<int, 3, pack<float, long, double>>, pack<float, long, double, int>>);
static_assert(std::same_as<pack_insert_t<int, 0, pack<>>, pack<int>>);

static_assert(std::same_as<pack_insert_all_t<pack<int, char>, 0, pack<float, long, double>>, pack<int, char, float, long, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<int, char>, 1, pack<float, long, double>>, pack<float, int, char, long, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<int, char>, 2, pack<float, long, double>>, pack<float, long, int, char, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<int, char>, 3, pack<float, long, double>>, pack<float, long, double, int, char>>);
static_assert(std::same_as<pack_insert_all_t<pack<int, char>, 0, pack<>>, pack<int, char>>);
static_assert(std::same_as<pack_insert_all_t<pack<>, 0, pack<>>, pack<>>);
static_assert(std::same_as<pack_insert_all_t<pack<>, 0, pack<float, long, double>>, pack<float, long, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<>, 1, pack<float, long, double>>, pack<float, long, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<>, 2, pack<float, long, double>>, pack<float, long, double>>);
static_assert(std::same_as<pack_insert_all_t<pack<>, 3, pack<float, long, double>>, pack<float, long, double>>);

static_assert(std::same_as<pack_filter_t<std::is_integral, pack<float, long, double>>, pack<long>>);
static_assert(std::same_as<pack_filter_t<std::is_integral, pack<float, double>>, pack<>>);
static_assert(std::same_as<pack_filter_t<std::is_integral, pack<char, long>>, pack<char, long>>);
static_assert(std::same_as<pack_filter_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_erase_filter_t<std::is_integral, pack<float, long, double>>, pack<float, double>>);
static_assert(std::same_as<pack_erase_filter_t<std::is_integral, pack<float, double>>, pack<float, double>>);
static_assert(std::same_as<pack_erase_filter_t<std::is_integral, pack<char, long>>, pack<>>);
static_assert(std::same_as<pack_erase_filter_t<std::is_integral, pack<>>, pack<>>);

static_assert(std::same_as<pack_remove_t<int, pack<float, int, double, int>>, pack<float, double>>);
static_assert(std::same_as<pack_remove_t<int, pack<float, double>>, pack<float, double>>);
static_assert(std::same_as<pack_remove_t<int, pack<>>, pack<>>);

static_assert(std::same_as<pack_remove_all_t<pack<int>, pack<float, int, double, int>>, pack<float, double>>);
static_assert(std::same_as<pack_remove_all_t<pack<int>, pack<float, double>>, pack<float, double>>);
static_assert(std::same_as<pack_remove_all_t<pack<int>, pack<>>, pack<>>);
static_assert(std::same_as<pack_remove_all_t<pack<>, pack<>>, pack<>>);
static_assert(std::same_as<pack_remove_all_t<pack<>, pack<float, int>>, pack<float, int>>);

static_assert(std::same_as<pack_reverse_t<pack<float, int, char>>, pack<char, int, float>>);
static_assert(std::same_as<pack_reverse_t<pack<float, int>>, pack<int, float>>);
static_assert(std::same_as<pack_reverse_t<pack<int>>, pack<int>>);
static_assert(std::same_as<pack_reverse_t<pack<>>, pack<>>);

template<class Ty> using transform_to_int = int;
template<class Ty> using transform_to_self = Ty;

static_assert(std::same_as<pack_transform_t<transform_to_int, pack<>>, pack<>>);
static_assert(std::same_as<pack_transform_t<transform_to_int, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_transform_t<transform_to_int, pack<float>>, pack<int>>);
static_assert(std::same_as<pack_transform_t<transform_to_int, pack<float, int>>, pack<int, int>>);
static_assert(std::same_as<pack_transform_t<transform_to_self, pack<float, int>>, pack<float, int>>);
static_assert(std::same_as<pack_transform_t<conditional_transform<std::is_integral, transform_to_int>::type, pack<float, char>>, pack<float, int>>);

static_assert(std::same_as<pack_append_t<char, pack<float, int>>, pack<float, int, char>>);
static_assert(std::same_as<pack_append_t<char, pack<>>, pack<char>>);

static_assert(std::same_as<pack_append_all_t<pack<char>, pack<float, int>>, pack<float, int, char>>);
static_assert(std::same_as<pack_append_all_t<pack<char>, pack<>>, pack<char>>);
static_assert(std::same_as<pack_append_all_t<pack<char, int>, pack<float, long>>, pack<float, long, char, int>>);
static_assert(std::same_as<pack_append_all_t<pack<char, int>, pack<>>, pack<char, int>>);

static_assert(std::same_as<pack_prepend_t<char, pack<float, int>>, pack<char, float, int>>);
static_assert(std::same_as<pack_prepend_t<char, pack<>>, pack<char>>);

static_assert(std::same_as<pack_prepend_all_t<pack<char>, pack<float, int>>, pack<char, float, int>>);
static_assert(std::same_as<pack_prepend_all_t<pack<char>, pack<>>, pack<char>>);
static_assert(std::same_as<pack_prepend_all_t<pack<char, int>, pack<float, long>>, pack<char, int, float, long>>);
static_assert(std::same_as<pack_prepend_all_t<pack<char, int>, pack<>>, pack<char, int>>);

static_assert(std::same_as<pack_swap_t<int, 0, pack<float, char, double>>, pack<int, char, double>>);
static_assert(std::same_as<pack_swap_t<int, 1, pack<float, char, double>>, pack<float, int, double>>);
static_assert(std::same_as<pack_swap_t<int, 2, pack<float, char, double>>, pack<float, char, int>>);
static_assert(std::same_as<pack_swap_t<int, 0, pack<char>>, pack<int>>);
static_assert(std::same_as<pack_swap_t<int, 0, pack<int>>, pack<int>>);

static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<0>, pack<float, char, double>>, pack<int, char, double>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<1>, pack<float, char, double>>, pack<float, int, double>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<2>, pack<float, char, double>>, pack<float, char, int>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<0>, pack<char>>, pack<int>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<0>, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<0, 2>, pack<float, char, double>>, pack<int, char, int>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<0, 1>, pack<float, char, double>>, pack<int, int, double>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<1, 2>, pack<float, char, double>>, pack<float, int, int>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<1, 1>, pack<float, char, double>>, pack<float, int, double>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<>, pack<float, char, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_swap_all_t<int, std::index_sequence<>, pack<>>, pack<>>);

static_assert(std::same_as<pack_replace_t<int, char, pack<float, char, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_t<int, char, pack<float, int, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_t<int, char, pack<int, int, double>>, pack<char, char, double>>);
static_assert(std::same_as<pack_replace_t<int, char, pack<int, int, int>>, pack<char, char, char>>);
static_assert(std::same_as<pack_replace_t<int, char, pack<>>, pack<>>);

static_assert(std::same_as<pack_replace_all_t<pack<int>, char, pack<float, char, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_all_t<pack<int>, char, pack<float, int, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_all_t<pack<int>, char, pack<int, int, double>>, pack<char, char, double>>);
static_assert(std::same_as<pack_replace_all_t<pack<int>, char, pack<int, int, int>>, pack<char, char, char>>);
static_assert(std::same_as<pack_replace_all_t<pack<int>, char, pack<>>, pack<>>);
static_assert(std::same_as<pack_replace_all_t<pack<int, float>, char, pack<float, int, int>>, pack<char, char, char>>);
static_assert(std::same_as<pack_replace_all_t<pack<int, float>, char, pack<float, int, double>>, pack<char, char, double>>);
static_assert(std::same_as<pack_replace_all_t<pack<>, char, pack<float, int, double>>, pack<float, int, double>>);
static_assert(std::same_as<pack_replace_all_t<pack<>, char, pack<>>, pack<>>);

static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<float, float, double>>, pack<float, float, double>>);
static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<float, char, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<float, int, double>>, pack<float, char, double>>);
static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<int, int, double>>, pack<char, char, double>>);
static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<int, int, int>>, pack<char, char, char>>);
static_assert(std::same_as<pack_replace_filter_t<std::is_integral, char, pack<>>, pack<>>);

static_assert(std::same_as<pack_sub_t<0, 1, pack<int, double, char, float, long>>, pack<int>>);
static_assert(std::same_as<pack_sub_t<0, 3, pack<int, double, char, float, long>>, pack<int, double, char>>);
static_assert(std::same_as<pack_sub_t<2, 3, pack<int, double, char, float, long>>, pack<char>>);
static_assert(std::same_as<pack_sub_t<4, 5, pack<int, double, char, float, long>>, pack<long>>);
static_assert(std::same_as<pack_sub_t<5, 5, pack<int, double, char, float, long>>, pack<>>);
static_assert(std::same_as<pack_sub_t<0, 5, pack<int, double, char, float, long>>, pack<int, double, char, float, long>>);
static_assert(std::same_as<pack_sub_t<0, 0, pack<>>, pack<>>);

template<class A, class B>
struct sort_on_size {
    constexpr static bool value = sizeof(A) < sizeof(B);
};

static_assert(std::same_as<pack_sort_t<sort_on_size, pack<double, char, int>>, pack<char, int, double>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<char, double, int>>, pack<char, int, double>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<int, double, char>>, pack<char, int, double>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<char, int, double>>, pack<char, int, double>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<int, char, double>>, pack<char, int, double>>);
static_assert(std::same_as<pack_sort_t<sorter_reverse<sort_on_size>::type, pack<double, char, int>>, pack<double, int, char>>);
static_assert(std::same_as<pack_sort_t<sorter_reverse<sort_on_size>::type, pack<char, double, int>>, pack<double, int, char>>);
static_assert(std::same_as<pack_sort_t<sorter_reverse<sort_on_size>::type, pack<int, double, char>>, pack<double, int, char>>);
static_assert(std::same_as<pack_sort_t<sorter_reverse<sort_on_size>::type, pack<char, int, double>>, pack<double, int, char>>);
static_assert(std::same_as<pack_sort_t<sorter_reverse<sort_on_size>::type, pack<int, char, double>>, pack<double, int, char>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<int>>, pack<int>>);
static_assert(std::same_as<pack_sort_t<sort_on_size, pack<>>, pack<>>);

// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------

using namespace kaixo::tuples;
using namespace kaixo::views;

constexpr auto aioneefae1 = std::tuple_size_v<std::tuple<int>>;
constexpr auto aioneefae2 = std::tuple_size_v<std::tuple<int&>>;
constexpr auto aioneefae3 = std::tuple_size_v<std::tuple<int&&>>;
constexpr auto aioneefae4 = std::tuple_size_v<std::tuple<const int>>;
constexpr auto aioneefae5 = std::tuple_size_v<std::tuple<const int&>>;
constexpr auto aioneefae6 = std::tuple_size_v<std::tuple<const int&&>>;

// Check that std::get gives same cv-ref qualifiers on view as with normal tuple
template<class Tuple>
constexpr bool compare_get = std::same_as<
    decltype(std::get<0>(std::declval<all_t<Tuple>>() | take<1>)),
    decltype(std::get<0>(std::declval<Tuple>()))>;

static_assert(compare_get<std::tuple<int>>);
static_assert(compare_get<std::tuple<int&>>);
static_assert(compare_get<std::tuple<int&&>>);
static_assert(compare_get<std::tuple<int>&>);
static_assert(compare_get<std::tuple<int&>&>);
static_assert(compare_get<std::tuple<int&&>&>);
static_assert(compare_get<std::tuple<int>&&>);
static_assert(compare_get<std::tuple<int&>&&>);
static_assert(compare_get<std::tuple<int&&>&&>);
static_assert(compare_get<std::tuple<const int>>);
static_assert(compare_get<std::tuple<const int&>>);
static_assert(compare_get<std::tuple<const int&&>>);
static_assert(compare_get<std::tuple<const int>&>);
static_assert(compare_get<std::tuple<const int&>&>);
static_assert(compare_get<std::tuple<const int&&>&>);
static_assert(compare_get<std::tuple<const int>&&>);
static_assert(compare_get<std::tuple<const int&>&&>);
static_assert(compare_get<std::tuple<const int&&>&&>);
static_assert(compare_get<const std::tuple<int>&>);
static_assert(compare_get<const std::tuple<int&>&>);
static_assert(compare_get<const std::tuple<int&&>&>);
static_assert(compare_get<const std::tuple<const int>&>);
static_assert(compare_get<const std::tuple<const int&>&>);
static_assert(compare_get<const std::tuple<const int&&>&>);


// Check that both get and forward give the expected qualifiers
// the parts that are commented out are invalid because the tuple contains an rvalue
// which would have to be copied. And that is not possible.


// get


// value is value

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>&&>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>&&>().template get<0>()), const int&&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>&&>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>&&>().template get<0>()), const int&&>);

// ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>&&>().template get<0>()), int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>&&>().template get<0>()), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>&&>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>&&>().template get<0>()), const int&&>);

// value is const value

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>&&>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>&&>().template get<0>()), const int&&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>&&>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>&&>().template get<0>()), const int&&>);

// ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>&&>().template get<0>()), const int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>&&>().template get<0>()), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>&&>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>&&>().template get<0>()), const int&&>);

// value is reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>&&>().template get<0>()), int&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>&&>().template get<0>()), int&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>&&>().template get<0>()), int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>&&>().template get<0>()), int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>&&>().template get<0>()), int&>);

// value is rvalue reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>&&>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>>().template get<0>()), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>&&>().template get<0>()), int&&>);

// const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>&>().template get<0>()), int&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>&&>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>&>().template get<0>()), int&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>&&>().template get<0>()), int&&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>&&>().template get<0>()), int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>&&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>&>().template get<0>()), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>&&>().template get<0>()), int&>);

// copied const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>&>().template get<0>()), int&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>&&>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>>().template get<0>()), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>&>().template get<0>()), int&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>&&>().template get<0>()), int&&>);

// value is const reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>&&>().template get<0>()), const int&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>&&>().template get<0>()), const int&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>&&>().template get<0>()), const int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>&&>().template get<0>()), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>&&>().template get<0>()), const int&>);

// value is const rvalue reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>&&>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>>().template get<0>()), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>&&>().template get<0>()), const int&&>);

// const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>&>().template get<0>()), const int&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>&&>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>&>().template get<0>()), const int&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>&&>().template get<0>()), const int&&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>&&>().template get<0>()), const int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>&&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>&>().template get<0>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>&&>().template get<0>()), const int&>);

// copied const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>&>().template get<0>()), const int&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>&&>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>>().template get<0>()), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>&>().template get<0>()), const int&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>&&>().template get<0>()), const int&&>);


// forwarding


// value is value

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>>&&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>>&&>() | forward<0>), const int&&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>>&&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>>&&>() | forward<0>), const int&&>);

// ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int>&>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int>&>&&>() | forward<0>), int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&>&&>() | forward<0>), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int>&&>&&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int>&&>&&>() | forward<0>), const int&&>);

// value is const value

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>>&&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>>&&>() | forward<0>), const int&&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>>&&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>>&&>() | forward<0>), const int&&>);

// ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int>&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int>&>&&>() | forward<0>), const int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&>&&>() | forward<0>), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int>&&>&&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int>&&>&&>() | forward<0>), const int&&>);

// value is reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>>&&>() | forward<0>), int&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>>&&>() | forward<0>), int&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&>&>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&>&>&&>() | forward<0>), int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&>&&>() | forward<0>), int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&>&&>&&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>&>() | forward<0>), int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&>&&>&&>() | forward<0>), int&>);

// value is rvalue reference

// owning view
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>>&&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>>&&>() | forward<0>), int&&>);

// const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>>&&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>>&&>() | forward<0>), int&&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<int&&>&>&&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<int&&>&>&&>() | forward<0>), int&&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&>&&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>&>() | forward<0>), int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&>&&>() | forward<0>), int&&>);

// copied const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<int&&>&&>&&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>&>() | forward<0>), int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<int&&>&&>&&>() | forward<0>), int&&>);

// value is const reference

// owning view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>>&&>() | forward<0>), const int&>);

// const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>>&&>() | forward<0>), const int&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&>&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&>&>&&>() | forward<0>), const int&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&>&&>() | forward<0>), const int&>);

// copied const owning view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&>&&>&&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>&>() | forward<0>), const int&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&>&&>&&>() | forward<0>), const int&>);

// value is const rvalue reference

// owning view
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>>&&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>>&&>() | forward<0>), const int&&>);

// const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>>&&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>>&&>() | forward<0>), const int&&>);

// Ref view
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<std::tuple<const int&&>&>&&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<std::tuple<const int&&>&>&&>() | forward<0>), const int&&>);

// const ref view
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&>&&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>&>() | forward<0>), const int&&>);
static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&>&&>() | forward<0>), const int&&>);

// copied const owning view
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<all_t<const std::tuple<const int&&>&&>&&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>&>() | forward<0>), const int&&>);
//static_assert(std::same_as<decltype(std::declval<const all_t<const std::tuple<const int&&>&&>&&>() | forward<0>), const int&&>);



// Other tests
constexpr std::tuple<int, double, float> value{ 1, 2., 3.f };
constexpr std::tuple<int, double, int> duple{ 1, 2., 3 };
constexpr std::tuple<> empty{};

static_assert(std::same_as<as_pack_t<decltype(value | drop<0>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop<1>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop<3>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop<0>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | drop_while<std::is_integral>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_while<std::is_floating_point>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop_while<std::is_integral>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | drop_until<std::is_floating_point>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_until<std::is_integral>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop_until<std::is_floating_point>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take<0>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(value | take<1>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | take<3>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take<0>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take_while<std::is_integral>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_while<std::is_floating_point>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take_while<std::is_integral>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take_until<std::is_floating_point>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_until<std::is_integral>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take_until<std::is_floating_point>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | drop_last<0>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_last<1>)>, pack<int, double>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_last<3>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop_last<0>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | drop_last_while<std::is_floating_point>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_last_while<std::is_integral>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop_last_while<std::is_floating_point>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | drop_last_until<std::is_integral>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | drop_last_until<std::is_floating_point>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | drop_last_until<std::is_integral>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take_last<0>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_last<1>)>, pack<float>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_last<3>)>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take_last<0>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take_last_while<std::is_floating_point>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_last_while<std::is_integral>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take_last_while<std::is_floating_point>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | take_last_until<std::is_integral>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | take_last_until<std::is_floating_point>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | take_last_until<std::is_integral>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(value | sub<1, 3>)>, pack<double, float>>);
static_assert(std::same_as<as_pack_t<decltype(value | sub<0, 1>)>, pack<int>>);
static_assert(std::same_as<as_pack_t<decltype(value | sub<2, 3>)>, pack<float>>);
static_assert(std::same_as<as_pack_t<decltype(value | sub<2, 2>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(value | sub<0, 0>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(empty | sub<0, 0>)>, pack<>>);

static_assert(std::same_as<as_pack_t<decltype(duple | unique)>, pack<int, double>>);
static_assert((duple | unique).get<0>() == 1);
static_assert((duple | unique).get<1>() == 2.0);

static_assert(std::same_as<as_pack_t<decltype(duple | first_unique)>, pack<int, double>>);
static_assert((duple | first_unique).get<0>() == 1);
static_assert((duple | first_unique).get<1>() == 2.0);

static_assert(std::same_as<as_pack_t<decltype(duple | last_unique)>, pack<double, int>>);
static_assert((duple | last_unique).get<0>() == 2.0);
static_assert((duple | last_unique).get<1>() == 3);

static_assert(std::same_as<as_pack_t<decltype(duple | nth_unique<1>)>, pack<int>>);
static_assert((duple | nth_unique<1>).get<0>() == 3);

static_assert(std::same_as<as_pack_t<decltype(duple | views::remove<int>)>, pack<double>>);
static_assert((duple | views::remove<int>).get<0>() == 2.0);

static_assert(std::same_as<as_pack_t<decltype(duple | remove_all<pack<int, double>>)>, pack<>>);
static_assert(std::same_as<as_pack_t<decltype(duple | remove_all<pack<int>>)>, pack<double>>);
static_assert((duple | remove_all<pack<int>>).get<0>() == 2.0);
static_assert(std::same_as<as_pack_t<decltype(duple | remove_all<pack<>>)>, pack<int, double, int>>);
static_assert((duple | remove_all<pack<>>).get<0>() == 1);
static_assert((duple | remove_all<pack<>>).get<1>() == 2.0);
static_assert((duple | remove_all<pack<>>).get<2>() == 3);

static_assert(std::same_as<as_pack_t<decltype(duple | filter<std::is_integral>)>, pack<int, int>>);
static_assert((duple | filter<std::is_integral>).get<0>() == 1);
static_assert((duple | filter<std::is_integral>).get<1>() == 3);
static_assert(std::same_as<as_pack_t<decltype(duple | filter<std::is_floating_point>)>, pack<double>>);
static_assert((duple | filter<std::is_floating_point>).get<0>() == 2.0);

static_assert(std::same_as<as_pack_t<decltype(duple | erase_filter<std::is_floating_point>)>, pack<int, int>>);
static_assert((duple | erase_filter<std::is_floating_point>).get<0>() == 1);
static_assert((duple | erase_filter<std::is_floating_point>).get<1>() == 3);
static_assert(std::same_as<as_pack_t<decltype(duple | erase_filter<std::is_integral>)>, pack<double>>);
static_assert((duple | erase_filter<std::is_integral>).get<0>() == 2.0);

constexpr long single = 10;

static_assert(std::same_as<as_pack_t<decltype(duple | insert<0>(1.f, single))>, pack<float, const long&, int, double, int>>);
static_assert(std::same_as<as_pack_t<decltype(duple | insert<1>(single, 2.f))>, pack<int, const long&, float, double, int>>);
static_assert(std::same_as<as_pack_t<decltype(duple | insert<3>(1.f, single))>, pack<int, double, int, float, const long&>>);
static_assert(std::same_as<as_pack_t<decltype(empty | insert<0>(single, 2.f))>, pack<const long&, float>>);
static_assert((duple | insert<0>(4)).get<0>() == 4);
static_assert((duple | insert<1>(4)).get<1>() == 4);
static_assert((duple | insert<2>(4)).get<2>() == 4);
static_assert((duple | insert<3>(4)).get<3>() == 4);
static_assert((duple | insert<0>(single)).get<0>() == single);
static_assert((duple | insert<1>(single)).get<1>() == single);
static_assert((duple | insert<2>(single)).get<2>() == single);
static_assert((duple | insert<3>(single)).get<3>() == single);
static_assert((empty | insert<0>(4, 5, 6)).get<2>() == 6);
static_assert((empty | insert<0>(4, single, 6)).get<1>() == single);

static_assert(std::same_as<as_pack_t<decltype(duple | prepend(single, 2.f))>, pack<const long&, float, int, double, int>>);
static_assert(std::same_as<as_pack_t<decltype(empty | prepend(1.f, single))>, pack<float, const long&>>);
static_assert(std::same_as<as_pack_t<decltype(empty | prepend(single))>, pack<const long&>>);
static_assert((duple | prepend(4)).get<0>() == 4);
static_assert((duple | prepend(single)).get<0>() == single);
static_assert((empty | prepend(4, 5, 6)).get<2>() == 6);
static_assert((empty | prepend(4, single, 6)).get<1>() == single);

static_assert(std::same_as<as_pack_t<decltype(duple | append(single, 2.f))>, pack<int, double, int, const long&, float>>);
static_assert(std::same_as<as_pack_t<decltype(empty | append(1.f, single))>, pack<float, const long&>>);
static_assert(std::same_as<as_pack_t<decltype(empty | append(single))>, pack<const long&>>);
static_assert((duple | append(4)).get<3>() == 4);
static_assert((duple | append(single)).get<3>() == single);
static_assert((empty | append(4, 5, 6)).get<2>() == 6);
static_assert((empty | append(4, single, 6)).get<1>() == single);

// Check whether inserted values also give correct expected qualifiers

using inserted_tuple_value = decltype(duple | insert<0>(std::declval<long>()));
static_assert(std::same_as<inserted_tuple_value::element<0>, long>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&&>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value>().get<0>()), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&&>().get<0>()), long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value>().get<0>()), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&&>().get<0>()), const long&&>);

// Check that original values still work as well
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&&>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&&>() | forward<1>), const int&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value>().get<1>()), const int&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&>().get<1>()), const int&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_value&&>().get<1>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value>().get<1>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&>().get<1>()), const int&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_value&&>().get<1>()), const int&>);

using inserted_tuple_rvalue = decltype(duple | insert<0>(std::declval<long&&>()));
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue&>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue&&>() | forward<0>), long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue&&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue>().get<0>()), long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue&>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_rvalue&&>().get<0>()), long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue>().get<0>()), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_rvalue&&>().get<0>()), const long&&>);

using inserted_tuple_lvalue = decltype(duple | insert<0>(std::declval<long&>()));
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue&>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue&&>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue&>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue&&>() | forward<0>), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue&>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_lvalue&&>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue&>().get<0>()), long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_lvalue&&>().get<0>()), long&>);

using inserted_tuple_clvalue = decltype(duple | insert<0>(std::declval<const long&>()));
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue&>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue&&>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue&>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue&&>() | forward<0>), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_clvalue&&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_clvalue&&>().get<0>()), const long&>);

using inserted_tuple_crvalue = decltype(duple | insert<0>(std::declval<const long&&>()));
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue&&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue&&>() | forward<0>), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue>().get<0>()), const long&&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<inserted_tuple_crvalue&&>().get<0>()), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue>().get<0>()), const long&&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue&>().get<0>()), const long&>);
static_assert(std::same_as<decltype(std::declval<const inserted_tuple_crvalue&&>().get<0>()), const long&&>);

static_assert(std::same_as<as_pack_t<decltype(concat(duple, value))>, pack<int, double, int, int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(concat(value, duple))>, pack<int, double, float, int, double, int>>);
static_assert(std::same_as<as_pack_t<decltype(concat(value, empty))>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(concat(empty, value))>, pack<int, double, float>>);
static_assert(std::same_as<as_pack_t<decltype(concat(duple, empty))>, pack<int, double, int>>);
static_assert(std::same_as<as_pack_t<decltype(concat(empty, duple))>, pack<int, double, int>>);
static_assert(concat(duple, value).get<0>() == 1);
static_assert(concat(duple, value).get<1>() == 2.0);
static_assert(concat(duple, value).get<2>() == 3);
static_assert(concat(duple, value).get<3>() == 1);
static_assert(concat(duple, value).get<4>() == 2.0);
static_assert(concat(duple, value).get<5>() == 3.f);
static_assert(concat(empty, value).get<0>() == 1);
static_assert(concat(value, empty).get<0>() == 1);

// ------------------------------------------------

int main() {}

// ------------------------------------------------

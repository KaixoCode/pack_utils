# pack utils

Single header template pack utilities. Here is a list of features:

```cpp
// Size of Pack
pack_size<Pack>

// Ith element in Pack
pack_element<I, Pack>

// Pack contains Type
pack_contains<Type, Pack>

// Pack contains all in Types
pack_contains_all<Types, Pack>

// Pack contains any in Types
pack_contains_any<Types, Pack>

// Find match for Filter in Pack
pack_find<Filter, Pack>

// Number of occurences of Type in Pack
pack_count<Type, Pack>

// Sum of the number of occurences of all Types in Pack
pack_count_all<Types, Pack>

// Count unique elements in Pack
pack_count_unique<Pack>

// Count number of matches for Filter in Pack
pack_count_filter<Filter, Pack>

// Index of the Nth occurence of Type in Pack
pack_nth_index_of<Type, N, Pack>

// Index of the Nth occurence of any of Types in Pack
pack_nth_index_of_any<Types, N, Pack>

// Index of the Nth match of Filter in Pack
pack_nth_index_filter<Filter, N, Pack>

// Index of the first occurence of Type in Pack
pack_index_of<Type, Pack>

// Index of the first occurence of any of Types in Pack
pack_index_of_any<Types, Pack>

// Index of the first match of Filter in Pack
pack_index_filter<Filter, Pack>

// Index of the first occurence of Type in Pack
pack_first_index_of<Type, Pack>

// Index of the first occurence of any of Types in Pack
pack_first_index_of_any<Types, Pack>

// Index of the first match of Filter in Pack
pack_first_index_filter<Filter, Pack>

// Index of the last occurence of Type in Pack
pack_last_index_of<Type, Pack>

// Index of the last occurence of any of Types in Pack
pack_last_index_of_any<Types, Pack>

// Index of the last match of Filter in Pack
pack_last_index_filter<Filter, Pack>

// All indices of Type in Pack
pack_indices_of<Type, Pack>

// All indices of all Types in Pack
pack_indices_of_all<Types, Pack>

// All indices of all matches of Filter in Pack
pack_indices_filter<Filter, Pack>

// First indices of all elements in Pack
pack_first_indices<Pack>

// Create new pack by selecting Indices from Pack
pack_at_indices<Indices, Pack>

// Only keep unique elements in Pack
pack_unique<Pack>

// Drop the first I elements of Pack
pack_drop<I, Pack>

// Drop elements from Pack while Filter matches
pack_drop_while<Filter, Pack>

// Drop elements from Pack until Filter matches
pack_drop_until<Filter, Pack>

// Take the first I elements of Pack
pack_take<I, Pack>

// Take elements from Pack while Filter matches
pack_take_while<Filter, Pack>

// Take elements from Pack until Filter matches
pack_take_until<Filter, Pack>

// Drop the last I elements of Pack
pack_drop_last<I, Pack>

// Drop elements from the end of Pack while Filter matches
pack_drop_last_while<Filter, Pack>

// Drop elements from the end of Pack until Filter matches
pack_drop_last_until<Filter, Pack>

// Take the last I elements of Pack
pack_take_last<I, Pack>

// Take elements from the end of Pack while Filter matches
pack_take_last_while<Filter, Pack>

// Take elements from the end of Pack until Filter matches
pack_take_last_until<Filter, Pack>

// Concat all types in all Packs to single pack
pack_concat<Packs...>

// Erase index I from Pack
pack_erase<I, Pack>

// Erase all Indices from Pack
pack_erase_all<Indices, Pack>

// Insert Type in Pack at index I
pack_insert<Type, I, Pack>

// Insert all Types in Pack at index I
pack_insert_all<Types, I, Pack>

// Only keep matches of Filter in Pack
pack_filter<Filter, Pack>

// Remove matches of Filter from Pack
pack_erase_filter<Filter, Pack>

// Remove Type from Pack
pack_remove<Type, Pack>

// Remove all Types from Pack
pack_remove_all<Types, Pack>

// Reverse order of elements in Pack
pack_reverse<Pack>

// Transform elements in Pack using Transform
pack_transform<Transform, Pack>

// Append Type to Pack
pack_append<Type, Pack>

// Append all Types to Pack
pack_append_all<Types, Pack>

// Prepend Type to Pack
pack_prepend<Type, Pack>

// Prepend all Types to Pack
pack_prepend_all<Types, Pack>

// Swap element I of Pack with Type
pack_swap<Type, I, Pack>

// Swap all elements at Indices in Pack with Type
pack_swap_all<Type, Indices, Pack>

// Replace Type in Pack with Replacement
pack_replace<Type, Replacement, Pack>

// Replace all matches of Filter in Pack with Replacement
pack_replace_filter<Filter, Replacement, Pack>

// Keep indices from Start to End in Pack
pack_sub<Start, End, Pack>

// Sort elements in Pack using Sorter
pack_sort<Sorter, Pack>
```

A `Filter` is a `template<class> class` that contains a `::value`, an example would be `std::is_integral`. 

A `Transform` is a `template<class> class` that transforms the template argument, here's an example:
```cpp
template<class Type>
using transform_to_self = Type;
```

A `Sorter` is a `template<class, class> class` that contains a `::value` for sorting the type, here's an example that sorts on size:
```cpp
template<class A, class B>
struct sort_on_size {
    constexpr static bool value = sizeof(A) < sizeof(B);
};
```

This utility header also contains a couple `Filter`, `Sorter`, and `Transform` utilities:
```cpp
// Combine Filters using logical and
filter_and<Filters...>

// Combine Filters using logical or
filter_or<Filters...>

// Invert Filter using logical not
filter_invert<Filter>

// Reverse the Sorter
sorter_reverse<Sorter>

// Only apply Transform if Filter matches
conditional_transform<Filter, Transform>
```

Here are a bunch of examples:

```cpp

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

static_assert(std::same_as<pack_first_indices_t<pack<int, double, int, float>>, std::index_sequence<0, 1, 3>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, double, char, float>>, std::index_sequence<0, 1, 2, 3>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, double, int, double>>, std::index_sequence<0, 1>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, int, double, double>>, std::index_sequence<0, 2>>);
static_assert(std::same_as<pack_first_indices_t<pack<int, int, int, int>>, std::index_sequence<0>>);
static_assert(std::same_as<pack_first_indices_t<pack<>>, std::index_sequence<>>);

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
```
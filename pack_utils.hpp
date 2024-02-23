
// ------------------------------------------------

#pragma once

// ------------------------------------------------

#include <cstddef>
#include <concepts>
#include <utility>

// ------------------------------------------------

namespace kaixo {

    // ------------------------------------------------

    constexpr std::size_t npos = static_cast<std::size_t>(-1);

    // ------------------------------------------------

    // Combine filters using logical and
    template<template<class> class ...Filter>
    struct filter_and {
        template<class Ty>
        struct type {
            constexpr static bool value = (static_cast<bool>(Filter<Ty>::value) && ...);
        };
    };

    // ------------------------------------------------

    // Combine filters using logical or
    template<template<class> class ...Filter>
    struct filter_or {
        template<class Ty>
        struct type {
            constexpr static bool value = (static_cast<bool>(Filter<Ty>::value) || ...);
        };
    };

    // ------------------------------------------------

    // Combine filters using logical or
    template<template<class> class Filter>
    struct filter_invert {
        template<class Ty>
        struct type {
            constexpr static bool value = !static_cast<bool>(Filter<Ty>::value);
        };
    };

    // ------------------------------------------------

    template<class ...Tys>
    struct pack;

    // ------------------------------------------------

    template<class Pack>
    struct pack_size;

    template<class ...Tys>
    struct pack_size<pack<Tys...>> {
        constexpr static std::size_t value = sizeof...(Tys);
    };

    // Size of Pack
    template<class Pack>
    constexpr std::size_t pack_size_v = pack_size<Pack>::value;

    // ------------------------------------------------

    template<std::size_t I, class Ty>
    struct pack_element;

    template<class Ty, class ...Tys>
    struct pack_element<0, pack<Ty, Tys...>> {
        using type = Ty;
    };

    template<std::size_t I, class Ty, class ...Tys>
    struct pack_element<I, pack<Ty, Tys...>> : pack_element<I - 1, pack<Tys...>> {};

    // Get the Ith element in Pack
    template<std::size_t I, class Pack>
    using pack_element_t = typename pack_element<I, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_contains {
        constexpr static bool value = false;
    };

    template<class Type, class ...Tys>
    struct pack_contains<Type, pack<Type, Tys...>> {
        constexpr static bool value = true;
    };

    template<class Type, class Ty, class ...Tys>
    struct pack_contains<Type, pack<Ty, Tys...>> : pack_contains<Type, pack<Tys...>> {};

    // Pack contains Type
    template<class Type, class Pack>
    constexpr bool pack_contains_v = pack_contains<Type, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_contains_all;

    template<class ...Types, class ...Tys>
    struct pack_contains_all<pack<Types...>, pack<Tys...>> {
        constexpr static bool value = (pack_contains<Types, pack<Tys...>>::value && ...);
    };

    // Pack contains all Types
    template<class Types, class Pack>
    constexpr bool pack_contains_all_v = pack_contains_all<Types, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_contains_any;

    template<class ...Types, class ...Tys>
    struct pack_contains_any<pack<Types...>, pack<Tys...>> {
        constexpr static bool value = (pack_contains<Types, pack<Tys...>>::value || ...);
    };

    // Pack contains any in Find
    template<class Types, class Pack>
    constexpr bool pack_contains_any_v = pack_contains_any<Types, Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_find;

    template<template<class> class Filter, class ...Tys>
    struct pack_find<Filter, pack<Tys...>> {
        constexpr static bool value = (Filter<Tys>::value || ...);
    };

    // Find match for Filter in Pack
    template<template<class> class Filter, class Pack>
    constexpr bool pack_find_v = pack_find<Filter, Pack>::value;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_count;

    template<class Type, class ...Tys>
    struct pack_count<Type, pack<Type, Tys...>> {
        constexpr static std::size_t value = 1 + pack_count<Type, pack<Tys...>>::value;
    };

    template<class Type, class Ty, class ...Tys>
    struct pack_count<Type, pack<Ty, Tys...>> {
        constexpr static std::size_t value = pack_count<Type, pack<Tys...>>::value;
    };

    template<class Type>
    struct pack_count<Type, pack<>> {
        constexpr static std::size_t value = 0;
    };

    // Number of occurences of Type in Pack
    template<class Type, class Pack>
    constexpr std::size_t pack_count_v = pack_count<Type, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_count_all;

    template<class ...Types, class ...Tys>
    struct pack_count_all<pack<Types...>, pack<Tys...>> {
        constexpr static std::size_t value = (pack_count<Types, pack<Tys...>>::value + ... + 0);
    };

    // Sum of the number of occurences of all Types in Pack
    template<class Types, class Pack>
    constexpr std::size_t pack_count_all_v = pack_count_all<Types, Pack>::value;

    // ------------------------------------------------

    template<class Pack>
    struct pack_count_unique;

    template<class ...Tys>
    struct pack_count_unique<pack<Tys...>> {
        template<class T>
        constexpr static double _unq_cnt = 1.0 / (std::same_as<T, Tys> +...);

        constexpr static std::size_t value = static_cast<std::size_t>((_unq_cnt<Tys> +... + 0) + 0.5);
    };

    // Count unique elements in Pack
    template<class Pack>
    constexpr std::size_t pack_count_unique_v = pack_count_unique<Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_count_filter;

    template<template<class> class Filter, class ...Tys>
    struct pack_count_filter<Filter, pack<Tys...>> {
        constexpr static std::size_t value = (static_cast<bool>(Filter<Tys>::value) + ... + 0);
    };

    // Count number of matched for Filter in Pack
    template<template<class> class Filter, class Pack>
    constexpr std::size_t pack_count_filter_v = pack_count_filter<Filter, Pack>::value;

    // ------------------------------------------------

    template<class Type, std::size_t I, class Pack>
    struct pack_nth_index_of;

    template<class Type, std::size_t I, class Ty, class ...Tys>
    struct pack_nth_index_of<Type, I, pack<Ty, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_of<Type, I, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<class Type, std::size_t I, class ...Tys>
    struct pack_nth_index_of<Type, I, pack<Type, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_of<Type, I - 1, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<class Type, class ...Tys>
    struct pack_nth_index_of<Type, 0, pack<Type, Tys...>> {
        constexpr static std::size_t value = 0;
    };

    template<class Type, std::size_t I>
    struct pack_nth_index_of<Type, I, pack<>> {
        constexpr static bool _found = false;
        constexpr static std::size_t value = npos;
    };

    // Index of the Ith occurance of Type in Pack
    template<class Type, std::size_t I, class Pack>
    constexpr std::size_t pack_nth_index_of_v = pack_nth_index_of<Type, I, Pack>::value;

    // ------------------------------------------------

    template<class Types, std::size_t I, class Pack>
    struct pack_nth_index_of_any;

    template<class ...Types, std::size_t I, class Ty, class ...Tys>
        requires (!(std::same_as<Types, Ty> || ...))
    struct pack_nth_index_of_any<pack<Types...>, I, pack<Ty, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_of_any<pack<Types...>, I, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<class ...Types, std::size_t I, class Ty, class ...Tys>
        requires (std::same_as<Types, Ty> || ...)
    struct pack_nth_index_of_any<pack<Types...>, I, pack<Ty, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_of_any<pack<Types...>, I - 1, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<class ...Types, class Ty, class ...Tys>
        requires (std::same_as<Types, Ty> || ...)
    struct pack_nth_index_of_any<pack<Types...>, 0, pack<Ty, Tys...>> {
        constexpr static std::size_t value = 0;
    };

    template<class Types, std::size_t I>
    struct pack_nth_index_of_any<Types, I, pack<>> {
        constexpr static bool _found = false;
        constexpr static std::size_t value = npos;
    };

    // Index of the Ith occurance of any of Types in Pack
    template<class Types, std::size_t I, class Pack>
    constexpr std::size_t pack_nth_index_of_any_v = pack_nth_index_of_any<Types, I, Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, std::size_t I, class Pack>
    struct pack_nth_index_filter;

    template<template<class> class Filter, std::size_t I, class Ty, class ...Tys>
        requires (!Filter<Ty>::value)
    struct pack_nth_index_filter<Filter, I, pack<Ty, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_filter<Filter, I, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<template<class> class Filter, std::size_t I, class Ty, class ...Tys>
        requires (Filter<Ty>::value)
    struct pack_nth_index_filter<Filter, I, pack<Ty, Tys...>> {
        constexpr static std::size_t _last = pack_nth_index_filter<Filter, I - 1, pack<Tys...>>::value;
        constexpr static std::size_t value = _last == npos ? npos : _last + 1;
    };

    template<template<class> class Filter, class Ty, class ...Tys>
        requires (Filter<Ty>::value)
    struct pack_nth_index_filter<Filter, 0, pack<Ty, Tys...>> {
        constexpr static std::size_t value = 0;
    };

    template<template<class> class Filter, std::size_t I>
    struct pack_nth_index_filter<Filter, I, pack<>> {
        constexpr static bool _found = false;
        constexpr static std::size_t value = npos;
    };

    // Index of the Ith match of Filter in Pack
    template<template<class> class Filter, std::size_t I, class Pack>
    constexpr std::size_t pack_nth_index_filter_v = pack_nth_index_filter<Filter, I, Pack>::value;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_index_of {
        constexpr static std::size_t value = pack_nth_index_of<Type, 0, Pack>::value;
    };

    // Index of the first occurance of Type in Pack
    template<class Type, class Pack>
    constexpr std::size_t pack_index_of_v = pack_index_of<Type, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_index_of_any {
        constexpr static std::size_t value = pack_nth_index_of_any<Types, 0, Pack>::value;
    };

    // Index of the first occurance of any of Types in Pack
    template<class Types, class Pack>
    constexpr std::size_t pack_index_of_any_v = pack_index_of_any<Types, Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_index_filter {
        constexpr static std::size_t value = pack_nth_index_filter<Filter, 0, Pack>::value;
    };

    // Index of the first match of Filter in Pack
    template<template<class> class Filter, class Pack>
    constexpr std::size_t pack_index_filter_v = pack_index_filter<Filter, Pack>::value;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_first_index_of {
        constexpr static std::size_t value = pack_nth_index_of<Type, 0, Pack>::value;
    };

    // Index of the first occurance of Type in Pack
    template<class Type, class Pack>
    constexpr std::size_t pack_first_index_of_v = pack_first_index_of<Type, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_first_index_of_any {
        constexpr static std::size_t value = pack_nth_index_of_any<Types, 0, Pack>::value;
    };

    // Index of the first occurance of any of Types in Pack
    template<class Types, class Pack>
    constexpr std::size_t pack_first_index_of_any_v = pack_first_index_of_any<Types, Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_first_index_filter {
        constexpr static std::size_t value = pack_nth_index_filter<Filter, 0, Pack>::value;
    };

    // Index of the first match of Filter in Pack
    template<template<class> class Filter, class Pack>
    constexpr std::size_t pack_first_index_filter_v = pack_first_index_filter<Filter, Pack>::value;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_last_index_of {
        constexpr static std::size_t value = pack_nth_index_of<Type, pack_count<Type, Pack>::value - 1, Pack>::value;
    };

    // Index of the last occurance of Type in Pack
    template<class Type, class Pack>
    constexpr std::size_t pack_last_index_of_v = pack_last_index_of<Type, Pack>::value;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_last_index_of_any {
        constexpr static std::size_t value = pack_nth_index_of_any<Types, pack_count_all<Types, Pack>::value - 1, Pack>::value;
    };

    // Index of the last occurance of any of Types in Pack
    template<class Types, class Pack>
    constexpr std::size_t pack_last_index_of_any_v = pack_last_index_of_any<Types, Pack>::value;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_last_index_filter {
        constexpr static std::size_t value = pack_nth_index_filter<Filter, pack_count_filter<Filter, Pack>::value - 1, Pack>::value;
    };

    // Index of the last match of Filter in Pack
    template<template<class> class Filter, class Pack>
    constexpr std::size_t pack_last_index_filter_v = pack_last_index_filter<Filter, Pack>::value;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_indices_of {
        template<class>
        struct _impl;

        template<std::size_t ...Is>
        struct _impl<std::index_sequence<Is...>> {
            using type = std::index_sequence<pack_nth_index_of<Type, Is, Pack>::value...>;
        };

        using type = typename _impl<std::make_index_sequence<pack_count<Type, Pack>::value>>::type;
    };

    // All indices of Type in Pack
    template<class Type, class Pack>
    using pack_indices_of_t = pack_indices_of<Type, Pack>::type;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_indices_of_all {
        template<class>
        struct _impl;

        template<std::size_t ...Is>
        struct _impl<std::index_sequence<Is...>> {
            using type = std::index_sequence<pack_nth_index_of_any<Types, Is, Pack>::value...>;
        };

        using type = typename _impl<std::make_index_sequence<pack_count_all<Types, Pack>::value>>::type;
    };

    // All indices of Type in Pack
    template<class Types, class Pack>
    using pack_indices_of_all_t = pack_indices_of_all<Types, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_indices_filter {
        template<class>
        struct _impl;

        template<std::size_t ...Is>
        struct _impl<std::index_sequence<Is...>> {
            using type = std::index_sequence<pack_nth_index_filter<Filter, Is, Pack>::value...>;
        };

        using type = typename _impl<std::make_index_sequence<pack_count_filter<Filter, Pack>::value>>::type;
    };

    // All indices of matches of Filter in Pack
    template<template<class> class Filter, class Pack>
    using pack_indices_filter_t = pack_indices_filter<Filter, Pack>::type;

    // ------------------------------------------------

    namespace detail {
        template<class Nums, std::size_t Index = 0, std::size_t ...Result>
        struct remove_number_if_not_same_as_index;

        template<std::size_t Num, std::size_t ...Nums, std::size_t Index, std::size_t ...Result>
        struct remove_number_if_not_same_as_index<std::index_sequence<Num, Nums...>, Index, Result...> {
            using type = typename remove_number_if_not_same_as_index<
                std::index_sequence<Nums...>, Index + 1, Result...>::type;
        };

        template<std::size_t ...Nums, std::size_t Index, std::size_t ...Result>
        struct remove_number_if_not_same_as_index<std::index_sequence<Index, Nums...>, Index, Result...> {
            using type = typename remove_number_if_not_same_as_index<
                std::index_sequence<Nums...>, Index + 1, Result..., Index>::type;
        };

        template<std::size_t Index, std::size_t ...Result>
        struct remove_number_if_not_same_as_index<std::index_sequence<>, Index, Result...> {
            using type = std::index_sequence<Result...>;
        };
    }

    template<class Pack>
    struct pack_first_indices {
        template<class>
        struct _impl;

        template<std::size_t ...Is>
        struct _impl<std::index_sequence<Is...>> {
            using _first_indices = std::index_sequence<pack_first_index_of<typename pack_element<Is, Pack>::type, Pack>::value...>;
            using type = typename detail::remove_number_if_not_same_as_index<_first_indices>::type;
        };

        using type = typename _impl<std::make_index_sequence<pack_size<Pack>::value>>::type;
    };

    // First indices of all elements in Pack
    template<class Pack>
    using pack_first_indices_t = typename pack_first_indices<Pack>::type;

    // ------------------------------------------------

    template<class Indices, class Pack>
    struct pack_at_indices;

    template<std::size_t ...Is, class Pack>
    struct pack_at_indices<std::index_sequence<Is...>, Pack> {
        using type = pack<typename pack_element<Is, Pack>::type...>;
    };

    // Only keep all Indices in Pack
    template<class Indices, class Pack>
    using pack_at_indices_t = typename pack_at_indices<Indices, Pack>::type;

    // ------------------------------------------------

    template<class Pack>
    struct pack_unique {
        using type = typename pack_at_indices<typename pack_first_indices<Pack>::type, Pack>::type;
    };

    // Only keep unique elements in Pack
    template<class Pack>
    using pack_unique_t = typename pack_unique<Pack>::type;

    // ------------------------------------------------

    template<std::size_t I, class Pack>
    struct pack_drop;

    template<std::size_t I, class Ty, class ...Tys>
    struct pack_drop<I, pack<Ty, Tys...>> {
        using type = typename pack_drop<I - 1, pack<Tys...>>::type;
    };

    template<class Pack>
    struct pack_drop<0, Pack> {
        using type = Pack;
    };

    // Drop the first I elements of Pack
    template<std::size_t I, class Pack>
    using pack_drop_t = typename pack_drop<I, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_drop_while;

    template<template<class> class Filter, class Ty, class ...Tys>
        requires (Filter<Ty>::value)
    struct pack_drop_while<Filter, pack<Ty, Tys...>> {
        using type = typename pack_drop_while<Filter, pack<Tys...>>::type;
    };

    template<template<class> class Filter, class Ty, class ...Tys>
        requires (!Filter<Ty>::value)
    struct pack_drop_while<Filter, pack<Ty, Tys...>> {
        using type = pack<Ty, Tys...>;
    };

    template<template<class> class Filter>
    struct pack_drop_while<Filter, pack<>> {
        using type = pack<>;
    };

    // Drop elements from Pack while Filter matches
    template<template<class> class Filter, class Pack>
    using pack_drop_while_t = typename pack_drop_while<Filter, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_drop_until;

    template<template<class> class Filter, class Ty, class ...Tys>
        requires (!Filter<Ty>::value)
    struct pack_drop_until<Filter, pack<Ty, Tys...>> {
        using type = typename pack_drop_until<Filter, pack<Tys...>>::type;
    };

    template<template<class> class Filter, class Ty, class ...Tys>
        requires (Filter<Ty>::value)
    struct pack_drop_until<Filter, pack<Ty, Tys...>> {
        using type = pack<Ty, Tys...>;
    };

    template<template<class> class Filter>
    struct pack_drop_until<Filter, pack<>> {
        using type = pack<>;
    };

    // Drop elements from Pack until Filter matches
    template<template<class> class Filter, class Pack>
    using pack_drop_until_t = typename pack_drop_until<Filter, Pack>::type;

    // ------------------------------------------------

    template<std::size_t I, class Pack>
    struct pack_take {
        template<class>
        struct _impl;

        template<std::size_t ...Is>
        struct _impl<std::index_sequence<Is...>> {
            using type = pack<typename pack_element<Is, Pack>::type...>;
        };

        using type = typename _impl<std::make_index_sequence<I>>::type;
    };

    // Take the first I elements of Pack
    template<std::size_t I, class Pack>
    using pack_take_t = typename pack_take<I, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_take_while {
        template<std::size_t Take>
        struct _impl {
            using type = typename pack_take<Take, Pack>::type;
        };

        template<>
        struct _impl<npos> {
            using type = Pack;
        };

        constexpr static std::size_t _first_non_match = pack_first_index_filter<filter_invert<Filter>::type, Pack>::value;
        using type = typename _impl<_first_non_match>::type;
    };

    // Take the first I elements of Pack
    template<template<class> class Filter, class Pack>
    using pack_take_while_t = typename pack_take_while<Filter, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_take_until {
        template<std::size_t Take>
        struct _impl {
            using type = typename pack_take<Take, Pack>::type;
        };

        template<>
        struct _impl<npos> {
            using type = Pack;
        };

        constexpr static std::size_t _first_non_match = pack_first_index_filter<Filter, Pack>::value;
        using type = typename _impl<_first_non_match>::type;
    };

    // Take the first I elements of Pack
    template<template<class> class Filter, class Pack>
    using pack_take_until_t = typename pack_take_until<Filter, Pack>::type;

    // ------------------------------------------------

    template<class ...Packs>
    struct pack_concat;

    template<class ...As, class ...Bs, class ...Packs>
    struct pack_concat<pack<As...>, pack<Bs...>, Packs...> {
        using type = typename pack_concat<pack<As..., Bs...>, Packs...>::type;
    };

    template<class Pack>
    struct pack_concat<Pack> {
        using type = Pack;
    };

    template<>
    struct pack_concat<> {
        using type = pack<>;
    };

    // Concat all types in all Packs to single pack
    template<class ...Packs>
    using pack_concat_t = typename pack_concat<Packs...>::type;

    // ------------------------------------------------

    template<std::size_t I, class Pack>
    struct pack_erase {
        using type = typename pack_concat<typename pack_take<I, Pack>::type, typename pack_drop<I + 1, Pack>::type>::type;
    };

    // Erase index I from Pack
    template<std::size_t I, class Pack>
    using pack_erase_t = typename pack_erase<I, Pack>::type;

    // ------------------------------------------------

    namespace detail {
        template<class Indices, class Pack, class Result = pack<>, std::size_t Index = 0>
        struct pack_erase_all;

        template<std::size_t ...Is, class Ty, class ...Tys, class ...Result, std::size_t Index>
            requires ((Is != Index) && ...) // Index not in erase
        struct pack_erase_all<std::index_sequence<Is...>, pack<Ty, Tys...>, pack<Result...>, Index> {
            using type = typename pack_erase_all<std::index_sequence<Is...>, pack<Tys...>, pack<Result..., Ty>, Index + 1>::type;
        };

        template<std::size_t ...Is, class Ty, class ...Tys, class Result, std::size_t Index>
            requires ((Is == Index) || ...) // Index in erase
        struct pack_erase_all<std::index_sequence<Is...>, pack<Ty, Tys...>, Result, Index> {
            using type = typename pack_erase_all<std::index_sequence<Is...>, pack<Tys...>, Result, Index + 1>::type;
        };

        template<class Indices, class Result, std::size_t Index>
        struct pack_erase_all<Indices, pack<>, Result, Index> {
            using type = Result;
        };
    }

    template<class Indices, class Pack>
    struct pack_erase_all {
        using type = typename detail::pack_erase_all<Indices, Pack>::type;
    };

    // Erase all Indices from Pack
    template<class Indices, class Pack>
    using pack_erase_all_t = typename pack_erase_all<Indices, Pack>::type;

    // ------------------------------------------------

    template<class Type, std::size_t I, class Pack>
    struct pack_insert {
        using type = typename pack_concat<typename pack_take<I, Pack>::type, pack<Type>, typename pack_drop<I, Pack>::type>::type;
    };

    // Insert Type in Pack at index I
    template<class Type, std::size_t I, class Pack>
    using pack_insert_t = typename pack_insert<Type, I, Pack>::type;

    // ------------------------------------------------

    template<class Types, std::size_t I, class Pack>
    struct pack_insert_all {
        using type = typename pack_concat<typename pack_take<I, Pack>::type, Types, typename pack_drop<I, Pack>::type>::type;
    };

    // Insert all Types in Pack at index I
    template<class Types, std::size_t I, class Pack>
    using pack_insert_all_t = typename pack_insert_all<Types, I, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_filter {
        using type = typename pack_at_indices<typename pack_indices_filter<Filter, Pack>::type, Pack>::type;
    };

    // Only keep matches of Filter in Pack
    template<template<class> class Filter, class Pack>
    using pack_filter_t = typename pack_filter<Filter, Pack>::type;

    // ------------------------------------------------

    template<template<class> class Filter, class Pack>
    struct pack_erase_filter {
        using type = typename pack_at_indices<typename pack_indices_filter<filter_invert<Filter>::type, Pack>::type, Pack>::type;
    };

    // Remove matches of Filter from Pack
    template<template<class> class Filter, class Pack>
    using pack_erase_filter_t = typename pack_erase_filter<Filter, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_remove {
        using type = typename pack_erase_all<typename pack_indices_of<Type, Pack>::type, Pack>::type;
    };

    template<class Type, class Pack>
    using pack_remove_t = typename pack_remove<Type, Pack>::type;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_remove_all {
        using type = typename pack_erase_all<typename pack_indices_of_all<Types, Pack>::type, Pack>::type;
    };

    template<class Types, class Pack>
    using pack_remove_all_t = typename pack_remove_all<Types, Pack>::type;

    // ------------------------------------------------

    namespace detail {
        template<class, class>
        struct pack_reverse;

        template<std::size_t ...Is, class Pack>
        struct pack_reverse<std::index_sequence<Is...>, Pack> {
            using type = pack<typename pack_element<pack_size<Pack>::value - Is - 1ull, Pack>::type...>;
        };
    }

    template<class Pack>
    struct pack_reverse;

    template<class ...Tys>
    struct pack_reverse<pack<Tys...>> {
        using type = typename detail::pack_reverse<std::index_sequence_for<Tys...>, pack<Tys...>>::type;
    };

    // Reverse elements in Pack
    template<class Pack>
    using pack_reverse_t = typename pack_reverse<Pack>::type;

    // ------------------------------------------------

    template<template<class> class Transform, class Pack>
    struct pack_transform;

    template<template<class> class Transform, class ...Tys>
    struct pack_transform<Transform, pack<Tys...>> {
        using type = pack<Transform<Tys>...>;
    };

    // Transform elements in Pack using Transform
    template<template<class> class Transform, class Pack>
    using pack_transform_t = typename pack_transform<Transform, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_append;

    template<class Type, class ...Tys>
    struct pack_append<Type, pack<Tys...>> {
        using type = pack<Tys..., Type>;
    };

    // Append Type to Pack
    template<class Type, class Pack>
    using pack_append_t = typename pack_append<Type, Pack>::type;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_append_all;

    template<class ...Types, class ...Tys>
    struct pack_append_all<pack<Types...>, pack<Tys...>> {
        using type = pack<Tys..., Types...>;
    };

    // Append all Types to Pack
    template<class Types, class Pack>
    using pack_append_all_t = typename pack_append_all<Types, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Pack>
    struct pack_prepend;

    template<class Type, class ...Tys>
    struct pack_prepend<Type, pack<Tys...>> {
        using type = pack<Type, Tys...>;
    };

    // Prepend Type to Pack
    template<class Type, class Pack>
    using pack_prepend_t = typename pack_prepend<Type, Pack>::type;

    // ------------------------------------------------

    template<class Types, class Pack>
    struct pack_prepend_all;

    template<class ...Types, class ...Tys>
    struct pack_prepend_all<pack<Types...>, pack<Tys...>> {
        using type = pack<Types..., Tys...>;
    };

    // Prepend all Types to Pack
    template<class Types, class Pack>
    using pack_prepend_all_t = typename pack_prepend_all<Types, Pack>::type;

    // ------------------------------------------------

    template<class Type, std::size_t I, class Pack>
    struct pack_swap {
        using type = typename pack_insert<Type, I, typename pack_erase<I, Pack>::type>::type;
    };

    // Swap element I of Pack with Type
    template<class Type, std::size_t I, class Pack>
    using pack_swap_t = typename pack_swap<Type, I, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Indices, class Pack>
    struct pack_swap_all;

    template<class Type, std::size_t ...Is, class ...Tys>
    struct pack_swap_all<Type, std::index_sequence<Is...>, pack<Tys...>> {
        template<class>
        struct _impl;

        template<std::size_t N, class Ty>
        using _element = std::conditional_t<((Is == N) || ...), Type, Ty>;

        template<std::size_t ...Ns>
        struct _impl<std::index_sequence<Ns...>> {
            using type = pack<_element<Ns, Tys>...>;
        };

        using type = typename _impl<std::index_sequence_for<Tys...>>::type;
    };

    // Swap all elements at Indices of Pack with Type
    template<class Type, class Indices, class Pack>
    using pack_swap_all_t = typename pack_swap_all<Type, Indices, Pack>::type;

    // ------------------------------------------------

    template<class Type, class Replacement, class Pack>
    struct pack_replace {
        using type = typename pack_swap_all<Replacement, typename pack_indices_of<Type, Pack>::type, Pack>::type;
    };

    // Replace Type in Pack with Replacement
    template<class Type, class Replacement, class Pack>
    using pack_replace_t = typename pack_replace<Type, Replacement, Pack>::type;

    // ------------------------------------------------

    template<class Type, template<class> class Filter, class Pack>
    struct pack_replace_filter;

    template<class Type, template<class> class Filter, class ...Tys>
    struct pack_replace_filter<Type, Filter, pack<Tys...>> {
        using type = pack<std::conditional_t<Filter<Tys>::value, Type, Tys>...>;
    };

    // Replace all matches of Filter in Pack with Type
    template<class Type, template<class> class Filter, class Pack>
    using pack_replace_filter_t = typename pack_replace_filter<Type, Filter, Pack>::type;

    // ------------------------------------------------

    template<std::size_t Start, std::size_t End, class Pack>
    struct pack_sub {
        using type = typename pack_take<End - Start, typename pack_drop<Start, Pack>::type>::type;
    };

    // Keep indices from Start to End in Pack
    template<std::size_t Start, std::size_t End, class Pack>
    using pack_sub_t = typename pack_sub<Start, End, Pack>::type;

    // ------------------------------------------------

    namespace detail {
        template<template<class, class> class Sorter, class Left, class Right>
        struct merge_sort_merge;

        template<template<class, class> class Sorter, class A, class ...As, class B, class ...Bs>
            requires (!Sorter<A, B>::value)
        struct merge_sort_merge<Sorter, pack<A, As...>, pack<B, Bs...>> {
            using _recurse = typename merge_sort_merge<Sorter, pack<As...>, pack<B, Bs...>>::type;
            using type = typename pack_append<A, _recurse>::type;
        };

        template<template<class, class> class Sorter, class A, class ...As, class B, class ...Bs>
            requires (Sorter<A, B>::value)
        struct merge_sort_merge<Sorter, pack<A, As...>, pack<B, Bs...>> {
            using _recurse = typename merge_sort_merge<Sorter, pack<A, As...>, pack<Bs...>>::type;
            using type = typename pack_append<B, _recurse>::type;
        };

        template<template<class, class> class Sorter, class ...As>
        struct merge_sort_merge<Sorter, pack<As...>, pack<>> {
            using type = pack<As...>;
        };

        template<template<class, class> class Sorter, class ...Bs>
        struct merge_sort_merge<Sorter, pack<>, pack<Bs...>> {
            using type = pack<Bs...>;
        };

        template<template<class, class> class Sorter, class Pack>
        struct merge_sort {
            constexpr static std::size_t _mid = pack_size<Pack>::value / 2;
            using _left = typename merge_sort<Sorter, typename pack_take<_mid, Pack>::type>::type;
            using _right = typename merge_sort<Sorter, typename pack_drop<_mid, Pack>::type>::type;
            using type = typename merge_sort_merge<Sorter, _left, _right>::type;
        };

        template<template<class, class> class Sorter, class Ty>
        struct merge_sort<Sorter, pack<Ty>> {
            using type = pack<Ty>;
        };

        template<template<class, class> class Sorter>
        struct merge_sort<Sorter, pack<>> {
            using type = pack<>;
        };
    }

    template<template<class, class> class Sorter, class Pack>
    struct pack_sort {
        using type = typename detail::merge_sort<Sorter, Pack>::type;
    };

    // Sort elements in Pack using Sorter
    template<template<class, class> class Sorter, class Pack>
    using pack_sort_t = typename pack_sort<Sorter, Pack>::type;

    // ------------------------------------------------

}

// ------------------------------------------------

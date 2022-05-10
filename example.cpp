#include "pack_utils.hpp"

int main() {

	constexpr auto sum = [](auto ...values) { return (values + ...); };
	constexpr auto even = [](auto value) { return value % 2 == 0; };
	constexpr auto to_array = [](auto ...values) { return std::array{ values... }; };

	constexpr auto res = kaixo::to_pack<1, 3, 5, 7, 9>::for_each<sum>;
	constexpr auto arr = kaixo::to_pack<1, 4, 5, 6, 8, 9>::filter<even>::for_each<to_array>;

	return 0;
}
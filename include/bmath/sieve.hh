#ifndef BMATH_SIEVE_HH
#define BMATH_SIEVE_HH

#include <bitset>
#include <cstdint>
#include <format>
#include <stdexcept>

namespace bmath {

template <typename Derived, size_t Limit>
  requires(Limit > 0)
class Sieve {
 public:
  constexpr explicit Sieve() noexcept { static_cast<Derived *>(this)->build(); }

 protected:
  std::bitset<Limit + 1> sieve;
};

template <size_t Limit>
  requires(Limit > 0)
class Eratosthenes : public Sieve<Eratosthenes<Limit>, Limit> {
 public:
  constexpr void build() noexcept {
    this->sieve.set();
    this->sieve[0] = false;
    this->sieve[1] = false;

    for (size_t x = 2; x * x <= Limit; ++x) {
      if (!this->sieve[x]) {
        continue;
      }

      for (size_t current = x + x; current <= Limit; current += x) {
        this->sieve[current] = false;
      }
    }
  }

  [[nodiscard]] constexpr bool operator[](size_t const number) const {
    if consteval {
      // TODO: does/can this run at compile time?
      if (number > Limit) {
        throw std::out_of_range(
            std::format("cannot determine primality of {} > size of sieve {}",
                        number, Limit));
      }
    } else {
      if (number > Limit) {
        throw std::out_of_range(
            std::format("cannot determine primality of {} > size of sieve {}",
                        number, Limit));
      }
    }

    return this->sieve[number];
  };
};

}  // namespace bmath

#endif

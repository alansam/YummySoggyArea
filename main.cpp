//
//  Created by Alan Sampson on 8/27/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/utility/bitset/bitset
//

#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>
#include <string>
#include <bitset>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <climits>

using namespace std::string_literals;

//  MARK: - Definitions.
template<typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & vec) {
  for (auto & el : vec) {
      os << el << ' ';
  }
  return os;
}

//  MARK: Struct S
#define B 3
#define C 12
#define D 4
struct S {
  uint32_t b : B;
  bool       : 1;  //  filler ~ 1 bit.
  uint32_t c : C;
  uint64_t   : 0;  //  filler ~ next int
  bool       : 8;  //  filler ~ next byte
  uint32_t d : D;
};

//  MARK: Class junk
class junk {
private:
  uint64_t bigval_;
  std::string name_;
  junk() = delete;  //  no default constructor
public:
  junk(std::string name, uint64_t bigval)
    : name_(name), bigval_(bigval) {
    return;
  }
  virtual ~junk() {
    name_.clear();
    bigval_ = 0;
    return;
  }
  uint64_t const get_bigval() const {
    return bigval_;
  }

  std::string const & get_name() const {
    return name_;
  }
};

//  MARK: Enumeration E
enum E {
  One = 1, Two, Three, Ten = 10, Eleven, Onehundred = 100,
  LoVal = 0x00, HiVal = 0xff,
  SP = ' ', HT = '\t', NL = '\n', CR = '\r', FF = '\f',
};
//  MARK: Enumeration Alpha
enum Alpha {
  Au = 'A', Bu, Cu, Du, Eu, Fu, Gu, Hu, Iu, Ju, Ku, Lu, Mu,
  Nu,       Ou, Pu, Qu, Ru, Su, Tu, Uu, Vu, Wu, Xu, Yu, Zu,
  Al = 'a', Bl, Cl, Dl, El, Fl, Gl, Hl, Il, Jl, Kl, Ll, Ml,
  Nl,       Ol, Pl, Ql, Rl, Sl, Tl, Ul, Vl, Wl, Xl, Yl, Zl,
};

//  MARK: Union U
union U {
  uint8_t  bytes[sizeof(uint64_t)];
  uint64_t ul;
  uint32_t ui[sizeof(uint64_t) / sizeof(uint32_t)];
  uint16_t us[sizeof(uint64_t) / sizeof(uint16_t)];
};

//  MARK: Prototypes
void S_sample(void);
void junk_sample(void);
void E_sample(void);
void U_sample(void);
void cppreference_sample(void);
template <class T>
void my_prdump(T const & s, std::string const & title);

//  MARK: - Implementation
/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
  std::vector<std::string> vec = {
    "Hello", "from",
    "GCC", __VERSION__,
    "\n          ",
    "C++", std::to_string(__cplusplus),
    "!",
    "\nCF.BitFiddling01"
  };
  std::cout << vec << std::endl;

  S_sample();
  junk_sample();
  E_sample();
  U_sample();
  cppreference_sample();

  return EXIT_SUCCESS;
}

/*
 *  MARK: S_sample()
 */
void S_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  //  set up the struct bin-3, bin-12, bin-4
  S s { .b = 0b101, .c = 0b111011101110, .d = 0b1011, };

  //  create bitsets from the struct parts
  std::bitset<B> bB(s.b);
  std::bitset<C> bC(s.c);
  std::bitset<D> bD(s.d);

  //  display the struct contents
  std::cout << std::setw(6) << s.b << ' '
            << std::setw(2) << std::setfill('0') << std::hex << s.b << ' '
            << std::setw(8) << std::setfill(' ') << bB
            << " : "
            << std::setw(4) << std::setfill('0') << std::hex << s.c << ' '
            << std::setw(16) << std::setfill(' ') << bC
            << " : "
            << std::setw(4) << std::setfill('0') << std::hex << s.d << ' '
            << std::setw(8) << std::setfill(' ') << bD
            << std::endl;

  //  do a print dump of the structure
  my_prdump(s, "Struct \"S\""s);

  return;
}

/*
 *  MARK: E_sample()
 */
void E_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  std::pair<E, std::string const &> e_things[] {
    { Onehundred, "Onehundred"s, },
    { LoVal, "LoVal"s }, { HiVal, "HiVal"s },
    { SP, "SP"s }, { HT, "HT"s }, { NL, "NL"s }, { CR, "CR"s, }, { FF, "FF"s, },
  };
  for (auto e : e_things) {
    std::cout << e.second << ": "
              << std::dec << std::setfill(' ') << std::setw(4)
              << e.first
              << " ["
              << std::hex << std::setfill('0') << std::setw(sizeof(E) * sizeof(uint8_t) * 2)
              << e.first
              << "]"
              << std::endl;
    my_prdump(e.first, "Enumeration \'e.first\'"s);
    my_prdump(e.second, "std::string & \'e.second\'"s);
    my_prdump(e, "std::pair<E,std::string const &> \'e\'"s);
  }

  std::vector<std::tuple<Alpha, std::string>> Alpha_things {
    { Uu, "Uu"s, }, { Ml, "Ml"s, }, { Al, "Al"s }, { Zu, "Zu"s },
  };
  for (auto a : Alpha_things) {
    Alpha aA = std::get<0>(a);
    std::string aStr = std::get<1>(a);
    std::cout << "std::vector: "s
              << aA
              << ' '
              << aStr
              << std::endl;
    my_prdump(aA, "Enumeration \'Alpha\'"s);
    my_prdump(aStr, "std::string \'aStr\'"s);
    my_prdump(a, "std::tuple<Alpha, std::string>");
  }
  my_prdump(Alpha_things,
            "std::vector<std::tuple<Alpha, std::string>>"s);

  return;
}

void U_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  U u { .ul = 0xf010002080400080LL, };
  std::cout << "uint64_t:"s << std::endl;
  std::cout << std::dec  << std::setw(22) << std::setfill(' ')
            << u.ul
            << ' '
            << std::hex << std::setw(16) << std::setfill('0')
            << u.ul
            << std::endl;
  std::putchar('\n');

  std::cout << "uint32_t:"s << std::endl;
  for (auto ii : u.ui) {
    std::cout << std::dec << std::setw(22) << std::setfill(' ')
              << ii
              << ' '
              << ""s.append(8, ' ')
              << std::hex << std::setw(8) << std::setfill('0')
              << ii
              << std::endl;
  }
  std::putchar('\n');

  std::cout << "uint16_t:"s << std::endl;
  for (auto ss : u.us) {
    std::cout << std::dec << std::setw(22) << std::setfill(' ')
              << ss
              << ' '
              << ""s.append(12, ' ')
              << std::hex << std::setw(4) << std::setfill('0')
              << ss
              << std::endl;
  }
  std::putchar('\n');

  std::cout << "uint8_t:"s << std::endl;
  for (auto bb : u.bytes) {
    std::cout << std::dec << std::setw(22) << std::setfill(' ')
              << static_cast<unsigned>(bb)
              << ' '
              << ""s.append(14, ' ')
              << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<unsigned>(bb)
              << std::endl;
  }
  std::putchar('\n');

  my_prdump(u, "Union \'U\'");

  return;
}
/*
 *  MARK: junk_sample()
 */
void junk_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  junk j("Alan"s, UINT64_MAX);
  std::cout << j.get_name() << ' '
            << std::dec << j.get_bigval()
            << ' '
            << std::hex << j.get_bigval()
            << std::endl;
  my_prdump(j, "Class \"junk\"");

  return;
}
/*
 *  MARK: cppreference_sample()
 *  @see: https://en.cppreference.com/w/cpp/utility/bitset/bitset
 */
void cppreference_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  // empty constructor
  std::bitset<8> b1; // [0,0,0,0,0,0,0,0]

  // unsigned long long constructor
  std::bitset<8> b2(42);          // [0,0,1,0,1,0,1,0]
  std::bitset<70> bl(ULLONG_MAX); // [0,0,0,0,0,0,1,1,1,...,1,1,1] in C++11
  std::bitset<8> bs(0xfff0);      // [1,1,1,1,0,0,0,0]

  // string constructor
  std::string bit_string = "110010";
  std::bitset<8> b3(bit_string);       // [0,0,1,1,0,0,1,0]
  std::bitset<8> b4(bit_string, 2);    // [0,0,0,0,0,0,1,0]
  std::bitset<8> b5(bit_string, 2, 3); // [0,0,0,0,0,0,0,1]

  // string constructor using custom zero/one digits
  std::string alpha_bit_string = "aBaaBBaB";
  std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(),
                    'a', 'B');         // [0,1,0,0,1,1,0,1]

  // char* constructor using custom digits
  std::bitset<8> b7("XXXXYYYY", 8, 'X', 'Y'); // [0,0,0,0,1,1,1,1]

  std::cout << b1 << '\n' << b2 << '\n' << bl << '\n' << bs << '\n'
            << b3 << '\n' << b4 << '\n' << b5 << '\n' << b6 << '\n'
            << b7 << '\n';

  return;
}

/*
 *  MARK: my_prdump()
 *  Print a dump (hex, decimal octal, binary & character)
 *  of an instance of a class/struct etc.
 * Copyright (C) Alan Sampson, 202. All rights reserved.
 */
template<class T>
void my_prdump(T const & s, std::string const & title) {

  uint8_t const * sp;
  sp = reinterpret_cast<uint8_t const *>(&s);

  std::cout << '\n' << title
            << " - Size: " << std::dec << std::setw(6)
            << sizeof(T)
            << " ["
            << std::setw(8) << std::setfill('0') << std::hex
            << sizeof(T)
            << "]"
            << std::endl;
  std::cout << "Dump address: "
            << static_cast<void const *>(sp)
            << std::endl;
  std::cout << "Offset: Hex - Dec - Oct - Bin      - Char"
            << std::endl;
  uint16_t offset = 0;
  for (size_t p_ = 0; p_ < sizeof(T); ++p_) {
    uint8_t ibyte = *sp++;
    std::bitset<8> bbyte(ibyte);
    std::cout << "  "
              << std::hex << std::setw(4) << std::setfill('0')
              << offset++ << ": "
              << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<uint16_t>(ibyte)
              << "  - "
              << std::dec << std::setw(3) << std::setfill(' ')
              << static_cast<uint16_t>(ibyte)
              << " - "
              << std::oct << std::setw(3) << std::setfill('0')
              << static_cast<uint16_t>(ibyte)
              << " - "
              << std::hex << std::setw(8) << std::setfill(' ')
              << bbyte
              << " - "
              << std::dec << std::setw(1) << std::setfill(' ')
              << (std::isprint(ibyte) ? static_cast<char>(ibyte) : '.')
              << '\n';
  }
  std::cout << std::endl;

  return;
}

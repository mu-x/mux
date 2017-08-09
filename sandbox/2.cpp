
#define A0() PRINT("A0")
#define A1(X) PRINT("A1")
#define A2(X, Y) PRINT("A2")

#define EXPAND(x) x
#define GET3(A1, A2, A3, ...) A3
#define GET4(A1, A2, A3, A4, ...) A4
#define GET6(A1, A2, A3, A4, A5, A6, ...) A6


#define V(...) M(y, __VA_ARGS__)
#define A(...) GET3(__VA_ARGS__, A2, A1, A0)

#define x(...) y(a __VA_ARGS__,b)


int main()
{
    x 7
    x(,)
    x(,1)

    A();
    A(1);
    A(1, 2);
}

#define _ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define HAS_COMMA(...) _ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define _TRIGGER_PARENTHESIS_(...) ,

#define ISEMPTY(...)                                                    \
_ISEMPTY(                                                               \
          /* test if there is just one argument, eventually an empty    \
             one */                                                     \
          HAS_COMMA(__VA_ARGS__),                                       \
          /* test if _TRIGGER_PARENTHESIS_ together with the argument   \
             adds a comma */                                            \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__),                 \
          /* test if the argument together with a parenthesis           \
             adds a comma */                                            \
          HAS_COMMA(__VA_ARGS__ (/*empty*/)),                           \
          /* test if placing it between _TRIGGER_PARENTHESIS_ and the   \
             parenthesis adds a comma */                                \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/))      \
          )

#define PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _ISEMPTY(_0, _1, _2, _3) HAS_COMMA(PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define _IS_EMPTY_CASE_0001 ,

#define EATER0(...)
#define EATER1(...) ,
#define EATER2(...) (/*empty*/)
#define EATER3(...) (/*empty*/),
#define EATER4(...) EATER1
#define EATER5(...) EATER2
#define MAC0() ()
#define MAC1(x) ()
#define MACV(...) ()
#define MAC2(x,y) whatever
__LINE__ ISEMPTY()
__LINE__ ISEMPTY(/*comment*/)
__LINE__ ISEMPTY(a)
__LINE__ ISEMPTY(a, b)
__LINE__ ISEMPTY(a, b, c)
__LINE__ ISEMPTY(a, b, c, d)
__LINE__ ISEMPTY(a, b, c, d, e)
__LINE__ ISEMPTY((void))
__LINE__ ISEMPTY((void), b, c, d)
__LINE__ ISEMPTY(_TRIGGER_PARENTHESIS_)
__LINE__ ISEMPTY(EATER0)
__LINE__ ISEMPTY(EATER1)
__LINE__ ISEMPTY(EATER2)
__LINE__ ISEMPTY(EATER3)
__LINE__ ISEMPTY(EATER4)
__LINE__ ISEMPTY(MAC0)
__LINE__ ISEMPTY(MAC1)
__LINE__ ISEMPTY(MACV)
/* This one will fail because MAC2 is not called correctly */
//ISEMPTY(MAC2)

#define CONCAT(...) CONCAT2(__VA_ARGS__)
#define CONCAT2(x, y) x##y

#define B(...) CONCAT(Z, ISEMPTY(__VA_ARGS__))(__VA_ARGS__)
#define Z0(...) ZZZ0
#define Z1(...) ZZZ1
B()
B(1)
B(1, 2)

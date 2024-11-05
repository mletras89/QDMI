/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/
#pragma once

#define APPLY(func, arg) func(arg)
#define APPLY_PAREN(func, arg) func arg

#define CAT(a, b) CAT_I(a, b)
#define CAT_I(a, b) a##b

#define TO_SEQ(n) TO_SEQ_I(n)
#define TO_SEQ_I(n) TO_SEQ_##n
#define TO_SEQ_0
#define TO_SEQ_1 ()
#define TO_SEQ_2 () TO_SEQ_1
#define TO_SEQ_3 () TO_SEQ_2
#define TO_SEQ_4 () TO_SEQ_3
#define TO_SEQ_5 () TO_SEQ_4
#define TO_SEQ_6 () TO_SEQ_5
#define TO_SEQ_7 () TO_SEQ_6
#define TO_SEQ_8 () TO_SEQ_7
#define TO_SEQ_9 () TO_SEQ_8

#define HEAD(x) HEAD_I(HEAD_III x)
#define HEAD_I(x) HEAD_II(x)
#define HEAD_II(x, _) x
#define HEAD_III(x) x, NIL

#define TAIL(seq) TAIL_I seq
#define TAIL_I(_)

#define EMPTY(seq) HEAD(CAT(EMPTY_, EMPTY_I seq))
#define EMPTY_I(_) NOT_EMPTY_I
#define EMPTY_NOT_EMPTY_I (0)
#define EMPTY_EMPTY_I (1)

#define SIZE(seq) CAT(SIZE_, SIZE_0 seq)
#define SIZE_0(_) SIZE_1
#define SIZE_1(_) SIZE_2
#define SIZE_2(_) SIZE_3
#define SIZE_3(_) SIZE_4
#define SIZE_4(_) SIZE_5
#define SIZE_5(_) SIZE_6
#define SIZE_6(_) SIZE_7
#define SIZE_7(_) SIZE_8
#define SIZE_8(_) SIZE_9

#define SIZE_SIZE_0 0
#define SIZE_SIZE_1 1
#define SIZE_SIZE_2 2
#define SIZE_SIZE_3 3
#define SIZE_SIZE_4 4
#define SIZE_SIZE_5 5
#define SIZE_SIZE_6 6
#define SIZE_SIZE_7 7
#define SIZE_SIZE_8 8
#define SIZE_SIZE_9 9

#define NTH(i, seq) NTH_I(NTH_##i seq)
#define NTH_I(e) NTH_II(e)
#define NTH_II(e, _) e
#define NTH_0(e) e, NIL
#define NTH_1(_) NTH_0
#define NTH_2(_) NTH_1
#define NTH_3(_) NTH_2
#define NTH_4(_) NTH_3
#define NTH_5(_) NTH_4
#define NTH_6(_) NTH_5
#define NTH_7(_) NTH_6
#define NTH_8(_) NTH_7

#define SUB(a, b) SUB_I(TO_SEQ(a), b)
#define SUB_I(a, b) SIZE(CAT(SUB_, SUB_##b a))
#define SUB_1(_) SUB_0
#define SUB_2(_) SUB_1
#define SUB_3(_) SUB_2
#define SUB_4(_) SUB_3
#define SUB_5(_) SUB_4
#define SUB_6(_) SUB_5
#define SUB_7(_) SUB_6
#define SUB_8(_) SUB_7
#define SUB_9(_) SUB_8
#define SUB_SUB_0
#define SUB_SUB_1
#define SUB_SUB_2
#define SUB_SUB_3
#define SUB_SUB_4
#define SUB_SUB_5
#define SUB_SUB_6
#define SUB_SUB_7
#define SUB_SUB_8
#define SUB_SUB_9

#define NOT(x) CAT(NOT_, x)
#define NOT_0 1
#define NOT_1 0
#define BOOL(x) NOT(EMPTY(TO_SEQ(x)))

#define ITE(bit, t, f) ITE_I(bit, t, f)
#define ITE_I(bit, t, f) CAT(ITE_, bit(t, f))
#define ITE_0(t, f) f
#define ITE_1(t, f) t

#define MIN(a, b) ITE(BOOL(SUB(b, a)), a, b)

#define NTH_MAX(i, seq) NTH_MAX_I(i, SUB(SIZE(seq), 1), seq)
#define NTH_MAX_I(i, n, seq) NTH_MAX_II(MIN(i, n), seq)
#define NTH_MAX_II(i, seq) NTH(i, seq)

#define ITERATE(macro, seq) CONTINUE_1(macro, (seq))

#define ITERATE_1(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_2)(macro, (seq))
#define ITERATE_2(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_3)(macro, (seq))
#define ITERATE_3(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_4)(macro, (seq))
#define ITERATE_4(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_5)(macro, (seq))
#define ITERATE_5(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_6)(macro, (seq))
#define ITERATE_6(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_7)(macro, (seq))
#define ITERATE_7(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_8)(macro, (seq))
#define ITERATE_8(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_9)(macro, (seq))
#define ITERATE_9(macro, seq) ITE(EMPTY(seq), BREAK, CONTINUE_10)(macro, (seq))

#define CONTINUE_1(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_1(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_2(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_2(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_3(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_3(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_4(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_4(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_5(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_5(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_6(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_6(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_7(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_7(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_8(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_8(macro, APPLY_PAREN(TAIL, seq))
#define CONTINUE_9(macro, seq)                                                 \
  APPLY(macro, APPLY_PAREN(HEAD, seq)) ITERATE_9(macro, APPLY_PAREN(TAIL, seq))

#define BREAK(macro, seq)

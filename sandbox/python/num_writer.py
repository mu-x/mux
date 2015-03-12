#!/usr/bin/python

NUMBERS = ['', 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight',
           'Nine', 'Ten', 'Eleven', 'Twelve', 'Thirteen']
NUMBERS += [(NUMBERS[i] + 'teen').replace('tt', 't') for i in range(4, 10)]

TEN_N = ['', '', 'Twenty', 'Thirty']
TEN_N += [(NUMBERS[i] + 'ty').replace('tt', 't') for i in range(4, 10)]

def num_writer(num):
    if num <= 19:
        return NUMBERS[num]
    if num <= 99:
        return TEN_N[num / 10] + ' ' + NUMBERS[num % 10]
    if num <= 999:
        return NUMBERS[num / 100] + ' Hundred ' + num_writer(num % 100)
    if num <= 999999:
        return num_writer(num / 1000) + ' Tauthand ' + num_writer(num % 1000)
    raise Exception('Numbers > 999999 are not supported')

if __name__ == '__main__':
    import sys
    print num_writer(int(sys.argv[1]))

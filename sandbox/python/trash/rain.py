#!/usr/bin/python


def calcWater(land):
    l, r = 0, len(land) - 1
    lm, rm = land[l], land[r]
    water = 0
    while l < r:
        if lm < rm:
            l += 1
            if land[l] < lm:
                water += lm - land[l]
            else:
                lm = land[l]
        else:
            r -= 1
            if land[r] < rm:
                water += rm - land[r]
            else:
                rm = land[r]
    return water


def main():
    def test(land, res):
        water = calcWater(land)
        print land, res, water, res == water
    test([2, 1, 3, 0, 4], 1 + 3)
    test([2, 1, 0, 4], 1 + 2)
    test([2, 1, 0, -2, 8, 1, 2], 1 + 2 + 4 + 1)


if __name__ == '__main__':
    main()

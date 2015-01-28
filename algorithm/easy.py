import sys

def perm(word = 'abc', *args):
    '''Returns all possible permutations of [word]
    '''
    if len(word) == 1: return [word]
    poss = []
    first, rest = word[0], word[1:]
    for each in perm(rest):
        for index in xrange(len(each) + 1):
            poss.append(each[:index] + first + each[index:])
    return poss

def phs(count = 3, *args):
    '''Returns all possible combinations of [count] parentheses
    '''
    count = int(count)
    if count <= 1: return ['()']
    poss = []
    for each in phs(count - 1):
        poss.append('()' + each)
        poss.append('(' + each + ')')
    return poss

def rep(ammount = 10, coins='5,10,25'):
    '''Returns all possible representations of [ammount] in [coins]
    '''
    ammount = int(ammount)
    if not coins: return [{1: ammount}]
    if not isinstance(coins, list):
        coins = sorted([int(c) for c in coins.split(',')], reverse=True)
    first, rest, current = coins[0], coins[1:], 0
    poss = rep(ammount, rest)
    while ammount >= first:
        ammount -= first;
        current += 1
        for each in rep(ammount, rest):
            poss.append(dict(each, **{first: current}))
    return poss

def main():
    '''Executes function with params according to sys.argv
    '''
    function = globals()[sys.argv[1]]
    for each in function(*sys.argv[2:]):
        print repr(each)

if __name__ == '__main__':
    main()


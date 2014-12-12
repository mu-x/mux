#!/usr/bin/python
""" Interface Manager test script.
    
    File: test.py
    Author: Uskov M. V.
    Date: 2013-01-22 
"""
import sys
from subprocess import *


def main():
    print check_output('/sbin/ifconfig | /usr/bin/grep ^[^.]').split('\n')
    
if __name__ == '__main__':
    main()
